#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1

//带参宏，可以像内联函数一样使用
#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_1)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_2)

#define LED3(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_3)

#define LED4(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_4)

#define LED5(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_5)

#define LED6(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_6)
					
#define LED7(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_7)

#define LED8(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_8)
					
								
void LED_GPIO_Config(void);

#endif /* __LED_H */
