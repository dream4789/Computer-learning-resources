#include "led.h"

/*
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * LED1:PA1-PA8
 * LED2:PB1-PB8
 * ����  ����
 * ���  ����
 */
 
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//���������ʼ���ṹ�����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);//��������ʱ�� 
	/* ����LED1:PA1-PA8 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ͨ���������     
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//���Ƶ��Ϊ50M
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
	//��ʼ������,LEDȫ��
	GPIO_SetBits(GPIOA,GPIO_Pin_All); //Ĭ������ߵ�ƽ����λ�ò���
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
