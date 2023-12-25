/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * 文件名  ：SysTick.c
 * 描述    ：SysTick 系统滴答时钟10us中断函数库,中断时间可自由配置，
 *           常用的有 1us 10us 1ms 中断。         
 * 实验平台：野火STM32开发板
 * 硬件连接：-----------------
 *          |                 |
 *          |      无         |
 *          |                 |
 *           -----------------
 * 库版本  ：ST3.5.0
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "SysTick.h"
static u8 fac_us = 0;
static u16 fac_ms = 0;

static __IO u32 TimingDelay;

/*
 * 函数名：SysTick_Init
 * 描述  ：启动系统滴答定时器 SysTick
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用 
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
		// 关闭滴答定时器  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

void delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us = SystemCoreClock/8000000;
	fac_ms = (u16)fac_us*1000;
}
/*
void Delay_ms(__IO u32 nTime)
{
	TimingDelay = nTime;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(TimingDelay!=0);
	SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;

}
*/
void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD = nus*fac_us;//时间加载
	SysTick->VAL = 0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;//开始倒计时
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));//等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭计数器
	SysTick->VAL = 0x00;//清空计数器
}

void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD = (u32)nms*fac_ms;//时间加载
	SysTick->VAL = 0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;//开始倒计时
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));//等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭计数器
	SysTick->VAL = 0x00;//清空计数器
}

void SysTick_Handler(void)
{
	TimingDelay--;
}

/*
 * 函数名：Delay_us
 * 描述  ：us延时程序,10us为一个单位
 * 输入  ：- nTime
 * 输出  ：无
 * 调用  ：Delay_us( 1 ) 则实现的延时为 1 * 10us = 10us
 *       ：外部调用 
 */

/*
void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// 使能滴答定时器  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}
*/

/*
 * 函数名：TimingDelay_Decrement
 * 描述  ：获取节拍程序
 * 输入  ：无
 * 输出  ：无
 * 调用  ：在 SysTick 中断函数 SysTick_Handler()调用
 */  
 
/*
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
	TimingDelay--;
	}
}
*/
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
