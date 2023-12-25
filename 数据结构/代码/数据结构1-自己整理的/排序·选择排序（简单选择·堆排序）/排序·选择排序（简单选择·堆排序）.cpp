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

//简单选择排序
void SelectSort(SqList * s)
{
    int i,j,t;
    DataType tmp;
    for(i=1;i<s->length;i++)  //作 S->length-1 趟选取
    {
        for(j=i+1,t=i;j<=s->length;j++)
        {//在i开始的 length-i+1条待排序记录中选关键字最小的记录*1
            if(s->r[t].key>s->r[j].key)
            t=j;  //t中存放关键字最小的记录下标
        }
        tmp=s->r[t];
        s->r[t]=s->r[i];
        s->r[i]=tmp;  //关键字最小的记录与第 i条记录交换
    }
}

//大顶堆
void HeapAdjust(SqList* s,int n,int len)
{//S->r[n…len]中的记录关键字除 r[n]外均满足堆的定义,本函数将对第 n个结点为根的子树筛选,使其成为大顶堆
    int j;
    DataType rc=s->r[n];  //先对操作位置上的结点数据进行保存，放置后序移动元素丢失。
    for(j=2*n;j<=len;j=j*2)  //沿关键字较大的孩子结点向下筛选
    {
        if(j<len && s->r[j].key < s->r[j+1].key)
            j++;  //如果当前结点比最大的孩子结点的值还大，跳过
        if(rc.key > s->r[j].key)  //rc应插入在位置i上
            break;
        s->r[n]=s->r[j];
        n=j;  //使n结点满足堆定义
    }
    s->r[n]=rc;
    /*
    for(j=1;j<=s->length;j++)//分析行
        printf("%d ",s->r[j].key);
    printf("\n");
	*/
}
    
//堆排序实质上是对无序序列不断建堆和调整堆的过程
//堆排序算法
void HeapSort(SqList *s)
{
    int i;
    DataType tmp;
    for(i=s->length/2;i>0;i--)  //将r[1..length]建成堆
        HeapAdjust(s,i,s->length);
    //printf("\n");  //分析行
    for(i=s->length;i>1;i--)  //将大顶堆改成小顶堆
    {
        tmp=s->r[1];  //堆顶与堆底元素交换,将最大元素移到后面
        s->r[1]=s->r[i];
        s->r[i]=tmp;
        HeapAdjust(s,1,i-1);  //将r[1..i-1]重新调整为堆
    }
}

int main()
{
    SqList L=init_sqlist();
    SqList S=L;
	int i;
    
    SelectSort(&L);
    printf("简单选择排序：");
    for(i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
    
    HeapSort(&S);
    printf("堆排序-大顶堆：");
    for(i=1;i<=S.length;i++)
        printf("%d ",S.r[i].key);
    printf("\n");
    
    return 0;
}
/*

输入串长：5
输入串的元素：
5
12
9
23
18
简单选择排序：5 9 12 18 23
堆排序-大顶堆：5 9 12 18 23


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
*/
