//
//  main.c
//  ���ݽṹ�����С���ʽ�洢
//

#include <stdio.h>
#include<stdlib.h>
#define maxsize 100
typedef int datatype;


typedef struct node{
    datatype data;
    struct node *next;
}qnode,*pqnode;

typedef struct{
    pqnode front,rear;
}linkqueue,*plinkqueue;

plinkqueue init_linkqueue(void)
{
    plinkqueue q;
    q=(plinkqueue)malloc(sizeof(linkqueue));
    if(q)
    {
        q->front=NULL;
        q->rear=NULL;
    }
    return 0;
}

int empty_linkqueue(plinkqueue q)
{
    if(q&&q->front==NULL&&q->rear==NULL)
        return 1;
    else
        return 0;
}

int in_linkqueue(plinkqueue q,datatype x)
{
    pqnode p;
    p=(pqnode)malloc(sizeof(qnode));
    if(!q)
    {
        printf("�ڴ����");
        return 0;
    }
    p->data=x;
    p->next=NULL;
    if(empty_linkqueue(q))
        q->rear=q->front=p;
    else{
        q->rear->next=p;
        q->rear=p;
    }
    return 1;
}

int out_linkqueue(plinkqueue q,datatype *x)
{
    pqnode p;
    if(empty_linkqueue(q))
    {
        printf("�ӿ�");
        return 0;
    }
    *x=q->front->data;
    p=q->front;
    q->front=q->front->next;
    free(p);
    if(!q->front)
        q->rear=NULL;
    return 1;
}

int front_linkqueue(plinkqueue q,datatype *x)
{
    if(empty_linkqueue(q))
    {
        printf("�ӿ�");
        return 0;
    }
    *x=q->front->data;
    return 1;
}

void destroy_linkqueue(plinkqueue q)
{
    pqnode p;
    if(q)
    {
        while (q->front) {
            p=q->front;
            q->front=q->front->next;
            free(p);
        }
        free(q);
    }
    q=NULL;
}

int main() {
    printf("��ʽ���С������С÷ͬѧҪ�Լ��밡��\n");
    return 0;
}
