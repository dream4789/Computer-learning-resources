#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
 
 
int main(void)
 {	
	  delay_init();	    //��ʱ��ʼ������
	  LED_Init();		  	//����ܳ�ʼ������
	while(1)
	{
				Display(0);
		D0=0;//�Ȳ�
		delay_ms(1);
		D0=1;//����ʾ   //��һ���������ʾ����0
				Display(1);D1=0;delay_ms(1);D1=1;   //�ڶ����������ʾ����1
				Display(2);D2=0;delay_ms(1);D2=1;   //�������������ʾ����2
				Display(3);D3=0;delay_ms(1);D3=1;   //���ĸ��������ʾ����3
				Display(4);D4=0;delay_ms(1);D4=1;   //������������ʾ����4
				Display(5);D5=0;delay_ms(1);D5=1;   //�������������ʾ����5
				Display(6);D6=0;delay_ms(1);D6=1;   //�������������ʾ����6
				Display(7);D7=0;delay_ms(1);D7=1;	  //���߸��������ʾ����7
	}
 }


