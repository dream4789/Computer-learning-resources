// PlayerBullet.h: interface for the PlayerBullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERBULLET_H__27D0EDE1_AE62_4A72_9BC4_B363E6E27A32__INCLUDED_)
#define AFX_PLAYERBULLET_H__27D0EDE1_AE62_4A72_9BC4_B363E6E27A32__INCLUDED_

#include "global.h"
#include "EnemyTank.h"
#include "EnemyBullet.h"
#include<mmsystem.h>  //PlaySound����wav�ļ�����
#pragma comment(lib, "winmm.lib") //PlaySound����wav�ļ�����
class PlayerBullet
{
protected:
	int x,y,width,height;//���꣨ͼƬ�����ĵ㻭�ڴ˴��������
	Direction dir;//����
	int speed;  //�ٶ� 
	int power;	//ɱ����
	DWORD lastTickCount;	//���ʱ���
	DWORD delayTimer;	//��ʱʱ���,�������ѵļ��
	BOOL  dead;		//������־

public:
	static HBITMAP pbBITMAP;//����ӵ�ͼƬ����
	PlayerBullet(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Power,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead=FALSE);
	~PlayerBullet();
    void getRect(RECT& R);//ȡ�ö���ռ�ݵľ�������RECT��Win32 API�еľ��νṹ�塷
    BOOL isMyTime(); //���ݡ���ǰʱ���-���ʱ���>=��ʱʱ��Ρ��ж��Ƿ���ұ�����
	int getPower(); 
    void setDead() ;//��Ϊ����
	BOOL getDead();//����Ƿ�����
	BOOL hitET(EnemyTank *pET);
	BOOL hitEB(EnemyBullet *pEB);
    void move();	//����ġ����ݡ�
	void draw();	//���ƶ���
};
#endif // !defined(AFX_PLAYERBULLET_H__27D0EDE1_AE62_4A72_9BC4_B363E6E27A32__INCLUDED_)
