#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

void do_exe(char *buf, char *argv[]) {  // 加载程序
    pid_t pid = fork();
    if (pid == 0) {
        execvp(buf, argv);
        perror("fork");
        exit(1);
    }
    wait(NULL);  // 等待子进程死亡，回收
}

// 对命令进行解析
void do_parse(char *buf) {
    char *argv[8] = {}; // 定义指针数组，用于存放解析后的命令和参数
    int argc = 0; // 计数器，用于记录解析出的命令和参数数量
    int status = 0; // 标记变量，用于判断是否遇到空格或者制表符
    for (int i = 0; buf[i] != 0; ++i) { // 遍历输入的命令字符串buf
        if (status == 0 && !isspace(buf[i])) { // 当遇到第一个非空白字符时
            argv[argc++] = buf + i; // 将该字符的地址存入指针数组argv，并且argc自增1
            status = 1; // 将status设置为1，表示当前正在扫描一个字符串
        } else if (isspace(buf[i])) { // 当遇到空格或者制表符时
            status = 0; // 将status设置为0，表示当前正在扫描的字符串已结束
            buf[i] = 0; // 将这个字符设置为字符串结束符'\0'
        }
    }
    argv[argc] = NULL; // 指针数组最后一项设置为NULL，以便于在execvp调用时判断参数列表的结束。
    do_exe(buf, argv); // 执行解析出来的命令及其参数
}

int main(void) {
    char buf[1024] = {}; // 定义存储用户输入的缓冲区
    while (1) { // 循环读取用户输入
        printf("my shell#"); // 打印提示符
        memset(buf, 0x00, sizeof(buf)); // 清空buf缓冲区
        while (scanf("%[^\n]%*c", buf) == 0) { // 如果用户只是输入了换行符，则需要重新打印提示符等待用户输入有效的命令
            printf("my shell#");
            while (getchar() != '\n');  // 需将输入队列中除了换行符之外的其他字符全部读取掉
        }
        do_parse(buf); // 对用户输入的命令进行解析并执行
    }
    return 0; // 程序正常退出
}
