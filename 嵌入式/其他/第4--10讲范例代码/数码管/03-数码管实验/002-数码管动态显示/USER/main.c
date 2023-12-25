#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
 
 
int main(void)
 {	
	  delay_init();	    //延时初始化函数
	  LED_Init();		  	//数码管初始化函数
	while(1)
	{
				Display(0);
		D0=0;//先擦
		delay_ms(1);
		D0=1;//再显示   //第一个数码管显示数字0
				Display(1);D1=0;delay_ms(1);D1=1;   //第二个数码管显示数字1
				Display(2);D2=0;delay_ms(1);D2=1;   //第三个数码管显示数字2
				Display(3);D3=0;delay_ms(1);D3=1;   //第四个数码管显示数字3
				Display(4);D4=0;delay_ms(1);D4=1;   //第五个数码管显示数字4
				Display(5);D5=0;delay_ms(1);D5=1;   //第六个数码管显示数字5
				Display(6);D6=0;delay_ms(1);D6=1;   //第六个数码管显示数字6
				Display(7);D7=0;delay_ms(1);D7=1;	  //第七个数码管显示数字7
	}
 }


