#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ARGV 64  // 定义最大参数数量为 64

void err_exit() {
    printf("\033[31m\n NOTE!!!  Please enter 'exit' or 'q' to exit the program.\n\033[0m");
}

void err_command(char *buf) {
    printf("\033[31m NOTE!!!  Command \033[0m'%s'\033[31m not found!\n\033[0m", buf);
    fflush(stdout);
}

// 定义信号处理函数，忽略SIGINT和SIGTSTP信号
void sig_handler(int signo) {
    fflush(stdout);
    if (signo == SIGINT || signo == SIGTSTP) {
        err_exit();
    } else if (signo == SIGQUIT) {
        printf("\n");
    } else {
        printf("Unknown signal received.\n");
    }
    fflush(stdout);
}

// 加载程序
void do_exe(char *buf, char **argv) {
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(buf, argv) < 0) {  // 执行
        	err_command(buf);
            // perror("exec error");
            exit(1);
        }
        exit(1);
    } else {                    // father process
        waitpid(pid, NULL, 0);
    }
}

// 加载程序
void do_pipe(char **argv1, int argc1, char **argv2, int argc2) {
    int fd[2];
    pid_t pid1, pid2;

    int stdout_copy = dup(STDOUT_FILENO);  // 保存 标准输出

    if (pipe(fd) < 0) {
        perror("pipe error");
        return;
    }

    if ((pid1 = fork()) < 0) {  // child 1 error
        perror("fork error");
        return;
    } else if (pid1 == 0) {  // 管道左边命令
        close(fd[0]);    // 关read
        dup2(fd[1], 1);  // 标准输出 重定向 write
        close(fd[1]);    // 关write

        if (execvp(argv1[0], argv1) < 0) {  // 执行
            perror("exec error");
            exit(1);
        }
    } else {  // 管道右边命令

        if ((pid2 = fork()) < 0) {  // child 2 error
            perror("fork error");
            return;
        } else if (pid2 == 0) {  // 管道右边命令
            close(fd[1]);    // 关write
            dup2(fd[0], 0);  // 标准输入 重定向 read
            close(fd[0]);    // 关read
            
            if (execvp(argv2[0], argv2) < 0) {  // 执行
                perror("exec error");
                exit(1);
            }
        } else {           // father fork
            close(fd[0]);  // 关read
            close(fd[1]);  // 关write

            waitpid(pid1, NULL, 0);  // wait fork1 end
            waitpid(pid2, NULL, 0);  // wait fork2 end
        }
    }
    dup2(stdout_copy, STDOUT_FILENO);  // 恢复标准输出的文件描述符
    close(stdout_copy);
}

void do_redirect_input(char *argv[], int argc, char *filename) {
    int fd;
    fd = open(filename, O_RDONLY);    // 打开文件，准备读取文件内容
    if (fd < 0) {
        printf("Failed to open file %s for reading\n", filename);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {              // Child process
        dup2(fd, STDIN_FILENO);  // 标准输入 重定向到 文件
        close(fd);
        if (execvp(argv[0], argv) < 0) {  // 执行
            perror("exec error");
            exit(1);
        }
        printf("Unknown command: %s\n", argv[0]);
        exit(1);
    } else if (pid < 0) {
        printf("Failed to create child process\n");
        return;
    } else {  // Parent process
        wait(NULL);
    }
}

void do_redirect_output(char *argv[], int argc, char *filename) {
    int fd;
    // 打开文件，如果文件不存在，则创建该文件；如果文件存在，则清空文件内容
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        printf("Failed to open file %s for writing\n", filename);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {  // Child process
        dup2(fd, STDOUT_FILENO);  // 标准输出 重定向到 文件
        close(fd);

        if (execvp(argv[0], argv) < 0) {  // 执行
            perror("exec error");
            exit(1);
        }
        printf("Unknown command: %s\n", argv[0]);
        exit(1);
    } else if (pid < 0) {  // Error occurred
        printf("Failed to create child process\n");
        return;
    } else {  // Parent process
        wait(NULL);
    }
}

void do_parse(char *buf) {
    char *argv[MAX_ARGV] = {};
    int argc = 0;
    char *args[MAX_ARGV] = {};  // 用于存储 | > < 后面的命令及其参数
    int args_count = 0;

    // 解析命令行参数
    while (*buf != '\0') {
        if (!isspace(*buf)) {  // first character not ' '
            argv[argc++] = buf;
            while (!isspace(*buf) && *buf != '\0' && *buf != '|' && *buf != '<' && *buf != '>') {
                buf++;
            }
            if (*buf == '\0') break;

            if (*buf == '|') {  // 解析管道符号后面的命令及其参数
                *buf++ = '\0';
                while (isspace(*buf)) buf++;  // 跳过管道符号后面的空格
                while (*buf != '\0' && *buf != '|' && *buf != '<' && *buf != '>') {
                    args[args_count++] = buf;
                    while (!isspace(*buf) && *buf != '\0' && *buf != '|' && *buf != '<' && *buf != '>') {
                        buf++;
                    }
                    if (*buf == '\0') break;
                    if (*buf == '|' || *buf == '<' || *buf == '>') {
                        *buf++ = '\0';
                        break;
                    }
                    *buf++ = '\0';
                }
                do_pipe(argv, argc, args, args_count);  // 执行管道操作
                return;
            } else if (*buf == '>') {
                // 解析输出重定向符号后面的文件名
                *buf++ = '\0';
                while (isspace(*buf)) buf++;  // 跳过输出重定向符号后面的空格
                if (*buf != '\0') {
                    do_redirect_output(argv, argc, buf);
                    return;
                } else {
                    printf("Error: missing destination file after '>'\n");
                    return;
                }
            } else if (*buf == '<') {
                // 解析输入重定向符号后面的文件名
                *buf++ = '\0';
                while (isspace(*buf)) buf++;  // 跳过输入重定向符号后面的空格
                if (*buf != '\0') {
                    do_redirect_input(argv, argc, buf);
                    return;
                } else {
                    printf("Error: missing source file after '<'\n");
                    return;
                }
            } else {
                *buf++ = '\0';
            }
        } else {  // first character is ' '
            buf++;
        }
    }

    if (argc == 0) return;  // 没有输入任何命令
    do_exe(argv[0], argv);  // single command
}

int main(void) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handler;    // 设置信号处理函数为sig_handler
    sigaction(SIGINT, &sa, NULL);   // 注册SIGINT信号处理函数
    sigaction(SIGTSTP, &sa, NULL);  // 注册SIGTSTP信号处理函数
    sigaction(SIGQUIT, &sa, NULL);

    char buf[1024] = {};  // 定义存储用户输入的缓冲区
    int a;

    while (1) {  // 循环读取用户输入
        printf("\033[33mmy shell# \033[0m");
        fflush(stdout);                  // 刷新标准输出缓冲区
        memset(buf, 0x00, sizeof(buf));  // 清空buf缓冲区

        if (read(STDIN_FILENO, buf, sizeof(buf)) == -1) {
            // perror("read");
            fflush(stdout);  // 刷新标准输出缓冲区
            continue;
        }

        if (*buf == 0) {  //  handle: ctrl + d
            err_exit();
            continue;
        }

        char *p = buf + strlen(buf) - 1;  // 获取字符串的最后一个字符位置
        if (*p == '\n') *p = '\0';  // 如果最后一个字符是换行符，则将其替换为字符串结束符

        // 如果输入的是"exit"或"q"，则退出程序
        if (strcmp(buf, "exit") == 0 || strcmp(buf, "q") == 0) break;

        do_parse(buf);  // 对用户输入的命令进行解析并执行
        while (waitpid(-1, NULL, WNOHANG) > 0);  // 循环回收所有已经终止的子进程资源，避免出现僵尸进程
    }
    return 0;
}
