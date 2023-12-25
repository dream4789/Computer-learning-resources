//
//  main.c
//  ���ݽṹ��ջ��˳��洢
//
//  Created by ���� on 2021/10/18.
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
{//����˳��ջ
    pseqstack s;
    s=(pseqstack)malloc(sizeof(seqstack));
    if(s)
        s->top=-1;
    return s;
}

int empty(pseqstack s)
{//�ж�ջ�Ƿ�Ϊ��
    if(s->top==-1)
        return 1;
    else
        return 0;
}

int push(pseqstack s,datatype x)
{//ջ��������Ԫ��x
    if(s->top==MAXSIZE-1)
        return 0;//ջ���޷���ջ
    else
    {
        s->top++;
        s->data[s->top]=x;
        return 1;
    }
}

int pop(pseqstack s,datatype *x)
{//ɾ��ջ��Ԫ�أ���������*x
    if(empty(s))
        return 0;//ջ�ղ��ܳ�ջ
    else
    {
        *x=s->data[s->top];
        s->top--;
        return 1;
    }
}

int gettop(pseqstack s,datatype *x)
{//ȡ��ջ��Ԫ��
    if(empty(s))
        return 0;//ջ��
    else
    {
        *x=s->data[s->top];//ջ��Ԫ�ش���*x��
        return (1);
    }
}

void destroy(pseqstack *s)
{//����ջ
    if(*s)
        free(*s);
    *s=NULL;
    return ;
}

int main()
{
    printf("˳��ջ�������С÷ͬѧҪ�Լ��밡��\n");
    return 0;
}
