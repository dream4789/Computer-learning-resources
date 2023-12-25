#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
using namespace std;

HANDLE Mutex=CreateMutex(NULL,FALSE,NULL);//互斥对象

int GameOver=0;
int level=0;
int map[23][23];
//坦克种类，Normal为玩家坦克
#define Normal 0
#define Red 1
#define Blue 2
#define Green 3
//方向的宏定义
#define Up 0
#define Down 1
#define Left 2
#define Right 3
//地图标记的宏定义
#define Empty 0
#define Player 1
#define PlayerBullet 2
#define EnemyBullet 3
#define Enemy 4

int Kill;
int KillRed;
int KillGreen;
int EnemyExist;

void SetPos(int i,int j)//设定光标位置
{
	COORD pos={i,j};
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(Out, pos);
}

void HideCurSor(void)//隐藏光标
{
	CONSOLE_CURSOR_INFO info={1,0};
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(Out,&info);
}

int sharp[4][12]=
{
	{0,1,1,0,1,1,1,2,2,0,2,2},
	{0,0,0,2,1,0,1,1,1,2,2,1},
	{0,1,0,2,1,0,1,1,2,1,2,2},
	{0,0,0,1,1,1,1,2,2,0,2,1},
};//此数组用来保存坦克各个方向的形状信息

DWORD WINAPI Bulletfly(LPVOID lpParameter);//子弹函数申明
void Updata();//更新界面信息函数申明

class Tank//坦克类
{
private:
	int Direction;//方向
	int hotpoint[2];//活动点
	int Speed;//速度
	int FirePower;//火力
public:
	Tank(int dir,int hot1,int hot2,int typ,int spe,int firepow)//构造函数
	{
		Direction=dir;
		hotpoint[0]=hot1;
		hotpoint[1]=hot2;
		Type=typ;
		Speed=spe;
		FirePower=firepow;
	}
	int Type;//坦克的种类（详见宏定义）
	int ID;//坦克在MAP中的标记（详见宏定义）
	int FireEnable;//是否可以开火
	int Life;//生命值
	void Running();//运行函数
	int Judge(int x,int y,int ID);//判断是否可以绘制坦克
	void DrawTank();//重绘坦克
	void Redraw();//擦除坦克
	int GetSpeed()//获取速度
	{
		return Speed;
	}
	int GetFire()//获取火力
	{
		return FirePower;
	}
	int GetDirection()//获取方向
	{
		return Direction;
	}
	int GetHotX()//获取活动点坐标
	{
		return hotpoint[0];
	}
	int GetHotY()
	{
		return hotpoint[1];
	}
	void IncreaseFire()//火力+
	{
		FirePower++;
	}
	void IncreaseSpeed()//速度+
	{
		Speed++;
	}
	void ChangeDirection(int newD)//改变方向
	{
		Direction=newD;
	}
	void ChangePos(int x,int y)//改变活动点
	{
		hotpoint[0]=x;
		hotpoint[1]=y;
	}
};

Tank player(Right,0,0,Normal,1,1);//玩家
Tank enemy(Left,20,0,Red,1,1);//敌人

void Tank::DrawTank()//绘制坦克
{
	 int i;
	 int nx,ny;
	 if(Type==Red)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_RED);
		else if(Type==Blue)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_BLUE);
		else if(Type==Green)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_GREEN);
		else if(Type==Normal)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	 for(i=0;i<6;i++)
	{ 
		nx=hotpoint[0]+sharp[Direction][i*2];
		ny=hotpoint[1]+sharp[Direction][i*2+1];
		SetPos((ny+1)*2,nx+1);//利用sharp数组相对于点x,y绘制形状
		map[nx][ny]=ID;
		cout<<"■";
	}
}

void Tank::Redraw()//擦除坦克，原理同上
{
	 int i;
	 int nx,ny;
	 for(i=0;i<6;i++)
	{ 
		nx=hotpoint[0]+sharp[Direction][i*2];
		ny=hotpoint[1]+sharp[Direction][i*2+1];
		map[nx][ny]=Empty;
		SetPos((ny+1)*2,nx+1);
		cout<<" ";
	}
}

int Tank::Judge(int x,int y,int dir)//判断当前是否可以绘制坦克
{
	int i;
	int nx,ny;
	for(i=0;i<6;i++)
	{ 
		nx=x+sharp[dir][i*2];
		ny=y+sharp[dir][i*2+1];
		if(nx<0||nx>=23||ny<0||ny>=23||map[nx][ny]!=Empty)//不能绘制，返回1
			return 1;
	}
	return 0;
}


void Tank::Running()//坦克运行函数
{
	int newD;
	//坦克的运行
	while(1)
	{
		if(Life==0)
		{
			EnemyExist=0;//敌人不存在
			return;
		}
		if(GameOver==1)
			return;
		if(FireEnable==1&&GameOver==0)//如果可以开火
		{
			WaitForSingleObject(Mutex,INFINITE);//线程拥有互斥对象
			FireEnable=0;//设为不可开火
			HANDLE bullet=CreateThread(NULL,0,Bulletfly,&ID,0,NULL);//创建子弹线程
			CloseHandle(bullet);
			ReleaseMutex(Mutex);//释放互斥对象
			Sleep(100);
		}
		WaitForSingleObject(Mutex,INFINITE);//线程拥有互斥对象
		srand((int)time(0));
	    newD=rand()%4;
		
		if(newD==Up)//随机出新的方向并重新绘制坦克
		{
			Redraw();
			if(Judge(hotpoint[0]-1,hotpoint[1],newD)==0)
			{
				hotpoint[0]--;
				Direction=newD;
			}
			else
			{
				if(Judge(hotpoint[0],hotpoint[1],newD)==0)
					Direction=newD;
            }
		}
		else if(newD==Down)
		{
			Redraw();
			if(Judge(hotpoint[0]+1,hotpoint[1],newD)==0)
			{
				hotpoint[0]++;
				Direction=newD;
			}
			else
			{
				if(Judge(hotpoint[0],hotpoint[1],newD)==0)
					Direction=newD;
            }
		}
		else if(newD==Left)
		{
			Redraw();
			if(Judge(hotpoint[0],hotpoint[1]-1,newD)==0)
			{
				hotpoint[1]--;
				Direction=newD;
			}
			else
			{
				if(Judge(hotpoint[0],hotpoint[1],newD)==0)
					Direction=newD;
            }
		}
		else if(newD==Right)
		{
			Redraw();
			if(Judge(hotpoint[0],hotpoint[1]+1,newD)==0)
			{
				hotpoint[1]++;
				Direction=newD;
			}
			else
			{
				if(Judge(hotpoint[0],hotpoint[1],newD)==0)
					Direction=newD;
            }
		}
		if(GameOver==0&&Life!=0)
		   DrawTank();
		ReleaseMutex(Mutex);//释放互斥对象
		Sleep(500-80*Speed);
	}
}

/*********************子弹线程函数*******************/
DWORD WINAPI Bulletfly(LPVOID lpParameter)
{
	int *ID=(int *)lpParameter;//ID用来获取发射子弹坦克的ID
	int Pos[2];//子弹活动点
	int direction;
	int Speed;
	int type;
	int hit=0;//击中标记
	int oldx,oldy;//旧活动点
	int flag=0;//子弹是否有移动的标记
	if(*ID==Player)//如果是玩家坦克
	{
		type=PlayerBullet;
		direction=player.GetDirection();
		Speed=player.GetFire();
		Pos[0]=player.GetHotX();
		Pos[1]=player.GetHotY();
	}
    else if(*ID==Enemy)//如果是敌人坦克
	{
		type=EnemyBullet;
		direction=enemy.GetDirection();
		Speed=enemy.GetFire();
		Pos[0]=enemy.GetHotX();
		Pos[1]=enemy.GetHotY();
	}
	if(direction==Up)//根据坦克的位置和方向确定子弹的初始坐标
	{
		Pos[0]--;
		Pos[1]++;
	}
	else if(direction==Down)
	{
		Pos[0]+=3;
		Pos[1]++;
	}
	else if(direction==Left)
	{
		Pos[0]++;
		Pos[1]--;
	}
	else if(direction==Right)
	{
		Pos[0]++;
		Pos[1]+=3;
	}
	//子弹的运行
	while(1)
	{
		WaitForSingleObject(Mutex,INFINITE);//这个不再注释了。。。。。
		if(flag==1&&hit!=1)//擦除原位置
		{
    	   map[oldx][oldy]=Empty;
		   SetPos((oldy+1)*2,oldx+1);
		   cout<<" ";
		}
		if(GameOver==1)
			return 0;
		if(hit==1||Pos[0]<0||Pos[0]>22||Pos[1]<0||Pos[1]>22)//如果击中
		{
			ReleaseMutex(Mutex);
			Sleep(500);
			if(type==PlayerBullet)
				player.FireEnable=1;
			else if(type=EnemyBullet)
				enemy.FireEnable=1;
			break;
		}
		switch(map[Pos[0]][Pos[1]])//子弹经过的MAP的标记
		{
			
		   case Empty://如果是空位置就绘制子弹
			    map[Pos[0]][Pos[1]]=type;
				SetPos((Pos[1]+1)*2,Pos[0]+1);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout<<"■";
			    break;
		   case Player://如果是玩家位置
			   if(type!=PlayerBullet)
			   {
			      player.Life--;//生命减少
				  if(player.Life<=0)
					 GameOver=1;
			    }
			    Updata();
			    hit=1;
			    break;
		   case Enemy://如果是敌人位置
			    if(type!=PlayerBullet)
					hit=1;
				else
				{
					hit=1;
					Kill++;
					if(Kill%20==0&&player.Life<5)//击杀数++
						player.Life++;
					if(enemy.Type==Red)//如果击杀红坦克
					{
						KillRed++;
						if(KillRed%10==0&&player.GetFire()<5)
							player.IncreaseFire();
					}
					if(enemy.Type==Green)///如果击杀绿坦克
					{
						KillGreen++;
						if(KillGreen%10==0&&player.GetSpeed()<5)
							player.IncreaseSpeed();
					}
					enemy.Redraw();//擦除敌人
					enemy.Life=0;//敌人死亡
				}
				Updata();
			   break;
		}
		oldx=Pos[0];
		oldy=Pos[1];
		if(direction==Up)//子弹移动
		   Pos[0]--;
	     else if(direction==Down)
	    	Pos[0]++;
	     else if(direction==Left)
	    	Pos[1]--;
	    else if(direction==Right)
	    	Pos[1]++;
		 ReleaseMutex(Mutex);
		 flag=1;
		 Sleep(60-10*Speed);
    }
	return 0;
}


/*************************敌人线程函数***************************/
DWORD WINAPI TankRuning(LPVOID lpParameter)
{
	Sleep(400);
	int Pos;
	int Start[2];//敌人起始地址
	int typ;
	int fire;
	int spe;
	while(1)
	{
		if(GameOver==1)
			return 0;
	    srand((int)time(0));//随机出敌人起始地址
	    Pos=rand()%4;
	    if(Pos==0)
	    {
		     Start[0]=2;
		     Start[0]=2;
	    }
	    else if(Pos==1)
	    {
	     	Start[0]=2;
	    	Start[1]=18;
	     }
	     else if(Pos==2)
	    {
		    Start[0]=18;
		    Start[1]=2;
	     }
	     else if(Pos==3)
	    {
		   Start[0]=18;
		   Start[1]=18;
	    }
		 if(player.Judge(Start[0],Start[1],Down)==0)
			 break;
	}
	WaitForSingleObject(Mutex,INFINITE);
	srand((int)time(0));
	typ=rand()%3+1;//随机出敌人的种类
	if(typ==Blue)
	{
		spe=1+level;
		fire=1+level;
	}
	else if(typ==Red)
	{
		spe=1+level;
		fire=3+level;
	}
	else if(typ==Green)
	{
		spe=3+level;
		fire=1+level;
	}
    enemy=Tank(Down,Start[0],Start[1],typ,spe,fire);//重新生成敌人坦克
	enemy.ID=Enemy;
	enemy.Life=1;
	enemy.FireEnable=1;
	ReleaseMutex(Mutex);
	enemy.Running();
	return 0;
}


void Init()//初始化函数
{
	Kill=0;
	KillRed=0;
	KillGreen=0;
	player=Tank(Left,0,0,Normal,1,1);
	enemy=Tank(Left,0,0,Red,1,1);
	player.Life=2;
	player.FireEnable=1;
	enemy.Life=0;
	enemy.FireEnable=1;
	player.ID=Player;
	enemy.ID=Enemy;
	EnemyExist=0;
}

void Updata()//更新界面信息
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	int i;
	SetPos(53,0);
	cout<<"生命值：";
	SetPos(53,1);
	for(i=0;i<5;i++)
	{
		if(i<player.Life)
			cout<<"■";
		else
			cout<<" ";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_GREEN);
	SetPos(53,3);
	cout<<"移动速度：";
	SetPos(53,4);
	for(i=0;i<5;i++)
	{
		if(i<player.GetSpeed())
			cout<<"■";
		else
			cout<<" ";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_RED);
	SetPos(53,5);
	cout<<"火力：";
	SetPos(53,6);
	for(i=0;i<5;i++)
	{
		if(i<player.GetFire())
			cout<<"■";
		else
			cout<<" ";
	}
    SetPos(53,8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<"杀敌数："<<Kill;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_RED);
	SetPos(53,9);
	cout<<"杀死红坦克："<<KillRed;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_GREEN);
	SetPos(53,10);
	cout<<"杀死绿坦克："<<KillGreen;

}
void DrawMap()//画界面
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	system("cls");
	int i;
	for(i=0;i<25;i++)
	{
		 SetPos(i*2,0);
		 cout<<"■";
	}
	for(i=1;i<25;i++)
	{
		SetPos(0,i);
		cout<<"■";
		SetPos(24*2,i);
		cout<<"■";
	}
	for(i=0;i<25;i++)
	{
		 SetPos(i*2,24);
		 cout<<"■";
	}
	
	Updata();
	
}

void Welcome()//欢迎界面
{
	int x;
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	SetPos(10,5);
	cout<<"■■■■■■■■■■■■■■■■■■■■■■■■";
	SetPos(10,6);
	cout<<"■        坦克大战控制台版                    ■";
	SetPos(10,7);
	cout<<"■■■■■■■■■■■■■■■■■■■■■■■■";
	SetPos(10,8);
	cout<<"■       方向键移动，空格键射击               ■";
	SetPos(10,9);
	cout<<"■       敌人分为3种，蓝色为普通敌人          ■";
	SetPos(10,10);
	cout<<"■     红色敌人高射速，绿色敌人高机动性       ■";
	SetPos(10,11);
	cout<<"■ 每杀死10个红坦克，玩家射速提高(最高五级）  ■";
	SetPos(10,12);
	cout<<"■ 每杀死10个绿坦克，玩家移动性提高(最高五级）■";
	SetPos(10,13);
	cout<<"■   每杀死20个坦克，玩家生命+1（最高五格）   ■";
	SetPos(10,14);
	cout<<"■■■■■■■■■■■■■■■■■■■■■■■■";	
	SetPos(10,15);
	cout<<"■                                            ■";
	SetPos(10,16);
	cout<<"■           按1-3选择难度                    ■";
	SetPos(10,17);
	cout<<"■■■■■■■■■■■■■■■■■■■■■■■■";
	while(1)
	{
		x=getch();
		if(x<='3'&&x>='1')
			break;
	}
	level=x-'0'-1;
}

int main()
{
	Init();
	HideCurSor();
	Welcome();
	DrawMap();
	HANDLE temp;
	int newD;
	player.DrawTank();
	while(GameOver==0)
	{
		if(GetAsyncKeyState(VK_UP))//按键上
		{
			WaitForSingleObject(Mutex,INFINITE);
			newD=Up;
			player.Redraw();
			if(player.Judge(player.GetHotX()-1,player.GetHotY(),newD)==0)//移动玩家坦克，原理和敌人函数一样
			{
				player.ChangePos(player.GetHotX()-1,player.GetHotY());
				player.ChangeDirection(newD);
			}
			else
			{
				if(player.Judge(player.GetHotX(),player.GetHotY(),newD)==0)
					player.ChangeDirection(newD);
            }
			if(GameOver==0)
			   player.DrawTank();
			ReleaseMutex(Mutex);
			Sleep(200-player.GetSpeed()*20);//按键延迟，决定玩家坦克的速度
		}
		else if(GetAsyncKeyState(VK_DOWN))//按键下，同上
		{
			WaitForSingleObject(Mutex,INFINITE);
			newD=Down;
			player.Redraw();
			if(player.Judge(player.GetHotX()+1,player.GetHotY(),newD)==0)
			{
				player.ChangePos(player.GetHotX()+1,player.GetHotY());
				player.ChangeDirection(newD);
			}
			else
			{
				if(player.Judge(player.GetHotX(),player.GetHotY(),newD)==0)
					player.ChangeDirection(newD);
            }
			if(GameOver==0)
			   player.DrawTank();
			ReleaseMutex(Mutex);
			Sleep(200-player.GetSpeed()*20);
		}
		else if(GetAsyncKeyState(VK_RIGHT))//按键右，同上
		{
			WaitForSingleObject(Mutex,INFINITE);
			newD=Right;
			player.Redraw();
			if(player.Judge(player.GetHotX(),player.GetHotY()+1,newD)==0)
			{
				player.ChangePos(player.GetHotX(),player.GetHotY()+1);
				player.ChangeDirection(newD);
			}
			else
			{
				if(player.Judge(player.GetHotX(),player.GetHotY(),newD)==0)
					player.ChangeDirection(newD);
            }
			if(GameOver==0)
			   player.DrawTank();
			ReleaseMutex(Mutex);
			Sleep(200-player.GetSpeed()*20);
		}
		else if(GetAsyncKeyState(VK_LEFT))//按键左，同上
		{
			WaitForSingleObject(Mutex,INFINITE);
			newD=Left;
			player.Redraw();
			if(player.Judge(player.GetHotX(),player.GetHotY()-1,newD)==0)
			{
				player.ChangePos(player.GetHotX(),player.GetHotY()-1);
				player.ChangeDirection(newD);
			}
			else
			{
				if(player.Judge(player.GetHotX(),player.GetHotY(),newD)==0)
					player.ChangeDirection(newD);
            }
			if(GameOver==0)
			   player.DrawTank();
			ReleaseMutex(Mutex);
			Sleep(110-player.GetSpeed()*10);
		}
		else if(GetAsyncKeyState(VK_SPACE))//按键空格，发射子弹
		{
			WaitForSingleObject(Mutex,INFINITE);
			if(player.FireEnable==1)//如果可以发射
			{
			   HANDLE bullet=CreateThread(NULL,0,Bulletfly,&(player.ID),0,NULL);//创建玩家子弹进程
			   CloseHandle(bullet);
			   player.FireEnable=0;
			}
			ReleaseMutex(Mutex);
        }
		if(EnemyExist==0&&GameOver==0)//如果敌人不存在生成新敌人
		{
			WaitForSingleObject(Mutex,INFINITE);
			EnemyExist=1;
			temp=CreateThread(NULL,0,TankRuning,NULL,0,NULL);//创建敌人线程
			CloseHandle(temp);
			ReleaseMutex(Mutex);
		}
	}
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_BLUE);
	SetPos(20,10);
	cout<<"游戏结束"<<endl;
	SetPos(20,11);
	cout<<"杀敌数："<<Kill;
	SetPos(20,12);
	cout<<"杀死红坦克"<<KillRed;
	SetPos(20,13);
	cout<<"杀死绿坦克"<<KillGreen<<endl;
	return 0;
}