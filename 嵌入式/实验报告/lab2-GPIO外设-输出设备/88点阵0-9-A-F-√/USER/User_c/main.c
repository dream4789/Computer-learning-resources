#include "stm32f10x.h"
#include "SysTick.h"
#include "dz.h"

// 3.3v - GND

int main(void)
{
	SysTick_Init();
	LED_Init();
	// delay_init();
	while(1)
	{
		led_display();
	}
}









// --------------------------------------------------------------------------
// 定义一个8x8的点阵屏数据
unsigned char matrix[8] = {0x7E,0xBD,0xDB,0xE7,0xE7,0xDB,0xBD,0x7E};
uint16_t counter = 0;// 定义定时器计数器
uint8_t position = 0;// 定义滚动位置
int main1(void)
{
	SysTick_Init();
	LED_Init();
	while(1)
	{
		// 滚动位置加1
		position++;
		// 如果滚动位置已经超出了屏幕范围，重置为0
		if(position >= 8) position = 0;
		// 更新点阵屏显示数据
		for(int i = 0; i < 8; i++)
		{
			GPIO_Write(GPIOD, matrix[i] << position);
			GPIO_SetBits(GPIOE, GPIO_Pin_5); // 设置锁存信号
			GPIO_ResetBits(GPIOE, GPIO_Pin_5);
			delay_us(100); // 等待一段时间，确保数据被稳定地写入到点阵屏上
		}
		// 延迟一段时间，控制滚动速度
		delay_ms(10);
	}
}





// --------------------------------------------------------------------------
uint8_t matrix1[8] = { 0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C }; // 显示数据
void delay_us1(uint32_t n){
	uint32_t i;
	for(i=0;i<n;i++){
		__nop();
		__nop();
	}
}
void delay_ms1(uint32_t n){
	uint32_t i,j;
	for(i=0;i<n;i++)
		for(j=0;j<8000;j++);
}
int main2(void) {
	SysTick_Init();
	LED_Init();

	while (1) {
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				/* 将数据移位并写入到GPIO中 */
				if(matrix1[i] & (1 << j)) GPIOE->BSRR = 1 << j;
				else GPIOE->BRR = 1 << j;
				if(matrix1[i + 8] & (1 << j)) GPIOD->BSRR = 1 << j;
				else GPIOD->BRR = 1 << j;
				delay_us(100);/* 等待一段时间，确保数据被稳定地写入到点阵屏上 */
			}
			/* 锁存信号 */
			GPIOE->BSRR = 1 << 8;
			GPIOD->BSRR = 1 << 8;
			delay_us1(100);
			GPIOE->BRR = 1 << 8;
			GPIOD->BRR = 1 << 8;
		}
		delay_ms1(500);    /* 延迟一段时间，控制滚动速度 */
	}
}

