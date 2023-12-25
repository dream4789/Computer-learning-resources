// PlayerTank.cpp: implementation of the PlayerTank class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PlayerTank.h"
#include "GameWorld.h"

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

PlayerTank::PlayerTank(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Blood,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead)//���캯�����½�������ǻ��
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
void PlayerTank::setDead() { dead=TRUE;}//��Ϊ����
BOOL PlayerTank::getDead(){return(dead);}//����Ƿ����� 

void PlayerTank::getRect(RECT& R)//ȡ�ö���ռ�ݵľ�������RECT��Win32 API�еľ��νṹ�塷
{
	R.left=x-width/2;
	R.top=y-height/2;
	R.right=x+width/2;
	R.bottom=y+height/2;
}
BOOL PlayerTank::isMyTime()//���ݡ���ǰʱ���-���ʱ���>=��ʱʱ��Ρ��ж��Ƿ���ұ�����
{
	if(GetTickCount()-lastTickCount>=delayTimer) 
	{
		lastTickCount = GetTickCount();
		return TRUE;
	}
	return FALSE;
}

BOOL PlayerTank::hitET(EnemyTank *pET)////��ײ�з�̹��
{
	RECT rc1,rc2,temp;
	getRect(rc1);
	pET->getRect(rc2);
	return IntersectRect(&temp,&rc1,&rc2);//��3����������win32 SDK�ģ�����MFC�ġ�rc1,rc2���εĽ�����temp��û�õ������������
}
void PlayerTank::move()
{  
	if (!isMyTime()) return;
	if (blood<0)
    {
		setDead();//����������־
		//newһ����ը��ը���󣬲����뱬ը������
		return;
    }
	//�����򰴼������Ըı䷽����ƶ�̹��
	int oldX=x , oldY=y;//����ԭ����
	if (GetAsyncKeyState(VK_UP) )  //��������ϼ�
	{
		dir=DirUp;
		y-=speed;//���ٶ��ƶ�
		if(y <= 0+height/2) y=height/2;//��ֹ����
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
    BOOL canMove=TRUE; //��̽���ƶ�
	if (gameWorld.ptHitAllET(this))//�����е�̹���Ƿ���ײ����Ϊ�棬�����ƶ�
		canMove=FALSE;
	if (canMove==FALSE) {  x=oldX;y=oldY;}//�����ƶ����ָ�ԭ����
	
	static DWORD fireTick=GetTickCount();
	if (GetTickCount()-fireTick>200)//�ҷ��ӵ�������
	{ if (GetAsyncKeyState(VK_LCONTROL) )  //��ctrl����
	   {
        PlayerBullet *pPB=new PlayerBullet(x,y,8,8,dir,8,50,0,40,FALSE);
        gameWorld.addPB(pPB);
		PlaySound("�ӵ�������.wav", NULL, SND_FILENAME | SND_ASYNC);
	   }
	   fireTick=GetTickCount();
	} 
	
}
void  PlayerTank::draw()
{
    SelectObject(bufdc,PlayerTank::ptBITMAP);//�������������̹��ͼƬ����
	BitBlt(mdc,x-width/2,y-height/2,width,height,bufdc,0,height*dir,SRCCOPY);//�����������ڴ���
}
