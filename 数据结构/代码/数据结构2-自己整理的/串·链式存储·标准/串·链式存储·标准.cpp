//
//  main.c
//  串·链式存储

#include <stdio.h>
#include <stdlib.h>

//链串插入 删除 连接

typedef char datatype;
typedef struct node
{
    datatype  data;
    struct node *next;
}node;

typedef node *linkstr;


void createstr(linkstr *s)//创建字符串
{
    char ch;
    node *p,*r; //p,r,linkstr(*s)都是节点
    *s=NULL;  //*s记录第一个节点
    r=NULL;//初始化节点为空
    while((ch=getchar())!='\n')
    {
        //p=(linkstr)malloc(sizeof(node));
        p=(node*)malloc(sizeof(node));
        p->data=ch;
        if(*s==NULL)//执行第一次
        {
            *s=p;
            r=p;
        }
        else
        {
            r->next=p;//划线
            r=p;
        }
    }
    if(r!=NULL)
        r->next=NULL;
}
linkstr strinsert(linkstr *s,int i,linkstr t)//插入
{//原始字符串；插入位置（第i个字母后面）；要插入的字符串
    int k=1;
    linkstr p,q;
    p = *s;//p为s串的第一个节点
    while(p&&k<i-1)//用p查找第i-1个位置
    {
        p=p->next;
        k++;
    }
    if(!p)//第i-1个元素不存在,则出错
    {
        puts("error!");
        exit(1);
    }
    else
    {
       q=t;
       while(q&&q->next)  //用q查找t中最后一个元素的位
           q=q->next;
       if(i==1)
       {
           q->next=p;//q的最后一个指向s
           *s=t;//s头结点给t
           return *s;
       }
        q->next=p->next; //n和d   将t连接到s中的第i个位置
        p->next=t;//c和m划线
    }
    return *s;
}

void del(linkstr *s,int i,int length)//删除
{//原始字符串；第i个字符开始删；所删长度为length
    int k=1;
    linkstr p,q,r;
    p=*s;
    q=NULL;  //q=null删除第一个赋初始值
    //第i个位置第一个位置
    while(p&&k<i)  //用p查找s的第i个元素，q始终跟随p的前驱节点
    {
        q=p;
        p=p->next;
        ++k;
    }
    if(!p)//*s从第i个元素不存在则出错
        printf("error!");
    else
    {
        k=1;
        while(k<length&&p)  //p从第i个元素开始查找长度为len子串的最后元素
        {
            p=p->next;
            ++k;
        }
        if(!p)
            printf("two error!");
        else
        {
            if(!q)     //被删除的子串位于s
            {
                r=*s;//用r记录原字符串第一个节点
                *s=p->next;//*s记录删除后的新起始节点
            }
            else   //被删除的子字符串位于s的中间或者最后的情形
            {
               r=q->next;  //用r记录要删除子串的第一个节点
               q->next=p->next;
            }
            p->next=NULL;
            while(r!=NULL)    //回收子字符串占用的空间
            {
                p=r;
                r=r->next;
                free(p);
            }
        }
    }
}

void concatstr(linkstr *s1,linkstr s2)//连接
{//把串s2连接到s1后
    linkstr p;
    if(!(*s1))//考虑串s1为空串时
    {
        *s1=s2;
        return ;
    }
    else
    {
        if(s2) //s1和s2均不为空串时
        {
            p=*s1;//用p查找s1的最后一个字符的位置
            while(p->next)
            {
                p=p->next;
            }
            p->next=s2;//将串s2连接到串s1之后
        }
    }
}

linkstr substring(linkstr *s,int i,int len)//取链式串的子串
{//原始字符串；第i个字符开始，取长度len的子串
    int k=1;//p为原字符串第一个节点，用p记录s中的第i个位置
    linkstr p=*s,q,r,t;
    while(p&&k<i)
    {
        p=p->next;
        ++k;
    }
    if(!p)
    {
        printf("error!");
        return NULL;
    }
    else
    {//r保存第一个节点
        r=(node*)malloc(sizeof(node));
        r->data=p->data;
        r->next=NULL;
        k=1;
        q=r;
        while(p->next&&k<len)
        {
            p=p->next;//p第二个节点
            ++k;
            t=(node*)malloc(sizeof(node));//保存第二个节点t++节点
            t->data=p->data;
            q->next=t; //第一个和第二个节点划线
            q=t;      //q指向字符串最后一个位置
        }
        if(k<len)
        {
            printf("two error!");
            return NULL;
        }
        else
        {
            q->next=NULL;
            return r;
        }
    }
}
void dispaly(linkstr *s)
{
    node *p;
    //linkstr p;
    p=*s;
    while(p)
    {
        printf("%c",p->data);
        p=p->next;
    }
    printf("\n");
}
int main()
{
    linkstr s,t;
    printf("输入初始字符串1：");
    createstr(&s);//创建原始字符串
    printf("   1.输出创建好字符串s: ");
    dispaly(&s);


    printf("输入要插入的字符串：");//插入
    createstr(&t);//创建要插入的字符串
    strinsert(&s,5,t);
    printf("   2.输出插入后的字符串s: ");
    dispaly(&s);

    del(&s,2,2);//删除,从第2位开始到第2位后面删掉
    printf("   3.输出删除后的字符串s: ");
    dispaly(&s);
    printf("\n");

    printf("输入要连接的字符串2：");
    createstr(&t);
    concatstr(&s,t);//连接
    printf("   4.输出连接后的字符串s: ");
    dispaly(&s);

    t=substring(&s,1,1);//取子串，从第1位开始到第1位后面取子串
    printf("   5.输出子串s: ");
    dispaly(&t);
    
    return 0;
}
/*
 
测试数据：
(注意：第一行有俩个空格，最后一行最前有一个空格）
 
mzt  student
is a sun
 forever

输出结果：
 
 输入初始字符串1：mzt  student
    1.输出创建好字符串s: mzt  student
 输入要插入的字符串：is a sun
    2.输出插入后的字符串s: mzt is a sun student
    3.输出删除后的字符串s: m is a sun student

 输入要连接的字符串2： forever
    4.输出连接后的字符串s: m is a sun student forever
    5.输出子串s: m
 




 哈哈哈哈哈哈哈！发现了，串连接蛮好玩的～
 
 */
