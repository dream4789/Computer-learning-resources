#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_ms(__IO u32 nTime);
void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u16 nms);
#endif /* __SYSTICK_H */
