//
//  main.c
//  ���ݽṹ�����С�˳��洢
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
{//��������
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
{//�����п�
    if(q&&q->front==q->rear)
        return 1;
    else
        return 0;
}

int in_seqqueue(pseqqueue q,datatype x)
{//���
    if((q->rear+1)%maxsize==q->front)
    {
        printf("����");
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
{//����
    if(empty_seqqueue(q))
    {
        printf("�ӿ�");
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
        printf("�ӿ�");
        return -1;
    }
    else
    {
        *x=q->data[(q->front+1)]%maxsize;
        return 1;
    }
}

void destroy_seqqueue(pseqqueue *q)
{//���ٶ���
    if(*q)
        free(*q);
    *q=NULL;
}


int main(int argc, const char * argv[]) {
    printf("˳����С������С÷ͬѧҪ�Լ��밡��\n");
    return 0;
}
