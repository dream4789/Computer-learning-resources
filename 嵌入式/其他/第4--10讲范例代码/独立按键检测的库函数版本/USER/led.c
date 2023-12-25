/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * 文件名  ：led.c
 * 描述    ：led 应用函数库         
 * 实验平台：野火STM32开发板
 * 硬件连接：-----------------
 *          |   PC3 - LED1     |
 *          |   PC4 - LED2     |
 *          |   PC5 - LED3     |
 *           ----------------- 
 * 库版本  ：ST3.5.0
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "led.h"

/*
 * 函数名：LED_GPIO_Config
 * 描述  ：配置LED用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);//激活GPIOC对应时钟

  //使用引脚pc1--pc4	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出      
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//输出频率50Mhz
  	GPIO_Init(GPIOC, &GPIO_InitStructure);//按照上述设定初始化GPIOC

	GPIO_SetBits(GPIOC, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);	 // 熄灭led1--led4（共阳）
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
