//
//  main.c
//  数据结构·栈·顺序存储
//
//  Created by 徐龙 on 2021/10/18.
//

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int datatype;

typedef struct {
    datatype data[MAXSIZE];
    int top;
}seqstack,*pseqstack;

pseqstack start(void)
{//创建顺序栈
    pseqstack s;
    s=(pseqstack)malloc(sizeof(seqstack));
    if(s)
        s->top=-1;
    return s;
}

int empty(pseqstack s)
{//判断栈是否为空
    if(s->top==-1)
        return 1;
    else
        return 0;
}

int push(pseqstack s,datatype x)
{//栈顶插入新元素x
    if(s->top==MAXSIZE-1)
        return 0;//栈满无法入栈
    else
    {
        s->top++;
        s->data[s->top]=x;
        return 1;
    }
}

int pop(pseqstack s,datatype *x)
{//删除栈顶元素，并保存在*x
    if(empty(s))
        return 0;//栈空不能出栈
    else
    {
        *x=s->data[s->top];
        s->top--;
        return 1;
    }
}

int gettop(pseqstack s,datatype *x)
{//取出栈顶元素
    if(empty(s))
        return 0;//栈空
    else
    {
        *x=s->data[s->top];//栈顶元素存入*x中
        return (1);
    }
}

void destroy(pseqstack *s)
{//销毁栈
    if(*s)
        free(*s);
    *s=NULL;
    return ;
}

int main()
{
    printf("顺序栈——这个小梅同学要自己想啊！\n");
    return 0;
}
