#include "stm32f10x.h"

void LED_Init(void)
{
	RCC->APB2ENR|=1<<3;	//¿ªÆôÊ±ÖÓ
	RCC->APB2ENR|=1<<6;
					
	GPIOB->CRL&=0xFF0FFFFF; //ÅäÖÃGPIO¶Ë¿ÚPB5
	GPIOB->CRL|=0x00300000;
	GPIOB->ODR|=1<<5;
		
	GPIOE->CRL&=0xFF0FFFFF;  //ÅäÖÃGPIO¶Ë¿ÚPE5
	GPIOE->CRL|=0x00300000;
	GPIOE->ODR|=1<<5;

}

int main()
{
	int i,j;
	LED_Init();

	while(1)
	{
		GPIOB->ODR|=1<<5;
		GPIOE->ODR|=1<<5;
		
		for(i=0;i<1000;i++)
		{
			for(j=0;j<1000;j++);
		}
		
		GPIOB->ODR&=~(1<<5);
		GPIOE->ODR&=~(1<<5);
		
		for(i=0;i<1000;i++)
		{
			for(j=0;j<1000;j++);
		}
	}
}
