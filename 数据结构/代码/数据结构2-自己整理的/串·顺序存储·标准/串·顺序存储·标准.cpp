//
//  main.c
//  串·顺序存储·标准
//

#include <stdio.h>

#define maxsize 256
char s[maxsize];

typedef struct
{
    char data[maxsize];
    int length;
}seqstring;

int strlength(char *s)
{//求串长
    int i=0;
    while(s[i]!='\0')
        i++;
    return i;
}

int strconcat(char *s1,char *s2,char *s)
{//新串储存在指针s中,串连接
    int i=0,j,len1,len2;
    len1=strlength(s1);
    len2=strlength(s2);
    if(len1+len2>maxsize-1)
        return 0;
    j=0;
    while(s1[j]!='\0')
    {
        s[i]=s1[j];
        i++;
        j++;
    }
    j=0;
    while(s2[j]!='\0')
    {
        s[i]=s2[j];
        i++;
        j++;
    }
    s[i]='\0';
    return 1;
}

int strsub(char *t,char *s,int i,int len)
{//求子串，用t返回串s中第i个字符开始的长度为len的子串，1≤i≤串长
    int slen,j;
    slen=strlength(s);
    if(i<1||i>slen||len>slen-i+1)
    {
        printf("参数不对");
        return 0;
    }
    for(j=0;j<len;j++)
        t[j]=s[i+j-1];
    t[j]='\0';
    return 1;
}

int Strcmp(char *s1,char *s2)
{//串比较
    int i=0;
    while(s1[i]==s2[i]&&s1[i]!='\0')
        i++;
    return  s1[i]==s2[i];
}

int main(int argc, const char * argv[])
{
    char s1[10]="12345";
    char s2[10]="6789";
    char s[20],t[10];
    
    int l=strlength(s1);    //求串长
    printf("s1串长为：%d\n",l);
    
    strconcat(s1, s2, s);  //串连接
    printf("串连接：%s\n",s);
    
    strsub(t, s1, 1, 3);   //求子串
    printf("求子串：%s\n",t);
    
    int c=Strcmp(s1, s2);  //串比较
    printf("串比较：%d(相等为1，不等为0)\n",c);  //相等为1，不等为0
    
    return 0;
}
/*
 s1串长为：5
 串连接：123456789
 求子串：123
 串比较：0(相等为1，不等为0)
 */
