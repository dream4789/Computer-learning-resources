// PlayerTank.h: interface for the PlayerTank class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERTANK_H__19A5E98B_4663_45CD_8875_E7DB80D7705E__INCLUDED_)
#define AFX_PLAYERTANK_H__19A5E98B_4663_45CD_8875_E7DB80D7705E__INCLUDED_
#include "list"
using namespace std;//��list����
#include "global.h"
#include "EnemyTank.h"
class PlayerTank
{
protected:
	int x,y,width,height;//���꣨ͼƬ�����ĵ㻭�ڴ˴��������
	Direction dir;//����
	int speed;  //�ٶ� 
	int blood;	//����ֵ
	DWORD lastTickCount;	//���ʱ���
	DWORD delayTimer;	//��ʱʱ���,�������ѵļ��
	BOOL  dead;		//������־
	public:
static HBITMAP ptBITMAP;//���̹��ͼƬ����
    PlayerTank(int X,int Y,int Width,int Height,Direction Dir,int Speed,int Blood,DWORD LastTickCount,DWORD DelayTimer,BOOL  Dead=FALSE);//���캯�����½�������ǻ��
    ~PlayerTank();     
    void getRect(RECT& R);//ȡ�ö���ռ�ݵľ�������RECT��Win32 API�еľ��νṹ�塷
    BOOL isMyTime(); //���ݡ���ǰʱ���-���ʱ���>=��ʱʱ��Ρ��ж��Ƿ���ұ�����
    int getBlood();
	void setBlood(int Blood);
	void setDead();//��Ϊ����
	BOOL getDead();//����Ƿ�����
	BOOL hitET(EnemyTank* pET);//��ײ�з�̹��
    void move();	//����ġ����ݡ�
	void draw();	//���ƶ���
};

#endif 
