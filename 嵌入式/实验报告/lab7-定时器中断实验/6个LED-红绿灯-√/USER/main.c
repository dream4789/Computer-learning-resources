/******************** (C) COPYRIGHT 2012 WildFire Team **************************

 * 描述    ：LED1以0.5hz的频率闪烁(定时器 TIM2 产生定时)

**********************************************************************************/
#include "stm32f10x.h"
#include "led.h" 
#include "Time_test.h"

volatile u32 time; // ms 计时变量

int main(void)
{
	int i;
	SystemInit();	   /* 配置系统时钟为 72M */  
	LED_GPIO_Config();  /* led 端口配置 */
	TIM2_NVIC_Configuration();	/* TIM2 定时配置 */
  TIM2_Configuration();	/*TIM_Period--1000   TIM_Prescaler--71 -->中断周期为1ms*/
	START_TIME;	/* TIM2 开始计时 */
	
  while(1)
  {
		
		GPIOD->ODR^=GPIO_Pin_1;   // 红灯亮
		GPIOD->ODR^=GPIO_Pin_8;
		// GPIO_WriteBit(GPIOD, GPIO_Pin_1, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_1)))); 
		// GPIOD->ODR^=GPIO_Pin_4; 错
		// GPIO_WriteBit(GPIOD, GPIO_Pin_4, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_4)))); 错
		
		while(time!=3000);
		time = 0;
		
		GPIOD->ODR^=GPIO_Pin_1;  // 红灯灭
		GPIOD->ODR^=GPIO_Pin_8;
		// GPIO_WriteBit(GPIOD, GPIO_Pin_1, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_1)))); 
		// GPIOD->ODR^=GPIO_Pin_4; 错
		// GPIO_WriteBit(GPIOD, GPIO_Pin_4, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_4)))); 错
						

		GPIOD->ODR^=GPIO_Pin_2;  // 绿灯亮
		GPIOD->ODR^=GPIO_Pin_7;
		
		while(time!=3000);
		time = 0;
		
		GPIOD->ODR^=GPIO_Pin_2; // 绿灯灭
		GPIOD->ODR^=GPIO_Pin_7;
		
		for(i = 0; i<6; i++)
		{
				GPIOD->ODR^=GPIO_Pin_3;  // 黄灯闪烁
				GPIOD->ODR^=GPIO_Pin_6;
				while(time!=800);
				time = 0;
		}
  }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
