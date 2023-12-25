#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define ON  0
#define OFF 1

#define KEY_ON	0
#define KEY_OFF	1

//PB5
#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_5)

void myLED2_Init(void);
void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);

#endif /* __LED_H */
