/******************** (C) COPYRIGHT 2012 WildFire Team ********************
 * 文件名  ：exti.c
 * 描述    ：I/O线中断应用函数库         
 * 实验平台：野火STM32开发板
 * 硬件连接：-------------------------
 *          | PD12 - key1              |
 *          | PE6 - key2(本实验没用到)|
 *          |                         |
 *           -------------------------
 * 库版本  ：ST3.0.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "exti.h"

/*
 * 函数名：NVIC_Configuration
 * 描述  ：配置嵌套向量中断控制器NVIC
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置P[A|B|C|D|E]5为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}

/*
 * 函数名：EXTI_PE5_Config
 * 描述  ：配置 PE5 为线中断口，并设置中断优先级
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void EXTI_PE5_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline(PD12) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
												
	/* config the NVIC(PD12) */
	NVIC_Configuration();

	/* EXTI line gpio config(PD12) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // 上拉输入
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* EXTI line(PD5) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource12); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE****/

