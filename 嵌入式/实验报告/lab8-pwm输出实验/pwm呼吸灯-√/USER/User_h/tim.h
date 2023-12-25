#ifndef __TIM_H
#define __TIM_H

#include "stm32f10x.h"
void myTIM_Tim3BaseInit(u16 _arr, u16 _psc);
void myTIM_TimingItInit(void);
void myTIM_Tim3PWM2Init(void);
void myTIM_TimxStart(TIM_TypeDef* TIMx);

#endif /* __TIM_H */
