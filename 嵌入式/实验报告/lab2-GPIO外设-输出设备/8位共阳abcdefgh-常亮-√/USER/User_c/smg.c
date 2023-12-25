#include "smg.h"
				// 共阳  	a			b			c			d			e			f			f			g
u8 seg_tab[10]={0x88, 0x80, 0xc6, 0xc0, 0x86, 0x8e, 0x82, 0x89};

void led_duan_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能 PA 端口时钟
	
	//初始化PA0~PA7(控制数码管LED)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA,GPIO_Pin_All);	//默认输出高电平
}

/*
数码管位选控制	PE0-PE7 的初始化
*/
void led_wei_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	//使能 PE 端口时钟
	
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP; 	//推挽输出
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOE,GPIO_Pin_All);					  	//默认输出高电平，各位置不亮
}


void Display(u8 index)
{
	GPIO_Write(GPIOA ,seg_tab[index]);//将译码写到GPIOA的端口
}

