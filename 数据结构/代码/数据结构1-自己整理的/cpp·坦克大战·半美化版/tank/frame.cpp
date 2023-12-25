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
#include<mmsystem.h>  //PlaySound播放wav文件必须
#pragma comment(lib, "winmm.lib") //PlaySound播放wav文件必须
//#pragma comment(lib,"User32.lib")//GetAsyncKeyState取按键必须
//#include <stdio.h>
#include <stdlib.h>//取随机数需要
using namespace std;//<list>需要
//*****************全局变量
HDC		hdc;//窗口DC(窗口设备环境)
HDC		mdc;//内存DC
HDC		bufdc;//缓冲DC
HINSTANCE hInst;//实例句柄
HWND	hWnd;//窗口句柄
DWORD	tPre,tNow;//上次重绘的结束时间滴,当前时间滴(本次重绘开始前的时间滴)
HBITMAP bg;//背景位图对象
int winW=800;//窗口宽度
int winH=600;////窗口高度
int cW;  //窗口客户区宽度
int cH;  //窗口客户区高度
int		num=0;//动画计数器
HBITMAP bz; //爆炸位图对象
HBITMAP gameOverBITMAP;
BOOL gameOver;
GameWorld gameWorld;//游戏世界对象

//*****************函数原型声明
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int );
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

void MyPaint(HDC hdc);
HBITMAP PlayerTank::ptBITMAP=(HBITMAP)LoadImage(NULL,"玩家坦克.bmp",IMAGE_BITMAP,40,160,LR_LOADFROMFILE); //加载位图文件到位图对象
HBITMAP  EnemyTank::etBITMAP=(HBITMAP)LoadImage(NULL,"敌人坦克.bmp",IMAGE_BITMAP,40,160,LR_LOADFROMFILE); 
HBITMAP  PlayerBullet::pbBITMAP=(HBITMAP)LoadImage(NULL,"玩家子弹.bmp",IMAGE_BITMAP,8,8,LR_LOADFROMFILE); 
HBITMAP  EnemyBullet::ebBITMAP=(HBITMAP)LoadImage(NULL,"敌人子弹.bmp",IMAGE_BITMAP,8,8,LR_LOADFROMFILE); 


//******************程序入口
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	//应用初始化
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	//消息循环
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
		
		MyPaint(hdc); //重绘
		
		gameWorld.moveAll();
		gameWorld.drawAll();
		
	}
 
    }

	return msg.wParam;
}

//**************定义和注册窗口类
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

//******************初始化函数
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	
	hInst = hInstance;
   
    HBITMAP bmp;
    	
    hWnd = CreateWindow("frame", "简单游戏框架" , WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
    //显示更新窗口
	MoveWindow(hWnd,0,0,winW,winH,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);//获取窗口DC
	mdc = CreateCompatibleDC(hdc);//建立与窗口DC兼容的内存DC
	bufdc = CreateCompatibleDC(hdc);//建立与窗口DC兼容的缓冲DC

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	cW=clientRect.right;
	cH=clientRect.bottom;
      
	bmp = CreateCompatibleBitmap(hdc,winW,winH);
	SelectObject(mdc,bmp);
    bg = (HBITMAP)LoadImage(NULL,"黑背景.bmp",IMAGE_BITMAP,800,600,LR_LOADFROMFILE);
    bz = (HBITMAP)LoadImage(NULL,"爆炸.bmp",IMAGE_BITMAP,40,160,LR_LOADFROMFILE); //加载位图文件到位图对象
    gameOverBITMAP=(HBITMAP)LoadImage(NULL,"失败.bmp",IMAGE_BITMAP,800,600,LR_LOADFROMFILE);
    gameWorld.init();

	return TRUE;
}

//**********自定义重绘函数

void MyPaint(HDC hdc)
{	
	BitBlt(hdc,0,0,800,600,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();     //取上次重绘的结束时间滴

	num++;
	if(num == 4)   num = 0;
}

//**************消息处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		
		case WM_DESTROY:			 //窗口结束消息
		
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
		default:							//其他消息
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
