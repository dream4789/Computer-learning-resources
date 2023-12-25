//
//  main.c
//  ���ݽṹ��ջ����ʽ�洢
//


#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int datatype;

typedef struct node {
    datatype data;
    struct node *next;
}stacknode,*pstacknode;

typedef struct {
    pstacknode top;
}linkstack,*plinkstack;

plinkstack start(void)
{//������ʽջ
    plinkstack s;
    s=(plinkstack)malloc(sizeof(linkstack));
    if(s)
        s->top=NULL;
    return s;
}

int empty(plinkstack s)
{
    return (s->top==NULL);
}

int push(plinkstack s,datatype x)
{
    pstacknode p;
    p=(pstacknode)malloc(sizeof(stacknode));
    if(!p)
    {
        printf("�ڴ����");
        return 0;
    }
    p->data=x;
    p->next=s->top;
    s->top=p;
    return (1);
}

int pop(plinkstack s,datatype *x)
{
    pstacknode p;
    if(empty(s))
    {
        printf("ջ�գ����ܳ�ջ");
        return  0;
    }
    *x=s->top->data;
    p=s->top;
    s->top=s->top->next;
    free(p);
    return (1);
}

int gettop(plinkstack s,datatype *x)
{//ȡ��ջ��Ԫ��
    if(empty(s))
    {
        printf("ջ��");
        return 0;//ջ��
    }
    else
    {
        *x=s->top->data;//ջ��Ԫ�ش���*x��
        return (1);
    }
}

void destroy(plinkstack *s)
{
    pstacknode p,q;
    if(*s)
    {
        p=(*s)->top;
        while (p) {
            q=p;
            p=p->next;
            free(q);
        }
        free(*s);
    }
    *s=NULL;
}


int main()
{
    printf("��ʽջ�������С÷ͬѧҪ�Լ��밡��\n");
    return 0;
}
