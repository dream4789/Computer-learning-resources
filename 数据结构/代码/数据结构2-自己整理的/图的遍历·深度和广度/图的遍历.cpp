//
//  main.c
//  ͼ���������������
//
//  �ڽӱ�
//  ������                        ����
//  [  vertex  |  firstedge  ] -> [  adjvertex  |  next  ]
//  ��Ȩͼ�߱�ṹ��
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

//�ڽӾ���
typedef struct
{
    VertexType vertexs[MaxVertexNum];        //��������
    Edgetype arcs[MaxVertexNum][MaxVertexNum];  //�ڽӾ���
    int vertexnum,edgenum;                   //ͼ�ĵ�ǰ�������ͱ���
    //GraphType type;                      //ͼ�������־
}MGraph;


//�ڽӱ�
typedef struct node {   //��Ȩͼ����
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
    int vertexnum,edgenum;   //�������ͱ���
}ALGraph;  //ALGraph�����ڽӱ�ʽ�洢��ͼ����

int visited[MaxVertexNum];


//����
typedef int datatype;

typedef struct{
    datatype data[maxsize];
    int front,rear;
}seqqueue,*pseqqueue;

pseqqueue init_seqqueue(void)
{//��������
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
{//�����п�
    if(q&&q->front==q->rear)
        return 1;
    else
        return 0;
}

int in_seqqueue(pseqqueue q,datatype x)
{//���
    if((q->rear+1)%maxsize==q->front)
    {
        printf("����");
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
{//����
    if(empty_seqqueue(q))
    {
        printf("�ӿ�");
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

void CreateALGraph(ALGraph *G)
{//���� ����ͼG ���ڽӱ�洢
    int i,j,k;
    EdgeNode *p,*s;
    printf("�ڽӱ�����\n");
    printf("  ���붥�����ͱ���:");
    scanf("%d%d",&(G->vertexnum),&(G->edgenum));   //���˶������ͱ���
    printf("  ����%d��������Ϣ:",G->vertexnum);
    getchar();
    for(i=0;i<G->vertexnum;i++)                //������n������Ķ����
    {
        scanf("%c",&(G->adjlist[i].vertex));    //���˶�����Ϣ v0,v1,v2,v3
        G->adjlist[i].firstedge=NULL;     //����ı߱�ͷָ����Ϊ��
    }
    for(k=0;k<G->edgenum;k++)             //�����߱�
    {
        printf("  �����%d���߱�����(0<=i,j<=%d)��",k+1,G->vertexnum-1);
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

void show_ALgraph(ALGraph *G)
{//����ڽӱ�
    int i;
    EdgeNode *p;
    printf("������ ����ͼ �ڽӱ� Ϊ��\n");
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
{//�ӵ�v�������������        <�������><�ڽӱ�>
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
        }//�ӳ�ʼ�����㣨v����ʼ��ָ���� ������ָ�� ��һ����ָ�ģ�1��False��Ԫ�أ��ٽ���Ԫ�ر�Ϊ�����㣬��ʼ�Ҵ� ������ָ�� ��ָ�ĵ�һ����1��Flase��Ԫ�ء�������û�У�1��Flase��Ԫ����ӳ�ʼ���������һ����ʼ�ң�
    }
}
void AL_DFStraverse(ALGraph G)
{//����ͼG           <�������><�ڽӱ�>
    int v;
    printf("����ͼ �ڽӱ� ������ȱ�����");
    for(v=0;v<G.vertexnum;v++)
        visited[v]=Flase;  //��־������ʼ��
    for(v=0;v<G.vertexnum;v++)
        if(!visited[v])
            AL_DFS(G,v);
}


void AL_BFS(ALGraph G,int v)
{//��v������������ȱ���ͼG��ʹ�ø�������q�ͷ��ʱ�־����visited      <�������><�ڽӱ�>
    EdgeNode *p;
    int u,w;
    pseqqueue q;       //����һ������
    q=init_seqqueue();      //�ÿն���
    printf("����ͼ �ڽӱ� ������ȱ�����");
    printf("%c",G.adjlist[v].vertex);     //����v
    visited[v]=True;   //�ѷ��ʱ�־��True
    in_seqqueue(q, v);
    while(!empty_seqqueue(q))
    {
        out_seqqueue(q,&u);     //������
        for(p=G.adjlist[u].firstedge;p;p=p->next)
        {
            w=p->adjvertex;
            if(!visited[w])
            {
                printf("->%c",G.adjlist[w].vertex);
                visited[w]=True;
                in_seqqueue(q, w);    //u��δ���ʵ��ڽӶ���w�����q
            }
        }//�ӳ�ʼ�����㣨v����ʼ��ָ�������ң�1��False��Ԫ�أ����ʲ���ӣ�������ϡ��ٳ���һ������Ԫ�أ�������Ϊ�����㣬ָ�������ң�1��False��Ԫ�أ����ʲ���ӣ�������ϡ����������������ȫTrue���ӳ�ʼ�����㣨v����һ����ʼ��
    }
    printf("\n");
}


void MG_DFS(MGraph *G,int V)
{//������ȱ�������,��V�ڵ㿪ʼ    <�ڽӾ���>
    int w;
    printf("%c",G->vertexs[V]);
    visited[V]=True;  //���Ϊ�Է���
    for(w=0;w<G->vertexnum;w++)
    {
        if(!visited[w]&&(G->arcs[V][w]!=0||G->arcs[w][V]!=0))  //δ���� �� ��Ӧ�����Ϊ1
        {
            printf("->");
            MG_DFS(G,w);
        }//�ȳ�ʼ�У�V��ѭ���ӵ�һ���ҵ����һ�У���һ��Ϊ��1��Flase������������ٰѴ����� �������� ��Ϊ ���������ڴ���ѭ���ӵ�һ���ҵ����һ�С��������ѭ����ĳһ���ж����ʹ������ٴӳ�ʼ�У�V����ʼ�ң�
    }
    
}
void MG_DFStraverse(MGraph *G)
{//������ȱ������нڵ�          <�ڽӾ���>
    int i;
    for(i=0;i<G->vertexnum;i++)
        visited[i] = Flase;
    printf("����ͼ �ڽӾ��� ������ȱ�����");
    for(i=0;i<G->vertexnum; i++)
    {//�������������Ԫ�ض�����������ȱ�������
        if(!visited[i])
            MG_DFS(G, i);
    }
    printf("\n");
}

void MG_BFS(MGraph G,int v)
{//��vΪ�����㡣��G����BFS       <�������><�ڽӾ���>
    int i,j;
    pseqqueue q;
    q=init_seqqueue();
    printf("%c",G.vertexs[v]);     //����v
    visited[v]=True;     //���ʹ�
    in_seqqueue(q, v);
    while(!empty_seqqueue(q))
    {
        out_seqqueue(q,&i);     //������
        //printf("i=%d",i);  //i����Ϊ0��1��2��3��4���������������仯��
        for(j=0;j<G.vertexnum;j++)  //��������i����ѭ��j
        {
            if(G.arcs[i][j]==1&&!visited[j])   //�ڽӾ���Ϊ1����δ����
            {
                printf("->%c",G.vertexs[j]);     //����
                visited[j]=True;
                in_seqqueue(q, j);    //j���
            }//�ӳ�ʼ�У�V����ʼ����Ϊ��1��Flase����Ԫ�أ������������ӣ�һ�н����ˣ�����һ��Ԫ�ص����У��ٴ���һ�п�ʼ�ң���Ϊ��1��Flase����Ԫ�أ������������ӣ�һ�н������ٳ�����һ��Ԫ�ء���
        }
    }
}

void MG_BFStraverse(MGraph G)
{//����ͼG          <�������><�ڽӾ���>
    int v;
    for(v=0;v<G.vertexnum;v++)
        visited[v]=Flase;
    printf("����ͼ �ڽӾ��� ������ȱ�����");
    for(v=0;v<G.vertexnum;v++)
        if(!visited[v])  //vδ���ʹ�����v��ʼBFS
            MG_BFS(G,v);
    printf("\n");
}



int main()
{
    
    MGraph MG=init_mgraph();
    creatgraph(&MG);
    show_MGgraph(&MG);
    
    MG_BFStraverse(MG);       //�ڽӾ��󣬹�ȣ�����
    MG_DFStraverse(&MG);      //�ڽӾ�����ȣ�����
    

    ALGraph AL=init_alraph();
    CreateALGraph(&AL);
    show_ALgraph(&AL);
    
    AL_BFS(AL, 0);         //�ڽӱ���ȣ�����
    AL_DFStraverse(AL);    //�ڽӱ���ȣ�����
    
    printf("\n");
    
    return 0;
}


/*
 �ڽӾ�������
   ���붥�����ͱ�����8 9
   ����8������Ϣ:abcdefgh
   �����1���������(0<=i,j<=8)��0 1
   �����2���������(0<=i,j<=8)��0 2
   �����3���������(0<=i,j<=8)��1 3
   �����4���������(0<=i,j<=8)��1 4
   �����5���������(0<=i,j<=8)��3 7
   �����6���������(0<=i,j<=8)��4 7
   �����7���������(0<=i,j<=8)��2 5
   �����8���������(0<=i,j<=8)��2 6
   �����9���������(0<=i,j<=8)��5 6
 ������ ����ͼ �ڽӾ��� Ϊ��
  0<b>c>0 0 0 0 0
  1 0 0<d>1 0 0 0
  1 0 0 0 0<f>1 0
  0 1 0 0 0 0 0<h>
  0 1 0 0 0 0 0 1
  0 0 1 0 0 0<g>0
  0 0 1 0 0 1 0 0
  0 0 0 1<e>0 0 0
 ����ͼ �ڽӾ��� ������ȱ�����a->b->c->d->e->f->g->h   //���
 ����ͼ �ڽӾ��� ������ȱ�����a->b->d->h->e->c->f->g   //���
 
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
  <a> ->c->b->��
  <b> ->e->d->a->��
  <c> ->g->f->a->��
  <d> ->h->b->��
  <e> ->h->b->��
  <f> ->g->c->��
  <g> ->f->c->��
  <h> ->e->d->��
 ����ͼ �ڽӱ� ������ȱ�����a->c->b->g->f->e->d->h   //���
 ����ͼ �ڽӱ� ������ȱ�����a->c->g->f->b->e->h->d   //���
 */
