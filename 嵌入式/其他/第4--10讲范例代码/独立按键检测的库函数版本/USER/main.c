/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ���������Ժ���������Ϊɨ��ģʽ        
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h" 
#include "led.h"
#include "key.h"  

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
	

	/*config key*/
	Key_GPIO_Config();	
	
	while(1)                            
	{	   
		if( Key_Scan(GPIOE,GPIO_Pin_1) == KEY_ON  )
		{
			/*LED1��ת*/
			GPIO_WriteBit(GPIOC, GPIO_Pin_1, 
				(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_1))));
		}   
		if( Key_Scan(GPIOE,GPIO_Pin_2) == KEY_ON  )
		{
			/*LED2��ת*/
			GPIO_WriteBit(GPIOC, GPIO_Pin_2, 
				(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_2))));
		}   
		if( Key_Scan(GPIOE,GPIO_Pin_3) == KEY_ON  )
		{
			/*LED3��ת*/
			GPIO_WriteBit(GPIOC, GPIO_Pin_3, 
				(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_3))));
		}   
		if( Key_Scan(GPIOE,GPIO_Pin_4) == KEY_ON  )
		{
			/*LED4��ת*/
			GPIO_WriteBit(GPIOC, GPIO_Pin_4, 
				(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_4))));
		}   
	}
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
