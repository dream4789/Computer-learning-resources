//
//  main.c
//  图·遍历·深度与广度
//
//  邻接表：
//  顶点结点                        表结点
//  [  vertex  |  firstedge  ] -> [  adjvertex  |  next  ]
//  带权图边表结构：
//  [  adjvertex  |  info  |  next  ]

#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 50
#define maxsize 100
#define Flase 0
#define True 1

typedef char VertexType;
typedef int InfoType;
typedef int Edgetype;

//邻接矩阵
typedef struct
{
    VertexType vertexs[MaxVertexNum];        //顶点向量
    Edgetype arcs[MaxVertexNum][MaxVertexNum];  //邻接矩阵
    int vertexnum,edgenum;                   //图的当前顶点数和边数
    //GraphType type;                      //图的种类标志
}MGraph;


//邻接表
typedef struct node {   //带权图表结点
    int adjvertex;   //邻接点域,一般是存放顶点对应的序号或在表头向量中的下标
    InfoType info;   //与边(或弧)相关的信息
    struct node * next;   //指向下一个邻接点的指针域
}EdgeNode;

typedef struct vnode {  //顶点结点
    VertexType vertex;    //顶点域
    EdgeNode * firstedge;   //边表头指针
}VertexNode;

typedef struct {
    VertexNode adjlist[MaxVertexNum];   //邻接表
    int vertexnum,edgenum;   //顶点数和边数
}ALGraph;  //ALGraph是以邻接表方式存储的图类型

int visited[MaxVertexNum];


//队列
typedef int datatype;

typedef struct{
    datatype data[maxsize];
    int front,rear;
}seqqueue,*pseqqueue;

pseqqueue init_seqqueue(void)
{//创建队列
    pseqqueue q;
    q=(pseqqueue)malloc(sizeof(seqqueue));
    if(q)
    {
        q->front=0;
        q->rear=0;
    }
    return q;
}

int empty_seqqueue(pseqqueue q)
{//队列判空
    if(q&&q->front==q->rear)
        return 1;
    else
        return 0;
}

int in_seqqueue(pseqqueue q,datatype x)
{//入队
    if((q->rear+1)%maxsize==q->front)
    {
        printf("队满");
        return -1;
    }
    else
    {
        q->rear=(q->rear+1)%maxsize;
        q->data[q->rear]=x;
        return 1;
    }
}

int out_seqqueue(pseqqueue q,datatype *x)
{//出队
    if(empty_seqqueue(q))
    {
        printf("队空");
        return -1;
    }
    else
    {
        q->front=(q->front+1)%maxsize;
        *x=q->data[q->front];
        return 1;
    }
}

MGraph init_mgraph(void)
{
    MGraph *G;
    G=(MGraph *)malloc(sizeof(MGraph));
    if(G)
        return *G;
    exit(0);
}
ALGraph init_alraph(void)
{
    ALGraph *G;
    G=(ALGraph *)malloc(sizeof(ALGraph));
    if(G)
        return *G;
    exit(0);
}

void creatgraph(MGraph *G)
{//建立 无向图G 的邻接矩阵存储
    int i,j,k;
    printf("邻接矩阵建立：\n");
    printf("  输入顶点数和边数：");
    scanf("%d %d",&(G->vertexnum),&(G->edgenum));   //输入顶点数和边数
    printf("  输入%d顶点信息:",G->vertexnum);
    getchar();
    for(i=0;i<G->vertexnum;i++)      //输入顶点信息，建立顶点表v0,v1,v2,v3
        scanf("%c",&(G->vertexs[i]));
    for(i=0;i<G->vertexnum;i++)        //初始化邻接矩阵
        for(j=0;j<G->vertexnum;j++)
            G->arcs[i][j]=0;
    for(k=0;k<G->edgenum;k++)     //输入e条边，建立邻接矩阵
    {
        printf("  输入第%d个点的坐标(0<=i,j<=%d)：",k+1,G->vertexnum-1);
        scanf("%d %d",&i,&j);     //输入为 1 的点坐标 (i,j)
        G->arcs[i][j]=1;
        
        G->arcs[j][i]=1;    //若加入此行，则为无向图的邻接矩阵建立
    }
}

void CreateALGraph(ALGraph *G)
{//建立 无向图G 的邻接表存储
    int i,j,k;
    EdgeNode *p,*s;
    printf("邻接表建立：\n");
    printf("  输入顶点数和边数:");
    scanf("%d%d",&(G->vertexnum),&(G->edgenum));   //读人顶点数和边数
    printf("  输入%d个顶点信息:",G->vertexnum);
    getchar();
    for(i=0;i<G->vertexnum;i++)                //建立有n个顶点的顶点表
    {
        scanf("%c",&(G->adjlist[i].vertex));    //读人顶点信息 v0,v1,v2,v3
        G->adjlist[i].firstedge=NULL;     //顶点的边表头指针设为空
    }
    for(k=0;k<G->edgenum;k++)             //建立边表
    {
        printf("  输入第%d个边表连接(0<=i,j<=%d)：",k+1,G->vertexnum-1);
        scanf("%d%d",&i,&j);          //读入边<Vi,Vj>的顶点对应序号
        p=(EdgeNode*)malloc(sizeof(EdgeNode));    //生成新边表结点p*
        p->adjvertex=j;           //邻接点序号为j
        p->next=G->adjlist[i].firstedge;   //将新边表结点 p插人到顶点 Vi 的链表头部
        G->adjlist[i].firstedge=p;

        //加入以下代码，为创建无向图
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvertex = i;        //邻接点序号为i
        s->next = G->adjlist[j].firstedge;
        G->adjlist[j].firstedge = s;
        
    }
}
void show_MGgraph(MGraph *G)
{//输出邻接矩阵
    int i,j;
    printf("创建的 无向图 邻接矩阵 为：\n");
    for(i=0;i<G->vertexnum;i++)
    {
        for(j=0;j<G->vertexnum;j++)
            printf(" %d",G->arcs[i][j]);
        printf("\n");
    }
}

void show_ALgraph(ALGraph *G)
{//输出邻接表
    int i;
    EdgeNode *p;
    printf("创建的 无向图 邻接表 为：\n");
    for(i=0;i<G->vertexnum;i++)
    {
        printf(" <%c> ",G->adjlist[i].vertex);
        p=G->adjlist[i].firstedge;
        while (p) {
            printf("->%c",G->adjlist[p->adjvertex].vertex);
            p=p->next;
        }
        printf("\n");
    }
}



void AL_DFS(ALGraph G,int v)
{//从第v个顶点出发遍历        <深度优先><邻接表>
    EdgeNode *p;
    int w;
    printf("%c",G.adjlist[v].vertex);
    visited[v]=True;
    for(p=G.adjlist[v].firstedge;p;p=p->next)
    {
        w=p->adjvertex;
        //printf("%d",w);
        if(!visited[w])
        {
            printf("->");
            AL_DFS(G,w);
        }//从初始顶点结点（v）开始，指针找 顶点结点指针 第一个所指的（1且False）元素，再将此元素变为顶点结点，开始找此 顶点结点指针 所指的第一个（1且Flase）元素……（若没有（1且Flase）元素则从初始顶点结点的下一个开始找）
    }
}
void AL_DFStraverse(ALGraph G)
{//遍历图G           <深度优先><邻接表>
    int v;
    printf("无向图 邻接表 深度优先遍历：");
    for(v=0;v<G.vertexnum;v++)
        visited[v]=Flase;  //标志向量初始化
    for(v=0;v<G.vertexnum;v++)
        if(!visited[v])
            AL_DFS(G,v);
}


void AL_BFS(ALGraph G,int v)
{//从v出发按广度优先遍历图G；使用辅助队列q和访问标志数组visited      <广度优先><邻接表>
    EdgeNode *p;
    int u,w;
    pseqqueue q;       //定义一个队列
    q=init_seqqueue();      //置空队列
    printf("无向图 邻接表 广度优先遍历：");
    printf("%c",G.adjlist[v].vertex);     //访问v
    visited[v]=True;   //把访问标志置True
    in_seqqueue(q, v);
    while(!empty_seqqueue(q))
    {
        out_seqqueue(q,&u);     //出队列
        for(p=G.adjlist[u].firstedge;p;p=p->next)
        {
            w=p->adjvertex;
            if(!visited[w])
            {
                printf("->%c",G.adjlist[w].vertex);
                visited[w]=True;
                in_seqqueue(q, w);    //u尚未访问的邻接顶点w入队列q
            }
        }//从初始顶点结点（v）开始，指针依次找（1且False）元素，访问并入队，访问完毕。再出对一个顶点元素，将其设为顶点结点，指针依次找（1且False）元素，访问并入队，访问完毕……（若顶点结点后面全True，从初始顶点结点（v）下一个开始）
    }
    printf("\n");
}


void MG_DFS(MGraph *G,int V)
{//深度优先遍历搜索,从V节点开始    <邻接矩阵>
    int w;
    printf("%c",G->vertexs[V]);
    visited[V]=True;  //标记为以访问
    for(w=0;w<G->vertexnum;w++)
    {
        if(!visited[w]&&(G->arcs[V][w]!=0||G->arcs[w][V]!=0))  //未访问 且 对应点存在为1
        {
            printf("->");
            MG_DFS(G,w);
        }//先初始行（V）循环从第一列找到最后一列，第一个为（1且Flase）的数输出，再把此数的 纵坐标数 变为 行数，再在此行循环从第一列找到最后一列……（如果循环到某一行中都访问过，则再从初始行（V）开始找）
    }
    
}
void MG_DFStraverse(MGraph *G)
{//深度优先遍历所有节点          <邻接矩阵>
    int i;
    for(i=0;i<G->vertexnum;i++)
        visited[i] = Flase;
    printf("无向图 邻接矩阵 深度优先遍历：");
    for(i=0;i<G->vertexnum; i++)
    {//对与矩阵中所有元素都进行深度优先遍历搜索
        if(!visited[i])
            MG_DFS(G, i);
    }
    printf("\n");
}

void MG_BFS(MGraph G,int v)
{//以v为出发点。对G进行BFS       <广度优先><邻接矩阵>
    int i,j;
    pseqqueue q;
    q=init_seqqueue();
    printf("%c",G.vertexs[v]);     //访问v
    visited[v]=True;     //访问过
    in_seqqueue(q, v);
    while(!empty_seqqueue(q))
    {
        out_seqqueue(q,&i);     //出队列
        //printf("i=%d",i);  //i依此为0，1，2，3，4，。。。（行数变化）
        for(j=0;j<G.vertexnum;j++)  //依次搜索i行上循环j
        {
            if(G.arcs[i][j]==1&&!visited[j])   //邻接矩阵为1，且未访问
            {
                printf("->%c",G.vertexs[j]);     //访问
                visited[j]=True;
                in_seqqueue(q, j);    //j入队
            }//从初始行（V）开始，若为（1且Flase）的元素，依次输出并入队，一行结束了，出对一个元素当成行，再从那一行开始找，若为（1且Flase）的元素，依次输出并入队，一行结束，再出对下一个元素……
        }
    }
}

void MG_BFStraverse(MGraph G)
{//遍历图G          <广度优先><邻接矩阵>
    int v;
    for(v=0;v<G.vertexnum;v++)
        visited[v]=Flase;
    printf("无向图 邻接矩阵 广度优先遍历：");
    for(v=0;v<G.vertexnum;v++)
        if(!visited[v])  //v未访问过，从v开始BFS
            MG_BFS(G,v);
    printf("\n");
}



int main()
{
    
    MGraph MG=init_mgraph();
    creatgraph(&MG);
    show_MGgraph(&MG);
    
    MG_BFStraverse(MG);       //邻接矩阵，广度，无向
    MG_DFStraverse(&MG);      //邻接矩阵，深度，无向
    

    ALGraph AL=init_alraph();
    CreateALGraph(&AL);
    show_ALgraph(&AL);
    
    AL_BFS(AL, 0);         //邻接表，广度，无向
    AL_DFStraverse(AL);    //邻接表，深度，无向
    
    printf("\n");
    
    return 0;
}


/*
 邻接矩阵建立：
   输入顶点数和边数：8 9
   输入8顶点信息:abcdefgh
   输入第1个点的坐标(0<=i,j<=8)：0 1
   输入第2个点的坐标(0<=i,j<=8)：0 2
   输入第3个点的坐标(0<=i,j<=8)：1 3
   输入第4个点的坐标(0<=i,j<=8)：1 4
   输入第5个点的坐标(0<=i,j<=8)：3 7
   输入第6个点的坐标(0<=i,j<=8)：4 7
   输入第7个点的坐标(0<=i,j<=8)：2 5
   输入第8个点的坐标(0<=i,j<=8)：2 6
   输入第9个点的坐标(0<=i,j<=8)：5 6
 创建的 无向图 邻接矩阵 为：
  0<b>c>0 0 0 0 0
  1 0 0<d>1 0 0 0
  1 0 0 0 0<f>1 0
  0 1 0 0 0 0 0<h>
  0 1 0 0 0 0 0 1
  0 0 1 0 0 0<g>0
  0 0 1 0 0 1 0 0
  0 0 0 1<e>0 0 0
 无向图 邻接矩阵 广度优先遍历：a->b->c->d->e->f->g->h   //解决
 无向图 邻接矩阵 深度优先遍历：a->b->d->h->e->c->f->g   //解决
 
 邻接表建立：
   输入顶点数和边数:8 9
   输入8个顶点信息:abcdefgh
   输入第1个边表连接(0<=i,j<=7)：0 1
   输入第2个边表连接(0<=i,j<=7)：0 2
   输入第3个边表连接(0<=i,j<=7)：1 3
   输入第4个边表连接(0<=i,j<=7)：1 4
   输入第5个边表连接(0<=i,j<=7)：3 7
   输入第6个边表连接(0<=i,j<=7)：4 7
   输入第7个边表连接(0<=i,j<=7)：2 5
   输入第8个边表连接(0<=i,j<=7)：2 6
   输入第9个边表连接(0<=i,j<=7)：5 6
 创建的 无向图 邻接表 为：
  <a> ->c->b->∧
  <b> ->e->d->a->∧
  <c> ->g->f->a->∧
  <d> ->h->b->∧
  <e> ->h->b->∧
  <f> ->g->c->∧
  <g> ->f->c->∧
  <h> ->e->d->∧
 无向图 邻接表 广度优先遍历：a->c->b->g->f->e->d->h   //解决
 无向图 邻接表 深度优先遍历：a->c->g->f->b->e->h->d   //解决
 */
