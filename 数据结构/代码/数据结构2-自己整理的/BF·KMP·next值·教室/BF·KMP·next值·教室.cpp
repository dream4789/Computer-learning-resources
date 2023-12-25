//
//  main.c
//  BF·KMP·next值·教室
//

#include <stdio.h>
#include <string.h>

int strindex_BF(char *s,char *t)
{//从串s的第1个字符开始找首次与串t相等的子串    //简单模式匹配
    int i=0,j=0;
    int count=0;
    int ls=(int)strlen(s),lt=(int)strlen(t);
    while(i<ls&&j<lt)
    {
        if(s[i]==t[j])
        {
            //printf("[%c %c]",s[i],t[j]);   //检验行
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
            //printf("<%d|%c>",i,s[i]);   //检验行
        }
        count++;
    }
    printf("BF的比较次数为：%d       ",count+1);//最后一位匹配成功也要算上
    if(j>=lt)
        return i-lt;
    else
        return -1;
}

/*
int strindex_BF(char *s,char *t)
{//从串s的第1个字符开始找首次与串t相等的子串    //简单模式匹配
    int i=1,j=1;
    while(i<=s[0]&&j<=t[0])
        if(s[i]==t[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+2;
            j=1;
        }
    if(j>t[0])
        return i-t[0];
    else
        return -1;
}
*/
void web_getnext1(char *t,int next[])
{//第一第二位为-1，0。之后找最长相同子串，相同位数加1
    int j=0,k=-1;
    next[0]=-1;
    int lt=(int)strlen(t);
    while(j<lt-1)
    {
        if(k ==-1||t[j]==t[k])
        {
            j++;
            k++;
            /*
            if(t[j]==t[k])//当两个字符相同时，就跳过
                next[j] = next[k];
            else
                */
            next[j] = k;
        }
        else
            k = next[k];
    }
    printf("next(-1,0开始)值为：");
    for(int i=0;i<lt;i++)   //检验行
        printf("%d ",next[i]);
}
int web_KMP(char *s,char *t)
{//从串s的第1个字符开始找首次与串t相等的子串
    int next[10],i=0,j=0;
    int count=0;
    web_getnext1(t,next);
    int ls=(int)strlen(s),lt=(int)strlen(t);
    while(i<ls&&j<lt)
    {
        if(j==-1 || s[i]==t[j])
        {
            i++;
            j++;
        }
        else
            j=next[j];               //j回退
        count++;
    }
    printf("  WEB_KMP的比较次数为：%d  ",count);
    if(j>=lt)
        return (i-lt);         //匹配成功，返回子串的位置
    else
        return (-1);                  //没找到
}

void getnext(char *t,int next[])
{//求模式t的next值并存入next数组中，字符串长度保留在t[0]
    //第一第二位为-1，0。之后找最长相同子串，相同位数加1
    int i=0,j=-1;
    int lt=(int)strlen(t);
    next[0]=-1;
    while(i<lt-1)
        if(j==-1||t[i]==t[j])
        {
            ++i;
            ++j;
            next[i]=j;//回溯
        }
        else
            j=next[j];
    printf("next(-1,0开始)值为：");
    for(i=0;i<lt;i++)   //检验行
        printf("%d ",next[i]);
}

int strindex_KMP(char *s,char *t,int pos,int *next)
{//从串s的第pos个字符开始找首次与串t相等的子串    //KPM模式匹配，找匹配最长子串，平移
    int i=pos-1,j=0;
    //char next[10];
    int ls=(int)strlen(s),lt=(int)strlen(t);
    while(i<ls&&j<lt)
        if(j==-1||s[i]==t[j])
        {
            i++;
            j++;
        }
        else
            j=next[j];//回溯
    if(j>=lt)
        return i-j;//匹配成功，返回存储位置
    else
        return -1;
}

/*
int strindex_KMP(char *s,char *t,int pos)
{//从串s的第pos个字符开始找首次与串t相等的子串    //KPM模式匹配，找匹配最长子串，平移
    int i=pos,j=1;
    char next[10];
    while(i<=s[0]&&j<=t[0])
        if(j==0||s[i]==t[j])
        {
            i++;
            j++;
        }
        else
            j=next[j];//回溯
    if(j>t[0])
        return i-t[0];//匹配成功，返回存储位置
    else
        return -1;
}
*/

void getnext_rec(char *t,int next[],int l)
{//递归算法求next值，t为模式串，l为模式串长度=t[0]
    if(l==1)//l=1，递归出口
    {
        next[1]=0;//递归求next[l-1],为next[l]作准备
        return;
    }
    getnext_rec(t,next,l-1);
    int k=next[l-1];
    while(1)//直到next[l]计算完毕
    {
        if(t[k]==t[l-1])
        {
            next[l]=k+1;
            return;
        }
        k=next[k];//回溯
        if(k==0)//不存在最大相等的前缀和后缀子串，next[1]=1
        {
            next[l]=1;
            return;
        }
    }
}


int main() {
    char s[]={"001000100001010"};
    char s1[]="00101";
    
    int BF,KMP,WEB_KMP;
    BF=strindex_BF(s,s1);
    printf("BF匹配：第%d位 \n",BF+1);
    WEB_KMP=web_KMP(s,s1);
    printf("WEB_KMP匹配：第%d位\n",WEB_KMP+1);
    
    int next[10];
    getnext(s1, next);
    KMP=strindex_KMP(s, s1, 2, next);
    printf("  KMP匹配：第%d位\n",KMP+1);

    return 0;
}
/*
 BF的比较次数为：31       BF匹配：第10位
 next(-1,0开始)值为：-1 0 1 0 1   WEB_KMP的比较次数为：19  WEB_KMP匹配：第10位
 next(-1,0开始)值为：-1 0 1 0 1   KMP匹配：第10位
 */
