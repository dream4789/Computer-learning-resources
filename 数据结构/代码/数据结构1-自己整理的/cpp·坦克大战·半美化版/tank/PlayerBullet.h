// PlayerBullet.h: interface for the PlayerBullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERBULLET_H__27D0EDE1_AE62_4A72_9BC4_B363E6E27A32__INCLUDED_)
#define AFX_PLAYERBULLET_H__27D0EDE1_AE62_4A72_9BC4_B363E6E27A32__INCLUDED_

#include "global.h"
#include "EnemyTank.h"
#include "EnemyBullet.h"
#include<mmsystem.h>  //PlaySound播放wav文件必须
#pragma comment(lib, "winmm.lib") //PlaySound播放wav文件必须
class PlayerBullet
{
protected:
	int x,y,width,height;//坐标（图片的中心点画在此处），宽高
	Direction dir;//方向
	int speed;  //速度 
	int power;	//杀伤力
	DWORD lastTickCount;	//最近时间滴
	DWORD delayTimer;	//延时时间滴,对象苏醒的间隔
	BOOL  dead;		//死亡标志

public:
	static HBITMAP pbBITMAP;//玩家子弹图片对象
	PlayerBullet(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Power,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead=FALSE);
	~PlayerBullet();
    void getRect(RECT& R);//取得对象占据的矩形区域《RECT是Win32 API中的矩形结构体》
    BOOL isMyTime(); //根据“当前时间滴-最近时间滴>=延时时间滴”判断是否该我表演了
	int getPower(); 
    void setDead() ;//设为死亡
	BOOL getDead();//检查是否死亡
	BOOL hitET(EnemyTank *pET);
	BOOL hitEB(EnemyBullet *pEB);
    void move();	//对象的“表演”
	void draw();	//绘制对象
};
#endif // !defined(AFX_PLAYERBULLET_H__27D0EDE1_AE62_4A72_9BC4_B363E6E27A32__INCLUDED_)
