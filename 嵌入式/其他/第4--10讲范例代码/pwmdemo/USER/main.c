/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：定时器TIM3产生四路PWM波输出。
 *           - PA.06: (TIM3_CH1)
 *           - PA.07: (TIM3_CH2)
 *           - PB.00: (TIM3_CH3)
 *           - PB.01: (TIM3_CH4) 
 *           TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
 *           TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
 *           TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
 *           TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
 *       
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "pwm_output.h"

/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{

	
	/* TIM3 PWM波输出初始化，并使能TIM3 PWM输出 */
	TIM3_PWM_Init();
	
	while (1)
	{}
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
