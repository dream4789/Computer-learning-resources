/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：3个LED在 SysTick 的控制下，以500ms的频率闪烁。         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "SysTick.h"
#include "led.h"

uint32_t ticktime;
/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{	
	/* LED 端口初始化 */
	LED_GPIO_Config();

	/* 配置SysTick 为10us中断一次 */
	SysTick_Init();

	for(;;)
	{

		LED1( 0 ); 
	    Delay_us(50000);    	// 50000 * 10us = 500ms
		LED1( 1 );
	  
		LED2( 0 );
	    Delay_us(50000);		// 50000 * 10us = 500ms
		LED2( 1 );
	
		LED3( 0 );
	    Delay_us(50000);		// 50000 * 10us = 500ms
		LED3( 1 );	

	}
    
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
