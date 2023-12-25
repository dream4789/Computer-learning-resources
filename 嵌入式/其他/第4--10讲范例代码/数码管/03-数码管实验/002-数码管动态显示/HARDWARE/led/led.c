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

//h g f e d c b a
//1 1 0 0 0 0 0 0 --共阳方式显示0   
u8 seg_tab[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能PA口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOA, &GPIO_InitStructure);				
	 GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);


	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能PE口时钟

	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//KEY0-KEY2
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
 	 GPIO_Init(GPIOE, &GPIO_InitStructure);//
	 GPIO_SetBits(GPIOE,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

}

void Display(u8 index)	//??1????,??2 0:??/1:??
{
	DX0 = seg_tab[index]&0x01;
	DX1 = (seg_tab[index]>>1)&0x01;
	DX2 = (seg_tab[index]>>2)&0x01;
	DX3 = (seg_tab[index]>>3)&0x01;
	DX4 = (seg_tab[index]>>4)&0x01;
	DX5 = (seg_tab[index]>>5)&0x01;
	DX6 = (seg_tab[index]>>6)&0x01;
	DX7 = (seg_tab[index]>>7)&0x01;
	

}
 
