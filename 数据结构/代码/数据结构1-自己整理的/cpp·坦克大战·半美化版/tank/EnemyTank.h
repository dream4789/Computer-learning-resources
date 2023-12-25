// EnemyTank.h: interface for the EnemyTank class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYTANK_H__B72C9169_94EC_4AB5_A806_01673EA24448__INCLUDED_)
#define AFX_ENEMYTANK_H__B72C9169_94EC_4AB5_A806_01673EA24448__INCLUDED_

#include "global.h"
#include<mmsystem.h>  //PlaySound播放wav文件必须
#pragma comment(lib, "winmm.lib") //PlaySound播放wav文件必须
class EnemyTank
{
protected:
	int x,y,width,height;//坐标（图片的中心点画在此处），宽高
	Direction dir;//方向
	int speed;  //速度 
	int blood;	//生命值
	//int currentFrame;//当前图号
	DWORD lastTickCount;	//最近时间滴
	DWORD delayTimer;	//延时时间滴,对象苏醒的间隔
	BOOL  dead;		//死亡标志

public:
	static HBITMAP etBITMAP;//敌坦克图片对象
	EnemyTank(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Blood,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead=FALSE);
	~EnemyTank();
	int getX();
	int getY();
    void getRect(RECT& R);//取得对象占据的矩形区域《RECT是Win32 API中的矩形结构体》
    BOOL isMyTime(); //根据“当前时间滴-最近时间滴>=延时时间滴”判断是否该我表演了
	int getBlood();
	void setBlood(int Blood);
    void setDead() ;//设为死亡
	BOOL getDead();//检查是否死亡
	BOOL EnemyTank::hitET(EnemyTank *pET);
    void move();	//对象的“表演”
	void draw();	//绘制对象
};

#endif // !defined(AFX_ENEMYTANK_H__B72C9169_94EC_4AB5_A806_01673EA24448__INCLUDED_)
