#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef struct
{
    KeyType key;
}DataType;

typedef struct AVLNode
{
    DataType elem;  //elem含有关键字域
    int bf;         //bf记录平衡因子
    struct AVLNode *lchild;
    struct AVLNode *rchild;
}AVLNode,*AVLTree;

//LL型调整代码
AVLTree LL_Rotate(AVLTree a)
{//对以a为当前结点的最小不平衡子树进行LL型调整
    AVLTree b;
    b=a->lchild;   //b指向a的左子树根结点
    a->lchild=b->rchild; //b的右子树挂接为a的左子树
    b->rchild=a;
    a->bf=b->bf=0;//调整结点的平衡因子
    return(b);
}

//RR型调整代码
AVLTree RR_Rotate(AVLTree a)
{//对以a为当前结点的最小不平衡子树进行RR型调整
    AVLTree b;
    b=a->rchild;          //b指向a的右子树根结点
    a->rchild=b->lchild;  //b的左子树挂接为a的右子树
    b->lchild=a;
    a->bf=b->bf=0;        //调整结点的平衡因子
    return b;
}

//LR型调整代码
AVLTree LR_Rotate(AVLTree a)
{   //对以a为当前结点的最小不平衡子树进行LR型调整
    AVLTree b,c;
    b=a->lchild;
    c=b->rchild;
    a->lchild=c->rchild;  // c的右子树挂接为a的左子树
    b->rchild=c->lchild;  // c的左子树挂接为b的右子树
    c->lchild=b;
    c->rchild=a;
    if (c->bf==1)         // 调整结点的平衡因子
    {
        a->bf=-1;
        b->bf=0;
    }
    else if (c->bf==-1)
    {
        a->bf=0;
        b->bf=1;
    }
    else
        a->bf=b->bf=0;
    c->bf=0;
    return(c);
}

//RL型调整代码
AVLTree RL_Rotate(AVLTree a)
{// 对以a为当前结点的最小不平衡子树进行RL型调整
    AVLTree b,c;
    b=a->rchild;
    c=b->lchild;
    a->rchild=c->lchild;      //c的左子树挂接为a的右子树
    b->lchild=c->rchild;      //c的右子树挂接为b的左子树
    c->lchild=a;              //c指向a的左子树根结点
    c->rchild=b;              //c指向b的右子树根结点
    if (c->bf==1)             //调整结点的平衡因子
    {
        a->bf=0;
        b->bf=-1;
    }
    else if (c->bf==-1)
    {
        a->bf=1;
        b->bf=0;
    }
    else
        a->bf=b->bf=0;
    c->bf=0;
    return(c);
}

//AVL平衡二叉树 查找 和 插入 算法
void AVLInsert(AVLTree *pavlt,AVLTree s)
{//将结点 s 插入到以 *pavlt 为根结点的平衡二叉排序树中
    AVLTree f,a,b,p,q;
    if(*pavlt==NULL)   //AVL 树为空
    {
        *pavlt=s;
        return;
    }
    a=*pavlt;
    f=NULL;  //指针a记录离*s最近的平衡因子不为0的结点,f指向*a的父结点
    p=*pavlt;
    q=NULL;
    while(p!=NULL)    //寻找插人结点的位置及最小不平衡子树
    {
        if(p->elem.key == s->elem.key)
            return;   //AVL树中已存在该关键字
        if(p->bf!=0)  //寻找最小不平衡子树
        {
            a=p;
            f=q;
        }
        q=p;
        if(s->elem.key < p->elem.key)
            p=p->lchild;
        else
            p=p->rchild;
    }
    if(s->elem.key < q->elem.key)
        q->lchild=s; //将结点*s插入到合适的位置上去
    else
        q->rchild=s;
    p=a;
    while(p!=s)      //插人结点后,修改相关结点的平衡因子
    {
        if(s->elem.key < p->elem.key)
        {
            p->bf++;
            p=p->lchild;
        }
        else
        {
            p->bf--;
            p=p->rchild;
        }
    }
    if(a->bf > -2 && a->bf < 2)
        return;              //插人结点后,没有破坏树的平衡性
    if(a->bf==2)
    {
        b=a->lchild;
        if(b->bf==1)         //结点插在*a的左孩子的左子树中
            p=LL_Rotate(a);        //LL 型调整
        else                 //结点插在*a的左孩子的右子树中
            p=LR_Rotate(a);        //LR 型调整
    }
    else
    {
        b=a->rchild;
        if(b->bf==1)         //结点插在*a的右孩子的左子树中
            p=RL_Rotate(a);        //RL 型调整
        else                 //结点插在*a的右孩子的右子树中
            p=RR_Rotate(a);        //RR 型调整
    }
    if(f==NULL)              //原*a是AVL树的根
        *pavlt=p;
    else if(f->lchild==a)    //将新子树链到原结点*a的双亲结点上
        f->lchild=p;
    else
        f->rchild=p;
}

int main()
{
    printf("看不懂～～\n");
    return 0;
}
