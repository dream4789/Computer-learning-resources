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
	 MyDelay(0x7fffff);//软件延时
	
	LED_Init();		  	//PA0--PA7对应控制LED1--LED8，PA口初始化为推挽式输出
	while(1)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);//对于共阳接法，PA0输出0代表点亮LED1
		GPIO_SetBits(GPIOA, GPIO_Pin_1);//对于共阳接法，PA1输出1代表熄灭LED2
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
		
		MyDelay(0x7fffff);//软件延时
		GPIO_SetBits(GPIOA, GPIO_Pin_0);//对于共阳接法，PA0输出1代表熄灭LED1
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);//对于共阳接法，PA1输出0代表点亮LED2
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		
		MyDelay(0x7fffff);//软件延时
	}
 }


