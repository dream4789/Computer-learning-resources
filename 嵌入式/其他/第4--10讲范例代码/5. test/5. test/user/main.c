#include "stm32f10x.h"

#define PA0out *((volatile unsigned long *)(0x42000000 + (GPIOA_BASE + 0x0C -0x40000000)*32 + 0 * 4))
#define PA1out *((volatile unsigned long *)(0x42000000 + (GPIOA_BASE + 0x0C -0x40000000)*32 + 1 * 4))

int main()
{
		/***1. ��ʼ������***/
		/***2. ����ѭ����ִ�и��߼�����***/
	//PA0 ����͵�ƽ
	//PA1 ����ߵ�ƽ
	//PA2 ��������
	//PA3 ������ţ�==PA2


	GPIO_InitTypeDef GPIO_InitTypeSrtuc;

	//����PAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	
	/******************�Ĵ�������BEGIN******************/
	//��ʼ��PA0��PA1Ϊ����ʽ���
	GPIOA->CRL &= 0xFFFFFF00;
	GPIOA->CRL |= 0x00000023;

	//PA0����͵�ƽ��PA1����ߵ�ƽ
//	GPIOA->ODR &= 0xFFFC;
//	GPIOA->ODR |= 0X0002;
	
	//PA0����͵�ƽ��PA1����ߵ�ƽ
//	GPIOA->BRR  |= 0x00000001;
//	GPIOA->BSRR |= 0x00000002;
	
	//PA0����͵�ƽ��PA1����ߵ�ƽ
//	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
//	GPIO_SetBits(GPIOA, GPIO_Pin_1);
		PA0out = 0;
		PA1out = 1;
	
	/******************�Ĵ�������END*******************/

	/******************�⺯������BEGIN******************/
	
	//��ʼ��PA2Ϊ����ʽ����
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
	/******************�⺯������END******************/
}
