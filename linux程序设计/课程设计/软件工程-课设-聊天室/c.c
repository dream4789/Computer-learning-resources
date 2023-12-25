#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>
#include<time.h>

#define SIZE 1024

int main(int argc, char *argv[]) {
    pid_t pid;
    int sockfd, confd;
    char buffer[SIZE], buf[SIZE];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    struct hostent *host;
    short port;
    char *name;
    //四个参数
    if (argc != 4) {
        fprintf(stderr, "Usage:%s hostname \a\n", argv[0]);
        exit(1);
    }
    //使用hostname查询host 名字 
    if ((host = gethostbyname(argv[1])) == NULL) {
        fprintf(stderr, "Gethostname error\n");
        exit(1);
    }
    port = atoi(argv[2]);
    name = argv[3];
    /*客户程序开始建立 sockfd描述符 */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "Socket Error:%s\a\n", strerror(errno));
        exit(1);
    } else {
        printf("Socket successful!\n");
    }
    /*客户程序填充服务端的资料 */
    bzero(&server_addr, sizeof(server_addr)); // 初始化,置0
    server_addr.sin_family = AF_INET;          // IPV4
    server_addr.sin_port = htons(port);  // (将本机器上的short数据转化为网络上的short数据)端口号
    server_addr.sin_addr = *((struct in_addr *) host->h_addr); // IP地址
    /* 客户程序发起连接请求 */
    if (confd = connect(sockfd, (struct sockaddr *) (&server_addr), sizeof(struct sockaddr)) == -1) {
        fprintf(stderr, "Connect Error:%s\a\n", strerror(errno));
        exit(1);
    } else {
        printf("Connect successful!\n");
    }
    /*将客户端的名字发送到服务器端*/
    send(sockfd, name, 20, 0);
    /*创建子进程，进行读写操作*/
    pid = fork();//创建子进程
    while (1) {
        /*父进程用于发送信息*/
        if (pid > 0) {
            /*时间函数*/
            struct tm *p;
            time_t timep;
            time(&timep);
            p = localtime(&timep);
            strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", p);
            /*输出时间和客户端的名字*/
            strcat(buffer, " \n\t昵称 ->");
            strcat(buffer, name);
            strcat(buffer, ":\n\t\t  ");
            memset(buf, 0, SIZE);
            fgets(buf, SIZE, stdin);
            /*对客户端程序进行管理*/
            if (strncmp("e", buf, 1) == 0) {
                printf("该客户端下线...\n");
                strcat(buffer, "退出聊天室！");
                if ((send(sockfd, buffer, SIZE, 0)) <= 0) {
                    perror("error send");
                }
                close(sockfd);
                sockfd = -1;
                exit(0);
            } else {
                strncat(buffer, buf, strlen(buf) - 1);
                strcat(buffer, "\n");
                if ((send(sockfd, buffer, SIZE, 0)) <= 0) {
                    perror("send");
                }
            }
        } else if (pid == 0) {
            /*子进程用于接收信息*/
            memset(buffer, 0, SIZE);
            if (sockfd > 0) {
                if ((recv(sockfd, buffer, SIZE, 0)) <= 0) {
                    close(sockfd);
                    exit(1);
                }
                printf("%s\n", buffer);
            }
        }
    }
    close(sockfd);
    return 0;
}
