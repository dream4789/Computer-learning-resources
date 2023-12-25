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
	/* ����ϵͳʱ��Ϊ 72M */  
	SystemInit();

	/* led �˿����� */ 
	LED_GPIO_Config();

	/* TIM2 ��ʱ���� */
	TIM2_NVIC_Configuration();
	/*TIM_Period--1000   TIM_Prescaler--71 -->�ж�����Ϊ1ms*/
  TIM2_Configuration();

	/* TIM2 ��ʼ��ʱ */
	START_TIME;
	
  while(1)
  {
    if ( time == 1000 ) /* 1s ʱ�䵽 */
    {
      time = 0;
			/* LED1 ȡ�� */      
			GPIO_WriteBit(GPIOC, GPIO_Pin_3, 
		               (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_3)))); 
    }        
  }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
