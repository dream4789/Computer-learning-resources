#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX_ARGV 64 // 定义最大参数数量为64

void do_exe(char *buf, char *argv[]) { // 加载程序

    pid_t pid = fork();
    if (pid == 0) {
        int fd_in = STDIN_FILENO;
        int fd_out = STDOUT_FILENO;

        char *p = buf;
        while (*p != '\0') {   // 遍历输入的命令字符串buf
            if (*p == '|') {   // 如果找到管道符号'|'，则执行管道操作
                *p++ = '\0';   // 将'|'处置为'\0'，以便于后续处理
                int fd_pipe[2];
                pipe(fd_pipe); // 创建管道
                pid_t pid2 = fork();
                if (pid2 == 0) { // 子进程中执行管道符号右边的命令
                    close(fd_pipe[1]); // 关闭写端
                    dup2(fd_pipe[0], STDIN_FILENO); // 将管道读端作为标准输入
                    execvp(p, argv + (p - buf) / sizeof(char)); // 在子进程中执行管道符号右边的命令
                    perror("execvp");
                    exit(1);
                } else { // 父进程中执行管道符号左边的命令
                    close(fd_pipe[0]); // 关闭读端
                    dup2(fd_pipe[1], STDOUT_FILENO); // 将管道写端作为标准输出
                    do_exe(buf, argv); // 在父进程中递归调用do_exe函数，执行管道符号左边的命令
                    close(fd_pipe[1]); // 关闭管道写端
                    waitpid(pid2, NULL, 0); //  等待子进程结束
                    return;
                }
            } else if (*p == '>') { //如果找到重定向符号'>'，则执行重定向操作
                *p++ = '\0'; //将'>'处置为'\0'，以便于后续处理
                if (*p == '>') { //如果重定向符号'>>'，则以追加模式打开文件
                    fd_out = open(p + 1, O_CREAT | O_WRONLY | O_APPEND, 0644);
                } else { //否则以覆盖模式打开文件
                    fd_out = open(p, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                }
                dup2(fd_out, STDOUT_FILENO); //将文件描述符fd_out作为标准输出
            } else if (*p == '<') { //如果找到重定向符号'<'，则执行重定向操作
                *p++ = '\0'; //将'<'处置为'\0'，以便于后续处理
                fd_in = open(p, O_RDONLY); //以只读模式打开文件
                dup2(fd_in, STDIN_FILENO); //将文件描述符fd_in作为标准输入
            } else {
                p++; //跳过当前字符
            }
        }
        execvp(buf, argv); //在子进程中执行指定的程序
        perror("execvp"); //打印错误信息
        exit(1); //退出子进程
    } else { //父进程
        waitpid(pid, NULL, 0); //等待子进程结束
    }
}

// 对命令进行解析
void do_parse(char *buf) {
    char *argv[MAX_ARGV] = {}; // 定义指针数组，用于存放解析后的命令和参数
    int argc = 0; // 计数器，用于记录解析出的命令和参数数量
    int status = 0; // 标记变量，用于判断是否遇到空格或者制表符
    while (*buf != '\0') { // 遍历输入的命令字符串buf
        if (!isspace(*buf)) { // 当遇到第一个非空白字符时
            argv[argc++] = buf; // 将该字符的地址存入指针数组argv，并且argc自增1
            while (!isspace(*buf) && *buf != '\0' && *buf != '|' && *buf != '<' && *buf != '>') buf++; // 跳过当前单词
            if (*buf == '\0') break; // 如果已经扫描到字符串末尾，则退出循环
            *buf++ = '\0'; // 将空格、制表符、管道符号'|'和重定向符号'>'或'<'处置为'\0'，以便于后续处理
        } else {
            buf++; // 跳过当前空白字符
        }
    }
    argv[argc] = NULL; // 指针数组最后一项设置为NULL，以便于在execvp调用时判断参数列表的结束
    do_exe(argv[0], argv); // 执行解析出来的命令及其参数
}

int main(void) {
    char buf[1024] = {}; // 定义存储用户输入的缓冲区

    while (1) { // 循环读取用户输入
        // printf("my shell# "); // 打印提示符
        printf("\033[33mmy shell# \033[0m");
        memset(buf, 0x00, sizeof(buf)); // 清空buf缓冲区

        if (fgets(buf, sizeof(buf), stdin) == NULL) { // 使用fgets函数读取用户输入，避免因为输入过长导致的缓冲区溢出问题
            perror("fgets");
            continue;
        }

        char *p = buf + strlen(buf) - 1; // 去掉字符串末尾的换行符
        if (*p == '\n') *p = '\0';

        // 如果输入的是"exit"或"q"，则退出程序
        if (strcmp(buf, "exit") == 0 || strcmp(buf, "q") == 0) break;
        
        do_parse(buf); // 对用户输入的命令进行解析并执行
        while (waitpid(-1, NULL, WNOHANG) > 0); // 循环回收所有已经终止的子进程资源，避免出现僵尸进程
    }
    return 0;
}
