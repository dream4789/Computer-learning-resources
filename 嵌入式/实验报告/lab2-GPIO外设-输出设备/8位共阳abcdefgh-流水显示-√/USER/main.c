#include "stm32f10x.h"
void Delay(u32 count) {
 u32 i=0;
 for(;i<count;i++);
}	
char str[8] = "abcdefgh";
									// a    b     c     d     e     f     g     h
int showNum[8] = {0x88, 0x80, 0xc6, 0xc0, 0x86, 0x8e, 0x82, 0x89};

int main(void) {
	int i, j, k;
	// char ch;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);    
	//disable JTAG
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	// GPIO_E
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	while (1) {
		for (k = 0; k < 300; ++k) {
			for (i = 0; i < 8; ++i) {
				for (j = 0; j < 1000000; ++j) {
					GPIOA->ODR = showNum[str[i] - 'a'];
					GPIOE->ODR = 0xff - (1 << i);
				}				
			}
		}
	}
} 
