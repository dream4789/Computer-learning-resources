#include "stm32f10x.h"
int main()
{
	
	int key;
		/***1. 初始化外设***/
		/***2. 在死循环中执行各逻辑功能***/
	//PA0 输出低电平
	//PA1 输出高电平
	//Pe5 输入引脚,read key
	//Pb5 输出引脚，==Pe5


	GPIO_InitTypeDef GPIO_InitTypeSrtuc;

	//开启PA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	
	/******************寄存器操作BEGIN******************/
	//初始化PA0，PA1为推挽式输出
	GPIOA->CRL &= 0xFFFFFF00;
	GPIOA->CRL |= 0x00000023;

	//PA0输出低电平，PA1输出高电平
	GPIOA->ODR &= 0xFFFC;
	GPIOA->ODR |= 0X0002;
	/******************寄存器操作END*******************/

	/******************库函数操作BEGIN******************/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//初始化Pe5为浮空式输入
  GPIO_InitTypeSrtuc.GPIO_Mode = GPIO_Mode_IPU;//独立按键模块无外部上拉，需要内部上拉提供默认的高电平
	GPIO_InitTypeSrtuc.GPIO_Pin  = GPIO_Pin_5;
	GPIO_Init(GPIOE, &GPIO_InitTypeSrtuc);
	
  GPIO_InitTypeSrtuc.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitTypeSrtuc.GPIO_Pin   = GPIO_Pin_5;
	GPIO_InitTypeSrtuc.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitTypeSrtuc);
	
	while(1)
	{
		key=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);
		if(key == Bit_SET)
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
		else
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		
	}
	/******************库函数操作END******************/
}
