#include "sys.h"
#include "systick.h"


 
//h g f e d c b a
//1 1 0 0 0 0 0 0 -- 共阳方式显示0   
// 共阳 
u8 seg_tab[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; 

// 共阴
// u8 seg_tab[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};


//0x7f=01111111此时仅最左边的管子被激活
u8 pos[8]={0x7f, 0xBF, 0xDF, 0xEF, 0xf7, 0xFB, 0xFD, 0xFe};

void LED_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// 使能PA口时钟

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOA, &GPIO_InitStructure);				
	 GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);


	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);// 使能PE口时钟

	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;// KEY0-KEY2
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
 	 GPIO_Init(GPIOE, &GPIO_InitStructure);
	 GPIO_SetBits(GPIOE,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}

int main1(void){	
	int i;
	SysTick_Init();	 // 延时初始化函数
	LED_Init();		   // 数码管初始化函数
	GPIOE->ODR=0xff; // 数码管全熄灭
	
	while(1){
		for(i=0;i<8;i++){
			GPIOA->ODR = seg_tab[i]; // 字形控制
			GPIOE->ODR = pos[i];     // 位置控制
			Delay_us(10);
		}
	}
}

int main(void){    
    int i = 0;
    SysTick_Init();
    LED_Init();
    GPIOE->ODR=0xff;
    
    while(1){
			GPIOA->ODR = seg_tab[i];
			GPIOE->ODR = pos[i];
			i++;
			if(i>=8) i=0;
			Delay_us(1000);
    }
}

