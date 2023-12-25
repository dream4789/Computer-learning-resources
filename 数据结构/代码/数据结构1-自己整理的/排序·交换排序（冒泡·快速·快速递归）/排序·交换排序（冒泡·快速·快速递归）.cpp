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

void BubbleSort(SqList * s)
{//对顺序表 s 作冒泡排序
    int i,j;
    for(i=1;i<=s->length-1;i++)  //进行 n-1 趟排序
        for(j=2;j<=1+s->length-i;j++)
            if(s->r[j].key < s->r[j-1].key)  //S->r[j]与s->r[j-1]交换
            {
                s->r[0]=s->r[j];
                s->r[j]=s->r[j-1];
                s->r[j-1]=s->r[0];
            }
}

//一趟快速排序
int QuickSort1(SqList* s,int low,int high)
{//交换顺序表 S中子表 r[lowhigh」的记录,使轴值(支点)记录到位,并返回其所在位置
//此时,在它之前(后)的记录均不大(小)于它
    KeyType pivotkey;
    s->r[0]=s->r[low];  //以子表的第一个记录作为轴值(支点)记录
    pivotkey=s->r[low].key;  //取轴值(支点)记录关键字
    while(low<high)  //从表的两端交替地向中间扫描
    {
        while(low<high && s->r[high].key>=pivotkey)
            high--;
        s->r[low]=s->r[high];
        while(low<high && s->r[low].key<=pivotkey)
            low++;  //将比轴值(支点)记录小的交换到低端
        s->r[high]=s->r[low];  //将比轴值(支点)记录大的交换到高端
    }
    s->r[low]=s->r[0];  //轴值(支点)记录到位
    return low;  //返回轴值(支点)记录所在位置
}

//快速排序算法的递归
void QuickSort(SqList* s,int low,int high)  //递归形式的快速排序
{//对顺序表 s 中的子序列 r[low…high)作快速排序
    int pivotloc;
    if(low<high)
    {
        pivotloc=QuickSort1(s,low,high);  //将待排序序列一分为二
        QuickSort(s,low,pivotloc-1);  //对小于轴值序列实现递归排序
        QuickSort(s,pivotloc+1,high);  //对大于轴值序列实现递归排序
    }
}

int main()
{
    SqList L=init_sqlist();
    SqList S=L;
	int i;
    
    BubbleSort(&L);
    printf("冒泡排序：");
    for(i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
    
    QuickSort(&S, 1, S.length);
    printf("快速排序：");
    for(i=1;i<=L.length;i++)
        printf("%d ",S.r[i].key);
    printf("\n");
    
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
冒泡排序：8 10 14 16 23 26 31 37 45 67
快速排序：8 10 14 16 23 26 31 37 45 67
 
 */
