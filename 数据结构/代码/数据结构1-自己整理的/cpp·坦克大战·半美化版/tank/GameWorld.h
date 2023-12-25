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
	  PlayerTank *pt;//һ����Ҷ���ָ��
	  list <EnemyTank*> etList;//һ�����̹��ָ���list
      list <PlayerBullet*> pbList;//һ������ӵ�ָ���list
      list <EnemyBullet*> ebList;//һ������ӵ�ָ���list
public:	  
	   GameWorld(); 
	   ~GameWorld() {}
	   void init();//��ʼ����Ϸ����
	   void destory();//������Ϸ����
       void moveAll();//���ж��󡰱��ݡ�
	   void drawAll();//���ж������
	   BOOL ptHitAllET(PlayerTank *pPT);//��������е���̹�˽�����ײ���
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
