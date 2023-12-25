#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
 
 
/************************************************
 ALIENTEK??STM32?????1
 ????? 
 ????:www.openedv.com
 ????:http://eboard.taobao.com 
 ???????????:"????",????STM32???
 ?????????????  
 ??:???? @ALIENTEK
************************************************/

 
 int main(void)
 {	
	delay_init();	    //延时初始化函数 
	LED_Init();		  	//LED初始化函数
	while(1)
	{
		LED0=0;	delay_ms(300);	
//		LED1=0;	delay_ms(300);
//		LED2=0;	delay_ms(300);
//		LED3=0;	delay_ms(300);
//		LED4=0;	delay_ms(300);
//		LED5=0;	delay_ms(300);
//		LED6=0;	delay_ms(300);
//		LED7=0;	delay_ms(300);	
		LED0=1;	
		//LED1=1;LED2=1;LED3=1;LED4=1;LED5=1;LED6=1;LED7=1;
		delay_ms(300);		
	
	}
 }


