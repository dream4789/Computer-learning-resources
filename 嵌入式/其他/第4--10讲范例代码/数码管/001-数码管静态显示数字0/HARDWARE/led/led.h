#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define DX0 PAout(0)     //������������ݶ˿�
#define DX1 PAout(1)
#define DX2 PAout(2)
#define DX3 PAout(3)
#define DX4 PAout(4)
#define DX5 PAout(5)
#define DX6 PAout(6)
#define DX7 PAout(7)

#define D0 PEout(0)     //�����һ��������������ƽ�
#define D1 PEout(1)     //����ڶ���������������ƽ�
#define D2 PEout(2)     //���������������������ƽ�
#define D3 PEout(3)     //������ĸ�������������ƽ�
#define D4 PEout(4)     //��������������������ƽ�
#define D5 PEout(5)     //���������������������ƽ�
#define D6 PEout(6)     //������߸�������������ƽ�
#define D7 PEout(7)     //����ڰ˸�������������ƽ�


void LED_Init(void);
void Display(u8 index);


		 				    
#endif
