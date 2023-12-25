//
//  main.c
//  串·堆存储结构·动态·标准
//

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *p;
    int length;
}hstring,*phstring;

phstring InitString(void)
{//开辟 字符串 空间
    phstring H=(phstring)malloc(sizeof(hstring));
    if(NULL==H)
    {
        printf("内存开辟失败!");
        exit(0);
    }
    else
    {
        H->p=NULL;
        H->length=0;
        return H;
    }
}

int strassign(phstring s1,char *s2)
{//串常量赋值，将一个字符串常量的值赋值给一个字符串变量
    int i;
    char *pc;
    if(s1->p)
        free(s1->p);
    for(i=0,pc=s2;*pc!='\0';i++,pc++);//求s2长度
    //printf("%d",i);
    if(i==0)
    {
        s1->p=NULL;
        s1->length=0;
        return 0;
    }
    if(!(s1->p=(char *)malloc((i+1) * sizeof(char))))
    {// +1 为了添加字符串结束标识符需要多申请一个字节内存；
        printf("堆空间不足，赋值失败！\n");
        return 0;
    }
    for(int j=0;j<i;j++)
        s1->p[j]=s2[j];
    s1->p[i]='\0';  //字符串结束标识符
    s1->length=i;
    printf("字符串长度为：%d\n",s1->length);
    return 1;//赋值成功
}

int strcopy(phstring s1,hstring s2)
{//s2也可以输入为 phstring s2 ，后面 . 全改为 ->
//赋值一个串,将一个字符串的值赋值给一个字符串变量,将s2赋值给s1
    if(s2.length<=0)
        return 0;
    if(!(s1->p=(char *)malloc((s2.length+1) * sizeof(char))))
    {
        printf("堆空间不足,赋值失败!\n");
        return 0;
    }
    for(int i=0;i<s2.length;i++)
        s1->p[i]=s2.p[i];
    s1->length=s2.length;
    s1->p[s2.length]='\0';
    //for(int i=0;i<7;i++)      //输出 s1  方法一
        //printf("%c",s1->p[i]);
    printf("赋值串s3后输出：%s\n",s1->p);   //输出 s1  方法二
    return 1;//赋值成功
}
                      
int substring(phstring sub, phstring s, int pos, int len)
{//求子串,用sub返回串s的第pos个字符起长度为len的子串;其中,1≤pos≤strlength(s)且0≤len≤strlength(s)-pos+1
    int i;
    if(pos<1||pos>s->length||len<0||len>s->length-pos+1)
        return 0;
    if(sub->p)//释放旧空间
        free(sub->p);
    if(!len)
    {
        sub->p=0;
        sub->length=0;//空子串
    }
    else//完整子串
    {
        sub->p=(char *)malloc((len+1) * sizeof(char));
        for(i=0;i<len;i++)
            sub->p[i]=s->p[pos+i-1];
        sub->p[len]='\0';
        sub->length=len;
    }
    printf("求s1第%d位长度%d的子串sub：%s\n",pos,len,sub->p);  //输出子串
    return 1;
}


int strcontact(phstring t,phstring s1,phstring s2)
//int strcontact(hstring *t,hstring s1,hstring s2)
{//串连接,t 保存由字符串 s1 和 s2 连接而成的新串
	int i;
    if(t->p)
        free(t->p);//释放旧空间
    if(!(t->p=(char*)malloc((s1->length+s2->length+1)*sizeof(char))))
        printf("堆空间不足,串连接失败!\n");
    for(i=0;i<s1->length;i++)
        t->p[i]=s1->p[i];
    t->length=s1->length+s2->length;
    for(i=s1->length;i<t->length;i++)
        t->p[i]=s2->p[i-s1->length];
    t->p[t->length]='\0';
    printf("由s1和s2连接的串t为：%s\n",t->p);  //输出 t
    return 1;
}

int strinsert(phstring s,int pos,phstring t)
{//在目标串的指定位置前插入字符串,1≤pos≤strlength(s)+1,在串s的第pos字符前插入串t
    int i;
    if(pos<1||pos>s->length+1)
        return 0;
    if(t->length==0)//t是空串
        return 1;
    if(!(s->p=(char *)realloc(s->p,(s->length+t->length+1)*sizeof(char))))
    {         //realloc重新分配 s->p 的内存
        printf("堆空间不足,插人失败!\n");
        return 0;
    }
    for(i=s->length-1;i>=pos-1;i--)//让出插人的位置
        s->p[i+t->length]=s->p[i];
    for(i=pos-1;i<=pos+t->length-2;i++)
        s->p[i]=t->p[i-pos+1];
    s->length=s->length+t->length;
    s->p[s->length]='\0';
    printf("在串s2的第%d字符前插入串s3：%s\n",pos,s->p);  //输出 t
    return 1;
}

int initstring(hstring *s)
{//置空串
    s->p=0;//指针置空
    s->length=0;
    return 1;
}

int destorystring(phstring s)
{//销毁串
    if(s->length)
    {
        free(s->p);
        s->p=0;//指针收起
        s->length=0;
    }
    return 1;
}


int main(int argc, const char * argv[]) 
{
    phstring s1=InitString();
    phstring s2=InitString();
    phstring s3=InitString();
    phstring sub=InitString();
    phstring t=InitString();
    
    strassign(s1,"abcdefg");// 将 常量字符串 赋值给 s1
    strassign(s2,"12345678");// 将 常量字符串 赋值给 s2
    strcopy(s3, *s1);  //将s1 赋值给 s3
    substring(sub, s1, 2, 4);  //求 s1第 2位长度 4的子串sub
    strcontact(t, s1, s2);  //将 s1和 s2连接，给 t
    strinsert(s2, 3, sub);   //在串 s2的第 3字符前插入串 sub
    
    destorystring(s1);
    destorystring(s2);
    destorystring(s3);
    destorystring(sub);
    destorystring(t);
}
/*
 字符串长度为：7
 字符串长度为：8
 赋值串s3后输出：abcdefg
 求s1第2位长度4的子串sub：bcde
 由s1和s2连接的串t为：abcdefg12345678
 在串s2的第3字符前插入串s3：12bcde345678
 */
