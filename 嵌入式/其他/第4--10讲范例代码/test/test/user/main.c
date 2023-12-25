#include "stm32f10x.h"
int main()
{
	
	int key;
		/***1. ��ʼ������***/
		/***2. ����ѭ����ִ�и��߼�����***/
	//PA0 ����͵�ƽ
	//PA1 ����ߵ�ƽ
	//Pe5 ��������,read key
	//Pb5 ������ţ�==Pe5


	GPIO_InitTypeDef GPIO_InitTypeSrtuc;

	//����PAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	
	/******************�Ĵ�������BEGIN******************/
	//��ʼ��PA0��PA1Ϊ����ʽ���
	GPIOA->CRL &= 0xFFFFFF00;
	GPIOA->CRL |= 0x00000023;

	//PA0����͵�ƽ��PA1����ߵ�ƽ
	GPIOA->ODR &= 0xFFFC;
	GPIOA->ODR |= 0X0002;
	/******************�Ĵ�������END*******************/

	/******************�⺯������BEGIN******************/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//��ʼ��Pe5Ϊ����ʽ����
  GPIO_InitTypeSrtuc.GPIO_Mode = GPIO_Mode_IPU;//��������ģ�����ⲿ��������Ҫ�ڲ������ṩĬ�ϵĸߵ�ƽ
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
	/******************�⺯������END******************/
}
