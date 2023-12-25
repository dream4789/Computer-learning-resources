//
//  main.c
//  ͼ���洢�ṹ���ڽӾ�����
//


#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 50

typedef char VertexType;
typedef int Edgetype;

typedef struct
{
    VertexType vertexs[MaxVertexNum];        //��������
    Edgetype arcs[MaxVertexNum][MaxVertexNum];  //�ڽӾ���
    int vertexnum,edgenum;                   //ͼ�ĵ�ǰ�������ͱ���
    //GraphType type;                      //ͼ�������־
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
{//���� ����ͼG ���ڽӾ���洢
    int i,j,k;
    printf("�ڽӾ�������\n");
    printf("  ���붥�����ͱ�����");
    scanf("%d %d",&(G->vertexnum),&(G->edgenum));   //���붥�����ͱ���
    printf("  ����%d������Ϣ:",G->vertexnum);
    getchar();
    for(i=0;i<G->vertexnum;i++)      //���붥����Ϣ�����������v0,v1,v2,v3
        scanf("%c",&(G->vertexs[i]));
    for(i=0;i<G->vertexnum;i++)        //��ʼ���ڽӾ���
        for(j=0;j<G->vertexnum;j++)
            G->arcs[i][j]=0;
    for(k=0;k<G->edgenum;k++)     //����e���ߣ������ڽӾ���
    {
        printf("  �����%d���������(0<=i,j<=%d)��",k+1,G->vertexnum-1);
        scanf("%d %d",&i,&j);     //����Ϊ 1 �ĵ����� (i,j)
        G->arcs[i][j]=1;
        
        G->arcs[j][i]=1;    //��������У���Ϊ����ͼ���ڽӾ�����
    }
}

void show_MGgraph(MGraph *G)
{//����ڽӾ���
    int i,j;
    printf("������ ����ͼ �ڽӾ��� Ϊ��\n");
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
 �ڽӾ�������
   ���붥�����ͱ�����8 9
   ����8������Ϣ:abcdefgh
   �����1���������(0<=i,j<=7)��0 1
   �����2���������(0<=i,j<=7)��0 2
   �����3���������(0<=i,j<=7)��1 3
   �����4���������(0<=i,j<=7)��1 4
   �����5���������(0<=i,j<=7)��3 7
   �����6���������(0<=i,j<=7)��4 7
   �����7���������(0<=i,j<=7)��2 5
   �����8���������(0<=i,j<=7)��2 6
   �����9���������(0<=i,j<=7)��5 6
 ������ ����ͼ �ڽӾ��� Ϊ��
  0 1 1 0 0 0 0 0
  1 0 0 1 1 0 0 0
  1 0 0 0 0 1 1 0
  0 1 0 0 0 0 0 1
  0 1 0 0 0 0 0 1
  0 0 1 0 0 0 1 0
  0 0 1 0 0 1 0 0
  0 0 0 1 1 0 0 0
 */
