// EnemyTank.h: interface for the EnemyTank class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYTANK_H__B72C9169_94EC_4AB5_A806_01673EA24448__INCLUDED_)
#define AFX_ENEMYTANK_H__B72C9169_94EC_4AB5_A806_01673EA24448__INCLUDED_

#include "global.h"
#include<mmsystem.h>  //PlaySound����wav�ļ�����
#pragma comment(lib, "winmm.lib") //PlaySound����wav�ļ�����
class EnemyTank
{
protected:
	int x,y,width,height;//���꣨ͼƬ�����ĵ㻭�ڴ˴��������
	Direction dir;//����
	int speed;  //�ٶ� 
	int blood;	//����ֵ
	//int currentFrame;//��ǰͼ��
	DWORD lastTickCount;	//���ʱ���
	DWORD delayTimer;	//��ʱʱ���,�������ѵļ��
	BOOL  dead;		//������־

public:
	static HBITMAP etBITMAP;//��̹��ͼƬ����
	EnemyTank(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Blood,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead=FALSE);
	~EnemyTank();
	int getX();
	int getY();
    void getRect(RECT& R);//ȡ�ö���ռ�ݵľ�������RECT��Win32 API�еľ��νṹ�塷
    BOOL isMyTime(); //���ݡ���ǰʱ���-���ʱ���>=��ʱʱ��Ρ��ж��Ƿ���ұ�����
	int getBlood();
	void setBlood(int Blood);
    void setDead() ;//��Ϊ����
	BOOL getDead();//����Ƿ�����
	BOOL EnemyTank::hitET(EnemyTank *pET);
    void move();	//����ġ����ݡ�
	void draw();	//���ƶ���
};

#endif // !defined(AFX_ENEMYTANK_H__B72C9169_94EC_4AB5_A806_01673EA24448__INCLUDED_)
