//
//  main.c
//  ͼ����С��������Prim��Kruskal
//
//  Created by ���� on 2021/11/27.
//

#include <stdio.h>
#include <stdlib.h>
#define INFINITY 10  //����һ��Ȩֵ�����ֵ
#define MaxVertexNum 30  //��󶥵���
#define MaxEdge 100

typedef char VertexType;
typedef int Edgetype;
typedef int WeightType;

typedef struct
{
    VertexType vertexs[MaxVertexNum];        //��������
    Edgetype arcs[MaxVertexNum][MaxVertexNum];  //�ڽӾ���
    int vertexnum,edgenum;      //ͼ�ĵ�ǰ�������ͱ���
}MGraph;

//Prim
typedef struct
{
    char adjvertex;  //ĳ�������ѹ���õĲ����������Ķ���֮��Ȩֵ��С�Ķ���
    int lowcost;  //ĳ�������ѹ���õĲ����������Ķ���֮�����СȨֵ
}ClosEdge[MaxVertexNum];  //��Prim����С������ʱ�ĸ�������

//Kruskal
typedef struct
{
    int initial;
    int end;
    WeightType weight;   //�ߵ�Ȩֵ
}ENode;
typedef struct
{
    int vertexnum,edgenum;  //�������,�ߵĸ���
    VertexType vertexs[MaxVertexNum];  //������Ϣ
    ENode edges[MaxVertexNum];  //�ߵ���Ϣ
}ELGraph;   //ע�⣺��ͼ�Ĵ洢�ṹ��ǰ����ܵļ��ֲ�һ��

MGraph init_mgraph(void)
{
    MGraph *G;
    G=(MGraph *)malloc(sizeof(MGraph));
    if(G)
        return *G;
    exit(0);
}

void creatgraph(MGraph *G)
{//���� ����ͼG ���ڽӾ���洢
    int i,j,k,w;
    printf("�ڽӾ�������\n");
    printf("  ���붥�����ͱ�����");
    scanf("%d %d",&(G->vertexnum),&(G->edgenum));   //���붥�����ͱ���
    printf("  ����%d��������Ϣ:",G->vertexnum);
    getchar();
    for(i=0;i<G->vertexnum;i++)      //���붥����Ϣ�����������v0,v1,v2,v3
        scanf("%c",&(G->vertexs[i]));
    for(i=0;i<G->vertexnum;i++)        //��ʼ���ڽӾ���
        for(j=0;j<G->vertexnum;j++)
            G->arcs[i][j]=INFINITY;
    printf("  ����%d���������(0<=i,j<=10) �� Ȩֵ(w<10)��\n",G->edgenum);
    for(k=0;k<G->edgenum;k++)     //����e���ߣ������ڽӾ���
    {
        scanf("%d %d %d",&i,&j,&w);     //����Ϊ 1 �ĵ����� (i,j)
        G->arcs[i][j]=w;
        G->arcs[j][i]=w;    //��������У���Ϊ����ͼ���ڽӾ�����
    }
}
void show_MGgraph(MGraph *G)
{//����ڽӾ���
    int i,j;
    printf("������ ����ͼ �ڽӾ��� Ϊ��\n");
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
{//���� ��ͨ��G �Ĵ洢
    int i,k;
    printf("������ͨ����\n");
    printf("  ���붥�����ͱ�����");
    scanf("%d %d",&(EG->vertexnum),&(EG->edgenum));   //���붥�����ͱ���
    printf("  ������ͨ����%d��������Ϣ��",EG->vertexnum);
    getchar();
    for(i=0;i<EG->vertexnum;i++)      //���붥����Ϣ
        scanf("%c",&(EG->vertexs[i]));
    printf("  ����%d���������(0<=i,j<=10) �� Ȩֵ(w<10)��\n",EG->edgenum);
    for(k=0;k<EG->edgenum;k++)     //����e����
    {
        scanf("%d%d%d",&EG->edges[k].initial,&EG->edges[k].end,&EG->edges[k].weight);
    }
}
void show_ELGgraph(ELGraph *EG)
{//�����ͨ��
    int j;
    printf("������ ��ͨͼ Ϊ��\n");
    for(j=0;j<EG->edgenum;j++)
        printf("|%d <%d> %d|\n",EG->edges[j].initial,EG->edges[j].weight,EG->edges[j].end);
}


void mintree_Prim(MGraph *G,int u,ClosEdge closedge)
{//�ӵ�u���������������С����������С������������Ϣ���������closedge��
    int i,j,k=0,w;
    for(i=0;i<G->vertexnum;i++)  //���������ʼ��
    {
        if(i!=u)
        {
            closedge[i].adjvertex=G->vertexs[u];
            closedge[i].lowcost=G->arcs[u][i];
            //printf("[%c %d]\n",closedge[i].adjvertex,closedge[i].lowcost);
        }
    }
    
    closedge[u].lowcost=0;  //��ʼ��U={u}
    for(i=0;i<G->vertexnum;i++)  //ѡ�������G->vertexnum-1������
    {
        w=INFINITY;
        for(j=0;j<G->vertexnum;j++)
            if(closedge[j].lowcost!=0 && closedge[j].lowcost<w)
            {
                w=closedge[j].lowcost;
                k=j;  //�������������һ������k
                //printf("<%d %d>\n",w,k);
            }
        closedge[k].lowcost=0;  //��k���㲢��U��
        for(j=0;j<G->vertexnum;j++)  //�¶��㲢��U���޸ĸ�������
            if(G->arcs[k][j]<closedge[j].lowcost)
            {
                closedge[j].adjvertex=G->vertexs[k];
                closedge[j].lowcost=G->arcs[k][j];
                //printf("|[%c %d]|\n",closedge[j].adjvertex,closedge[j].lowcost);
            }
        /*
        //����
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
    printf("\n��ӡ��С�������ĸ�����:\n");
    for(i=0;i<G->vertexnum;i++)  //��ӡ��С�������ĸ�����
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
{//��ͼG�ı߱� Ȩֵweight ��С��������
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
    printf("����� �� ��ͨͼ Ϊ��\n");
    for(j=0;j<n;j++)
        printf("|%d <%d> %d|\n",G.edges[j].initial,G.edges[j].weight,G.edges[j].end);
    return G;
}

void mintree_Kruskal(ELGraph EG,ENode TE[])
{//�� Kruskal�㷨����ͼ G����С������,��С����������� TE[]��
    int i,j,k;
    int s1,s2;
    int f[MaxVertexNum];
    for(i=0;i<EG.vertexnum;i++)  //��ʼ��f����
        f[i]=i;
    EG=sort(EG,EG.edgenum);  //��ͼG�ı߱� Ȩֵweight ��С��������
    j=0;
    k=0;
    while(k<EG.vertexnum-1)  //ѡn-1����
    {
        //printf("|%d %d|\n",EG.edges[j].initial,EG.edges[j].end);
        s1=f[EG.edges[j].initial];
        s2=f[EG.edges[j].end];
        //printf("[%d %d %d]",EG.edges[j].initial,EG.edges[j].end,k);
        if(s1!=s2)   //����һ����С��
        {
            TE[k].initial=EG.edges[j].initial;
            TE[k].end=EG.edges[j].end;
            TE[k].weight=EG.edges[j].weight;
            k++;
            for(i=0;i<EG.vertexnum;i++)
                if(f[i]==s2)
                    f[i]=s1;  //�޸���ͨ�ı��
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
    MGraph MG=init_mgraph();     //��ʼ�ڽӾ���
    ClosEdge closedge;
    creatgraph(&MG);           //�����ڽӾ���
    show_MGgraph(&MG);            //��ӡ�ڽӾ���
    mintree_Prim(&MG, 0, closedge);   //Prim����С������
    printf("\n");
    
    
    ELGraph EG=init_elgraph();  //��ʼ����ͨ��
    ENode TE[MaxVertexNum];
    createlgraph(&EG);       //������ͨ��
    show_ELGgraph(&EG);        //��ӡ��ͨ��
    mintree_Kruskal(EG, TE);   //Lruskal����С������
}

/*
 �������ݣ�
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
 �ڽӾ�������
   ���붥�����ͱ�����5 7
   ����5��������Ϣ:abcde  ����5���������(0<=i,j<=10) �� Ȩֵ(w<10)��
 0 1 3
 0 2 6
 0 3 4
 1 2 7
 2 3 2
 2 4 8
 3 4 9
 ������ ����ͼ �ڽӾ��� Ϊ��
  10  3  6  4 10
   3 10  7 10 10
   6  7 10  2  8
   4 10  2 10  9
  10 10  8  9 10
 a<->b,weight:3
 d<->c,weight:2
 a<->d,weight:4
 c<->e,weight:8
 
 ������ͨ����
   ���붥�����ͱ�����5 7
   ������ͨ����5��������Ϣ��01234
   ����7���������(0<=i,j<=10) �� Ȩֵ(w<10)��
  0 1 3
  0 2 6
  0 3 4
  1 2 7
  2 3 2
  2 4 8
  3 4 9
 ������ ��ͨͼ Ϊ��
 |0 <3> 1|
 |0 <6> 2|
 |0 <4> 3|
 |1 <7> 2|
 |2 <2> 3|
 |2 <8> 4|
 |3 <9> 4|
 ����� �� ��ͨͼ Ϊ��
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
 
 ������ͨ����
   ���붥�����ͱ�����5 7
   ������ͨ����5��������Ϣ��abcde
   ����7���������(0<=i,j<=10) �� Ȩֵ(w<10)��
 0 1 3
 0 2 6
 0 3 4
 1 2 7
 2 3 2
 2 4 8
 3 4 9
 ������ ��ͨͼ Ϊ��
 |0 <3> 1|
 |0 <6> 2|
 |0 <4> 3|
 |1 <7> 2|
 |2 <2> 3|
 |2 <8> 4|
 |3 <9> 4|
 ����� �� ��ͨͼ Ϊ��
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
