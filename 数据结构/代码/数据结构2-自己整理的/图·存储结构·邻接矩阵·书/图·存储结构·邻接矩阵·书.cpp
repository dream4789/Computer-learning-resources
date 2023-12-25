//
//  main.c
//  图·存储结构·邻接矩阵·书
//


#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 50

typedef char VertexType;
typedef int Edgetype;

typedef struct
{
    VertexType vertexs[MaxVertexNum];        //顶点向量
    Edgetype arcs[MaxVertexNum][MaxVertexNum];  //邻接矩阵
    int vertexnum,edgenum;                   //图的当前顶点数和边数
    //GraphType type;                      //图的种类标志
}MGraph;

MGraph init_mgraph(void)
{
    MGraph *G;
    G=(MGraph *)malloc(sizeof(MGraph));
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

int main(int argc, const char * argv[])
{
    MGraph G=init_mgraph();
    creatgraph(&G);
    show_MGgraph(&G);
    return 0;
}
/*
 邻接矩阵建立：
   输入顶点数和边数：8 9
   输入8顶点信息:abcdefgh
   输入第1个点的坐标(0<=i,j<=7)：0 1
   输入第2个点的坐标(0<=i,j<=7)：0 2
   输入第3个点的坐标(0<=i,j<=7)：1 3
   输入第4个点的坐标(0<=i,j<=7)：1 4
   输入第5个点的坐标(0<=i,j<=7)：3 7
   输入第6个点的坐标(0<=i,j<=7)：4 7
   输入第7个点的坐标(0<=i,j<=7)：2 5
   输入第8个点的坐标(0<=i,j<=7)：2 6
   输入第9个点的坐标(0<=i,j<=7)：5 6
 创建的 无向图 邻接矩阵 为：
  0 1 1 0 0 0 0 0
  1 0 0 1 1 0 0 0
  1 0 0 0 0 1 1 0
  0 1 0 0 0 0 0 1
  0 1 0 0 0 0 0 1
  0 0 1 0 0 0 1 0
  0 0 1 0 0 1 0 0
  0 0 0 1 1 0 0 0
 */
