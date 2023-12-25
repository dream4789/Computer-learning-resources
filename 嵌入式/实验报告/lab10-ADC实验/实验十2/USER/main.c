/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ������1(USART1)����Եĳ����ն���1sΪ�����ӡ��ǰADC1��ת����ѹֵ         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "adc.h"
#include "smg.h"
#include "led.h"

        

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */

int main(void)
{	

  int ADC_ConvertedValue;
	float voltage;
	int i,j;
	uint8_t a[8];
	int b[8]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7};//�����λѡ�˿�
	
	led_duan_init();
	led_wei_init();	
	
	LED_GPIO_Config();
	/* USART1 config */
	USART1_Config();
	/* enable adc1 and config adc1 to dma mode */
	ADC1_Init();
	printf("ADC1ת�����\r\n");
	while (1)
	{
		/* ����û�в����ⲿ����������ʹ���������ADCת�� */ 
	  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		/* �ȴ�ת������ */
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
		ADC_ConvertedValue=ADC_GetConversionValue(ADC1);
		voltage =(float) ADC_ConvertedValue /4096*3.3; // ��ȡת����ADֵ
		if(voltage<1.5)//��ɫ
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_All);
			GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		}
		else if(1.5<=voltage&&voltage<1.6)//��ɫ
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_All);
			GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		}
		else 
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_All);
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}		
		a[0]=(int)voltage;
		a[1]=10;
		a[2]=((int)(voltage*10))%10;
		a[3]=((int)(voltage*100))%10;
		a[4]=((int)(voltage*1000))%10;
		a[5]=((int)(voltage*10000))%10;
		a[6]=((int)(voltage*100000))%10;
		a[7]=((int)(voltage*1000000))%10;				
		for(j=0;j<1000;j++)
		{
			for(i=0;i<8;i++)
			{
				Display(a[i]);//д���ѡ�˿�
				GPIO_ResetBits(GPIOD,b[i]);//��iλ��
				Delay(0x0000FF);//������ʱ
				GPIO_SetBits(GPIOD,b[i]);//��iλ��	
			}
			i=0;
		}
				
		printf("\r\n��ǰ��ѹ��������0x%04X \r\n", ADC_ConvertedValue); 
		printf("\r\n��ǰ��ѹģ��ֵ��%f V \r\n",voltage); 
		//Delay(0xffffee);                              // ��ʱ 
	}
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
