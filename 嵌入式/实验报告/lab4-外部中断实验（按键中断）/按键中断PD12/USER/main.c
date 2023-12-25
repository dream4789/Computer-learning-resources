/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：PE5连接到key1，PE5配置为线中断模式，key1按下时，进入线中断处理函数，
 *           LED1状态取反。         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h" 
#include "led.h"
#include "exti.h"

/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{	
	/* config the led */
	LED_GPIO_Config();
	LED1( ON );
	
	/* exti line config */
	EXTI_PE5_Config(); 
	
	/* wait interrupt */
	while(1)                            
	{
	}
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
