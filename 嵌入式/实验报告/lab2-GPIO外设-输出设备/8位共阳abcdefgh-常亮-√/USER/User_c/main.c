#include "stm32f10x.h"
#include "smg.h"
#include "SysTick.h"


int main(void) {
	led_duan_init();// 数码管段初始化
	led_wei_init();	// 数码管位初始化
	SysTick_Init(); // 定时器初始化	
	delay_init();   // 延时初始化
	
	int a[8]={GPIO_Pin_0 , GPIO_Pin_1 , GPIO_Pin_2 , GPIO_Pin_3 , GPIO_Pin_4 , GPIO_Pin_5 , GPIO_Pin_6 , GPIO_Pin_7};
	
	while(1){
		for(int i = 0 ; i < 8 ; i++){
			Display(i);   // 将A的译码写到GPIOA的端口
			GPIO_ResetBits(GPIOE, a[i]); //亮，位置控制
			// delay_us(100);   // 越大，越像流水灯
			delay_ms(1);

			GPIO_SetBits(GPIOE, a[i]);   // 灭
			// delay_us(100);   // 越大，越像流水灯，但越暗
			delay_ms(1); 

			// 想要常亮，两个时间要小
			// 但时间小到一定程度后 就没有区别了（差不多是1ms）
		}
	}
}



