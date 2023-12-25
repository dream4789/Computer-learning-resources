// GameWorld.cpp: implementation of the GameWorld class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameWorld.h"

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
extern HBITMAP gameOverBITMAP;
extern BOOL gameOver;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameWorld::GameWorld()
{

}

void GameWorld::init()
{
	gameOver=FALSE;
	pt=new PlayerTank (600,300,40,40,DirUp,10,100,/*0,*/0,100,FALSE);//1个玩家坦克
	
	srand(GetTickCount());//随机数种子	
	for (int i=0;i<=8;i++)//随机位置、方向、速度（将来也可加类型）产生9个敌人坦克
	{ 
		int randX=20+rand()%(cW-40);
		int randY=20+rand()%(cH-40);
		int randDir=rand()%3;
		int randSpeed=rand()%8;//产生0~8的随机数
		EnemyTank *pET=new EnemyTank(randX,randY,40,40,(Direction)randDir,randSpeed,100,0,100,FALSE);
		etList.push_back(pET); 
	}
}
void GameWorld::destory()
{
	
	delete pt;
 
	list<EnemyTank*>::iterator i;
	for(i=etList.begin(); i != etList.end(); ++i) 
		delete (*i);
    
	list<PlayerBullet*>::iterator j;
	for(j=pbList.begin(); j != pbList.end(); ++j) 
		delete (*j);
     
	list<EnemyBullet*>::iterator k;
	for(k=ebList.begin(); k != ebList.end(); ++k) 
		delete (*k);
    
}
void GameWorld::moveAll()
{
   
    if (pt->getDead()) 
		gameOver=TRUE;
	else
	    pt->move();
	
	list<EnemyTank*>::iterator i;
	for(i=etList.begin(); i != etList.end(); ) 
	{	
		if((*i)->getDead())
		{
			delete (*i); 
			i=etList.erase(i);
		}
		else
		{
			(*i)->move();
			++i;
		}
	}
    
	list<PlayerBullet*>::iterator j;
	for(j=pbList.begin(); j != pbList.end();) 
	{	
		if((*j)->getDead())
		{    
			 delete (*j);
			 j=pbList.erase(j);
		}
		else
		{
			(*j)->move();
			++j;
		}
	}

	list<EnemyBullet*>::iterator k;
	for(k=ebList.begin(); k != ebList.end();) 
	{	
		if((*k)->getDead())
		{    
			 delete (*k);
			 k=ebList.erase(k);
		}
		else
		{
			(*k)->move();
			++k;
		}
	}
}

void GameWorld::drawAll()
{
	SelectObject(bufdc,bg);
	BitBlt(mdc,0,0,cW,cH,bufdc,0,0,SRCCOPY);
	
	if (!gameOver)
	{
		pt->draw();
	}
	else
    {
		SelectObject(bufdc,gameOverBITMAP);
	    BitBlt(mdc,0,0,cW,cH,bufdc,0,0,SRCCOPY);
	}
	list<EnemyTank*>::iterator i;
	for(i=etList.begin(); i != etList.end(); ++i) 
	   if ((*i)!=NULL)	(*i)->draw();

	list<PlayerBullet*>::iterator j;
	for(j=pbList.begin(); j != pbList.end(); ++j) 
	   if ((*j)!=NULL)  (*j)->draw();

	list<EnemyBullet*>::iterator k;
	for(k=ebList.begin(); k != ebList.end(); ++k) 
	   if ((*k)!=NULL)	(*k)->draw();
}
BOOL GameWorld:: ptHitAllET(PlayerTank *ppt)//玩家坦克与全部敌人坦克碰撞检测
{
	list<EnemyTank*>::iterator i;
	for(i=etList.begin(); i != etList.end(); ++i) 
		if(ppt->hitET(*i))return TRUE;
    return FALSE;
}
BOOL GameWorld:: etHitElseET(EnemyTank *pET)//敌人坦克与其余敌人坦克碰撞检测
{
	list<EnemyTank*>::iterator i;
	for(i=etList.begin(); i != etList.end(); ++i) 
		if ((*i)!=pET)
		  if(pET->hitET(*i))return TRUE;
    return FALSE;
}

BOOL GameWorld::etHitPT(EnemyTank* pET)//敌人坦克与玩家坦克碰撞检测
{
	return(  pt->hitET(pET)  );
}

void GameWorld::addPB(PlayerBullet *pPB)//加入玩家子弹
{
	pbList.push_back(pPB);
}

BOOL GameWorld::pbHitAllET(PlayerBullet *pPB)//玩家子弹碰全部敌人坦克
{
    list<EnemyTank*>::iterator i;
	for(i=etList.begin(); i != etList.end(); ++i) 
		if(pPB->hitET(*i)) {(*i)->setBlood(  (*i)->getBlood()-pPB->getPower() );     return TRUE;}
    return FALSE;
}

void GameWorld::addEB(EnemyBullet *pEB)////加入敌人子弹
{
	ebList.push_back(pEB);
}
	   
BOOL GameWorld::ebHitPT(EnemyBullet *pEB)//敌人子弹碰唯一玩家坦克
{
    if(pEB->hitPT(pt)) {pt->setBlood(  pt->getBlood()-pEB->getPower() );     return TRUE;}
    return FALSE;
}


BOOL GameWorld::pbHitAllEB(PlayerBullet *pPB)//玩家子弹碰全部敌人子弹
{
    list<EnemyBullet*>::iterator i;
	for(i=ebList.begin(); i != ebList.end(); ++i) 
		if(pPB->hitEB(*i)) {(*i)->setDead();     return TRUE;}
    return FALSE;
}