/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ��3��LED�� SysTick �Ŀ����£���500ms��Ƶ����˸��         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "SysTick.h"
#include "led.h"

uint32_t ticktime;
/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();

	for(;;)
	{

		LED1( 0 ); 
	    Delay_us(50000);    	// 50000 * 10us = 500ms
		LED1( 1 );
	  
		LED2( 0 );
	    Delay_us(50000);		// 50000 * 10us = 500ms
		LED2( 1 );
	
		LED3( 0 );
	    Delay_us(50000);		// 50000 * 10us = 500ms
		LED3( 1 );	

	}
    
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
