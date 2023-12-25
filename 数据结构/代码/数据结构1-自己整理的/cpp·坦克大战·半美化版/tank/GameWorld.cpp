// GameWorld.cpp: implementation of the GameWorld class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
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
	pt=new PlayerTank (600,300,40,40,DirUp,10,100,/*0,*/0,100,FALSE);//1�����̹��
	
	srand(GetTickCount());//���������	
	for (int i=0;i<=8;i++)//���λ�á������ٶȣ�����Ҳ�ɼ����ͣ�����9������̹��
	{ 
		int randX=20+rand()%(cW-40);
		int randY=20+rand()%(cH-40);
		int randDir=rand()%3;
		int randSpeed=rand()%8;//����0~8�������
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
BOOL GameWorld:: ptHitAllET(PlayerTank *ppt)//���̹����ȫ������̹����ײ���
{
	list<EnemyTank*>::iterator i;
	for(i=etList.begin(); i != etList.end(); ++i) 
		if(ppt->hitET(*i))return TRUE;
    return FALSE;
}
BOOL GameWorld:: etHitElseET(EnemyTank *pET)//����̹�����������̹����ײ���
{
	list<EnemyTank*>::iterator i;
	for(i=etList.begin(); i != etList.end(); ++i) 
		if ((*i)!=pET)
		  if(pET->hitET(*i))return TRUE;
    return FALSE;
}

BOOL GameWorld::etHitPT(EnemyTank* pET)//����̹�������̹����ײ���
{
	return(  pt->hitET(pET)  );
}

void GameWorld::addPB(PlayerBullet *pPB)//��������ӵ�
{
	pbList.push_back(pPB);
}

BOOL GameWorld::pbHitAllET(PlayerBullet *pPB)//����ӵ���ȫ������̹��
{
    list<EnemyTank*>::iterator i;
	for(i=etList.begin(); i != etList.end(); ++i) 
		if(pPB->hitET(*i)) {(*i)->setBlood(  (*i)->getBlood()-pPB->getPower() );     return TRUE;}
    return FALSE;
}

void GameWorld::addEB(EnemyBullet *pEB)////��������ӵ�
{
	ebList.push_back(pEB);
}
	   
BOOL GameWorld::ebHitPT(EnemyBullet *pEB)//�����ӵ���Ψһ���̹��
{
    if(pEB->hitPT(pt)) {pt->setBlood(  pt->getBlood()-pEB->getPower() );     return TRUE;}
    return FALSE;
}


BOOL GameWorld::pbHitAllEB(PlayerBullet *pPB)//����ӵ���ȫ�������ӵ�
{
    list<EnemyBullet*>::iterator i;
	for(i=ebList.begin(); i != ebList.end(); ++i) 
		if(pPB->hitEB(*i)) {(*i)->setDead();     return TRUE;}
    return FALSE;
}