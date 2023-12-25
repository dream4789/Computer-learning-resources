#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

 
void MyDelay( uint32_t count )
{
	for(; count!=0; count--);
} 
 
 int main(void)
 {	
	 MyDelay(0x7fffff);//�����ʱ
	
	LED_Init();		  	//PA0--PA7��Ӧ����LED1--LED8��PA�ڳ�ʼ��Ϊ����ʽ���
	while(1)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);//���ڹ����ӷ���PA0���0�������LED1
		GPIO_SetBits(GPIOA, GPIO_Pin_1);//���ڹ����ӷ���PA1���1����Ϩ��LED2
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
		
		MyDelay(0x7fffff);//�����ʱ
		GPIO_SetBits(GPIOA, GPIO_Pin_0);//���ڹ����ӷ���PA0���1����Ϩ��LED1
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);//���ڹ����ӷ���PA1���0�������LED2
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		
		MyDelay(0x7fffff);//�����ʱ
	}
 }


