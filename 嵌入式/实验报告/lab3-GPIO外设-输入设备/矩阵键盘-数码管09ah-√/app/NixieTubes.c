 #include "stm32f10x.h"
 #include "NixieTubes.h"
 #include "SysTick.h"
 
 void NixieTubes_Init(void)
 {

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = 0xff;     // 使用Pin0--Pin7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);  // GPIOD作为控制
	GPIO_Init(GPIOE, &GPIO_InitStructure);  // GPIOE作为数据
}
 
void NixieDisplay(s16 value){
	// DP G F E D C B A
	//  0 0 1 1 1 1 1 1
	// 以上为适合共阴接法的 0 的字形码
	u16 num[16] = {0x3f, 0x06, 0x5b, 0x4f,
		             0x66, 0x6d, 0x7d, 0x07,
		             0x7f, 0x6F, 0x77, 0x7c,
	               0x39, 0x5e, 0x79, 0x71};
	s16 j;
	j=value;

	if(j>=0) {	
		// PD[7..0]对应选择从左到右的8个数码管，低电平选用，高电平禁用
    GPIOD->ODR = 0xff;    // 关闭全部显示
		
		GPIOE->ODR = ~num[j]; // 共阳接法
		// GPIOE->ODR = num[j];// 共阴接法
		
		GPIOD->ODR = 0x00;    // 选择全部管子
		Delay_ms(2);
	}
}
