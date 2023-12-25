#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 200
#define Row 10  //行
#define Col 10  //列

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
void print_Maze(PMaze m)  //打印迷宫
{
    for(int i=0;i<Row;i++)
    {
        for(int j=0;j<Col;j++)
            printf("%d ",m->map[i][j]);
        printf("\n");
    }
    printf("\n");
}
void init_Maze(PMaze m,int map[Row][Col])  //初始化迷宫
{
    for(int i=0;i<Row;i++)
        for(int j=0;j<Col;j++)
            m->map[i][j]=map[i][j];
}
int Judge_Enter(Position en)  //判断入口是否合法
{
    if((en.x>=0 || en.x<Row) && (en.y>=0 || en.y<Col))
        return 1;
    return 0;
}
int Judge_Exit(Position set,Position en)  //判断是否为出口
{
    if((set.x==0||set.y==0||set.x==Col-1||set.y==Row-1)&&(set.x!=en.x||set.y!=en.y))
        return 1;
    return 0;
}
int Judge_Pase(PMaze m,Position set)  //判断是否可走
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
        m->map[set.x][set.y]=2;   //当前位置变为2
        //print_Maze(m);   //展示每一步
        if(Judge_Exit(set, en))
        {
            Tranlate(m);
            print_Maze(m);      //打印迷宫
            return;
        }
        else
        {
            next=set;
            next.x-=1;   //上
            if(Judge_Pase(m, next))
            {
                push(s, next);
                continue;
            }
            next=set;
            next.y-=1;   //左
            if(Judge_Pase(m, next))
            {
                push(s, next);
                continue;
            }
            next=set;
            next.y+=1;   //右
            if(Judge_Pase(m, next))
            {
                push(s, next);
                continue;
            }
            next=set;
            next.x+=1;   //下
            if(Judge_Pase(m, next))
            {
                push(s, next);
                continue;
            }
            m->map[set.x][set.y]=3;
            pop(s);  //出栈
        }
    }
    printf("迷宫不存在通路\n");
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
    printf("迷宫图一：\n");
    for(int i=0;i<3;i++)
    {
        init_Maze(m, arry_maze);
        if(i==0) print_Maze(m);
        en.x=a[i];
        en.y=b[i];
        printf("解迷宫一%d：入口：(%d,%d)\n",i+1,en.y,en.x);
        Start_Maze(m, en);
    }
    printf("迷宫图二：\n");
    init_Maze(m, arry_maze1);
    print_Maze(m);
    en.x=0;
    en.y=1;
    printf("解迷宫二：入口：(%d,%d)\n",en.y,en.x);
    Start_Maze(m, en);
    return 0;
}
/*
 迷宫图一：
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

 解迷宫一1：入口：(2,9)
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

 解迷宫一2：入口：(6,9)
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

 解迷宫一3：入口：(1,0)
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

 迷宫图二：
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

 解迷宫二：入口：(1,0)
 迷宫不存在通路
 */
