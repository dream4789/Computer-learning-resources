#include "beep.h"

void BEEP_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //ʹ��GPIOF�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //BEEP-->PF.0 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOF, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOF.0
 
 GPIO_SetBits(GPIOF,GPIO_Pin_All);//���0���رշ��������
}
