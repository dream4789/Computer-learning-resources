//
//二叉树·遍历·全
//
#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>  //一般stdbool.h头文件中，函数bool开头，返回值为1或0，false或true
#define maxsize 100

typedef char datatype;

int count=0;//全局变量

typedef struct tnode{//二叉树定义，递归遍历
    datatype data;
    struct tnode *lchild;
    struct tnode *rchild;
}tnode,*bintree;

typedef struct snode{//顺序栈定义,非递归遍历
    bintree data[maxsize];
    int top;
}seqstack,*pseqstack;

typedef struct qnode{//顺序队列定义，层次遍历
    bintree data[maxsize];
    int front;
    int rear;
}seqqueue,*pseqqueue;


//*******二叉树部分********//
bintree create(void)
{//构建二叉树
    bintree t;
    datatype ch;
    ch=getchar();
    if(ch=='#')
        t=NULL;
    else
    {
        t=(bintree)malloc(sizeof(tnode));
        t->data=ch;
        t->lchild=create();
        t->rchild=create();
    }
    return t;
}

//*******顺序栈部分********//
pseqstack init(void)
{//创建顺序栈
    pseqstack s;
    s=(pseqstack)malloc(sizeof(seqstack));
    if(s)
        s->top=-1;
    return s;
}
bool empty(pseqstack s)
{//判断栈是否为空
    if(s->top==-1)
        return 1;
    else
        return 0;
}
bool push(pseqstack s,bintree x)
{//栈顶插入新元素x
    if(s->top==maxsize-1)
        return 0;//栈满无法入栈
    else
    {
        s->top++;
        s->data[s->top]=x;
        return 1;
    }
}
bool pop(pseqstack s,bintree *x)
{//删除栈顶元素，并保存在*x
    if(empty(s))
        return 0;//栈空不能出栈
    else
    {
        *x=s->data[s->top];
        s->top--;
        return 1;
    }
}

//*******队列部分********//
pseqqueue initqueue(void)
{//初始化队列
    pseqqueue q;
    if (!(q=(pseqqueue)malloc(sizeof(seqqueue))))
    {
        printf("内存分配失败！");
        exit(-1);
    }
    q->front=q->rear=-1;
    return q;
}
bool emptyqueue(pseqqueue q)
{//队列判空
    if(q->front==q->rear)
        return 1;//队空
    return 0;
}
bool inqueue(pseqqueue q,bintree t)
{//入队
    if(q->rear==maxsize-1)
        return 0;//队满
    q->rear++;
    q->data[q->rear]=t;
    return 1;
}
bool outqueue(pseqqueue q,bintree *t)
{//出队
    if(q->front==q->rear)
        return 0;
    q->front++;
    *t=q->data[q->front];
    return 1;
}

//*******遍历部分********//
void perorder1(bintree t)
{//先序遍历的递归算法
    if(t)
    {
        printf("%c ",t->data);
        perorder1(t->lchild);
        perorder1(t->rchild);
    }
}
void inorder1(bintree t)
{//中序遍历的递归算法
    if(t)
    {
        inorder1(t->lchild);
        printf("%c ",t->data);
        inorder1(t->rchild);
    }
}
void postorder1(bintree t)
{//后序遍历的递归算法
    if(t)
    {
        postorder1(t->lchild);
        postorder1(t->rchild);
        printf("%c ",t->data);
    }
}

void preorder2(bintree t)
{//栈的先序遍历的非递归算法
    pseqstack s;
    bintree p=t;
    s=init();
    while (p||!empty(s))
    {
        if(p)
        {
            push(s,p);
            printf("%c ",p->data);
            p=p->lchild;
        }
        else
        {
            pop(s,&p);
            p=p->rchild;
        }
    }
}
void inorder2(bintree t)
{//栈的中序遍历的非递归算法
    pseqstack s;
    bintree p=t;
    s=init();
    while (p||!empty(s))
    {
        if(p)
        {
            push(s,p);
            p=p->lchild;
        }
        else
        {
            pop(s,&p);
            printf("%c ",p->data);
            p=p->rchild;
        }
    }
}
void postorder2(bintree t)
{//栈的后序遍历的非递归算法
    pseqstack s1;//最终结果栈
    pseqstack s2;//辅助栈
    bintree p=t;
    s1=init();
    s2=init();
    while (p||!empty(s2))
    {
        if(p)
        {
            push(s1,p);
            push(s2,p);
            p=p->rchild;
        }
        else
        {
            pop(s2,&p);
            p=p->lchild;
        }
    }
    while (!empty(s1))
    {
        pop(s1,&p);
        printf("%c ",p->data);
    }
}

void preorder3(bintree t)
{//先序非递归-“栈”
    bintree p=t;
    bintree s[maxsize];
    int top=-1;
    do{
        while(p){
            top++;
            s[top]=p;//保留当前 p 结点在栈 s 中
            printf("%c ",p->data);
            p=p->lchild;//转到当前 p 结点的左孩子
        }
        p=s[top];//取 p 的上一个结点
        top--;//“头指针”减 1
        p=p->rchild;//转到当前 p 结点的右孩子
    }while(top!=-1||p);
}
void inorder3(bintree t)
{//中序非递归-“栈”
    bintree p=t;
    bintree s[maxsize];
    int top=-1;
    do{
        while (p)
        {
            top++;
            s[top]=p;//保留当前 p 结点在栈 s 中
            p=p->lchild;//转到当前 p 结点的左孩子
        }
        p=s[top];//取 p 的上一个结点
        top--;//“头指针”减 1
        printf("%c ",p->data);
        p=p->rchild;
    }while(top!=-1||p);
}
void postorder3(bintree t)
{//后序非递归-“栈”
    bintree p=t;
    bintree s1[maxsize];//最终结果栈
    bintree s2[maxsize];//辅助栈
    int top1=-1;
    int top2=-1;
    do{
        while (p){
            top1++;
            top2++;
            s1[top1]=p;//保留当前 p 结点在栈 s1 中
            s2[top2]=p;//保留当前 p 结点在栈 s2 中
            p=p->rchild;//转到当前 p 结点的左孩子
        }
        p=s2[top2];//取 p 的上一个结点
        top2--;//“头指针”减 1
        p=p->lchild;//转到当前 p 结点的左孩子
    }while(top2!=-1||p);
    while (top1!=-1)
    {
        p=s1[top1];//s1 从后往前输出 p 结点
        printf("%c ",p->data);
        top1--;
    }
}

void levelorder(bintree t)
{//层次遍历
    pseqqueue q;
    q=initqueue();//创建队列
    if(t!= NULL)//执行一次
        inqueue(q,t);//将第一个结点 t 存入队列中
    while (!emptyqueue(q))
    {
        outqueue(q,&t);// 出队时的节点
        printf("%c ",t->data);// 输出节点存储的值
        if(t->lchild!= NULL)//有左孩子时将该节点进队列
            inqueue(q,t->lchild);
        if(t->rchild != NULL)//有右孩子时将该节点进队列
            inqueue(q,t->rchild);
    }
}

int main()
{
    bintree t;
    printf("请输入字符串:");
    t=create();
    
    printf("\n先序递归: ");
    perorder1(t);
    printf("\n中序递归: ");
    inorder1(t);
    printf("\n后序递归: ");
    postorder1(t);
    
    printf("\n先序非递归-栈: ");
    preorder2(t);
    printf("\n中序非递归-栈: ");
    inorder2(t);
    printf("\n后序非递归-栈: ");
    postorder2(t);
    
    printf("\n先序非递归-“栈”: ");
    preorder3(t);
    printf("\n中序非递归-“栈”: ");
    inorder3(t);
    printf("\n后序非递归-“栈”: ");
    postorder3(t);

    printf("\n层次遍历-队列: ");
    levelorder(t);
    
    printf("\n");
}
/*
测试数据：
ABDH###E##CF##G##
1248###5##36##7##
1248##9##50###36##7##
 
 
 
请输入字符串:1248##9##50###36##7##

先序递归: 1 2 4 8 9 5 0 3 6 7
中序递归: 8 4 9 2 0 5 1 6 3 7
后序递归: 8 9 4 0 5 2 6 7 3 1
先序非递归-栈: 1 2 4 8 9 5 0 3 6 7
中序非递归-栈: 8 4 9 2 0 5 1 6 3 7
后序非递归-栈: 8 9 4 0 5 2 6 7 3 1
先序非递归-“栈”: 1 2 4 8 9 5 0 3 6 7
中序非递归-“栈”: 8 4 9 2 0 5 1 6 3 7
后序非递归-“栈”: 8 9 4 0 5 2 6 7 3 1
层次遍历-队列: 1 2 3 4 5 6 7 8 9 0

 */

