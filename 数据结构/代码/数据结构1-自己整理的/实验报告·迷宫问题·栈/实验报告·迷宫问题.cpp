#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 200
#define Row 10  //��
#define Col 10  //��

typedef struct Position
{
    int x;
    int y;
}Position;

typedef struct
{
    Position arry[MAXSIZE];
    int top;
}seqstack,*pseqstack;

typedef struct
{
    int map[Row][Col];
}Maze,*PMaze;

pseqstack start(void)
{
    pseqstack s;
    s=(pseqstack)malloc(sizeof(seqstack));
    if(s)
        s->top=-1;
    return s;
}

int empty(pseqstack s)
{
    if(s->top==-1)
        return 1;
    else
        return 0;
}

int push(pseqstack s,Position x)
{
    if(s->top==MAXSIZE-1)
        return 0;
    else
    {
        s->top++;
        s->arry[s->top]=x;
        return 1;
    }
}

void pop(pseqstack s)
{
    if(empty(s))
        return;
    else
        s->top--;
}

Position gettop(pseqstack s)
{
    if(empty(s))
        exit(0);
    else
        return s->arry[s->top];
}
void print_Maze(PMaze m)  //��ӡ�Թ�
{
    for(int i=0;i<Row;i++)
    {
        for(int j=0;j<Col;j++)
            printf("%d ",m->map[i][j]);
        printf("\n");
    }
    printf("\n");
}
void init_Maze(PMaze m,int map[Row][Col])  //��ʼ���Թ�
{
    for(int i=0;i<Row;i++)
        for(int j=0;j<Col;j++)
            m->map[i][j]=map[i][j];
}
int Judge_Enter(Position en)  //�ж�����Ƿ�Ϸ�
{
    if((en.x>=0 || en.x<Row) && (en.y>=0 || en.y<Col))
        return 1;
    return 0;
}
int Judge_Exit(Position set,Position en)  //�ж��Ƿ�Ϊ����
{
    if((set.x==0||set.y==0||set.x==Col-1||set.y==Row-1)&&(set.x!=en.x||set.y!=en.y))
        return 1;
    return 0;
}
int Judge_Pase(PMaze m,Position set)  //�ж��Ƿ����
{
    if(m->map[set.x][set.y]==1)
        return 1;
    return 0;
}
void Tranlate(PMaze m)
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(m->map[i][j]==1||m->map[i][j]==3)
                m->map[i][j]=0;
            if(m->map[i][j]==2)
                m->map[i][j]=1;
        }
    }
}
void Start_Maze(PMaze m,Position en)
{
    pseqstack s=start();
    push(s, en);
    while (!empty(s))
    {
        Position set=gettop(s);
        Position next;
        m->map[set.x][set.y]=2;   //��ǰλ�ñ�Ϊ2
        //print_Maze(m);   //չʾÿһ��
        if(Judge_Exit(set, en))
        {
            Tranlate(m);
            print_Maze(m);      //��ӡ�Թ�
            return;
        }
        else
        {
            next=set;
            next.x-=1;   //��
            if(Judge_Pase(m, next))
            {
                push(s, next);
                continue;
            }
            next=set;
            next.y-=1;   //��
            if(Judge_Pase(m, next))
            {
                push(s, next);
                continue;
            }
            next=set;
            next.y+=1;   //��
            if(Judge_Pase(m, next))
            {
                push(s, next);
                continue;
            }
            next=set;
            next.x+=1;   //��
            if(Judge_Pase(m, next))
            {
                push(s, next);
                continue;
            }
            m->map[set.x][set.y]=3;
            pop(s);  //��ջ
        }
    }
    printf("�Թ�������ͨ·\n");
}
int main()
{
    PMaze m=(PMaze)malloc(sizeof(Maze));
    Position en;

    int arry_maze[Row][Col]={
    { 0, 1, 0, 0, 0, 0 ,0 ,0 ,0 ,0 },
    { 0, 1, 1, 0, 1, 0 ,0 ,0 ,1 ,0 },
    { 0, 0, 1, 0, 1, 1 ,1 ,1 ,1 ,0 },
    { 0, 0, 1, 1, 1, 0 ,0 ,0 ,1 ,0 },
    { 0, 0, 1, 0, 1, 1 ,0 ,1 ,1 ,0 },
    { 0, 1, 1, 0, 0, 1 ,0 ,0 ,0 ,0 },
    { 0, 0, 1, 0, 0, 1 ,1 ,1 ,0 ,0 },
    { 0, 0, 1, 0, 0, 0 ,0 ,1 ,0 ,0 },
    { 0, 0, 1, 0, 0, 0 ,1 ,1 ,0 ,0 },
    { 0, 0, 1, 0, 0, 0 ,1 ,0 ,0 ,0 }
    };
    int arry_maze1[Row][Col]={
    { 0, 1, 0, 0, 0, 0 ,0 ,0 ,0 ,0 },
    { 0, 1, 1, 0, 1, 0 ,0 ,0 ,1 ,0 },
    { 0, 0, 1, 0, 1, 1 ,1 ,1 ,1 ,0 },
    { 0, 0, 1, 1, 1, 0 ,0 ,0 ,1 ,0 },
    { 0, 0, 1, 0, 1, 1 ,0 ,1 ,1 ,0 },
    { 0, 1, 1, 0, 0, 1 ,0 ,0 ,0 ,0 },
    { 0, 0, 1, 0, 0, 1 ,1 ,1 ,0 ,0 },
    { 0, 0, 1, 0, 0, 0 ,0 ,1 ,0 ,0 },
    { 0, 0, 1, 0, 0, 0 ,1 ,1 ,0 ,0 },
    { 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 }
    };
    
    int a[3]={9,9,0};
    int b[3]={2,6,1};
    printf("�Թ�ͼһ��\n");
    for(int i=0;i<3;i++)
    {
        init_Maze(m, arry_maze);
        if(i==0) print_Maze(m);
        en.x=a[i];
        en.y=b[i];
        printf("���Թ�һ%d����ڣ�(%d,%d)\n",i+1,en.y,en.x);
        Start_Maze(m, en);
    }
    printf("�Թ�ͼ����\n");
    init_Maze(m, arry_maze1);
    print_Maze(m);
    en.x=0;
    en.y=1;
    printf("���Թ�������ڣ�(%d,%d)\n",en.y,en.x);
    Start_Maze(m, en);
    return 0;
}
/*
 �Թ�ͼһ��
 0 1 0 0 0 0 0 0 0 0
 0 1 1 0 1 0 0 0 1 0
 0 0 1 0 1 1 1 1 1 0
 0 0 1 1 1 0 0 0 1 0
 0 0 1 0 1 1 0 1 1 0
 0 1 1 0 0 1 0 0 0 0
 0 0 1 0 0 1 1 1 0 0
 0 0 1 0 0 0 0 1 0 0
 0 0 1 0 0 0 1 1 0 0
 0 0 1 0 0 0 1 0 0 0

 ���Թ�һ1����ڣ�(2,9)
 0 1 0 0 0 0 0 0 0 0
 0 1 1 0 0 0 0 0 0 0
 0 0 1 0 0 0 0 0 0 0
 0 0 1 0 0 0 0 0 0 0
 0 0 1 0 0 0 0 0 0 0
 0 0 1 0 0 0 0 0 0 0
 0 0 1 0 0 0 0 0 0 0
 0 0 1 0 0 0 0 0 0 0
 0 0 1 0 0 0 0 0 0 0
 0 0 1 0 0 0 0 0 0 0

 ���Թ�һ2����ڣ�(6,9)
 0 1 0 0 0 0 0 0 0 0
 0 1 1 0 0 0 0 0 0 0
 0 0 1 0 0 0 0 0 0 0
 0 0 1 1 1 0 0 0 0 0
 0 0 0 0 1 1 0 0 0 0
 0 0 0 0 0 1 0 0 0 0
 0 0 0 0 0 1 1 1 0 0
 0 0 0 0 0 0 0 1 0 0
 0 0 0 0 0 0 1 1 0 0
 0 0 0 0 0 0 1 0 0 0

 ���Թ�һ3����ڣ�(1,0)
 0 1 0 0 0 0 0 0 0 0
 0 1 1 0 0 0 0 0 0 0
 0 0 1 0 0 0 0 0 0 0
 0 0 1 1 1 0 0 0 0 0
 0 0 0 0 1 1 0 0 0 0
 0 0 0 0 0 1 0 0 0 0
 0 0 0 0 0 1 1 1 0 0
 0 0 0 0 0 0 0 1 0 0
 0 0 0 0 0 0 1 1 0 0
 0 0 0 0 0 0 1 0 0 0

 �Թ�ͼ����
 0 1 0 0 0 0 0 0 0 0
 0 1 1 0 1 0 0 0 1 0
 0 0 1 0 1 1 1 1 1 0
 0 0 1 1 1 0 0 0 1 0
 0 0 1 0 1 1 0 1 1 0
 0 1 1 0 0 1 0 0 0 0
 0 0 1 0 0 1 1 1 0 0
 0 0 1 0 0 0 0 1 0 0
 0 0 1 0 0 0 1 1 0 0
 0 0 0 0 0 0 0 0 0 0

 ���Թ�������ڣ�(1,0)
 �Թ�������ͨ·
 */
