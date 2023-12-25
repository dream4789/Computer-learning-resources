#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

// 加载程序
void do_exe(char *buf, char *argv[]) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(buf, argv);
        perror("fork"); // exec 执行失败
        exit(1);
    }
    wait(NULL);  // 等待子进程死亡，回收
}

// 对命令进行解析
void do_parse(char *buf) {
    char *argv[8] = {}; // 将buf中的命令以‘ ’为分界存入指针数组中
    int argc = 0;
    int status = 0; // 一个新的字符串
    for (int i = 0; buf[i] != 0; ++i) {
        if (status == 0 && !isspace(buf[i])) { // 判断是否为空白字符（包括空格、制表符、换行符等）
            argv[argc++] = buf + i;
            status = 1;
        } else if (isspace(buf[i])) {
            status = 0;
            buf[i] = 0;
        }
    }
    argv[argc] = NULL;
    do_exe(buf, argv);  // 加载程序
}

int main(void) {
    //  char* argv[] = {"ls", "-lah", NULL};
    //  execvp("ls", argv);// 替换地址空间,实则将原进程的代码段，数据段进行替换，并未创建新的进程出来。

    char buf[1024] = {};
    while (1) {
        printf("my shell#");
        memset(buf, 0x00, sizeof(buf));

        // [^\n]匹配除\n以外的所有字符,*用于抑制转换
        // scanf 成功返回输入的项数
        while (scanf("%[^\n]%*c", buf) == 0) { // 为 0 表示只输入了换行
            printf("my shell#");
            while (getchar() != '\n');  // 到获得了一个'\n'
        }
        do_parse(buf);
    }
    return 0;
}
