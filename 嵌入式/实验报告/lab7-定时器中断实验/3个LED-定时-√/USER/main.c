/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：LED1以0.5hz的频率闪烁(定时器 TIM2 产生定时)。        
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "led.h" 
#include "Time_test.h"

volatile u32 time; // ms 计时变量

/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无	
 */
int main(void)
{
	SystemInit();	/* 配置系统时钟为 72M */  
	LED_GPIO_Config();	/* led 端口配置 */ 
	TIM2_NVIC_Configuration();	/* TIM2 定时配置 */
  TIM2_Configuration();	/*TIM_Period--1000   TIM_Prescaler--71 -->中断周期为1ms*/
	START_TIME;	/* TIM2 开始计时 */
	
  while(1)
  {
			while(time!=1000); time = 0;
			LED1(1);LED2(1);LED3(1);
			
			while(time!=1000); time = 0;
			LED1(0);LED2(0);LED3(0);  

			
			// GPIOD->ODR^=GPIO_Pin_1;
			// GPIO_WriteBit(GPIOD, GPIO_Pin_1, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_1)))); 
			// GPIOD->ODR^=GPIO_Pin_4;
			// GPIO_WriteBit(GPIOD, GPIO_Pin_4, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_4)))); 
			
			// while(time!=3000); time = 0;
			
			// GPIOD->ODR^=GPIO_Pin_1;
			// GPIO_WriteBit(GPIOD, GPIO_Pin_1, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_1)))); 
			// GPIOD->ODR^=GPIO_Pin_4;
			// GPIO_WriteBit(GPIOD, GPIO_Pin_4, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_4)))); 
			
			
			
			// GPIO_WriteBit(GPIOD, GPIO_Pin_3, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_3)))); 
			// GPIO_WriteBit(GPIOD, GPIO_Pin_4, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_4)))); 
			// GPIO_WriteBit(GPIOD, GPIO_Pin_5, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_5)))); 
			
  }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
