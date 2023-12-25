//
//  main.c
//  数据结构·队列·顺序存储
//


#include <stdio.h>
#include<stdlib.h>
#define maxsize 100
typedef int datatype;


typedef struct{
    datatype data[maxsize];
    int front,rear;
}seqqueue,*pseqqueue;

pseqqueue init_seqqueue(void)
{//创建队列
    pseqqueue q;
    q=(pseqqueue)malloc(sizeof(seqqueue));
    if(q)
    {
        q->front=0;
        q->rear=0;
    }
    return q;
}

int empty_seqqueue(pseqqueue q)
{//队列判空
    if(q&&q->front==q->rear)
        return 1;
    else
        return 0;
}

int in_seqqueue(pseqqueue q,datatype x)
{//入队
    if((q->rear+1)%maxsize==q->front)
    {
        printf("队满");
        return -1;
    }
    else
    {
        q->rear=(q->rear+1)%maxsize;
        q->data[q->rear]=x;
        return 1;
    }
}

int out_seqqueue(pseqqueue q,datatype *x)
{//出队
    if(empty_seqqueue(q))
    {
        printf("队空");
        return -1;
    }
    else
    {
        q->front=(q->front+1)%maxsize;
        *x=q->data[q->front];
        return 1;
    }
}

int front_seqqueue(pseqqueue q,datatype *x)
{
    if(q->front==q->rear)
    {
        printf("队空");
        return -1;
    }
    else
    {
        *x=q->data[(q->front+1)]%maxsize;
        return 1;
    }
}

void destroy_seqqueue(pseqqueue *q)
{//销毁队列
    if(*q)
        free(*q);
    *q=NULL;
}


int main(int argc, const char * argv[]) {
    printf("顺序队列——这个小梅同学要自己想啊！\n");
    return 0;
}
