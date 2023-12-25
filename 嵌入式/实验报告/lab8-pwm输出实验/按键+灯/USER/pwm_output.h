#ifndef __PWM_OUTPUT_H
#define	__PWM_OUTPUT_H

#include "stm32f10x.h"

#define KEY_ON	0
#define KEY_OFF	1

void TIM3_PWM_Init(void);
void Delay(__IO u32 nCount);
void Key_GPIO_Config(void);
static void TIM3_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
static void TIM3_Mode_Config(void);

#endif /* __PWM_OUTPUT_H */

