//frame.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <list>
#include "EnemyTank.h"
#include "global.h"
#include "GameWorld.h"
#include "PlayerTank.h"
#include "PlayerBullet.h"
#include<mmsystem.h>  //PlaySound����wav�ļ�����
#pragma comment(lib, "winmm.lib") //PlaySound����wav�ļ�����
//#pragma comment(lib,"User32.lib")//GetAsyncKeyStateȡ��������
//#include <stdio.h>
#include <stdlib.h>//ȡ�������Ҫ
using namespace std;//<list>��Ҫ
//*****************ȫ�ֱ���
HDC		hdc;//����DC(�����豸����)
HDC		mdc;//�ڴ�DC
HDC		bufdc;//����DC
HINSTANCE hInst;//ʵ�����
HWND	hWnd;//���ھ��
DWORD	tPre,tNow;//�ϴ��ػ�Ľ���ʱ���,��ǰʱ���(�����ػ濪ʼǰ��ʱ���)
HBITMAP bg;//����λͼ����
int winW=800;//���ڿ��
int winH=600;////���ڸ߶�
int cW;  //���ڿͻ������
int cH;  //���ڿͻ����߶�
int		num=0;//����������
HBITMAP bz; //��ըλͼ����
HBITMAP gameOverBITMAP;
BOOL gameOver;
GameWorld gameWorld;//��Ϸ�������

//*****************����ԭ������
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int );
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

void MyPaint(HDC hdc);
HBITMAP PlayerTank::ptBITMAP=(HBITMAP)LoadImage(NULL,"���̹��.bmp",IMAGE_BITMAP,40,160,LR_LOADFROMFILE); //����λͼ�ļ���λͼ����
HBITMAP  EnemyTank::etBITMAP=(HBITMAP)LoadImage(NULL,"����̹��.bmp",IMAGE_BITMAP,40,160,LR_LOADFROMFILE); 
HBITMAP  PlayerBullet::pbBITMAP=(HBITMAP)LoadImage(NULL,"����ӵ�.bmp",IMAGE_BITMAP,8,8,LR_LOADFROMFILE); 
HBITMAP  EnemyBullet::ebBITMAP=(HBITMAP)LoadImage(NULL,"�����ӵ�.bmp",IMAGE_BITMAP,8,8,LR_LOADFROMFILE); 


//******************�������
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	//Ӧ�ó�ʼ��
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	//��Ϣѭ��
    while( msg.message!=WM_QUIT )
    {
        if( PeekMessage( &msg, NULL, 0,0 ,PM_REMOVE) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
	else
	{
	    tNow = GetTickCount();
	    if(tNow-tPre >= 40)
		
		MyPaint(hdc); //�ػ�
		
		gameWorld.moveAll();
		gameWorld.drawAll();
		
	}
 
    }

	return msg.wParam;
}

//**************�����ע�ᴰ����
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "frame";
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

//******************��ʼ������
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	
	hInst = hInstance;
   
    HBITMAP bmp;
    	
    hWnd = CreateWindow("frame", "����Ϸ���" , WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
    //��ʾ���´���
	MoveWindow(hWnd,0,0,winW,winH,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);//��ȡ����DC
	mdc = CreateCompatibleDC(hdc);//�����봰��DC���ݵ��ڴ�DC
	bufdc = CreateCompatibleDC(hdc);//�����봰��DC���ݵĻ���DC

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	cW=clientRect.right;
	cH=clientRect.bottom;
      
	bmp = CreateCompatibleBitmap(hdc,winW,winH);
	SelectObject(mdc,bmp);
    bg = (HBITMAP)LoadImage(NULL,"�ڱ���.bmp",IMAGE_BITMAP,800,600,LR_LOADFROMFILE);
    bz = (HBITMAP)LoadImage(NULL,"��ը.bmp",IMAGE_BITMAP,40,160,LR_LOADFROMFILE); //����λͼ�ļ���λͼ����
    gameOverBITMAP=(HBITMAP)LoadImage(NULL,"ʧ��.bmp",IMAGE_BITMAP,800,600,LR_LOADFROMFILE);
    gameWorld.init();

	return TRUE;
}

//**********���Զ����ػ溯��

void MyPaint(HDC hdc)
{	
	BitBlt(hdc,0,0,800,600,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();     //ȡ�ϴ��ػ�Ľ���ʱ���

	num++;
	if(num == 4)   num = 0;
}

//**************��Ϣ������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		
		case WM_DESTROY:			 //���ڽ�����Ϣ��
		
			DeleteDC(mdc);
			DeleteDC(bufdc);
	
			DeleteObject(bg);
			DeleteObject(bz);
			ReleaseDC(hWnd,hdc);

        	DeleteObject(PlayerTank::ptBITMAP);  
			DeleteObject(EnemyTank::etBITMAP);  
			DeleteObject(PlayerBullet::pbBITMAP); 
			gameWorld.destory();
			
		    PostQuitMessage(0);
			break;
		default:							//������Ϣ��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
