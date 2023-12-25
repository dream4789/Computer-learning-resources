//
//  main.c
//  二叉树·应用举例·基本操作
//

#include <stdio.h>
#include <stdlib.h>
#define maxsize 100

typedef char datatype;
int count=0;//全局变量

typedef struct tnode{
    datatype data;
    struct tnode *lchild;
    struct tnode *rchild;
}Tnode,*bintree;


bintree create(void)
{//构造二叉链表创建二叉树,以加入空结点的先序序列输入
    bintree t;
    datatype ch;
    ch=getchar();
    if(ch=='#')   //读入#时,将相应结点指针置空
        t=NULL;
    else
    {
        t=(bintree)malloc(sizeof(Tnode));//生成结点空间
        t->data=ch;
        t->lchild=create();//构造二叉树的左子树
        t->rchild=create();//构造二叉树的右子树
    }
    return (t);
}

int count_tree(bintree t)
{//求二叉树的结点个数,中序思路
    if(t==NULL)
        return 0;
    if(t)
    {
        count_tree(t->lchild);
        count++;
        count_tree(t->rchild);
    }
    return count;
}

int Count(bintree t)
{//求二叉树的结点个数,后序思路
    int lcount,rcount;
    if (t==NULL)
        return 0;
    lcount=Count(t->lchild);     //求左子树的结点个数
    rcount=Count(t->rchild);     //求右子树的结点个数
    return  lcount+rcount+1;
}

int high(bintree t)
{//求二叉树高度，后序思路
    int l,r;
    if(t==NULL)
        return 0;
    else
    {
        l=high(t->lchild);//左子树高度
        r=high(t->rchild);//右子树高度
        if(l>r)
            return l+1;
        return r+1;
    }
}

bintree CopyTree(bintree  t)
{//复制二叉树算法
    bintree p,q,s;
    if (t==NULL)
        return NULL;
    p=CopyTree(t->lchild);    /*复制左子树*/
    q=CopyTree(t->rchild);    /*复制左子树*/
    s=(bintree)malloc(sizeof(Tnode));  /*复制根结点*/
    s->data=t->data;
    s->lchild=p;
    s->rchild=q;
    return s;
}

void Levcount(bintree t,int L,int num[])
{//求二叉树每层结点数算法,先序思路
    //求链式存储的二叉树t中每层结点个数L表示当前t所指结点的层次，当t初值为根时，L初值为1，num数组元素初始化0
    if(t)
    {
        printf("%c",t->data); //访问当前结点
        num[L]++;  //当前t所指结点的层次数增加1
        Levcount(t->lchild, L+1, num); //递归左子树
        Levcount(t->rchild, L+1, num); //递归右子树
     }
 }


int main(int argc, const char * argv[])
{
    printf("请输入二叉树：");
    bintree t=create(),s;
    printf("该二叉树结点个数为(中序思路)：%d\n",count_tree(t));
    printf("该二叉树高度为(后序思路)：%d\n",Count(t));
    printf("该二叉树高度为(后序思路)：%d\n",high(t));
    s=CopyTree(t);
    int num[10]={0};
    printf("二叉树每层结点数算法(先序思路):");
    Levcount(s, 1, num);
    printf("\n");
    return 0;
}

/*
 
测试数据：
ABDH###E##CF##G##
1248###5##36##7##
1248##9##50###36##7##
 
 
 请输入二叉树：1248##9##50###36##7##
 该二叉树结点个数为(中序思路)：10
 该二叉树高度为(后序思路)：10
 该二叉树高度为(后序思路)：4
 二叉树每层结点数算法(先序思路):1248950367
 
 */
