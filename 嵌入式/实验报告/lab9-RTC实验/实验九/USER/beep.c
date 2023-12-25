#include "beep.h"

void BEEP_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //使能GPIOF端口时钟
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //BEEP-->PF.0 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
 GPIO_Init(GPIOF, &GPIO_InitStructure);	 //根据参数初始化GPIOF.0
 
 GPIO_SetBits(GPIOF,GPIO_Pin_All);//输出0，关闭蜂鸣器输出
}
