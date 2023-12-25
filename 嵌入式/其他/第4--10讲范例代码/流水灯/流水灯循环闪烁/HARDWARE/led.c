#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//PA0--PA7对应控制LED1--LED8
////////////////////////////////////////////////////////////////////////////////// 	   
void LED_Init(void)
{
 	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//开启PA口对应时钟	
	//使用PA0--PA7	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出模式		
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出频率50Mhz		 
	 GPIO_Init(GPIOA, &GPIO_InitStructure);	//根据制定参数初始化PA口				
}
 
