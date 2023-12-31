// EnemyBullet.cpp: implementation of the EnemyBullet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EnemyBullet.h"
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

EnemyBullet::EnemyBullet(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Power,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead)//构造函数，新建对象必是活的
{
	x=X;
	y=Y;
	width=Width;
	height=Height;
	dir=Dir;
	speed=Speed;
	power=Power;
	lastTickCount=LastTickCount;
	delayTimer=DelayTimer;
	dead=Dead;
}
EnemyBullet::~EnemyBullet(){};
int EnemyBullet::getPower() {return power;}
void EnemyBullet::setDead() { dead=TRUE;}//设为死亡
BOOL EnemyBullet::getDead(){return(dead);}//检查是否死亡
void EnemyBullet::getRect(RECT& R)
{
	R.left=x-width/2;
	R.top=y-height/2;
	R.right=x+width/2;
	R.bottom=y+height/2;
}
BOOL EnemyBullet::isMyTime()//根据“当前时间滴-最近时间滴>=延时时间滴”判断是否该我表演了
{
  if(GetTickCount()-lastTickCount>=delayTimer) 
   {
     lastTickCount = GetTickCount();
     return TRUE;
   }
  return FALSE;
}
BOOL EnemyBullet::hitPT(PlayerTank *pPT)////碰撞玩家坦克
{
	RECT rc1,rc2,temp;
	getRect(rc1);
	pPT->getRect(rc2);
	return IntersectRect(&temp,&rc1,&rc2);//《3个参数的是win32 SDK的，不是MFC的。rc1,rc2矩形的交集赋temp（没用到），返回真假
}
void EnemyBullet::move()
{  
  if (!isMyTime()) return;
  switch(dir)   //移动
    {
	  case DirUp:     y-=speed;  break;
	  case DirRight:  x+=speed;  break;
      case DirDown:   y+=speed;  break;
      case DirLeft:   x-=speed;  break;
	}
  if (x<=width/2 ||x>=cW-width/2 ||y<=height/2 ||y>=cH-height/2) setDead();//出界,设置死亡标志
  //千万不能象下句那样从链表中剔除，因为此时程序还在该对象中运行。交给游戏世界的moveAll去处理
  //if (getDead()) gameWorld.removeEB(this);
  if (gameWorld.ebHitPT(this))//与玩家坦克是否碰撞，若为真，玩家坦克减血，子弹死
  {
	  this->setDead();
  }
  if(speed>8)
         speed = 8; //子弹不能太快,否则会跳过敌子弹或坦克
}

void  EnemyBullet::draw()
{
    SelectObject(bufdc,EnemyBullet::ebBITMAP);
	BitBlt(mdc,x-width/2,y-height/2,width,height,bufdc,0,0,SRCCOPY);
}