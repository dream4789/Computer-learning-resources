#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/shm.h>
#include<time.h>
#include<pthread.h>

#define PORT 4395
#define SIZE 1024
#define SIZE_SHMADD 2048
#define BACKLOG 3
int sockfd;
int fd[BACKLOG];
int i = 0;

/*********套接字描述符*******/
int get_sockfd() {
    struct sockaddr_in server_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "Socket error:%s\n\a", strerror(errno));
        exit(1);
    }
    else {
        printf("Socket successful!\n");
    }     /*sockaddr结构 */
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
    /*绑定服务器的ip和服务器端口号*/
    if (bind(sockfd, (struct sockaddr *) (&server_addr), sizeof(struct sockaddr)) == -1) {
        fprintf(stderr, "Bind error:%s\n\a", strerror(errno));
        exit(1);
    } else { printf("Bind successful!\n"); }
    /* 设置允许连接的最大客户端数 */
    if (listen(sockfd, BACKLOG) == -1) {
        fprintf(stderr, "Listen error:%s\n\a", strerror(errno));
        exit(1);
    }
    else {
        printf("Listening.....\n");
    }
    return sockfd;
}

/*创建共享存储区*/
int shmid_create() {
    int shmid;
    if ((shmid = shmget(IPC_PRIVATE, SIZE_SHMADD, 0777)) < 0) {
        perror("shmid error!");
        exit(1);
    }
    else printf("shmid success!\n");
    return shmid;
}

int main(int argc, char *argv[]) {
    char shmadd_buffer[SIZE_SHMADD], buffer[SIZE];
    struct sockaddr_in client_addr;
    int sin_size;
    pid_t ppid, pid;
    int new_fd;
    int shmid;
    char *shmadd;
    /***********共享内存**************/
    shmid = shmid_create();
    //映射共享内存
    shmadd = shmat(shmid, 0, 0);
    /*****创建套接字描述符***********/
    int sockfd = get_sockfd();
    /*循环接收客户端*/
    while (1) {   /* 服务器阻塞,直到客户程序建立连接 */
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sockfd, (struct sockaddr *) (&client_addr), &sin_size)) == -1) {
            fprintf(stderr, "Accept error:%s\n\a", strerror(errno));
            exit(1);
        }
        else { printf("Accept successful!\n"); }
        fd[i++] = new_fd;
        printf("\n已连接了客户端%d : %s:%d \n", i, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        /*把界面发送给客户端*/
        memset(buffer, 0, SIZE);
        strcpy(buffer, "\n——————————————————Welecom come char ———————————————————————\n");
        send(new_fd, buffer, SIZE, 0);
        //创建子进程客户端
        ppid = fork();
        if (ppid == 0) {
            //将加入的新客户发送给所有在线的客户端/
            recv(new_fd, buffer, SIZE, 0);
            strcat(buffer, " 进入了聊天室....");
            for (i = 0; i < BACKLOG; i++) {
                if (fd[i] != -1) {
                    send(fd[i], buffer, strlen(buffer), 0);
                }
            }
            //创建子进程进行读写操作/
            pid = fork();
            while (1) {
                if (pid > 0) {
                    //父进程用于接收信息/
                    memset(buffer, 0, SIZE);
                    if ((recv(new_fd, buffer, SIZE, 0)) <= 0) {
                        close(new_fd);
                        exit(1);
                    }
                    memset(shmadd, 0, SIZE_SHMADD);
                    strncpy(shmadd, buffer, SIZE_SHMADD);//将缓存区的客户端信息放入共享内存里
                    printf(" %s\n", buffer);
                }
                if (pid == 0) {
                    //子进程用于发送信息/
                    sleep(1);//先执行父进程
                    if (strcmp(shmadd_buffer, shmadd) != 0) {
                        strcpy(shmadd_buffer, shmadd);
                        if (new_fd > 0) {
                            if (send(new_fd, shmadd, strlen(shmadd), 0) == -1) {
                                perror("send");
                            }
                            memset(shmadd, 0, SIZE_SHMADD);
                            strcpy(shmadd, shmadd_buffer);
                        }
                    }
                }
            }
        }
    }
    free(buffer);
    close(new_fd);
    close(sockfd);
    return 0;
}