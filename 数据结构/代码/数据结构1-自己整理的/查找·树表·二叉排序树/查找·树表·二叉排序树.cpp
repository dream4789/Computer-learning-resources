#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef int KeyType;
typedef struct
{
    KeyType key;
}DataType;
typedef struct BinSTreeNode
{
    DataType  elem;   //elem含有关键字域
    struct BinSTreeNode  *lchild;
    struct BinSTreeNode  *rchild;
}*BinSTree;

//二叉排序树查找算法
BinSTree BSTreeSearch(BinSTree t ,KeyType k )
{//在根指针为t的二叉排序树中查找关键字为k的结点，若查找成功，则返回指向该结点的指针；否则返回空指针
    if (t==NULL)
        return NULL;
    if (t->elem.key==k)
        return t; //查找成功,返回值t一直不能带出，可能是递归原因
    if (t->elem.key>k)
        BSTreeSearch(t->lchild ,k); //在左子树中查找
    else
        BSTreeSearch(t->rchild ,k); //在右子树中查找
    return NULL;//返回值一直为NULL
}
//查找
BinSTree BSTreeSearch1(BinSTree t ,KeyType k )
{//在上面的查找BSTreeSearch()中，返回值t一直不能带出，可能是递归原因，所以用了BSTreeSearch1()
    if (t==NULL)
    {
        printf("\n二叉树排序未查找到\n");//查找失败
        return NULL;
    }
    if (t->elem.key==k)
    {
        printf("\n二叉树排序查找到了: %d\n",t->elem.key);//查找成功
        return t;
    }
    if (t->elem.key>k)
        BSTreeSearch1(t->lchild ,k); //在左子树中查找
    else
        BSTreeSearch1(t->rchild ,k); //在右子树中查找
    return NULL;
}

//二叉排序树插入算法
BinSTree BSTreeInsert (BinSTree *t , KeyType k)
{//在二叉排序树中插入关键字为k的结点，*t指向二叉排序树的根结点
    BinSTree r;
    if (*t==NULL)
    {
        r=(BinSTree)malloc(sizeof(struct BinSTreeNode));
        r->elem.key=k;
        r->lchild=r->rchild=NULL;
        *t=r;     //若二叉排序树为空，被插结点作为树的根结点
        return *t;
    }
    else if(k<((*t)->elem.key))
        BSTreeInsert(&((*t)->lchild),k);  //插入到p的左子树中
    else
        BSTreeInsert(&((*t)->rchild),k);  //插入到p的右子树中
    return NULL;
}

//二叉排序树的结点删除算法
int BSTreeDelete (BinSTree bt , KeyType k)
{//在二叉排序树中删除关键字为k的结点，*bt指向二叉排序树的根结点。删除成功返回1，不成功返回0
    BinSTree f,p,q,s;
    p=bt;
    f=NULL;
    while (p&& p ->elem.key!=k)
    {
        f=p;         //f为指向结点*p的双亲结点的指针
        if (p->elem.key>k)
            p=p->lchild;   //搜索左子树
        else
            p=p->rchild;   //搜索右子树
    }
    if (p==NULL)
        return 0;    //找不到待删的结点时返回
    if (p->lchild==NULL)     //待删结点的左子树为空
    {
        if (f==NULL)     //待删结点为根结点
            bt=p->rchild;
        else if (f->lchild==p)  //待删结点是其父结点的左孩子
            f->lchild=p->rchild ;
        else             //待删结点是其父结点的右孩子
            f->rchild=p->rchild;
        free (p);
    }
    else     //待删结点有左子树
    {
        q=p;
        s=p->lchild;
        while(s->rchild)   //在待删结点的左子树中查找最右下结点
        {
            q=s;
            s=s->rchild;
        }
        if (q==p)       //将最右下结点的左子树链到待删结点上
            q->lchild=s->lchild;
        else
            q->rchild=s->lchild;
        p->elem.key=s->elem.key;
        free (s) ;
        return 1;
   }
    return 0;
}

void inorder1(BinSTree t)
{//中序遍历的递归算法
    if(t)
    {
        inorder1(t->lchild);
        printf("%d ",t->elem.key);
        inorder1(t->rchild);
    }
}

int main()
{
    BinSTree t=NULL,r=NULL;
    int i,j=0;
    int a[10],b[10];
    
    srand((unsigned)time(NULL));
    int randnum=rand()%9+1;  //从 1 到（9+1-1）的随机数
    printf("二叉排序树要查找的数在第 %d 位\n",randnum);
    
    printf("二叉排序树要排序的数为：");
    for(i = 0; i<10;i++)
    {
        a[i]=rand()%90+10;  //产生随机数
        b[i]=a[i];
        printf("%d ",a[i]);
    }
    
    //二叉树插入，中序遍历，顺序输出
    for(i=0;i<10;i++)
    {
        if(j==0)  //只运行一次，记录根结点r
        {
            r=BSTreeInsert(&t, a[i]);
            j++;
        }
        else
            t=BSTreeInsert(&r, a[i]);  //t为插入时所在结点，没用处
        //printf("\n");  //分析行
        //inorder1(r);  //分析行
    }
    printf("\n二叉排序树排序结果为：");
    inorder1(r);
    
    //查找结点
    BSTreeSearch1(r, a[randnum]);
    
    //删除结点
    BSTreeDelete(r, a[randnum]);
    printf("二叉排序树删除 %d 为：",a[randnum]);
    inorder1(r);
    
    //查找结点
    BSTreeSearch1(r, a[randnum]);
    return 0;
}
/*
 
 二叉排序树要查找的数在第 8 位
 二叉排序树要排序的数为：57 10 43 23 45 59 37 97 53 41
 二叉排序树排序结果为：10 23 37 41 43 45 53 57 59 97
 二叉树排序查找到了: 53
 二叉排序树删除 53 为：10 23 37 41 43 45 57 59 97
 二叉树排序未查找到
 
 */
