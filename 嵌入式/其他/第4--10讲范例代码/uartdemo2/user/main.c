#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include <stdarg.h>
#include <string.h>
#include<stdio.h>

void RCC_Config(void);
void GPIO_Config(void);
void USART_Config(void);
void Uart_SendByte(int data);
void Uart_SendString(char *ptr);
void Uart_Printf(const char *fmt,...);


int main()
{
	RCC_Config();
	GPIO_Config();
	USART_Config();
	USART_ClearFlag(USART1,USART_FLAG_TC);
	Uart_Printf("hello,world 安徽工业大学计算机学院欢迎你\n");
	Uart_Printf("a=%d\n",10);
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

void Uart_SendByte(int data)
{
	if(data=='\n')
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,'\r');
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,data);
}

void Uart_SendString(char *pt)
{
	char *dst=pt;
	while(dst< pt+strlen(pt))
	{
		Uart_SendByte(*dst++);
	}
}

void Uart_Printf(const char *fmt,...)
{
	va_list ap;
	char string[50];
	va_start(ap,fmt);
	vsprintf(string,fmt,ap);
	va_end(ap);
	Uart_SendString(string);
}
