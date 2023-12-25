//
//  main.c
//  图·有向·AOV拓扑排序
//
//   　[   indegree  |   vertex  |  firstedge  ]



#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 30  //最大顶点数为 30

typedef struct node  //表结点
{
    int adjvertex;  //邻接点域,一般是存放顶点对应的序号或在表头向量中的下标
    struct node * next;  //指向下一个邻接点的指针域
}EdgeNode;

typedef struct vnode  //顶点表结点
{
    int indegree;  //存放顶点人度
    int vertex;  //顶点域
    EdgeNode * firstedge;  //边表头指针
}VertexNode;

typedef struct
{
    VertexNode adjlist[MaxVertexNum];  //邻接表
    int vertexNum,edgeNum;  //顶点数和边数
}ALGraph;  //ALGraph 是以邻接表方式存储

ALGraph init_alraph(void)
{
    ALGraph *G;
    G=(ALGraph *)malloc(sizeof(ALGraph));
    if(G)
        return *G;
    exit(0);
}

void CreateALGraph(ALGraph *G)
{//建立 有向图G 的邻接表存储
    int i,j,k;
    EdgeNode *p;
    printf("有向图邻接表建立：\n");
    printf("  输入顶点数和边数:");
    scanf("%d%d",&(G->vertexNum),&(G->edgeNum));   //读人顶点数和边数
    printf("  输入%d个顶点信息(数字）:\n",G->vertexNum);
    getchar();
    for(i=0;i<G->vertexNum;i++)                //建立有n个顶点的顶点表
    {
        scanf("%d",&(G->adjlist[i].vertex));    //读人顶点信息 v0,v1,v2,v3
        G->adjlist[i].firstedge=NULL;     //顶点的边表头指针设为空
    }
    for(k=0;k<G->edgeNum;k++)             //建立边表
    {
        printf("  输入第%d个边表连接(0<=i,j<=%d)：",k+1,G->vertexNum-1);
        scanf("%d%d",&i,&j);          //读入边<Vi,Vj>的顶点对应序号
        p=(EdgeNode*)malloc(sizeof(EdgeNode));    //生成新边表结点p*
        p->adjvertex=j;           //邻接点序号为j
        p->next=G->adjlist[i].firstedge;   //将新边表结点 p插人到顶点 Vi 的链表头部
        G->adjlist[i].firstedge=p;
    }
}

void FindInDegree(ALGraph *G)  //求各顶点的入度
{
    int i;
    EdgeNode *p;
    for(i=0;i<G->vertexNum;i++)
        G->adjlist[i].indegree=0;
    for(i=0;i<G->vertexNum;i++)
    {
        for(p=G->adjlist[i].firstedge;p;p=p->next)
            G->adjlist[p->adjvertex].indegree++;
    }
    for(i=0;i<G->vertexNum;i++)
        printf("第 %d 个顶点的入度为 %d \n",i+1,G->adjlist[i].indegree);
}
void Top_Sort (ALGraph G)
{//对以邻接链表为存储结构的图 G,输出其拓扑序列
    int i,j,k,count=0;
    int top=-1;  //栈顶指针初始化
    EdgeNode *p;
    FindInDegree(&G);  //求各顶点的入度
    for(i=0;i<G.vertexNum;i++)  //依次将入度为0的顶点压入链式栈
    {
        if(G.adjlist[i].indegree==0)
        {
            G.adjlist[i].indegree=top;
            top=i;
        }
    }
    printf("邻接链表的拓扑序列为：");
    while(top!=-1)  //栈不空
    {
        j=top;
        top=G.adjlist[top].indegree;  //从栈中退出一个顶点并输出
        printf(" %d",G.adjlist[j].vertex);
        count++;  //排序到的顶点计数
        for(p=G.adjlist[j].firstedge;p;p=p->next)
        {
            k=p->adjvertex;
            G.adjlist[k].indegree--;  //当前输出顶点邻接点的入度减1
            if(G.adjlist[k].indegree==0)  //新的入度为0的顶点进栈
            {
                G.adjlist[k].indegree=top;
                top=k;  //修改栈顶下标
            }
        }
    }
    if(count<G.vertexNum)
        printf("The network has a cycle");
}

void show_ALgraph(ALGraph *G)
{//输出邻接表
    int i;
    EdgeNode *p;
    printf("创建的 有向图 邻接表 为：\n");
    for(i=0;i<G->vertexNum;i++)
    {
        printf(" <%d> ",G->adjlist[i].vertex);
        p=G->adjlist[i].firstedge;
        while (p) {
            printf("->%d",G->adjlist[p->adjvertex].vertex);
            p=p->next;
        }
        printf("\n");
    }
}

int main()
{
    ALGraph G=init_alraph();
    CreateALGraph(&G);
    show_ALgraph(&G);
    Top_Sort(G);  //这里的拓扑排序可能有些问题，等一点时间，我会处理好
    printf("\n");
}
/*
 有向图邻接表建立：
   输入顶点数和边数:8 9
   输入8个顶点信息(数字）:
 1
 2
 3
 4
 5
 6
 7
 8
   输入第1个边表连接(0<=i,j<=7)：0 1
   输入第2个边表连接(0<=i,j<=7)：0 2
   输入第3个边表连接(0<=i,j<=7)：1 3
   输入第4个边表连接(0<=i,j<=7)：1 4
   输入第5个边表连接(0<=i,j<=7)：3 7
   输入第6个边表连接(0<=i,j<=7)：4 7
   输入第7个边表连接(0<=i,j<=7)：2 5
   输入第8个边表连接(0<=i,j<=7)：2 6
   输入第9个边表连接(0<=i,j<=7)：5 6
 创建的 有向图 邻接表 为：
  <1> ->3->2
  <2> ->5->4
  <3> ->7->6
  <4> ->8
  <5> ->8
  <6> ->7
  <7>
  <8>
 第 1 个顶点的入度为 0
 第 2 个顶点的入度为 1
 第 3 个顶点的入度为 1
 第 4 个顶点的入度为 1
 第 5 个顶点的入度为 1
 第 6 个顶点的入度为 1
 第 7 个顶点的入度为 2
 第 8 个顶点的入度为 2
 邻接链表的拓扑序列为： 1 2 4 5 8 3 6 7
 
 有向图邻接表建立：
   输入顶点数和边数:6 8
   输入6个顶点信息(数字）:
 0
 1
 2
 3
 4
 5
   输入第1个边表连接(0<=i,j<=5)：0 1
   输入第2个边表连接(0<=i,j<=5)：0 2
   输入第3个边表连接(0<=i,j<=5)：0 3
   输入第4个边表连接(0<=i,j<=5)：2 1
   输入第5个边表连接(0<=i,j<=5)：2 4
   输入第6个边表连接(0<=i,j<=5)：3 4
   输入第7个边表连接(0<=i,j<=5)：3 5
   输入第8个边表连接(0<=i,j<=5)：5 4
 创建的 有向图 邻接表 为：
  <0> ->3->2->1
  <1>
  <2> ->4->1
  <3> ->5->4
  <4>
  <5> ->4
 第 1 个顶点的入度为 0
 第 2 个顶点的入度为 2
 第 3 个顶点的入度为 1
 第 4 个顶点的入度为 1
 第 5 个顶点的入度为 3
 第 6 个顶点的入度为 1
 邻接链表的拓扑序列为： 0 2 1 3 5 4
 */
