/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：串口1(USART1)向电脑的超级终端以1s为间隔打印当前ADC1的转换电压值         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "adc.h"
#include "smg.h"
#include "led.h"

        

// 软件延时
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
	int b[8]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7};//数码管位选端口
	
	led_duan_init();
	led_wei_init();	
	
	LED_GPIO_Config();
	/* USART1 config */
	USART1_Config();
	/* enable adc1 and config adc1 to dma mode */
	ADC1_Init();
	printf("ADC1转换结果\r\n");
	while (1)
	{
		/* 由于没有采用外部触发，所以使用软件触发ADC转换 */ 
	  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		/* 等待转换结束 */
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
		ADC_ConvertedValue=ADC_GetConversionValue(ADC1);
		voltage =(float) ADC_ConvertedValue /4096*3.3; // 读取转换的AD值
		if(voltage<1.5)//黄色
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_All);
			GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		}
		else if(1.5<=voltage&&voltage<1.6)//绿色
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
				Display(a[i]);//写入段选端口
				GPIO_ResetBits(GPIOD,b[i]);//第i位亮
				Delay(0x0000FF);//短暂延时
				GPIO_SetBits(GPIOD,b[i]);//第i位灭	
			}
			i=0;
		}
				
		printf("\r\n当前电压数字量：0x%04X \r\n", ADC_ConvertedValue); 
		printf("\r\n当前电压模拟值：%f V \r\n",voltage); 
		//Delay(0xffffee);                              // 延时 
	}
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
