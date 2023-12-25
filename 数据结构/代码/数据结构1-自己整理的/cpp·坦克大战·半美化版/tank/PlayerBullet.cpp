// PlayerBullet.cpp: implementation of the PlayerBullet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PlayerBullet.h"
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

PlayerBullet::PlayerBullet(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Power,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead)//���캯�����½�������ǻ��
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
PlayerBullet::~PlayerBullet(){};
int PlayerBullet::getPower() {return power;}
void PlayerBullet::setDead() { dead=TRUE;}//��Ϊ����
BOOL PlayerBullet::getDead(){return(dead);}//����Ƿ�����
void PlayerBullet::getRect(RECT& R)
{
	R.left=x-width/2;
	R.top=y-height/2;
	R.right=x+width/2;
	R.bottom=y+height/2;
}
BOOL PlayerBullet::isMyTime()//���ݡ���ǰʱ���-���ʱ���>=��ʱʱ��Ρ��ж��Ƿ���ұ�����
{
  if(GetTickCount()-lastTickCount>=delayTimer) 
   {
     lastTickCount = GetTickCount();
     return TRUE;
   }
  return FALSE;
}
BOOL PlayerBullet::hitET(EnemyTank *pET)////��ײ�з�̹��
{
	RECT rc1,rc2,temp;
	getRect(rc1);
	pET->getRect(rc2);
	return IntersectRect(&temp,&rc1,&rc2);//��3����������win32 SDK�ģ�����MFC�ġ�rc1,rc2���εĽ�����temp��û�õ������������
}

BOOL PlayerBullet::hitEB(EnemyBullet *pEB)////��ײ�з��ӵ�
{
	RECT rc1,rc2,temp;
	getRect(rc1);
	pEB->getRect(rc2);
	return IntersectRect(&temp,&rc1,&rc2);//��3����������win32 SDK�ģ�����MFC�ġ�rc1,rc2���εĽ�����temp��û�õ������������
}

void PlayerBullet::move()
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
  //if (getDead()) gameWorld.removePB(this);
  if (gameWorld.pbHitAllET(this))//��ȫ����̹���Ƿ���ײ����Ϊ�棬��̹�˼�Ѫ���ӵ���
  {
	  this->setDead();
  }
  if (gameWorld.pbHitAllEB(this))//��ȫ�����ӵ��Ƿ���ײ����Ϊ�棬���ӵ��������ӵ���
  {
	  this->setDead();
  }
  if(speed>8)
         speed = 8; //�ӵ�����̫��,������������ӵ���̹��
}

void  PlayerBullet::draw()
{
    SelectObject(bufdc,PlayerBullet::pbBITMAP);
	BitBlt(mdc,x-width/2,y-height/2,width,height,bufdc,0,0,SRCCOPY);
}