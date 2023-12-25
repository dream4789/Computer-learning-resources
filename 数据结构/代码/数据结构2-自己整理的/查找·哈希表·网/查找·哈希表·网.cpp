//
//  main.c
//  查找·哈希表·网

#include <stdio.h>

#include <stdio.h>
#define MaxSize 100      //定义最大哈希表长度
#define NULLKEY -1       //定义空关键字值
#define DELKEY -2        //定义被删关键字值
typedef int KeyType;     //关键字类型
typedef char *InfoType;  //其他数据类型
typedef struct{
    KeyType key;        //关键字域
    InfoType data;      //其他数据域
    int count;          //探查次数域
}HashTable[MaxSize];    //哈希表类型

//将关键字k插入到哈希表中
int InsertHT(HashTable ha,int n,KeyType k,int p)
{
    int i,adr;
    adr = k%p;
    if (ha[adr].key==NULLKEY || ha[adr].key==DELKEY)  //x[j]可以直接放在哈希表中
    {
        ha[adr].key=k;
        ha[adr].count=1;
    }
    else      //发生冲突时,采用线性探查法解决冲突
    {
        i=1;  //i记录x[j]发生冲突的次数
        do
        {
            adr = (adr+1)%p;
            i++;
        } while (ha[adr].key!=NULLKEY && ha[adr].key!=DELKEY);
        ha[adr].key=k;
        ha[adr].count=i;
    }
    n++;
    return n;
}

//创建哈希表
void CreateHT(HashTable ha,KeyType x[],int n,int m,int p){
    int i,n1=0;
    for (i=0;i<m;i++)  //哈希表置初值
    {
        ha[i].key=NULLKEY;
        ha[i].count=0;
    }
    for(i=0;i<n;i++)
        InsertHT(ha,n1,x[i],p);
}

//在哈希表中查找关键字k
int SearchHT(HashTable ha,int p,KeyType k){
    int i=0,adr;
    adr = k%p;
    while (ha[adr].key!=NULLKEY && ha[adr].key!=k)
    {
        i++;             //采用线性探查法找下一个地址
        adr = (adr+1)%p;
    }
    if(ha[adr].key==k)  //查找成功
    {
        printf("  ha[%d].key=%d\n",adr,k);
        return adr;  //返回k所在位置
    }
    else                //查找失败
    {
        printf("  未找到%d\n",k);
        return -1;
    }
}

//删除哈希表中关键字k
int DeleteHT(HashTable ha,int p,int k,int n)
{
    int adr;
    adr = SearchHT(ha,p,k);
    if (adr!=-1)   //在哈希表中找到关键字
    {
        ha[adr].key=DELKEY;
        n--;       //哈希表长度减1
        return n;
    }
    else            //在哈希表中未找到该关键字
        return n;
}

//输出哈希表
void DispHT(HashTable ha,int n,int m)
{
    float avg=0;
    int i;
    printf(" 哈希表地址:\t");
    for(i=0;i<m;i++)
        printf(" %3d",i);
    printf("\n");
    printf(" 哈希表关键字:\t");
    for(i=0;i<m;i++)
    {
        if(ha[i].key==NULLKEY || ha[i].key==DELKEY)
            printf("    "); //输出4个空格
        else
            printf(" %3d",ha[i].key);
    }
    printf(" \n");
    printf(" 搜索次数:\t");
    for(i=0;i<m;i++)
    {
        if(ha[i].key==NULLKEY || ha[i].key==DELKEY)
            printf("    "); //输出4个空格
        else
            printf(" %3d",ha[i].count);
    }
    printf("\n");
    for(i=0;i<m;i++)
        if(ha[i].key!=NULLKEY && ha[i].key!=DELKEY)
            avg=avg+ha[i].count;
    avg=avg/n;
    printf(" 平均搜索长度ASL(%d)=%.3g\n",n,avg);

}

//查找成功时，平均查找长度
void CompASL(HashTable ha,int m)
{
    int i;
    int s=0,n=0;
    for (i=0;i<m;i++)
    {
        if(ha[i].key!=DELKEY && ha[i].key!=NULLKEY)
        {
            s=s+ha[i].count;
            n++;
        }
    }
    printf(" 查找成功的ASL=%.3g\n",s*1.0/n);
}
int main()
{
    int x[]={16,74,60,43,54,90,46,31,29,88,77};
    int n=11;  //元素个数
    int m=13,p=13,i;
    HashTable ha;
    
    int k=29;  //关键字k
    printf("建立哈希表:\n");
    CreateHT(ha,x,n,m,p);  //建立哈希表
    DispHT(ha,n,m);        //输出哈希表
    
    i=SearchHT(ha,p,k);    //查找关键字
    
    printf("\n删除关键字%d\n",k);
    n=DeleteHT(ha,p,k,n);  //删除关键字
    DispHT(ha,n,m);
    
    i=SearchHT(ha,p,k);    //查找关键字
    
    printf("\n插入关键字%d\n",k);
    n=InsertHT(ha,n,k,p);  //插入关键字
    DispHT(ha,n,m);
    
    printf("\n");
}
/*
 建立哈希表:
  哈希表地址:       0   1   2   3   4   5   6   7   8   9  10  11  12
  哈希表关键字:      77      54  16  43  31  29  46  60  74  88      90
  搜索次数:       2       1   1   1   1   4   1   1   1   1       1
  平均搜索长度ASL(11)=1.36
   ha[6].key=29

 删除关键字29
   ha[6].key=29
  哈希表地址:       0   1   2   3   4   5   6   7   8   9  10  11  12
  哈希表关键字:      77      54  16  43  31      46  60  74  88      90
  搜索次数:       2       1   1   1   1       1   1   1   1       1
  平均搜索长度ASL(10)=1.1
   未找到29

 插入关键字29
  哈希表地址:       0   1   2   3   4   5   6   7   8   9  10  11  12
  哈希表关键字:      77      54  16  43  31  29  46  60  74  88      90
  搜索次数:       2       1   1   1   1   4   1   1   1   1       1
  平均搜索长度ASL(11)=1.36
 */
