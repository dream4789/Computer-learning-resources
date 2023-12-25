// EnemyBullet.cpp: implementation of the EnemyBullet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EnemyBullet.h"
#include "GameWorld.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern HDC		hdc;//����DC
extern HDC		mdc;//�ڴ�DC
extern HDC		bufdc;//����DC
extern HINSTANCE hInst;//ʵ�����
extern HWND	hWnd;//���ھ��
extern DWORD	tPre,tNow;//�ϴ��ػ�Ľ���ʱ���,��ǰʱ���(�����ػ濪ʼǰ��ʱ���)
extern HBITMAP bg;//����λͼ����
extern int winW;//���ڿ��
extern int winH;////���ڸ߶�
extern int cW;  //���ڿͻ������
extern int cH;  //���ڿͻ����߶�
extern int		num;
extern HBITMAP bz; 
extern GameWorld gameWorld; //��Ϸ����

EnemyBullet::EnemyBullet(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Power,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead)//���캯�����½�������ǻ��
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
void EnemyBullet::setDead() { dead=TRUE;}//��Ϊ����
BOOL EnemyBullet::getDead(){return(dead);}//����Ƿ�����
void EnemyBullet::getRect(RECT& R)
{
	R.left=x-width/2;
	R.top=y-height/2;
	R.right=x+width/2;
	R.bottom=y+height/2;
}
BOOL EnemyBullet::isMyTime()//���ݡ���ǰʱ���-���ʱ���>=��ʱʱ��Ρ��ж��Ƿ���ұ�����
{
  if(GetTickCount()-lastTickCount>=delayTimer) 
   {
     lastTickCount = GetTickCount();
     return TRUE;
   }
  return FALSE;
}
BOOL EnemyBullet::hitPT(PlayerTank *pPT)////��ײ���̹��
{
	RECT rc1,rc2,temp;
	getRect(rc1);
	pPT->getRect(rc2);
	return IntersectRect(&temp,&rc1,&rc2);//��3����������win32 SDK�ģ�����MFC�ġ�rc1,rc2���εĽ�����temp��û�õ������������
}
void EnemyBullet::move()
{  
  if (!isMyTime()) return;
  switch(dir)   //�ƶ�
    {
	  case DirUp:     y-=speed;  break;
	  case DirRight:  x+=speed;  break;
      case DirDown:   y+=speed;  break;
      case DirLeft:   x-=speed;  break;
	}
  if (x<=width/2 ||x>=cW-width/2 ||y<=height/2 ||y>=cH-height/2) setDead();//����,����������־
  //ǧ�������¾��������������޳�����Ϊ��ʱ�����ڸö��������С�������Ϸ�����moveAllȥ����
  //if (getDead()) gameWorld.removeEB(this);
  if (gameWorld.ebHitPT(this))//�����̹���Ƿ���ײ����Ϊ�棬���̹�˼�Ѫ���ӵ���
  {
	  this->setDead();
  }
  if(speed>8)
         speed = 8; //�ӵ�����̫��,������������ӵ���̹��
}

void  EnemyBullet::draw()
{
    SelectObject(bufdc,EnemyBullet::ebBITMAP);
	BitBlt(mdc,x-width/2,y-height/2,width,height,bufdc,0,0,SRCCOPY);
}