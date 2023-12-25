//
//  main.c
//  数据结构·栈·链式存储
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
{//创建链式栈
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
        printf("内存溢出");
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
        printf("栈空，不能出栈");
        return  0;
    }
    *x=s->top->data;
    p=s->top;
    s->top=s->top->next;
    free(p);
    return (1);
}

int gettop(plinkstack s,datatype *x)
{//取出栈顶元素
    if(empty(s))
    {
        printf("栈空");
        return 0;//栈空
    }
    else
    {
        *x=s->top->data;//栈顶元素存入*x中
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
    printf("链式栈——这个小梅同学要自己想啊！\n");
    return 0;
}
