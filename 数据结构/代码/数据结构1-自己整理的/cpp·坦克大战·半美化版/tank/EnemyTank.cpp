// EnemyTank.cpp: implementation of the EnemyTank class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EnemyTank.h"
#include "GameWorld.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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

EnemyTank::EnemyTank(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Blood,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead)//构造函数，新建对象必是活的
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
EnemyTank::~EnemyTank(){};
int EnemyTank::getX(){return x;}
int EnemyTank::getY(){return y;}
int EnemyTank::getBlood(){return blood;}
void EnemyTank::setBlood(int Blood){blood=Blood;}
void EnemyTank::setDead() { dead=TRUE;}//设为死亡
BOOL EnemyTank::getDead(){return(dead);}//检查是否死亡
void EnemyTank::getRect(RECT& R)
{
	R.left=x-width/2;
	R.top=y-height/2;
	R.right=x+width/2;
	R.bottom=y+height/2;
}
BOOL EnemyTank::isMyTime()//根据“当前时间滴-最近时间滴>=延时时间滴”判断是否该我表演了
{
  if(GetTickCount()-lastTickCount>=delayTimer) 
   {
     lastTickCount = GetTickCount();
     return TRUE;
   }
  return FALSE;
}
BOOL EnemyTank::hitET(EnemyTank *pET)////碰撞敌方坦克
{
	RECT rc1,rc2,temp;
	getRect(rc1);
	pET->getRect(rc2);
	return IntersectRect(&temp,&rc1,&rc2);//《3个参数的是win32 SDK的，不是MFC的。rc1,rc2矩形的交集赋temp（没用到），返回真假
}
void EnemyTank::move()
{  
  if (!isMyTime()) return;
  if (blood<0)
    {
	   setDead();//设置死亡标志
	   //new一个爆炸爆炸对象，插入入爆炸链表中
	   /////////////////////限于篇幅，暂时未做。直接播放了一个动画:未必总能显示
       SelectObject(bufdc,bz);
       if(num <= 3)  {	BitBlt(mdc,x-width/2,y-height/2,40,40,bufdc,0,40*num,SRCCOPY);
       PlaySound("爆炸声.wav", NULL, SND_FILENAME | SND_ASYNC);}
	   BitBlt(hdc,0,0,800,600,mdc,0,0,SRCCOPY);
       ///////////////////// 
	   return;
    }
	int r=rand()%100;//产生0~100之间的随机数
	int oldX=x , oldY=y;//保存原坐标
	if (r<=3)    //3%概率
      dir=(Direction)r;   
    else 
      if (r<5)  //2%概率 
       {EnemyBullet *pEB=new EnemyBullet(x,y,8,8,dir,5,150,0,40,FALSE);
        gameWorld.addEB(pEB);
		PlaySound("子弹发射声.wav", NULL, SND_FILENAME | SND_ASYNC);
       }
      else
       {
	    switch(dir)   //试探性移动
        {
		  case DirUp:     y-=speed;  break;
		  case DirRight:  x+=speed;  break;
          case DirDown:   y+=speed;  break;
          case DirLeft:   x-=speed;  break;
		}
	  } 
	BOOL canMove=TRUE; //假设可移动
	if (gameWorld.etHitElseET(this))//与其他敌坦克是否碰撞，若为真，不能移动
		canMove=FALSE;
	if (x<=width/2 ||x>=cW-width/2 ||y<=height/2 ||y>=cH-height/2) canMove=FALSE;//出界
	if (gameWorld.etHitPT(this))//与玩家坦克是否碰撞，若为真，不能移动
		canMove=FALSE;
	if (canMove==FALSE) {  x=oldX;y=oldY;}//不能移动，恢复原坐标
}

void  EnemyTank::draw()
{
    SelectObject(bufdc,EnemyTank::etBITMAP);
	BitBlt(mdc,x-width/2,y-height/2,width,height,bufdc,0,height*this->dir,SRCCOPY);
}