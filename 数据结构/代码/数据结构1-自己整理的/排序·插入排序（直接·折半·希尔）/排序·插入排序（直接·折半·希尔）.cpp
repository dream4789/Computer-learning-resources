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
    SqList * L=(SqList*)malloc(sizeof(SqList));
    printf("输入串长：");
    scanf("%d",&L->length);
    printf("输入串的元素：\n");
    for(int i=1;i<=L->length;i++)
        scanf("%d",&L->r[i].key);
    return *L;
}

void StraightInsertSort(SqList* S)
{//对顺序表 s 中的 s->r[1..length]作直接插人排序
    int i,j;
    for(i=2;i<=S->length;i++)
    {
        S->r[0]=S->r[i];  //复制到前哨站
        j=i-1;
        while(S->r[0].key < S->r[j].key)  //记录后移
        {
            S->r[j+1]=S->r[j];
            j--;
        }
        S->r[j+1]=S->r[0];  //插入到正确位置
    }
}

void BinaryInsertsort(SqList * s)
{//对顺序表 s 作折半插入排序
    int low,high,mid;
    for(int i=2;i<=s->length;i++)
    {
        s->r[0]=s->r[i];  //保存待插入元素
        low=1;
        high=i-1;  //设置初始区间
        while(low<=high)  //该循环语句完成确定插人位置
        {
            mid=(low+high)/2;
            if(s->r[0].key >= s->r[mid].key)
                low=mid+1;  //插入位置在高半区中
            else
                high=mid-1;  //插入位置在低半区中
        }
        for(int j=i-1;j>=high+1;j--)  //high+1 为插入位置
            s->r[j+1] = s->r[j];  //后移元素,留出插入空位
        s->r[high+1]=s->r[0];  //将元素插人
    }
}  //BinaryInsertSort

void ShellInsert(SqList* s,int gap)
{//一趟增量为 gap 的插人排序,gap 为步长
    int i,j;
    for(i=gap+1 ; i<=s->length ; i++)
    {
        if(s->r[i].key < s->r[i-gap].key)  //前大运行,小于时,需将r[i]插入有序表
        {
            s->r[0]=s->r[i];  //为统一算法设置监视哨，暂存
            for(j=i-gap ; j>0 && s->r[0].key<s->r[j].key ; j=j-gap)
                s->r[j+gap]=s->r[j];  //记录后移
            s->r[j+gap]=s->r[0];  //插入到正确位置
        }
        /*
        for(int k=0;k<=s->length;k++)  //分析行
            printf("%d ",s->r[k].key);
        printf("\n");
         */
    }
    //printf("\n");  //分析行
}
void ShellSort(SqList* s,int gaps[],int t)
{//按增量序列 gaps[0,1,…t-1]对顺序表 s 作希尔排序
    for(int k=0;k<t;k++)
    {
        ShellInsert(s,gaps[k]);   //一趟增量为 gaps[k]的插人排序
        /*
        for(int i=1;i<=s->length;i++)  //分析行
            printf("%d ",s->r[i].key);
        printf("\n");
         */
    }
}

int main()
{
    SqList L=init_sqlist();
    SqList S=L;
    SqList S1=L;
	int i;
    
    //直接插人排序
    StraightInsertSort(&L);
    printf("直接插人排序:");
    for(i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
    
    //折半插入排序
    BinaryInsertsort(&S);
    printf("折半插入排序:");
    for(i=1;i<=L.length;i++)
        printf("%d ",S.r[i].key);
    printf("\n");
    
    //希尔排序
    int len=S1.length;
	int gaos[10];
    //int gaos[len];//vc6不支持这样写
	int t=0;
    printf("gaos[]增量(步长)：");
    for(i=0;len>1;i++)
    {
        gaos[i]=len/2;  //步长
        printf("%d ",gaos[i]);
        len/=2;
        t++;
    }
    printf("\n");
    ShellSort(&S1,gaos,t);
    printf("希尔排序：");
    for(i=1;i<=S1.length;i++)
        printf("%d ",S1.r[i].key);
    printf("\n");
	return 0;
}
/*
 
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
 直接插人排序:8 10 14 16 23 26 31 37 45 67
 折半插入排序:8 10 14 16 23 26 31 37 45 67
 gaos[]增量(布长)：5 2 1
 希尔排序：8 10 14 16 23 26 31 37 45 67
 
排序相关算法
* 插入排序：
*   1.直接插入排序   稳定
*   2.折半插入排序   稳定
*   3.希尔排序      不稳定
* 快速排序:
*   4.冒泡排序      稳定
*   5.快速排序      不稳定
* 选择排序:
*   6.简单选择排序   不稳定
*   7.堆排序        不稳定
* 归并排序:
*   8.二路归并排序   稳定

 
 */
