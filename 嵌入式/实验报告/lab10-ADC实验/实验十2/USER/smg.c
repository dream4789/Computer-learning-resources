#include "smg.h"
							//	0		 1		2		 3	  4		 5		6		 7   8		9    10
u8 seg_tab[11]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x7F};

void led_duan_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	//ʹ�� PA �˿�ʱ��
	
	//��ʼ��PC0~PC7(���������LED)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_SetBits(GPIOE,GPIO_Pin_All);	//Ĭ������ߵ�ƽ
}

/*
�����λѡ����	PD0-PD7 �ĳ�ʼ��
*/
void led_wei_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//ʹ�� PE �˿�ʱ��
	
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP; 	//�������
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_All);					  	//Ĭ������ߵ�ƽ����λ�ò���
}


void Display(u8 index)
{
	GPIO_Write(GPIOE ,seg_tab[index]);//������д��GPIOA�Ķ˿�
}

