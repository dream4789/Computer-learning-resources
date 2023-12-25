// PlayerTank.cpp: implementation of the PlayerTank class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PlayerTank.h"
#include "GameWorld.h"

extern HDC		hdc;//窗口DC
extern HDC		mdc;//内存DC
extern HDC		bufdc;//缓冲DC
extern HINSTANCE hInst;//实例句柄
extern HWND	hWnd;//窗口句柄
extern DWORD	tPre,tNow;//上次重绘的结束时间滴,当前时间滴(本次重绘开始前的时间滴)
extern HBITMAP bg;//背景位图对象
extern int winW;//窗口宽度
extern int winH;////窗口高度
extern int cW;  //窗口客户区宽度
extern int cH;  //窗口客户区高度
extern int		num;
extern HBITMAP bz;
extern GameWorld gameWorld; //游戏世界

PlayerTank::PlayerTank(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Blood,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead)//构造函数，新建对象必是活的
{
	x=X;
	y=Y;
	width=Width;
	height=Height;
	dir=Dir;
	speed=Speed;
	blood=Blood;
	lastTickCount=LastTickCount;
	delayTimer=DelayTimer;
	dead=Dead;
}
PlayerTank::~PlayerTank(){};

int PlayerTank::getBlood(){return blood;}
void PlayerTank::setBlood(int Blood){blood=Blood;}
void PlayerTank::setDead() { dead=TRUE;}//设为死亡
BOOL PlayerTank::getDead(){return(dead);}//检查是否死亡 

void PlayerTank::getRect(RECT& R)//取得对象占据的矩形区域《RECT是Win32 API中的矩形结构体》
{
	R.left=x-width/2;
	R.top=y-height/2;
	R.right=x+width/2;
	R.bottom=y+height/2;
}
BOOL PlayerTank::isMyTime()//根据“当前时间滴-最近时间滴>=延时时间滴”判断是否该我表演了
{
	if(GetTickCount()-lastTickCount>=delayTimer) 
	{
		lastTickCount = GetTickCount();
		return TRUE;
	}
	return FALSE;
}

BOOL PlayerTank::hitET(EnemyTank *pET)////碰撞敌方坦克
{
	RECT rc1,rc2,temp;
	getRect(rc1);
	pET->getRect(rc2);
	return IntersectRect(&temp,&rc1,&rc2);//《3个参数的是win32 SDK的，不是MFC的。rc1,rc2矩形的交集赋temp（没用到），返回真假
}
void PlayerTank::move()
{  
	if (!isMyTime()) return;
	if (blood<0)
    {
		setDead();//设置死亡标志
		//new一个爆炸爆炸对象，插入入爆炸链表中
		return;
    }
	//处理方向按键，尝试改变方向和移动坦克
	int oldX=x , oldY=y;//保存原坐标
	if (GetAsyncKeyState(VK_UP) )  //如果是向上键
	{
		dir=DirUp;
		y-=speed;//按速度移动
		if(y <= 0+height/2) y=height/2;//防止出界
	}
    if (GetAsyncKeyState(VK_RIGHT) ) 
	{
		dir=DirRight;
		x+=speed;
		if(x >= cW-width/2) x=cW-width/2;
	}
	if (GetAsyncKeyState(VK_DOWN) ) 
	{ 
		dir=DirDown;
		y+=speed;
		if(y >= cH-height/2) y=cH-height/2;
	}
	if (GetAsyncKeyState(VK_LEFT) ) 
	{ 
        dir=DirLeft;
		x-=speed;
        if(x <= 0+width/2) x=width/2;
    }
    BOOL canMove=TRUE; //试探性移动
	if (gameWorld.ptHitAllET(this))//与所有敌坦克是否碰撞，若为真，不能移动
		canMove=FALSE;
	if (canMove==FALSE) {  x=oldX;y=oldY;}//不能移动，恢复原坐标
	
	static DWORD fireTick=GetTickCount();
	if (GetTickCount()-fireTick>200)//我方子弹发射间隔
	{ if (GetAsyncKeyState(VK_LCONTROL) )  //左ctrl发射
	   {
        PlayerBullet *pPB=new PlayerBullet(x,y,8,8,dir,8,50,0,40,FALSE);
        gameWorld.addPB(pPB);
		PlaySound("子弹发射声.wav", NULL, SND_FILENAME | SND_ASYNC);
	   }
	   fireTick=GetTickCount();
	} 
	
}
void  PlayerTank::draw()
{
    SelectObject(bufdc,PlayerTank::ptBITMAP);//缓冲区关联玩家坦克图片对象
	BitBlt(mdc,x-width/2,y-height/2,width,height,bufdc,0,height*dir,SRCCOPY);//缓冲区贴到内存区
}
