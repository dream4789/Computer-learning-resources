#ifndef __dz_H
#define	__dz_H
#include"stm32f10x.h"

void LED_Init(void);
void Display(u8 index);
void Delay(__IO u32 nCount);
void zero(void);
void one(void);
void led_display(void);
#endif /* __dz_H */
