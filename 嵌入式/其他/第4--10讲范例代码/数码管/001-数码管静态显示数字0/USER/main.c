#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
 
 
int main(void)
 {	
	  delay_init();	    //��ʱ��ʼ������
	  LED_Init();       //����ܶ˿ڳ�ʼ������
		D0=0;D1=0;D2=0;D3=0;D4=0;D5=0;D6=0;D7=0;   
	while(1)
	{
				Display(0);  //�������ʾ0

	}
 }


