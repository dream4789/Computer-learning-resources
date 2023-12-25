//
//  main.c
//  ͼ���洢�ṹ���ڽӱ���
//

//   [   vertex   (������)  | firstedg���߱�ͷָ�룩        ]           [������]
//   [ adjvertex (�ڽӵ���) |  next��ָ����               ]          [����]
//   [ adjvertex (�ڽӵ���) |  info(������Ϣ) | next(ָ����) ]          [��Ȩͼ�ı߱�ṹ]


#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 30  /*��󶥵���Ϊ 30*/

typedef char VertexType;
typedef int InfoType;


typedef struct node {   //����w
    int adjvertex;   //�ڽӵ���,һ���Ǵ�Ŷ����Ӧ����Ż��ڱ�ͷ�����е��±�
    InfoType info;   //���(��)��ص���Ϣ
    struct node * next;   //ָ����һ���ڽӵ��ָ����
}EdgeNode;

typedef struct vnode {  //������
    VertexType vertex;    //������
    EdgeNode * firstedge;   //�߱�ͷָ��
}VertexNode;

typedef struct {
    VertexNode adjlist[MaxVertexNum];   //�ڽӱ�
    int vertexNum,edgeNum;   //�������ͱ���
}ALGraph;  //ALGraph�����ڽӱ�ʽ�洢��ͼ����

ALGraph init_alraph(void)
{//���ٿռ�
    ALGraph *G;
    G=(ALGraph *)malloc(sizeof(ALGraph));
    if(G)
        return *G;
    exit(0);
}

void CreateALGraph(ALGraph *G)
{//���� ����ͼG ���ڽӱ�洢
    int i,j,k;
    EdgeNode *p,*s;
    printf("�ڽӱ�����\n");
    printf("  ���붥�����ͱ���:");
    scanf("%d%d",&(G->vertexNum),&(G->edgeNum));   //���˶������ͱ���
    printf("  ����%d��������Ϣ:",G->vertexNum);
    getchar();
    for(i=0;i<G->vertexNum;i++)                //������n������Ķ����
    {
        scanf("%c",&(G->adjlist[i].vertex));    //���˶�����Ϣ v0,v1,v2,v3
        G->adjlist[i].firstedge=NULL;     //����ı߱�ͷָ����Ϊ��
    }
    for(k=0;k<G->edgeNum;k++)             //�����߱�
    {
        printf("  �����%d���߱�����(0<=i,j<=%d)��",k+1,G->vertexNum-1);
        scanf("%d%d",&i,&j);          //�����<Vi,Vj>�Ķ����Ӧ���
        p=(EdgeNode*)malloc(sizeof(EdgeNode));    //�����±߱���p*
        p->adjvertex=j;           //�ڽӵ����Ϊj
        p->next=G->adjlist[i].firstedge;   //���±߱��� p���˵����� Vi ������ͷ��
        G->adjlist[i].firstedge=p;

        //�������´��룬Ϊ��������ͼ
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvertex = i;        //�ڽӵ����Ϊi
        s->next = G->adjlist[j].firstedge;
        G->adjlist[j].firstedge = s;
        
    }
}

void show_ALgraph(ALGraph *G)
{//����ڽӱ�
    int i;
    EdgeNode *p;
    printf("������ ����ͼ �ڽӱ� Ϊ��\n");
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
 �ڽӱ�����
   ���붥�����ͱ���:8 9
   ����8��������Ϣ:abcdefgh
   �����1���߱�����(0<=i,j<=7)��0 1
   �����2���߱�����(0<=i,j<=7)��0 2
   �����3���߱�����(0<=i,j<=7)��1 3
   �����4���߱�����(0<=i,j<=7)��1 4
   �����5���߱�����(0<=i,j<=7)��3 7
   �����6���߱�����(0<=i,j<=7)��4 7
   �����7���߱�����(0<=i,j<=7)��2 5
   �����8���߱�����(0<=i,j<=7)��2 6
   �����9���߱�����(0<=i,j<=7)��5 6
 ������ ����ͼ �ڽӱ� Ϊ��
  <a> ->c->b
  <b> ->e->d->a
  <c> ->g->f->a
  <d> ->h->b
  <e> ->h->b
  <f> ->g->c
  <g> ->f->c
  <h> ->e->d
 */
