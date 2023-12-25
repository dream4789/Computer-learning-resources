/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ��LED1��0.5hz��Ƶ����˸(��ʱ�� TIM2 ������ʱ)��        
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "led.h" 
#include "Time_test.h"

volatile u32 time; // ms ��ʱ����

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����	
 */
int main(void)
{
	SystemInit();	/* ����ϵͳʱ��Ϊ 72M */  
	LED_GPIO_Config();	/* led �˿����� */ 
	TIM2_NVIC_Configuration();	/* TIM2 ��ʱ���� */
  TIM2_Configuration();	/*TIM_Period--1000   TIM_Prescaler--71 -->�ж�����Ϊ1ms*/
	START_TIME;	/* TIM2 ��ʼ��ʱ */
	
  while(1)
  {
			while(time!=1000); time = 0;
			LED1(1);LED2(1);LED3(1);
			
			while(time!=1000); time = 0;
			LED1(0);LED2(0);LED3(0);  

			
			// GPIOD->ODR^=GPIO_Pin_1;
			// GPIO_WriteBit(GPIOD, GPIO_Pin_1, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_1)))); 
			// GPIOD->ODR^=GPIO_Pin_4;
			// GPIO_WriteBit(GPIOD, GPIO_Pin_4, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_4)))); 
			
			// while(time!=3000); time = 0;
			
			// GPIOD->ODR^=GPIO_Pin_1;
			// GPIO_WriteBit(GPIOD, GPIO_Pin_1, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_1)))); 
			// GPIOD->ODR^=GPIO_Pin_4;
			// GPIO_WriteBit(GPIOD, GPIO_Pin_4, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_4)))); 
			
			
			
			// GPIO_WriteBit(GPIOD, GPIO_Pin_3, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_3)))); 
			// GPIO_WriteBit(GPIOD, GPIO_Pin_4, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_4)))); 
			// GPIO_WriteBit(GPIOD, GPIO_Pin_5, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_5)))); 
			
  }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
