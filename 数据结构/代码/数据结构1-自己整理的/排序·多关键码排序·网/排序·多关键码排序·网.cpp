#include <stdio.h>
#include <stdlib.h>

#define RADIX 101 //基数，分数有 101 种可能
#define K 3 //关键字，有 3 个关键字

struct tagMark
{
    int key[K]; //有 K 个关键字
}a[8]={
    {1,2,3},
    {0,2,3},
    {5,4,6},
    {6,2,6},
    {4,4,1},
    {0,1,4},
    {60,30,6},
    {60,20,6}};

/*
 a：待排序的数组地址
 size：元素数量
 radix：基数
 k：关键字数量
 */

void LSDSort(struct tagMark *a, int size,int k)
{//最次位优先
    int i;
    struct tagMark *tmp=(struct tagMark *)malloc(sizeof(struct tagMark) *size); //待排序的记录的数量
    while (k--)
    {
        int cnt[RADIX]={0};
        //计数
        for(i=size;i>0;)
            ++cnt[a[--i].key[k]];
        //累加cnt
        for(i=0;i<RADIX;i++)
            cnt[i+1]+=cnt[i];
        //按顺序把a[i]放入tmp中
        for(i=size;i>0;)
        {
            --i;
            tmp[--cnt[a[i].key[k]]] = a[i];
        }
        //把a[i]按照某一位排好的序，重新排序
        for(i=size;i>0;)
        {
            --i;
            a[i] = tmp[i];
        }
    }
}

int main()
{
    int i, j;
    LSDSort(a, 8, K); //对8个记录进行排序
    for(i=0;i<8;i++)
    {
        for(j=0;j<K;j++)
            printf("%d ",a[i].key[j]);
        printf("\n");
    }
    return 0;
}
/*
可能运行不了，不知道为什么
输出：
0 1 4 
0 2 3 
1 2 3 
4 4 1 
5 4 6 
6 2 6 
60 20 6 
60 30 6 
*/