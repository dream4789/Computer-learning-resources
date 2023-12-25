//  查找·线性表（顺序·前哨·折半·分块）
//
//

#include <stdio.h>
#include <stdlib.h>
#define maxsize 100    //查找表最大长度
typedef int  KeyType;  //整型

//顺序，前哨，折半
typedef struct
{
    KeyType key;
}DataType;

typedef struct
{
    DataType r[maxsize];  //数据元素存储空间
    int length;  //表的长度
}Sqlist;

//分块
#define MAXL 100     //顺序表的最大长度
#define MAXI 20      //索引表的最大长度
typedef int KeyType;

typedef struct
{
    KeyType key;  //顺序表数据
}NodeType;
typedef NodeType SeqList[MAXL];  //顺序表
typedef struct
{
    KeyType key;  //索引表最大关键字
    int link;  //每块的起始下标
}IdxType;
typedef IdxType IDX[MAXI];   //索引表

void init_Idxtype(SeqList R,IDX I)  //分块处理
{
    int a[]={8,14,6,9,10,22,34,18,19,31,40,38,54,66,46,71,78,68,80,85,100,94,88,96,87};
    for(int i=0;i<25;i++)    //建立顺序表
        R[i].key=a[i];
    //  8   <14>  6   9    10       0  -> 4
    //  22   34   18  19  <31>      5  -> 9
    //  40   38   54 <66>  46       10 -> 14
    //  71   78   68  80  <85>      15 -> 19
    // <100> 94   88  96   87       20 -> 24
    I[0].key=14;I[0].link=0;  //开始分块
    I[1].key=34;I[1].link=5;
    I[2].key=66;I[2].link=10;
    I[3].key=85;I[3].link=15;
    I[4].key=100;I[4].link=20;
}

Sqlist init_strlist(void)
{//创建查找表
    Sqlist *s;
    s=(Sqlist *)malloc(sizeof(Sqlist));
    printf("输入此线性表长度（前哨长度+1）：");
    scanf("%d",&s->length);
    printf("输入此线性表元素：\n");
    for(int i=0;i<s->length;i++)
        scanf("%d",&s->r[i].key);
    return *s;
}

//顺序查找算法
int SeqSearch(Sqlist s,KeyType k)
{//在表s中顺序查找关键字k，若查找成功，则函数值为该元素在表中的位置，若查找失败，返回-1
    int i;
    for(i=0;i<s.length;i++)
        if(s.r[i].key==k)
            return i;   //查找成功
    return -1;   //查找失败
}

//带前哨站的顺序查找改进算法
int SeqSearch_gai(Sqlist s,KeyType k)
{
    s.length+=1; // 让s.length长度加1，当前哨
    int i=0,n;
    n= s.length;
    s.r[n].key=k;   //设置前哨站，要多开辟一个存储空间
    while(s.r[i].key!=k)  //从表首开始向后扫描
        i++;
    return i;
}

//折半查找算法
int BinSearch(Sqlist s , KeyType k)
{//在表s中用折半查找法查找关键字k，若查找成功，则函数值为该元素在表中的位置，若查找失败，返回-1
    int low,mid,high;
    low = 0;
    high = s.length-1;
    while(low<=high)
    {
        mid=(low+high)/2;       //取区间中点
        if (s.r[mid].key==k)
            return mid;      //查找成功
        else if (s.r[mid].key>k)
            high=mid-1;       //在左区间中查找
        else
            low=mid+1;        //在右区间中查找
     }
    return -1;   //查找失败
}

//折半查找——递归算法
int BinSearch1(Sqlist s, KeyType k, int low, int high)
{//在表s中用折半查找法查找关键字k，若查找成功，则函数值为该元素在表中的位置，若查找失败，返回-1
    int mid;
    while(low <= high)
    {
        mid=(low+high)/2;       //取区间中点
        if(s.r[mid].key==k)
            return mid;      //查找成功
        else if(s.r[mid].key>k)
            return BinSearch1(s, k, low, mid-1);  //在左区间中查找
        else
            return BinSearch1(s, k, mid+1, high);  //在右区间中查找
     }
    return -1;   //查找失败
}

int IdxSearch(IDX I,int m,SeqList R,int n,KeyType k)
{//分块查找算法， m 为分块的数量，n 为顺序表数据的个数
    int low=0,high=m-1,mid,i;
    int b=n/m;     //b为每块数据的个数
    
    //在索引表中进行二分查找,找到存放在的对应分块
    printf("1.二分查找key在哪一分块：\n");
    while (low<=high)
    {
        mid=(low+high)/2;
        //printf("在 %d -> %d 分块中比较元素R[%d]:%d\n",low+1,high+1,mid,R[mid-1].key);
        if (I[mid].key>=k)
            high=mid-1;
        else
            low=mid+1;
    }
    if (low<m)//在索引表中查找成功后,再在线性表中进行顺序查找
    {
        printf("   该 key=%d 在索引表的第 %d 分块中\n",k,low+1);
        i=I[low].link-1;
        printf("2.顺序查找key在分块的第几个：\n");
        printf("   该分块的数据为：");
        while (i<=I[low].link+b-1 && R[i].key!=k)
        {
            i++;
            printf("%d ",R[i].key);
        }
        printf("\n   该 key=%d 在顺序表的第 %d 位\n",k,i);
        if (i<=I[low].link+b-1)
            return i;
        else
            return -1;
    }
    return -1;
}

int main(int argc, const char * argv[])
{

    Sqlist str1=init_strlist();  //正常创建
    //Sqlist str2=init_strlist();  //多创建一个空间

    int key;
    printf("输入你想查找的key：");
    scanf("%d",&key);
    
    printf("顺序查找 %d 在第 %d 位\n",key,SeqSearch(str1, key)+1);     //无前哨，顺序查找
    printf("前哨顺序查找 %d 在第 %d 位\n",key,SeqSearch_gai(str1, key)+1);    //有前哨
    
    printf("循环——折半查找 %d 在第 %d 位\n",key,BinSearch(str1, key)+1);    //循环——折半查找
    printf("递归——折半查找 %d 在第 %d 位\n",key,BinSearch1(str1, key, 0, str1.length)+1);   //递归——折半查找

    
    printf("\n分块查找:\n");
    
    KeyType k=46;  //分块查找要查找的元素k
    SeqList R;     //定义顺序表
    IDX I;         //定义索引表
    int i;
    init_Idxtype(R,I);   //初始化索引表，对顺序表进行分块处理
    if((i=IdxSearch(I,5,R,25,k))!=-1)
        printf("\n分块查找 key=%d 在第 %d 位\n",k,i);
    else
        printf("\n分块查找 key=%d 不在表中\n",k);
    printf("\n");

    
}
/*
 
 输入此线性表长度（前哨长度+1）：5
 输入此线性表元素：
 1
 2
 3
 4
 5
 输入你想查找的key：4
 顺序查找在第 4 位
 前哨顺序查找在第 4 位
 循环——折半查找在第 4 位
 递归——折半查找在第 4 位
 
 分块查找:
 1.二分查找key在哪一分块：
    该 key=46 在索引表的第 3 分块中
 2.顺序查找key在分块的第几个：
    该分块的数据为：40 38 54 66 46
    该 key=46 在顺序表的第 14 位

 分块查找 key=46 在第 14 位
 
 */
