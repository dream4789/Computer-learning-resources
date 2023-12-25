#include "led.h"
#include "delay.h"
// #include "key.h"
#include "sys.h"
// #include "usart.h"
#include "timer.h"
 
/************************************************
 PWM输出实验
 PB5 - LED1
************************************************/

	
int main(void)
{		
	u16 led0pwmval=0;
	u8 dir=1;	
	delay_init();	    	   // 延时函数初始化	  
	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	// uart_init(115200);	   //串口初始化为 115200
	LED_Init();			       // LED端口初始化
	TIM3_PWM_Init(899,0);	 // 不分频。PWM频率=72000000/900=80Khz

	while(1)
	{
		delay_ms(10);	 
		if(dir) led0pwmval++;
		else led0pwmval--;

		if(led0pwmval>300) dir=0;
		if(led0pwmval==0) dir=1;										 
		TIM_SetCompare2(TIM3, led0pwmval);		   
	}	 
}

