#include<stdio.h>
#include<stdlib.h>
#define m 6   /* 迷宫的实际行 */
#define n 8   /* 迷宫的实际列 */
int maze[m+2][n+2];
int maze_before[m][n]={
    {0 ,1 ,1 ,1 ,0 ,1 ,1 ,1},
    {0 ,0 ,0 ,0 ,1 ,1 ,1 ,1},
    {0 ,1 ,0 ,0 ,0 ,0 ,0 ,1},
    {0 ,1 ,1 ,1 ,0 ,0 ,1 ,1},
    {1 ,0 ,0 ,1 ,1 ,0 ,0 ,0},
    {0 ,1 ,1 ,0 ,0 ,1 ,1 ,0},
};
typedef struct
{
    int x,y;
}item;
item move1[4]={{0,1},{1,0},{0,-1},{-1,0}}; //方向，0右移，1是下移，2是左移，3是上移
//关于数据结构的问题
typedef struct
{
    int x,y,d;//横纵坐标及方向
}DataType ;

typedef struct Node
{
    DataType data;
    struct Node *next;
}QNode,*PQNode;//队列中结点的类型

typedef struct
{
    QNode *front;//队头指针
    QNode *rear;//队尾指针
}LinkQueue,*PLinkQueue;//链队列

//创建迷宫
void creat1(void)
{
    int i,j;
    for(i=0;i<=n+1;i++)
    {
        maze[0][i]=1;
        maze[m+1][i]=1;
    }  //i表示列，将迷宫的上下两行设为栅栏
    for(j=1;j<=m+1;j++)
    {
        maze[j][0]=1;
        maze[j][n+1]=1;
    }//j表示行，将迷宫的左右两类设为栅栏
    
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
           // scanf("%d",&maze[i][j]);//将迷宫内的数值设置
            maze[i][j]=maze_before[i-1][j-1];
}
//输出迷宫
void printe(void)
{
    int i,j;
    for(i=0;i<=m+1;i++)
    {
        for(j=0;j<=n+1;j++)
            printf("%d  ",maze[i][j]);
        printf("\n");
    }
}
//初始化队列（未设头结点）
PLinkQueue Init_LinkQueue(void)
{
    PLinkQueue Q;
    Q=(PLinkQueue)malloc(sizeof(LinkQueue));
    if(Q)
    {
        Q->front=Q->rear=NULL;
    }
    return Q;
}
//判断队列是否为空，空返回1
int Empty_LinkQueue(PLinkQueue Q)
{
    if(Q&&Q->front==NULL&&Q->rear==NULL)
        return 1;
    else
        return 0;
}
//数据进队列，在队尾插入
int In_LinkQueue(PLinkQueue Q,DataType tmp)
{
    PQNode p;
    p=(PQNode)malloc(sizeof(QNode));
    if(!p)
    {
        printf("内存溢出\n");
        return 0;
    }
    p->data.x=tmp.x;
    p->data.y=tmp.y;
    p->data.d=tmp.d;
    //printf("[%d %d %d]\n",p->data.x,p->data.y,p->data.d); //分析行
    p->next=NULL;
    if(Empty_LinkQueue(Q))
        Q->rear=Q->front=p;
    else
    {
        Q->rear->next=p;
        Q->rear=p;
    }
    return 1;
}
//将队尾的结点删除，通过建立一个新的链表间接删除
void Out_LinkQueue(PLinkQueue Q,DataType *tmp)
{
    tmp->x=Q->rear->data.x;
    tmp->y=Q->rear->data.y;
    tmp->d=Q->rear->data.d;
    //printf("(%d %d %d)\n",tmp->x,tmp->y,tmp->d);  //分析行
    PLinkQueue s=Init_LinkQueue();//初始化一个新队列
    PQNode q;
    q=Q->front;
    if(q->next==NULL)//仅一个结点
    {
        Q->front=Q->rear;
        //printf("@"); //分析行
        free(q);
    }
    else
    {
        while(q->next->next!=NULL)//从循环中找到倒数第二个结点
        {//不只一个结点
            s->rear=q;//把收索到的结点放入新队列的的队尾
            q=q->next;
        }
        free(q->next);
        q->next=NULL;
        s->front=Q->front;
        s->rear->next=q;
        s->rear=q;
    }
    Q->front=s->front;
    Q->rear=s->rear;//调整结束之后，将队列恢复成t的新队列
}
void Out_LinkQueue1(PLinkQueue Q,DataType *tmp)
{//出队
    tmp->x=Q->front->data.x;
    tmp->y=Q->front->data.y;
    tmp->d=Q->front->data.d;
    PQNode p;
    p=Q->front;
    Q->front=Q->front->next;
    free(p);
    if(!Q->front)
        Q->rear=NULL;
}
//销毁队列
void Destroy_LinkQueue(PLinkQueue *Q)
{
    PQNode p;
    if(*Q)
    {
        while((*Q)->front)
        {
            p=(*Q)->front;
            (*Q)->front=(*Q)->front->next;
            free(p);
        }
        free(*Q);
    }
    *Q=NULL;
}
//寻找路径的过程
int path(int maze[][n+2],item move1[],int x0,int y0)//迷宫，移动方向的数组，起始的位置
{
    PLinkQueue S;
    DataType temp;
    int x,y,d,i,j;
    temp.x=x0;
    temp.y=y0;
    temp.d=-1;
    S=Init_LinkQueue();
    if(!S)
    {
        printf("初始化失败\n");
        return 0;
    }
    In_LinkQueue(S,temp);
    while(!Empty_LinkQueue(S))
    {
        //printf("出1");  //分析行
        Out_LinkQueue(S,&temp);
        x=temp.x;
        y=temp.y;
        d=temp.d+1;
        while(d<4)
        {
            i=x+move1[d].x;
            j=y+move1[d].y;
            if(maze[i][j]==0)
            {
                temp.x=x;
                temp.y=y;
                temp.d=d;
                //printf("进");  //分析行
                In_LinkQueue(S,temp);
                x=i;y=j;maze[i][j]=-1;
                if(x==m&&y==n)
                {
                    printf("迷宫路径为：");
                    while(!Empty_LinkQueue(S))
                    {
                        Out_LinkQueue1(S,&temp);
                        printf("(%d,%d)->",temp.x,temp.y);
                    }
                    printf("(%d,%d)\n",m,n);
                    Destroy_LinkQueue(&S);
                    return 1;
                }
                else
                    d=0;
            }
            else
                d++;
        }
    }
    Destroy_LinkQueue(&S);
    printf("未找到通路");
    return 0;
}
//主函数
int main()
{
    creat1();
    printf("所建造的迷宫为：\n");
    printe();
    printf("从起点(1,1)到终点(%d,%d)寻找路径的情况如下:\n",m,n);
    path(maze,move1,1,1);
    return 0;
}

/*

//这是帮郝娜娜一个室友改的，正好是个迷宫问题新思路，可以看看

 所建造的迷宫为：
 1  1  1  1  1  1  1  1  1  1
 1  0  1  1  1  0  1  1  1  1
 1  0  0  0  0  1  1  1  1  1
 1  0  1  0  0  0  0  0  1  1
 1  0  1  1  1  0  0  1  1  1
 1  1  0  0  1  1  0  0  0  1
 1  0  1  1  0  0  1  1  0  1
 1  1  1  1  1  1  1  1  1  1
 从起点(1,1)到终点(6,8)寻找路径的情况如下:
 迷宫路径为：(1,1)->(2,1)->(2,2)->(2,3)->(2,4)->(3,4)->(3,5)->(3,6)->(4,6)->(5,6)->(5,7)->(5,8)->(6,8)
 */