#include"stm32f10x.h"
//#include"led.h"
#include "key.h"

#define ON  0
#define OFF 1

//SysTick_Init();

int main(void)
{
	Key_GPIO_Config();
	LED_Init();
	
	int dtime = 1000000; // 0x0FFFEF
	
	while(1)
	{
		if(Key_Scan(GPIOE,GPIO_Pin_1) == KEY_ON)
		{
			LED1(ON);Delay(dtime);LED1(OFF);
			LED2(ON);Delay(dtime);LED2(OFF);
			LED3(ON);Delay(dtime);LED3(OFF);
			LED4(ON);Delay(dtime);LED4(OFF);
			LED5(ON);Delay(dtime);LED5(OFF);
			LED6(ON);Delay(dtime);LED6(OFF);
			LED7(ON);Delay(dtime);LED7(OFF);
			LED8(ON);Delay(dtime);LED8(OFF);
		}
		
		if(Key_Scan(GPIOE,GPIO_Pin_2) == KEY_ON)
		{
			LED1(ON);LED2(OFF);LED3(ON);LED4(OFF);LED5(ON);LED6(OFF);LED7(ON);LED8(OFF);Delay(dtime);
			LED1(OFF);LED2(ON);LED3(OFF);LED4(ON);LED5(OFF);LED6(ON);LED7(OFF);LED8(ON);Delay(dtime);
			LED1(ON);LED2(OFF);LED3(ON);LED4(OFF);LED5(ON);LED6(OFF);LED7(ON);LED8(OFF);Delay(dtime);
			LED1(OFF);LED2(ON);LED3(OFF);LED4(ON);LED5(OFF);LED6(ON);LED7(OFF);LED8(ON);
			LED2(OFF);LED4(OFF);LED6(OFF);LED8(OFF);
		}
		
		if(Key_Scan(GPIOE,GPIO_Pin_3) == KEY_ON)
		{
			LED1(ON);LED2(ON);Delay(dtime);LED1(OFF);LED2(OFF);
			LED5(ON);LED6(ON);Delay(dtime);LED5(OFF);LED6(OFF);
			LED3(ON);LED4(ON);Delay(dtime);LED3(OFF);LED4(OFF);	
			LED7(ON);LED8(ON);Delay(dtime);LED7(OFF);LED8(OFF);
		}
		
		if(Key_Scan(GPIOE,GPIO_Pin_4) == KEY_ON)
		{
			LED1(ON);LED8(ON);Delay(dtime);LED1(OFF);LED8(OFF);
			LED2(ON);LED7(ON);Delay(dtime);LED2(OFF);LED7(OFF);
			LED3(ON);LED6(ON);Delay(dtime);LED3(OFF);LED6(OFF);
			LED4(ON);LED5(ON);Delay(dtime);LED4(OFF);LED5(OFF);
		}
	}
}
