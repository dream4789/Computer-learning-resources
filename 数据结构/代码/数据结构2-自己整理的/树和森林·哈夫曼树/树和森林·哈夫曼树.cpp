//
//  main.c
//  树和森林·哈夫曼树
//

#include <stdio.h>

#include <stdlib.h>
#define N 20

typedef int DataType;

typedef struct{//哈夫曼树结点类型定义
    char ch;
    DataType weight;
    int lchild,rchild,parent;
}Htnode;

//Htnode huffTree[];//采用静态链表存储哈夫曼树

typedef struct{//叶编码类型
    char *code;
    char leaf;
    int length;
}CodeType;

//CodeType cd[];//一维数组存储编码

void selectsort(Htnode huftree[],int n,int *s1,int *s2)
{
    int i,min1,min2;//两个最小数
    min1=huftree[0].weight;
    min2=huftree[0].weight;
    *s1=0;
    for(i=1;i<=n;i++)
    {
        if(huftree[i].parent==-1&&huftree[i].weight<min1)
        {//如果节点未被构建树,并且小于最小值,则更新最小值*/
            min1=huftree[i].weight;
            *s1=i;
        }
        else//为下边求另一个最小值赋初值*/
        {
            min2=huftree[i].weight;
            *s2=i;
        }
    }/*end for*/
    for(i=1;i<=n;i++)
    {
        if(huftree[i].parent==-1&&huftree[i].weight<min2&&huftree[i].weight>= min1&&*s1!=i)
        /*如果节点未被构建树,并且小于最小值,并且大于第一个最小值,*/
        /*并且在数组中的下标不等于第一个最小值,则更新最小值*/
        {
            min2 = huftree[i].weight;
            *s2 = i;
        }
    }/*end for*/
}

void Hufcoding(Htnode huftree[],CodeType cd[],int w[],int n)
{//哈夫曼树存放在静态链表huftree中,w存放结点权重,n是叶子个数,最后的编码放在cd[]
    int i,k,s1,s2,m,f,c,sum;
    char temp[N];   //暂存叶子编码字符串，最后需要转置
    m=2*n-1;     //计算哈夫曼树的结点总数
    for(i=1;i<=n;i++)  //初始化每个叶子结点自成一 棵树
    {
        huftree[i].weight=w[i-1];
        huftree[i].lchild=huftree[i].rchild=huftree[i].parent=-1;
        //huftree[i].ch=getch();
    }
    for(i=n+1;i<=m;i++)  //初始化非叶子结点
    {
        huftree[i].weight=-1;
        huftree[i].lchild=huftree[i].rchild=huftree[i].parent=-1;
    }
    for(i=1;i<=n-1;i++)  //生成n-1个非叶子结点的循环
    {
        selectsort(huftree,n+i-1,&s1,&s2);
        //对数组 huftree[1..n+i-1]中无双亲的结点权值进行排序，s1,s2将是无双亲且权重最小的两个结点下标
        sum=huftree[s1].weight+huftree[s2].weight;//求和,构造父节点
        huftree[n+i].weight=sum;
        huftree[s1].parent=huftree[s2].parent=n+i;//最小的两个节点的父节点的数组的下标
        huftree[n+i].lchild=s1;//父节点的左孩子下标
        huftree[n+i].rchild=s2;//父节点的右孩子下标
    }
    for(i=1;i<=n;i++)     //开始求每个叶子结点的编码
    {
        c=0;
        for (k=i,f=huftree[i].parent;f!=-1;k=f,f=huftree[f].parent)
        {
            if (huftree[f].lchild==k)
            {
                temp[c]='0' ;
                c++;
            }
            else
            {
                temp[c]='1';
                c++;
            }    //左分枝是0右分枝是1
        }
        cd[i].code=(char *)malloc(c+1);  //产生存储编码的空间
        cd[i].code[c]='\0';
        c--;
        k=0;
        while (c>=0)
            cd[i].code[k++]=temp[c--]; //将temp转置到cd中
        cd[i].leaf=huftree[i].ch;
        cd[i].length=k;
    }
}

/*功能:求哈夫曼树中各个节点的编码*/
/*传入参数:树huftree[],节点个数n,编码数组cd[]*/
void HuftreeCode(Htnode huftree[], CodeType cd[], int n)
{
    int i,c,f,k;
    char temp[N];/*暂存叶子编码字符串,最后需要转置*/
    for(i=1;i<=n;i++)/*开始求每个叶子结点的编码*/
    {
        c = 0;
        for(k=i,f=huftree[i].parent;f!=-1;k=f,f=huftree[f].parent)
            if(huftree[f].lchild == k)/*左分支是0*/
                temp[c++]='0';
            else
                temp[c++]='1';/*右分支是1*/
        cd[i].code=(char *)malloc(c+1); /*产生存储编码的空间*/
        cd[i].code[c--]='\0';
        k = 0;
        while(c>=0)
            cd[i].code[k++]=temp[c--];//将temp转置到cd中*/
        //cd[i].leaf=huftree[i].ch;
        cd[i].length=k;
    }
}

int main()
{
    Htnode huftree[2*N];   //夫曼树的数组
    CodeType cd[N];    //节点的编码数组
    int w[N],n,i,temp,sum=0;  //节点的临时存放及节点的个数
    printf("输入带权节点的个数:");  //输入带权节点的个数
    scanf("%d",&n);
    if(n < N)
    {
        A:printf("输入带权值的数:\n");   //输入带权值的数
        for(i = 1; i <= n; i++)
        {
            scanf("%d",&temp);
            w[i-1] = temp;
        }
        Hufcoding(huftree,cd,w,n);  //创建哈夫曼树
        printf("HuftreeCode每个节点的编码:\n");  //打印每个节点的编码
        HuftreeCode(huftree, cd, n);
        for(i = 1; i <= n; i++)
        {
            printf("%d 的 HuftreeCode 节点的编码:",huftree[i].weight);
            puts(cd[i].code);
        }
        printf("Huftree 带权路径长度:\n");   //打印WPL(带权路径长度)
        for(i = 1; i <= n; i++)
        {
            printf("%d * %d + ",huftree[i].weight,cd[i].length);
            sum += huftree[i].weight * cd[i].length;
        }
        printf("0 = %d\n",sum);
    }
    else
    {
        printf("输入错误！\n");
        goto A;
    }
}

/*
 输入带权节点的个数:5
 输入带权值的数:
 1
 2
 3
 4
 5
 HuftreeCode每个节点的编码:
 1 的 HuftreeCode 节点的编码:010
 2 的 HuftreeCode 节点的编码:011
 3 的 HuftreeCode 节点的编码:00
 4 的 HuftreeCode 节点的编码:10
 5 的 HuftreeCode 节点的编码:11
 Huftree 带权路径长度:
 1 * 3 + 2 * 3 + 3 * 2 + 4 * 2 + 5 * 2 + 0 = 33
 */
