#include "stm32f10x.h"

#define PA0out *((volatile unsigned long *)(0x42000000 + (GPIOA_BASE + 0x0C -0x40000000)*32 + 0 * 4))
#define PA1out *((volatile unsigned long *)(0x42000000 + (GPIOA_BASE + 0x0C -0x40000000)*32 + 1 * 4))

int main()
{
		/***1. 初始化外设***/
		/***2. 在死循环中执行各逻辑功能***/
	//PA0 输出低电平
	//PA1 输出高电平
	//PA2 输入引脚
	//PA3 输出引脚，==PA2


	GPIO_InitTypeDef GPIO_InitTypeSrtuc;

	//开启PA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	
	/******************寄存器操作BEGIN******************/
	//初始化PA0，PA1为推挽式输出
	GPIOA->CRL &= 0xFFFFFF00;
	GPIOA->CRL |= 0x00000023;

	//PA0输出低电平，PA1输出高电平
//	GPIOA->ODR &= 0xFFFC;
//	GPIOA->ODR |= 0X0002;
	
	//PA0输出低电平，PA1输出高电平
//	GPIOA->BRR  |= 0x00000001;
//	GPIOA->BSRR |= 0x00000002;
	
	//PA0输出低电平，PA1输出高电平
//	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
//	GPIO_SetBits(GPIOA, GPIO_Pin_1);
		PA0out = 0;
		PA1out = 1;
	
	/******************寄存器操作END*******************/

	/******************库函数操作BEGIN******************/
	
	//初始化PA2为浮空式输入
  GPIO_InitTypeSrtuc.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitTypeSrtuc.GPIO_Pin  = GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_InitTypeSrtuc);
	
  GPIO_InitTypeSrtuc.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitTypeSrtuc.GPIO_Pin   = GPIO_Pin_3;
	GPIO_InitTypeSrtuc.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeSrtuc);
	
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == Bit_SET)
			GPIO_SetBits(GPIOA, GPIO_Pin_3);
		else
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		
	}
	/******************库函数操作END******************/
}
