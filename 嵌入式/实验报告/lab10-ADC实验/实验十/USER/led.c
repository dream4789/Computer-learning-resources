#include "led.h"

/*
 * 函数名：LED_GPIO_Config
 * 描述  ：配置LED用到的I/O口
 * LED1:PA1-PA8
 * LED2:PB1-PB8
 * 输入  ：无
 * 输出  ：无
 */
 
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//声明外设初始化结构体变量
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);//启动外设时钟 
	/* 配置LED1:PA1-PA8 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //通用推挽输出     
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//最高频率为50M
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	//初始化外设,LED全灭
	GPIO_SetBits(GPIOA,GPIO_Pin_All); //默认输出高电平，各位置不亮
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
