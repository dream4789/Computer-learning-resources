#ifndef __smg_H
#define	__smg_H
#include "stm32f10x.h"

void led_duan_init(void);//段选初始化	GPIO A0~7
void led_wei_init(void);	//位选初始化	GPIO E0~7
void Display(u8 index);
#endif /* __smg_H */
