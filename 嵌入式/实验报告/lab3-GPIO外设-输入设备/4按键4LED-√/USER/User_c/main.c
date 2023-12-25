#include"stm32f10x.h"
#include "key.h"

int main(void)
{
	
	LED_GPIO_Config();
	Key_GPIO_Config();
	while(1)
	{
		if(Key_Scan(GPIOE,GPIO_Pin_1) == KEY_ON)
		{
			GPIO_WriteBit(GPIOC,GPIO_Pin_0,
			(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_0))));
		}
		
		if(Key_Scan(GPIOE,GPIO_Pin_2) == KEY_ON)
		{
			GPIO_WriteBit(GPIOC,GPIO_Pin_1,
			(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_1))));
		}
		
		if(Key_Scan(GPIOE,GPIO_Pin_3) == KEY_ON)
		{
			GPIO_WriteBit(GPIOC,GPIO_Pin_2,
			(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_2))));
		}
		
		if(Key_Scan(GPIOE,GPIO_Pin_4) == KEY_ON)
		{
			GPIO_WriteBit(GPIOC,GPIO_Pin_3,
			(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_3))));
		}
	
	}
}
