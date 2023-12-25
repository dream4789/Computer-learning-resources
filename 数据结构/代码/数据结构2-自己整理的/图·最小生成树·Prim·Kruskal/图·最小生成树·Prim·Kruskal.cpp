//
//  main.c
//  图·最小生成树·Prim·Kruskal
//
//  Created by 徐龙 on 2021/11/27.
//

#include <stdio.h>
#include <stdlib.h>
#define INFINITY 10  //定义一个权值的最大值
#define MaxVertexNum 30  //最大顶点数
#define MaxEdge 100

typedef char VertexType;
typedef int Edgetype;
typedef int WeightType;

typedef struct
{
    VertexType vertexs[MaxVertexNum];        //顶点向量
    Edgetype arcs[MaxVertexNum][MaxVertexNum];  //邻接矩阵
    int vertexnum,edgenum;      //图的当前顶点数和边数
}MGraph;

//Prim
typedef struct
{
    char adjvertex;  //某顶点与已构造好的部分生成树的顶点之间权值最小的顶点
    int lowcost;  //某顶点与已构造好的部分生成树的顶点之间的最小权值
}ClosEdge[MaxVertexNum];  //用Prim求最小生成树时的辅助数组

//Kruskal
typedef struct
{
    int initial;
    int end;
    WeightType weight;   //边的权值
}ENode;
typedef struct
{
    int vertexnum,edgenum;  //顶点个数,边的个数
    VertexType vertexs[MaxVertexNum];  //顶点信息
    ENode edges[MaxVertexNum];  //边的信息
}ELGraph;   //注意：此图的存储结构与前面介绍的几种不一样

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
    int i,j,k,w;
    printf("邻接矩阵建立：\n");
    printf("  输入顶点数和边数：");
    scanf("%d %d",&(G->vertexnum),&(G->edgenum));   //输入顶点数和边数
    printf("  输入%d个顶点信息:",G->vertexnum);
    getchar();
    for(i=0;i<G->vertexnum;i++)      //输入顶点信息，建立顶点表v0,v1,v2,v3
        scanf("%c",&(G->vertexs[i]));
    for(i=0;i<G->vertexnum;i++)        //初始化邻接矩阵
        for(j=0;j<G->vertexnum;j++)
            G->arcs[i][j]=INFINITY;
    printf("  输入%d个点的坐标(0<=i,j<=10) 和 权值(w<10)：\n",G->edgenum);
    for(k=0;k<G->edgenum;k++)     //输入e条边，建立邻接矩阵
    {
        scanf("%d %d %d",&i,&j,&w);     //输入为 1 的点坐标 (i,j)
        G->arcs[i][j]=w;
        G->arcs[j][i]=w;    //若加入此行，则为无向图的邻接矩阵建立
    }
}
void show_MGgraph(MGraph *G)
{//输出邻接矩阵
    int i,j;
    printf("创建的 无向图 邻接矩阵 为：\n");
    for(i=0;i<G->vertexnum;i++)
    {
        for(j=0;j<G->vertexnum;j++)
            printf("%3d",G->arcs[i][j]);
        printf("\n");
    }
}

ELGraph init_elgraph(void)
{
    ELGraph *EG;
    EG=(ELGraph *)malloc(sizeof(ELGraph));
    if(EG)
        return *EG;
    exit(0);
}

void createlgraph(ELGraph *EG)
{//建立 连通网G 的存储
    int i,k;
    printf("建立连通网：\n");
    printf("  输入顶点数和边数：");
    scanf("%d %d",&(EG->vertexnum),&(EG->edgenum));   //输入顶点数和边数
    printf("  输入连通网的%d个顶点信息：",EG->vertexnum);
    getchar();
    for(i=0;i<EG->vertexnum;i++)      //输入顶点信息
        scanf("%c",&(EG->vertexs[i]));
    printf("  输入%d个点的坐标(0<=i,j<=10) 和 权值(w<10)：\n",EG->edgenum);
    for(k=0;k<EG->edgenum;k++)     //输入e条边
    {
        scanf("%d%d%d",&EG->edges[k].initial,&EG->edges[k].end,&EG->edges[k].weight);
    }
}
void show_ELGgraph(ELGraph *EG)
{//输出连通网
    int j;
    printf("创建的 连通图 为：\n");
    for(j=0;j<EG->edgenum;j++)
        printf("|%d <%d> %d|\n",EG->edges[j].initial,EG->edges[j].weight,EG->edges[j].end);
}


void mintree_Prim(MGraph *G,int u,ClosEdge closedge)
{//从第u个顶点出发构造最小生成树，最小生成树顶点信息存放在数组closedge中
    int i,j,k=0,w;
    for(i=0;i<G->vertexnum;i++)  //辅助数组初始化
    {
        if(i!=u)
        {
            closedge[i].adjvertex=G->vertexs[u];
            closedge[i].lowcost=G->arcs[u][i];
            //printf("[%c %d]\n",closedge[i].adjvertex,closedge[i].lowcost);
        }
    }
    
    closedge[u].lowcost=0;  //初始，U={u}
    for(i=0;i<G->vertexnum;i++)  //选择其余的G->vertexnum-1个顶点
    {
        w=INFINITY;
        for(j=0;j<G->vertexnum;j++)
            if(closedge[j].lowcost!=0 && closedge[j].lowcost<w)
            {
                w=closedge[j].lowcost;
                k=j;  //求出生成树的下一个顶点k
                //printf("<%d %d>\n",w,k);
            }
        closedge[k].lowcost=0;  //第k顶点并入U集
        for(j=0;j<G->vertexnum;j++)  //新顶点并入U后，修改辅助数组
            if(G->arcs[k][j]<closedge[j].lowcost)
            {
                closedge[j].adjvertex=G->vertexs[k];
                closedge[j].lowcost=G->arcs[k][j];
                //printf("|[%c %d]|\n",closedge[j].adjvertex,closedge[j].lowcost);
            }
        /*
        //检验
        printf("closedge[j].lowcost:");
        for(j=0;j<G->vertexnum;j++)
            printf(" %d",closedge[j].lowcost);
        printf("\n");
        printf("closedge[j].adjvertex:");
        for(j=0;j<G->vertexnum;j++)
            printf(" %c",closedge[j].adjvertex);
        printf("\n");
         */
    }
    printf("\n打印最小生成树的各条边:\n");
    for(i=0;i<G->vertexnum;i++)  //打印最小生成树的各条边
    {
        if(i!=u)
        {
            for(j=0;j<G->vertexnum;j++)
                if(closedge[i].adjvertex==G->vertexs[j])
                    break;
            printf("%c<->%c,weight:%d\n",closedge[i].adjvertex,G->vertexs[i],G->arcs[i][j]);
        }
    }
    
}

ELGraph sort(ELGraph G, int n)
{//对图G的边表按 权值weight 从小到大排序
    int i,j;
    for(i=1;i<=n;i++)
    {
        for(j=0;j<n-i;j++)
        {
            if(G.edges[j].weight>G.edges[j+1].weight)
            {
                ENode t = G.edges[j];
                G.edges[j] = G.edges[j+1];
                G.edges[j+1] = t;
            }
        }
    }
    printf("排序后 的 连通图 为：\n");
    for(j=0;j<n;j++)
        printf("|%d <%d> %d|\n",G.edges[j].initial,G.edges[j].weight,G.edges[j].end);
    return G;
}

void mintree_Kruskal(ELGraph EG,ENode TE[])
{//用 Kruskal算法构成图 G的最小生成树,最小生成树存放在 TE[]中
    int i,j,k;
    int s1,s2;
    int f[MaxVertexNum];
    for(i=0;i<EG.vertexnum;i++)  //初始化f数组
        f[i]=i;
    EG=sort(EG,EG.edgenum);  //对图G的边表按 权值weight 从小到大排序
    j=0;
    k=0;
    while(k<EG.vertexnum-1)  //选n-1条边
    {
        //printf("|%d %d|\n",EG.edges[j].initial,EG.edges[j].end);
        s1=f[EG.edges[j].initial];
        s2=f[EG.edges[j].end];
        //printf("[%d %d %d]",EG.edges[j].initial,EG.edges[j].end,k);
        if(s1!=s2)   //产生一条最小边
        {
            TE[k].initial=EG.edges[j].initial;
            TE[k].end=EG.edges[j].end;
            TE[k].weight=EG.edges[j].weight;
            k++;
            for(i=0;i<EG.vertexnum;i++)
                if(f[i]==s2)
                    f[i]=s1;  //修改连通的编号
        }
        /*
        for(i=0;i<EG.vertexnum;i++)
            printf("%d ",f[i]);
        printf("\n");
         */
        j++;
    }
    for(i=0; i<EG.vertexnum-1; i++)
        printf("%c<->%c,weight:%d\n",EG.vertexs[TE[i].initial],EG.vertexs[TE[i].end],TE[i].weight);
}



int main()
{
    MGraph MG=init_mgraph();     //初始邻接矩阵
    ClosEdge closedge;
    creatgraph(&MG);           //创建邻接矩阵
    show_MGgraph(&MG);            //打印邻接矩阵
    mintree_Prim(&MG, 0, closedge);   //Prim求最小生成树
    printf("\n");
    
    
    ELGraph EG=init_elgraph();  //初始化连通网
    ENode TE[MaxVertexNum];
    createlgraph(&EG);       //创建连通网
    show_ELGgraph(&EG);        //打印连通表
    mintree_Kruskal(EG, TE);   //Lruskal求最小生成树
}

/*
 测试数据：
5 7
0 1 3
0 2 6
0 3 4
1 2 7
2 3 2
2 4 8
3 4 9
 
6 10
1 2 6
1 3 1
1 4 5
2 3 5
2 5 3
3 4 5
3 5 6
3 6 4
4 6 2
5 6 6
 
4 4
0 1 3
0 2 4
1 2 2
3 0 6
*/

/*
 邻接矩阵建立：
   输入顶点数和边数：5 7
   输入5个顶点信息:abcde  输入5个点的坐标(0<=i,j<=10) 和 权值(w<10)：
 0 1 3
 0 2 6
 0 3 4
 1 2 7
 2 3 2
 2 4 8
 3 4 9
 创建的 无向图 邻接矩阵 为：
  10  3  6  4 10
   3 10  7 10 10
   6  7 10  2  8
   4 10  2 10  9
  10 10  8  9 10
 a<->b,weight:3
 d<->c,weight:2
 a<->d,weight:4
 c<->e,weight:8
 
 建立连通网：
   输入顶点数和边数：5 7
   输入连通网的5个顶点信息：01234
   输入7个点的坐标(0<=i,j<=10) 和 权值(w<10)：
  0 1 3
  0 2 6
  0 3 4
  1 2 7
  2 3 2
  2 4 8
  3 4 9
 创建的 连通图 为：
 |0 <3> 1|
 |0 <6> 2|
 |0 <4> 3|
 |1 <7> 2|
 |2 <2> 3|
 |2 <8> 4|
 |3 <9> 4|
 排序后 的 连通图 为：
 |2 <2> 3|
 |0 <3> 1|
 |0 <4> 3|
 |0 <6> 2|
 |1 <7> 2|
 |2 <8> 4|
 |3 <9> 4|
 2<->3,weight:2
 0<->1,weight:3
 0<->3,weight:4
 2<->4,weight:8
 
 建立连通网：
   输入顶点数和边数：5 7
   输入连通网的5个顶点信息：abcde
   输入7个点的坐标(0<=i,j<=10) 和 权值(w<10)：
 0 1 3
 0 2 6
 0 3 4
 1 2 7
 2 3 2
 2 4 8
 3 4 9
 创建的 连通图 为：
 |0 <3> 1|
 |0 <6> 2|
 |0 <4> 3|
 |1 <7> 2|
 |2 <2> 3|
 |2 <8> 4|
 |3 <9> 4|
 排序后 的 连通图 为：
 |2 <2> 3|
 |0 <3> 1|
 |0 <4> 3|
 |0 <6> 2|
 |1 <7> 2|
 |2 <8> 4|
 |3 <9> 4|
 c<->d,weight:2
 a<->b,weight:3
 a<->d,weight:4
 c<->e,weight:8
 */
