// PlayerTank.h: interface for the PlayerTank class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERTANK_H__19A5E98B_4663_45CD_8875_E7DB80D7705E__INCLUDED_)
#define AFX_PLAYERTANK_H__19A5E98B_4663_45CD_8875_E7DB80D7705E__INCLUDED_
#include "list"
using namespace std;//用list必须
#include "global.h"
#include "EnemyTank.h"
class PlayerTank
{
protected:
	int x,y,width,height;//坐标（图片的中心点画在此处），宽高
	Direction dir;//方向
	int speed;  //速度 
	int blood;	//生命值
	DWORD lastTickCount;	//最近时间滴
	DWORD delayTimer;	//延时时间滴,对象苏醒的间隔
	BOOL  dead;		//死亡标志
	public:
static HBITMAP ptBITMAP;//玩家坦克图片对象
    PlayerTank(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Blood,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead=FALSE);//构造函数，新建对象必是活的
    ~PlayerTank();     
    void getRect(RECT& R);//取得对象占据的矩形区域《RECT是Win32 API中的矩形结构体》
    BOOL isMyTime(); //根据“当前时间滴-最近时间滴>=延时时间滴”判断是否该我表演了
    int getBlood();
	void setBlood(int Blood);
	void setDead();//设为死亡
	BOOL getDead();//检查是否死亡
	BOOL hitET(EnemyTank* pET);//碰撞敌方坦克
    void move();	//对象的“表演”
	void draw();	//绘制对象
};

#endif 
