/**********************************************************************
 * ????:    ---------------
 *          |   PA0 - A   |
 *          |   PA1 - B   |
 *          |   PA2 - C   |
 *          |   PA3 - D   |
 *          |   PA4 - E   |
 *          |   PA5 - F   |
 *          |   PA6 - G   |
 *          |   PA7 - DP  |
 *          ---------------
*********************************************************************/

#include "smg.h"
#include "delay.h"

u8 const smgs_data[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};


void SMG_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);	 // turn off all led
}


void SMG_Display(void) {
	u8 i;
	for(i=0;i<16;i++){
		GPIO_Write(GPIOA,smgs_data[i]);
		delay_ms(1000);    		
	}
}

void Display_N(u8 N) {
	GPIO_Write(GPIOA,smgs_data[N]);   		
}
