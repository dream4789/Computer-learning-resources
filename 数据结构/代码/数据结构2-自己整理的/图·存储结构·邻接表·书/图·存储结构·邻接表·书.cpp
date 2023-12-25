//
//  main.c
//  图·存储结构·邻接表·书
//

//   [   vertex   (顶点域)  | firstedg（边表头指针）        ]           [顶点结点]
//   [ adjvertex (邻接点域) |  next（指针域）               ]          [表结点]
//   [ adjvertex (邻接点域) |  info(边上信息) | next(指针域) ]          [带权图的边表结构]


#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 30  /*最大顶点数为 30*/

typedef char VertexType;
typedef int InfoType;


typedef struct node {   //表结点w
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
    int vertexNum,edgeNum;   //顶点数和边数
}ALGraph;  //ALGraph是以邻接表方式存储的图类型

ALGraph init_alraph(void)
{//开辟空间
    ALGraph *G;
    G=(ALGraph *)malloc(sizeof(ALGraph));
    if(G)
        return *G;
    exit(0);
}

void CreateALGraph(ALGraph *G)
{//建立 无向图G 的邻接表存储
    int i,j,k;
    EdgeNode *p,*s;
    printf("邻接表建立：\n");
    printf("  输入顶点数和边数:");
    scanf("%d%d",&(G->vertexNum),&(G->edgeNum));   //读人顶点数和边数
    printf("  输入%d个顶点信息:",G->vertexNum);
    getchar();
    for(i=0;i<G->vertexNum;i++)                //建立有n个顶点的顶点表
    {
        scanf("%c",&(G->adjlist[i].vertex));    //读人顶点信息 v0,v1,v2,v3
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

        //加入以下代码，为创建无向图
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvertex = i;        //邻接点序号为i
        s->next = G->adjlist[j].firstedge;
        G->adjlist[j].firstedge = s;
        
    }
}

void show_ALgraph(ALGraph *G)
{//输出邻接表
    int i;
    EdgeNode *p;
    printf("创建的 无向图 邻接表 为：\n");
    for(i=0;i<G->vertexNum;i++)
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
int main(int argc, const char * argv[])
{
    ALGraph G=init_alraph();
    CreateALGraph(&G);
    show_ALgraph(&G);
    return 0;
}

/*
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
  <a> ->c->b
  <b> ->e->d->a
  <c> ->g->f->a
  <d> ->h->b
  <e> ->h->b
  <f> ->g->c
  <g> ->f->c
  <h> ->e->d
 */
