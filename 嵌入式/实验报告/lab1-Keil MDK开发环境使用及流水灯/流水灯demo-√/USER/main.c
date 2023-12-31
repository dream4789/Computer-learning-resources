/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：LED流水灯，频率可调……         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "led.h"

//#define    MI_ERR    (-2)

void Delay(__IO u32 nCount);

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

	while (1)
	{
		LED1( ON );			  // 亮
		Delay(0x0FFFEF);
		LED1( OFF );		  // 灭
		
		LED2( ON );
		Delay(0x0FFFEF);
		LED2( OFF );
		
		LED3( ON );
		Delay(0x0FFFEF);
		LED3( OFF );      
		
		LED4( ON );			  // 亮
		Delay(0x0FFFEF);
		LED4( OFF );		  // 灭
		
		LED5( ON );
		Delay(0x0FFFEF);
		LED5( OFF );
		
		LED6( ON );
		Delay(0x0FFFEF);
		LED6( OFF );   
		
		LED7 ( ON );			  // 亮
		Delay(0x0FFFEF);
		LED7( OFF );		  // 灭
		
		LED8( ON );
		Delay(0x0FFFEF);
		LED8( OFF );
	}
}

void Delay(__IO u32 nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
} 


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
