// EnemyBullet.h: interface for the EnemyBullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBULLET_H__20AF722E_672A_4BCC_B675_23797C504F76__INCLUDED_)
#define AFX_ENEMYBULLET_H__20AF722E_672A_4BCC_B675_23797C504F76__INCLUDED_

#include "global.h"
#include "PlayerTank.h"
#include<mmsystem.h>  //PlaySound����wav�ļ�����
#pragma comment(lib, "winmm.lib") //PlaySound����wav�ļ�����
class EnemyBullet
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
	static HBITMAP ebBITMAP;//�����ӵ�ͼƬ����
	EnemyBullet(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Power,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead=FALSE);
	~EnemyBullet();
    void getRect(RECT& R);//ȡ�ö���ռ�ݵľ�������RECT��Win32 API�еľ��νṹ�塷
    BOOL isMyTime(); //���ݡ���ǰʱ���-���ʱ���>=��ʱʱ��Ρ��ж��Ƿ���ұ�����
	int getPower(); 
    void setDead() ;//��Ϊ����
	BOOL getDead();//����Ƿ�����
	BOOL hitPT(PlayerTank *pPT);
    void move();	//����ġ����ݡ�
	void draw();	//���ƶ���
};

#endif // !defined(AFX_ENEMYBULLET_H__20AF722E_672A_4BCC_B675_23797C504F76__INCLUDED_)
