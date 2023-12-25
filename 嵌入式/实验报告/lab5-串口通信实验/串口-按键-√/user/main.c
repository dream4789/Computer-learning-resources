#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include<stdio.h>

void RCC_Config(void);
void GPIO_Config(void);
void USART_Config(void);
int fputc(int ch,FILE *f);
int fgetc(FILE *f);

int main()
{
	char msg[100];//输入字符串长度最大不超过100
	int temp = 1;//作为对话次数的标志
	RCC_Config();//时钟初始化
	GPIO_Config();//GPIO初始化
	USART_Config();//USART初始化

	while(1)
	{
		USART_ClearFlag(USART1,USART_FLAG_TC);//清除发送标志
		USART_ClearFlag(USART1,USART_FLAG_RXNE);//清除接受标志
		printf("input:\n");
		scanf("%s",msg);//键盘输入
		printf("\r\noutput:%s\r\n",msg);
	}
}

void RCC_Config(void)
{
	//SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//串口1挂在APB2上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//USART_Tx(PA9)  USART_Rx(PA10)
}

void GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;       //USART1_TX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIOA初始化
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;      //USART1_RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIOA初始化
}

void USART_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate=115200;//通信波特率
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//一个字节8bit
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//一位停止位
	USART_InitStructure.USART_Parity=USART_Parity_No;//无校验
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;//收发模式
	USART_Init(USART1,&USART_InitStructure);//USART1初始化
	
	USART_Cmd(USART1,ENABLE);//允许其工作
}

int fputc(int ch,FILE *f)
{
	if(ch=='\n')//换行
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//是否发送完成
		USART_SendData(USART1,'\r');//发送完成则回车
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	USART_SendData(USART1,ch);//继续发送
	return ch;
}

int fgetc(FILE *f)
{
	int ch;
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);//是否已接收数据
	ch = USART_ReceiveData(USART1);
	//将接收的数据发送回去，实现键盘的回显功能
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	USART_SendData(USART1,(uint8_t)ch);
	return ch;
}
