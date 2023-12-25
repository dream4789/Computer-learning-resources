//
//  main.c
//  串·堆存储结构·静态·标准
//
//  Created by 徐龙 on 2021/11/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxsize 100
#define SMAX 100

char store[SMAX+1];//堆空间
int free1;//自由区指针

typedef struct
{//带串长度的索引表
    char name[maxsize];//串名
    int length;//串长
    char * stradr;//起始地址
}lnode;

typedef struct
{//末尾指针的索引表
    char name[maxsize];//串名
    char * stradr,* enadr;//起始地址，末尾地址
}enode;

typedef struct
{
    int length;//串长
    int stradr;//起始地址
}hstring,*phstring;

phstring InitString(void)
{//开辟 字符串 空间
    phstring H=(phstring)malloc(sizeof(hstring));
    if(NULL==H)
    {
        printf("Memory allocate is error!");
        system("pause");
        exit(0);
    }
    else
    {
        H->stradr = 0;
        H->length = 0;
        return H;
    }
}

int strassign(phstring s1,char *s2)
{//将一个字符数组s2中的字符串送入堆stroe中，free1是自由区指针，正常操作返回1
    int i=0;
    int len;
    len=(int)(strlen(s2));
    if(len<0||free1+len > SMAX+1)
        return 0;
    else
    {
        for(i=0;i<len;i++)
            store[free1+i]=s2[i];
        s1->stradr=free1;
        s1->length=len;
        free1=free1+len;    //修改自由区指针
        printf("s串为：");
        for(i=0;i<len;i++)  //输出
            printf("%c",store[s1->stradr+i]);
        printf("\n");
        return 1;
    }
}

int strcopy(phstring s1,phstring s2)
{//该运算将堆store中的s2复制到一个新串s1中
    int i=0;
    if(free1+s2->length > SMAX+1)
        return 0;
    else
    {
        for(i=0;i<s2->length;i++)
            store[free1+i]=store[s2->stradr+i];
        s1->length=s2->length;
        s1->stradr=free1;
        free1=free1+s2->length;
        printf("拷贝的新串为：");
        for(i=0;i<s1->length;i++)  //输出
            printf("%c",store[s1->stradr+i]);
        printf("\n");
        return 1;
    }
}

int main(int argc, const char * argv[])
{
    phstring s1=InitString(); //串空间初始化
    phstring s2=InitString();
    
    strassign(s1, "love ");  //串进堆
    strassign(s2, "you ");
    strcopy(s2, s1);  //串拷贝，把s2拷贝到s1
    
    printf("store中全部的串为：");
    for(int i=0;i<free1;i++)
        printf("%c",store[i]);
    printf("\n");
    return 0;
}
/*
 s串为：love
 s串为：you
 拷贝的新串为：love
 store中全部的串为：love you love 
 */