#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define DX0 PAout(0)//PA口规定字形
#define DX1 PAout(1)
#define DX2 PAout(2)
#define DX3 PAout(3)
#define DX4 PAout(4)
#define DX5 PAout(5)
#define DX6 PAout(6)
#define DX7 PAout(7)

#define D0 PEout(0)//PE口规定字位
#define D1 PEout(1)
#define D2 PEout(2)
#define D3 PEout(3)
#define D4 PEout(4)
#define D5 PEout(5)
#define D6 PEout(6)
#define D7 PEout(7)


void LED_Init(void);
void Display(u8 index);


		 				    
#endif
