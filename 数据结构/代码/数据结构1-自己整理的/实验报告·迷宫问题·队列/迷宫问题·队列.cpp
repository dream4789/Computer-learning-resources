#include<stdio.h>
#include<stdlib.h>
#define m 6   /* �Թ���ʵ���� */
#define n 8   /* �Թ���ʵ���� */
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
item move1[4]={{0,1},{1,0},{0,-1},{-1,0}}; //����0���ƣ�1�����ƣ�2�����ƣ�3������
//�������ݽṹ������
typedef struct
{
    int x,y,d;//�������꼰����
}DataType ;

typedef struct Node
{
    DataType data;
    struct Node *next;
}QNode,*PQNode;//�����н�������

typedef struct
{
    QNode *front;//��ͷָ��
    QNode *rear;//��βָ��
}LinkQueue,*PLinkQueue;//������

//�����Թ�
void creat1(void)
{
    int i,j;
    for(i=0;i<=n+1;i++)
    {
        maze[0][i]=1;
        maze[m+1][i]=1;
    }  //i��ʾ�У����Թ�������������Ϊդ��
    for(j=1;j<=m+1;j++)
    {
        maze[j][0]=1;
        maze[j][n+1]=1;
    }//j��ʾ�У����Թ�������������Ϊդ��
    
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
           // scanf("%d",&maze[i][j]);//���Թ��ڵ���ֵ����
            maze[i][j]=maze_before[i-1][j-1];
}
//����Թ�
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
//��ʼ�����У�δ��ͷ��㣩
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
//�ж϶����Ƿ�Ϊ�գ��շ���1
int Empty_LinkQueue(PLinkQueue Q)
{
    if(Q&&Q->front==NULL&&Q->rear==NULL)
        return 1;
    else
        return 0;
}
//���ݽ����У��ڶ�β����
int In_LinkQueue(PLinkQueue Q,DataType tmp)
{
    PQNode p;
    p=(PQNode)malloc(sizeof(QNode));
    if(!p)
    {
        printf("�ڴ����\n");
        return 0;
    }
    p->data.x=tmp.x;
    p->data.y=tmp.y;
    p->data.d=tmp.d;
    //printf("[%d %d %d]\n",p->data.x,p->data.y,p->data.d); //������
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
//����β�Ľ��ɾ����ͨ������һ���µ�������ɾ��
void Out_LinkQueue(PLinkQueue Q,DataType *tmp)
{
    tmp->x=Q->rear->data.x;
    tmp->y=Q->rear->data.y;
    tmp->d=Q->rear->data.d;
    //printf("(%d %d %d)\n",tmp->x,tmp->y,tmp->d);  //������
    PLinkQueue s=Init_LinkQueue();//��ʼ��һ���¶���
    PQNode q;
    q=Q->front;
    if(q->next==NULL)//��һ�����
    {
        Q->front=Q->rear;
        //printf("@"); //������
        free(q);
    }
    else
    {
        while(q->next->next!=NULL)//��ѭ�����ҵ������ڶ������
        {//��ֻһ�����
            s->rear=q;//���������Ľ������¶��еĵĶ�β
            q=q->next;
        }
        free(q->next);
        q->next=NULL;
        s->front=Q->front;
        s->rear->next=q;
        s->rear=q;
    }
    Q->front=s->front;
    Q->rear=s->rear;//��������֮�󣬽����лָ���t���¶���
}
void Out_LinkQueue1(PLinkQueue Q,DataType *tmp)
{//����
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
//���ٶ���
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
//Ѱ��·���Ĺ���
int path(int maze[][n+2],item move1[],int x0,int y0)//�Թ����ƶ���������飬��ʼ��λ��
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
        printf("��ʼ��ʧ��\n");
        return 0;
    }
    In_LinkQueue(S,temp);
    while(!Empty_LinkQueue(S))
    {
        //printf("��1");  //������
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
                //printf("��");  //������
                In_LinkQueue(S,temp);
                x=i;y=j;maze[i][j]=-1;
                if(x==m&&y==n)
                {
                    printf("�Թ�·��Ϊ��");
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
    printf("δ�ҵ�ͨ·");
    return 0;
}
//������
int main()
{
    creat1();
    printf("��������Թ�Ϊ��\n");
    printe();
    printf("�����(1,1)���յ�(%d,%d)Ѱ��·�����������:\n",m,n);
    path(maze,move1,1,1);
    return 0;
}

/*

//���ǰ������һ�����Ѹĵģ������Ǹ��Թ�������˼·�����Կ���

 ��������Թ�Ϊ��
 1  1  1  1  1  1  1  1  1  1
 1  0  1  1  1  0  1  1  1  1
 1  0  0  0  0  1  1  1  1  1
 1  0  1  0  0  0  0  0  1  1
 1  0  1  1  1  0  0  1  1  1
 1  1  0  0  1  1  0  0  0  1
 1  0  1  1  0  0  1  1  0  1
 1  1  1  1  1  1  1  1  1  1
 �����(1,1)���յ�(6,8)Ѱ��·�����������:
 �Թ�·��Ϊ��(1,1)->(2,1)->(2,2)->(2,3)->(2,4)->(3,4)->(3,5)->(3,6)->(4,6)->(5,6)->(5,7)->(5,8)->(6,8)
 */