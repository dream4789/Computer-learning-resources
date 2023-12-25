#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include<stdio.h>

void RCC_Config(void);
void GPIO_Config(void);
void USART_Config(void);
int fputc(int ch,FILE *f);

u16 flash_size;

int main()
{
	RCC_Config();
	GPIO_Config();
	USART_Config();
	USART_ClearFlag(USART1,USART_FLAG_TC);

	flash_size = *( unsigned  int * )( 0x1FFFF7E0 );	//…¡¥Ê»›¡ø
	printf("–æ∆¨…¡¥Ê»›¡ø¥Û–°Œ™%dK\r\n",flash_size);
	
}

void RCC_Config(void)
{
	//SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}

void GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;       //USART1_TX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;      //USART1_RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void USART_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}

int fputc(int ch,FILE *f)
{
	if(ch=='\n')
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		 USART_SendData(USART1,'\r');
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		 USART_SendData(USART1,ch);
	return ch;
}
