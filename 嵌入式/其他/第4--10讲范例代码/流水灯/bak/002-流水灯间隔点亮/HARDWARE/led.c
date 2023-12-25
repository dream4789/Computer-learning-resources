#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//?????????,??????,??????????
//ALIENTEK??STM32???
//LED????	   
//????@ALIENTEK
//????:www.openedv.com
//????:2012/9/2
//??:V1.0
//????,?????
//Copyright(C) ????????????? 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   


void LED_Init(void)                                                       //
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	                //使能PA口的时钟
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                //速度50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					                      //根据设定参数配置PA口
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); //把PA0-PA7置为高电平
		
}
 
