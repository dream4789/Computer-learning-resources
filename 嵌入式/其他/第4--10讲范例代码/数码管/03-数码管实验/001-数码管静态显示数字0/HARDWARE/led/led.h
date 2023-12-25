#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define DX0 PAout(0)     //定义数码管数据端口
#define DX1 PAout(1)
#define DX2 PAout(2)
#define DX3 PAout(3)
#define DX4 PAout(4)
#define DX5 PAout(5)
#define DX6 PAout(6)
#define DX7 PAout(7)

#define D0 PEout(0)     //定义第一个数码管阳极控制脚
#define D1 PEout(1)     //定义第二个数码管阳极控制脚
#define D2 PEout(2)     //定义第三个数码管阳极控制脚
#define D3 PEout(3)     //定义第四个数码管阳极控制脚
#define D4 PEout(4)     //定义第五个数码管阳极控制脚
#define D5 PEout(5)     //定义第六个数码管阳极控制脚
#define D6 PEout(6)     //定义第七个数码管阳极控制脚
#define D7 PEout(7)     //定义第八个数码管阳极控制脚


void LED_Init(void);
void Display(u8 index);


		 				    
#endif
