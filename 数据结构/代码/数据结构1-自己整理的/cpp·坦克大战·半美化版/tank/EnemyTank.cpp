// EnemyTank.cpp: implementation of the EnemyTank class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EnemyTank.h"
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

EnemyTank::EnemyTank(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Blood,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead)//���캯�����½�������ǻ��
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
void EnemyTank::setDead() { dead=TRUE;}//��Ϊ����
BOOL EnemyTank::getDead(){return(dead);}//����Ƿ�����
void EnemyTank::getRect(RECT& R)
{
	R.left=x-width/2;
	R.top=y-height/2;
	R.right=x+width/2;
	R.bottom=y+height/2;
}
BOOL EnemyTank::isMyTime()//���ݡ���ǰʱ���-���ʱ���>=��ʱʱ��Ρ��ж��Ƿ���ұ�����
{
  if(GetTickCount()-lastTickCount>=delayTimer) 
   {
     lastTickCount = GetTickCount();
     return TRUE;
   }
  return FALSE;
}
BOOL EnemyTank::hitET(EnemyTank *pET)////��ײ�з�̹��
{
	RECT rc1,rc2,temp;
	getRect(rc1);
	pET->getRect(rc2);
	return IntersectRect(&temp,&rc1,&rc2);//��3����������win32 SDK�ģ�����MFC�ġ�rc1,rc2���εĽ�����temp��û�õ������������
}
void EnemyTank::move()
{  
  if (!isMyTime()) return;
  if (blood<0)
    {
	   setDead();//����������־
	   //newһ����ը��ը���󣬲����뱬ը������
	   /////////////////////����ƪ������ʱδ����ֱ�Ӳ�����һ������:δ��������ʾ
       SelectObject(bufdc,bz);
       if(num <= 3)  {	BitBlt(mdc,x-width/2,y-height/2,40,40,bufdc,0,40*num,SRCCOPY);
       PlaySound("��ը��.wav", NULL, SND_FILENAME | SND_ASYNC);}
	   BitBlt(hdc,0,0,800,600,mdc,0,0,SRCCOPY);
       ///////////////////// 
	   return;
    }
	int r=rand()%100;//����0~100֮��������
	int oldX=x , oldY=y;//����ԭ����
	if (r<=3)    //3%����
      dir=(Direction)r;   
    else 
      if (r<5)  //2%���� 
       {EnemyBullet *pEB=new EnemyBullet(x,y,8,8,dir,5,150,0,40,FALSE);
        gameWorld.addEB(pEB);
		PlaySound("�ӵ�������.wav", NULL, SND_FILENAME | SND_ASYNC);
       }
      else
       {
	    switch(dir)   //��̽���ƶ�
        {
		  case DirUp:     y-=speed;  break;
		  case DirRight:  x+=speed;  break;
          case DirDown:   y+=speed;  break;
          case DirLeft:   x-=speed;  break;
		}
	  } 
	BOOL canMove=TRUE; //������ƶ�
	if (gameWorld.etHitElseET(this))//��������̹���Ƿ���ײ����Ϊ�棬�����ƶ�
		canMove=FALSE;
	if (x<=width/2 ||x>=cW-width/2 ||y<=height/2 ||y>=cH-height/2) canMove=FALSE;//����
	if (gameWorld.etHitPT(this))//�����̹���Ƿ���ײ����Ϊ�棬�����ƶ�
		canMove=FALSE;
	if (canMove==FALSE) {  x=oldX;y=oldY;}//�����ƶ����ָ�ԭ����
}

void  EnemyTank::draw()
{
    SelectObject(bufdc,EnemyTank::etBITMAP);
	BitBlt(mdc,x-width/2,y-height/2,width,height,bufdc,0,height*this->dir,SRCCOPY);
}