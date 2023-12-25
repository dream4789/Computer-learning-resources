// GameWorld.h: interface for the GameWorld class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEWORLD_H__DF1C81EA_241B_4A0A_9611_71FF28BE0413__INCLUDED_)
#define AFX_GAMEWORLD_H__DF1C81EA_241B_4A0A_9611_71FF28BE0413__INCLUDED_
#include <list>
#include "global.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
using namespace std;

class GameWorld
{
protected:
	  PlayerTank *pt;//一个玩家对象指针
	  list <EnemyTank*> etList;//一组敌人坦克指针的list
      list <PlayerBullet*> pbList;//一组玩家子弹指针的list
      list <EnemyBullet*> ebList;//一组敌人子弹指针的list
public:	  
	   GameWorld(); 
	   ~GameWorld() {}
	   void init();//初始化游戏世界
	   void destory();//销毁游戏世界
       void moveAll();//所有对象“表演”
	   void drawAll();//所有对象绘制
	   BOOL ptHitAllET(PlayerTank *pPT);//玩家与所有敌人坦克进行碰撞检测
	   BOOL etHitElseET(EnemyTank *pET);
	   BOOL etHitPT(EnemyTank* pET);
	   //void removePB(PlayerBullet *pPB);
	   void addPB(PlayerBullet *pPB);
	   BOOL pbHitAllET(PlayerBullet *pPB);
	   void addEB(EnemyBullet *pEB);
	   BOOL ebHitPT(EnemyBullet *pEB);
	   BOOL pbHitAllEB(PlayerBullet *pPB);

};

#endif // !defined(AFX_GAMEWORLD_H__DF1C81EA_241B_4A0A_9611_71FF28BE0413__INCLUDED_)
