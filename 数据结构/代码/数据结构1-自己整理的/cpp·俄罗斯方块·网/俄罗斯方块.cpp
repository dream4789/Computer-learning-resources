#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
using namespace std;

#define A1 0//A代表长条型，B为方块，C为L型，D为闪电型（实在无法描述那个形状）
#define A2 1

#define B 2

#define C11 3
#define C12 4
#define C13 5
#define C14 6

#define C21 7
#define C22 8
#define C23 9
#define C24 10

#define D11 11
#define D12 12

#define D21 13
#define D22 14

void SetPos(int i,int j)//设定光标位置
{
	COORD pos={i,j};
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(Out, pos);
}

int sharp[15][8]=
{
	{0,0,1,0,2,0,3,0},{0,0,0,1,0,2,0,3},
	{0,0,1,0,0,1,1,1},
	{0,0,1,0,1,1,1,2},{0,1,1,1,2,0,2,1},{0,0,0,1,0,2,1,2},{0,0,0,1,1,0,2,0},
	{1,0,1,1,1,2,0,2},{0,0,0,1,1,1,2,1},{0,0,0,1,0,2,1,0},{0,0,1,0,2,0,2,1},
	{0,0,0,1,1,1,1,2},{0,1,1,0,1,1,2,0},
	{0,1,0,2,1,0,1,1},{0,0,1,0,1,1,2,1}
};//这个2维数组是用来保存各个形状位置的

int high[15]={4,1,2,2,3,2,3,2,3,2,3,2,3,2,3};//这个数组是用来保存各个形状高度的

class Box//俄罗斯方块类
{
    private:
	   int map[23][12];//画面坐标
	   int hotpoint[2];//热点（即当前活动的点，所有图形都是相当此点绘制的）
	   int top;//当前最高位置
	   int point;//分数
	   int level;//等级
	   int ID;//当前活动图形的ID号
   public:
	   Box()//初始化
	   {
		   int i,j;
		   for(i=0;i<23;i++)
			   for(j=0;j<12;j++)
				   map[i][j]=0;
		   hotpoint[0]=0;
		   hotpoint[1]=5;
		   point=0;
		   level=1;
		   top=99;
		   ID=0;
	   }
	   void DrawMap();//画界面
	   int Judge(int x,int y);//判断当前位置能否绘制图形
	   void Welcome();//欢迎界面
	   void DrawBox(int x,int y,int num);//绘制图形
	   void Redraw(int x,int y,int num);//擦除图形
	   void Run();//运行
	   void Turn();//转动方块
	   void UpdataMap();//更新画面
};

void Box::DrawMap()//画界面
{
	int i;

	for(i=0;i<14;i++)
	{
		 SetPos(i*2,0);
		 cout<<"■";
	}
	for(i=1;i<=24;i++)
	{
		SetPos(0,i);
		cout<<"■";
		SetPos(13*2,i);
		cout<<"■";
	}
	for(i=0;i<14;i++)
	{
		 SetPos(i*2,24);
		 cout<<"■";
	}
	
	i=15;
	for(i=15;i<=25;i++)
	{
		 SetPos(i*2,0);
		 cout<<"■";
	}
	for(i=1;i<=8;i++)
	{
		SetPos(15*2,i);
		cout<<"■";
		SetPos(25*2,i);
		cout<<"■";
	}
	for(i=15;i<=25;i++)
	{
		 SetPos(i*2,9);
		 cout<<"■";
	}

	SetPos(16*2,16);
	cout<<"俄罗斯方块";
	SetPos(16*2,17);
	cout<<"分数："<<point;
	SetPos(16*2,18);
	cout<<"等级："<<level;
}

void Box::DrawBox(int x,int y,int num)//绘制图形
{
	 int i;
	 int nx,ny;
	 for(i=0;i<4;i++)
	{ 
		nx=x+sharp[num][i*2];
		ny=y+sharp[num][i*2+1];
		SetPos((ny+1)*2,nx+1);//利用sharp数组相对于点x,y绘制形状
		cout<<"■";
	}
}

void Box::Redraw(int x,int y,int num)//擦除图形，原理同上
{
	 int i;
	 int nx,ny;
	 for(i=0;i<4;i++)
	{ 
		nx=x+sharp[num][i*2];
		ny=y+sharp[num][i*2+1];
		SetPos((ny+1)*2,nx+1);
		cout<<" ";
	}
}

void Box::Turn()//转动图形，单纯的该ID而已
{
	switch(ID)
	{
	   case A1: ID=A2; break;
	   case A2: ID=A1; break;

	    case B: ID=B; break;

		case C11: ID=C12; break;
		case C12: ID=C13; break;
		case C13: ID=C14; break;
		case C14: ID=C11; break;

		case C21: ID=C22; break;
		case C22: ID=C23; break;
		case C23: ID=C24; break;
		case C24: ID=C21; break;
		
		case D11: ID=D12; break;
		case D12: ID=D11; break;

		case D21: ID=D22; break;
		case D22: ID=D21; break;
	}

}

void Box::Welcome()//欢迎界面
{
	char x;
	while(1)
	{
	  system("cls");
	  cout<<"■■■■■■■■■■■■■■■■■■■"<<endl;
	  cout<<"■    俄罗斯方块控制台版（不闪屏）  ■"<<endl;
	  cout<<"■■■■■■■■■■■■■■■■■■■"<<endl;
	  cout<<"■     A,D左右移动  S向下加速       ■"<<endl;
	  cout<<"■        空格键转动方块            ■"<<endl;
	  cout<<"■■■■■■■■■■■■■■■■■■■"<<endl;
	  cout<<"■                                  ■"<<endl;
	  cout<<"■                                  ■"<<endl;
	  cout<<"■                                  ■"<<endl;
	  cout<<"■         按1-9选择等级！！        ■"<<endl;
	  cout<<"■                                  ■"<<endl;
	  cout<<"■                                  ■"<<endl;
	  cout<<"■■■■■■■■■■■■■■■■■■■"<<endl;
	  SetPos(8,10);
	  x=getch();
	  if(x<='9'&&x>='1')//设置等级
	  {
		  level=x-'0';
		  break;
	  }
	}
}

void Box::UpdataMap()//更新画面（关键）
{
	 int clear;
	 int i,j,k;
	 int nx,ny;
	 int flag;
	 for(i=0;i<4;i++)//更新map数组的信息
	{ 
		nx=hotpoint[0]+sharp[ID][i*2];
		ny=hotpoint[1]+sharp[ID][i*2+1];
		map[nx][ny]=1;
	}
	 if(hotpoint[0]<top)//如果热点高于顶点则更新顶点
		 top=hotpoint[0];
	 clear=0;//消除的格数
	 for(i=hotpoint[0];i<hotpoint[0]+high[ID];i++)
	 {
		 flag=0;
		 for(j=0;j<12;j++)//检测是否可以消除此行
		 {
			 if(map[i][j]==0)
			 {
				 flag=1;
				 break;
			 }
		 }
		 if(flag==0)//可以消除
		 {
			 for(k=i;k>=top;k--)//从当前位置向上所有的点下移一行
			 {
				 if(k==0)//最高点特殊处理
					 for(j=0;j<12;j++)
					 {
						 map[k][j]=0;
						 SetPos((j+1)*2,k+1);
						 cout<<" ";
					 }
				 else
				 {
					 for(j=0;j<12;j++)
					 {
						 map[k][j]=map[k-1][j];
						 SetPos((j+1)*2,k+1);
		                 if(map[k][j]==0)
						    cout<<" ";
						 else
							cout<<"■";
					 }
				 }

			 }
			 top++;//消除成功，最高点下移
			 clear++;
			 point+=clear*100;
		 }
	 }
       
	 SetPos(16*2,17);
	    cout<<"分数："<<point;
}

void Box::Run()//运行游戏
{
	int i=0;
	char x;
	int Count;//计数器
	int tempID;
	int temp;
	srand((int)time(0));
	ID=rand()%15;//随机生成ID和下一个ID
	tempID=rand()%15;
	DrawBox(hotpoint[0],hotpoint[1],ID);//绘制图形
	DrawBox(3,17,tempID);
	Count=1000-level*100;//等级决定计数
	while(1)
	{
		if(i>=Count)//时间到
		{
			i=0;//计数器清零
			if(Judge(hotpoint[0]+1,hotpoint[1]))//如果下个位置无效（即到底）
			{
				 UpdataMap();//更新画面
				 ID=tempID;//生成新ID，用原等待ID替换为当前ID
				 hotpoint[0]=0;//热点更新
				 hotpoint[1]=5;
                 Redraw(3,17,tempID);
				 tempID=rand()%15;
	             DrawBox(hotpoint[0],hotpoint[1],ID);
	             DrawBox(3,17,tempID);
				 if(Judge(hotpoint[0],hotpoint[1]))//无法绘制开始图形，游戏结束
				 {
					 system("cls");
					 SetPos(25,15);
					 cout<<"游戏结束！！！最终得分为："<<point<<endl;
					 system("pause");
					 exit(0);
				 }

            }
			else
			{
				Redraw(hotpoint[0],hotpoint[1],ID);//没有到底，方块下移一位
			    hotpoint[0]++;//热点下移
				DrawBox(hotpoint[0],hotpoint[1],ID);
			}

		}
		if(kbhit())//读取键盘信息
		{
			x=getch();
			if(x=='a'||x=='A')//左移
			{
				 if(Judge(hotpoint[0],hotpoint[1]-1)==0)
				 {
					 Redraw(hotpoint[0],hotpoint[1],ID);
					 hotpoint[1]-=1;
				     DrawBox(hotpoint[0],hotpoint[1],ID);
				 }
			}
			if(x=='d'||x=='D')//右移
			{
			     if(Judge(hotpoint[0],hotpoint[1]+1)==0)
				 {
					 Redraw(hotpoint[0],hotpoint[1],ID);
					 hotpoint[1]+=1;
				     DrawBox(hotpoint[0],hotpoint[1],ID);
				 }
			}
			if(x=='s'||x=='S')//向下加速
			{
			     if(Judge(hotpoint[0]+1,hotpoint[1])==0)
				 {
					 Redraw(hotpoint[0],hotpoint[1],ID);
					 hotpoint[0]+=1;
				     DrawBox(hotpoint[0],hotpoint[1],ID);
				 }
			}
			if(x==' ')//转动方块
			{
				temp=ID;
				Turn();
				if(Judge(hotpoint[0],hotpoint[1])==0)
				 {
					 Redraw(hotpoint[0],hotpoint[1],temp);
				     DrawBox(hotpoint[0],hotpoint[1],ID);
				 }
				else
				    ID=temp;
			}
			while(kbhit())//读掉剩下的键盘信息
				getch();
		}
		Sleep(1);//等待1毫秒
		i++;//计数器加1
    }
}

int Box::Judge(int x,int y)//判断当前是否可以绘制方块
{
	int i;
	int nx,ny;
	for(i=0;i<4;i++)
	{ 
		nx=x+sharp[ID][i*2];
		ny=y+sharp[ID][i*2+1];
		if(nx<0||nx>=23||ny<0||ny>=12||map[nx][ny]==1)//不能，返回1
			return 1;
	}
	return 0;
}

int main()//主函数
{
	Box game;
    game.Welcome();
	system("cls");
	game.DrawMap();
	game.Run();
	system("pause");
}
//很nice