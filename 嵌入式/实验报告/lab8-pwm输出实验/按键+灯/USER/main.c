/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ����ʱ��TIM3������·PWM�������
 *           - PA.06: (TIM3_CH1)
 *           - PA.07: (TIM3_CH2)
 *           - PB.00: (TIM3_CH3)
 *           - PB.01: (TIM3_CH4) 
 *           TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
 *           TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
 *           TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
 *           TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
 *       
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "pwm_output.h"

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{

	
	/* TIM3 PWM�������ʼ������ʹ��TIM3 PWM��� */
	TIM3_PWM_Init();
	Key_GPIO_Config();
	
	while (1)
	{
		if(Key_Scan(GPIOE, GPIO_Pin_1) == KEY_ON)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_1,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1))));
		}
		
		if(Key_Scan(GPIOE, GPIO_Pin_2) == KEY_ON)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_7,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_7))));
		}
	}
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
