/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ��PE5���ӵ�key1��PE5����Ϊ���ж�ģʽ��key1����ʱ���������жϴ�������
 *           LED1״̬ȡ����         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h" 
#include "led.h"
#include "exti.h"

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{	
	/* config the led */
	LED_GPIO_Config();
	LED1( ON );
	
	/* exti line config */
	EXTI_PE5_Config(); 
	
	/* wait interrupt */
	while(1)                            
	{
	}
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
