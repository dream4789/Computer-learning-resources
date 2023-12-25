#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100  //顺序表的最大长度,假定顺序表的长度为 100

typedef int KeyType;  //假定关键字类型为整数类型
typedef int OtherType;
typedef struct
{
    KeyType key;  //关键字项
    OtherType other;  //其他项
}DataType;  //数据元素类型
typedef struct
{
    DataType r[MAXSIZE+1];  //r[0]闲置或充当前哨站
    int length;  //顺序表长度
}SqList;  //顺序表类型

SqList init_sqlist(void)
{
    int a[10]={10,23,45,31,8,37,16,67,26,14};
    SqList * L=(SqList*)malloc(sizeof(SqList));
    //printf("输入串长：");
    L->length=10;// 临时
    //scanf("%d",&L->length);
    //printf("输入串的元素：\n");
    for(int i=1;i<=L->length;i++)
    {
        L->r[i].key=a[i-1];  //临时
        //scanf("%d",&L->r[i].key);
    }
    return *L;
}

void Merge(DataType r[],DataType rf[],int u,int v,int t)
{//将有序的 r[u··v]和 r[v+1··t]归并为有序的 rf[u··t]
    int i,j,k;
    for(i=u,j=v+1,k=u;i<=v && j<=t;k++)  //将r中记录由小到大并到tf
    {
        if(r[i].key<=r[j].key)
        { rf[k]=r[i];i++;}  //j大给i
        else
        { rf[k]=r[j];j++;}  //i大给j
    }
    while(i<=v){rf[k++]=r[i++];}  //将剩余的 r[i··v]复制到tf
    while(j<=t){rf[k++]=r[j++];}  //将剩余的 r[j··t]复制到tf
}
//二路归并排序主要将整个序列划分为两个有序的子序列，然后将这两个子序列进行
//归并操作
void MSort(DataType p[],DataType p1[],int n,int t)
{//将 p[n··t]归并排序为 p1[n··t]
    int m;
    DataType p2[MAXSIZE+1];  //中间变量,存放部分排序结果
    if(n==t)
        p1[n]=p[n];  //P中只有一个元素，不需要进行归并操作
    else
    {
        m=(n+t)/2;  //平分待排序的序列
        MSort (p,p2,n,m);    //将 p[n··m]归并为有序的 p2[n··m],调用递归过程实现
        MSort (p,p2,m+1,t);  //将 p[m+1··t]归并为有序的 p2[m+1··t],调用递归过程实现
        Merge (p2,p1,n,m,t); //将 p2[n··m]和 p2[m+1··t]归并到 p1[n··t]
    }
}
void MergeSort(SqList * S)
{//对顺序表 S 作归并排序
    MSort(S->r,S->r,1,S->length);
}
int main()
{
    SqList L=init_sqlist();
	int i;
    
    MergeSort(&L);
    printf("归并排序：");
    for(i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
}
/*
 数组赋值方法：
 int z[5]={1,1,2,4};
 int n[10]={0};  //将n数组里的全部初始化为0
 char z[]="zhinanzhen";
 char t[6]={'s','t','u','d','e','n','t','\0'};
 char x[]="can l with you ?";
 
 输入串长：10
 输入串的元素：
 10
 23
 45
 31
 8
 37
 16
 67
 26
 14
 归并排序：8 10 14 16 23 26 31 37 45 67
 */
