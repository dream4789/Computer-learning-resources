#include "stm32f10x.h"
#include "led.h"
#include "SysTick.h"
#include "tim.h"

/*实现PB5引脚的PWM输出
 *软件调试使用逻辑分析仪查看输出波形图，CCR在 -898之间
 *硬件实验，PB5连接LED灯，实现呼吸灯效果，CRR在0-300之间变化
*/

int main(void)
{
	u16 pwmval = 0;//给CCR赋值-
	
	SysTick_Init();//系统延时函数初始化
	myLED2_Init();
	Key_GPIO_Config();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2抢占优先级
	myTIM_Tim3BaseInit(600,0);//时基单元初始化，arr=899,psc=0
	myTIM_Tim3PWM2Init();//定时器3通道2PWM初始化
	myTIM_TimxStart(TIM3);//开启定时器3
		
	while (1)
	{
		// if(Key_Scan(GPIOE, GPIO_Pin_1) == KEY_ON) pwmval = 500;
		// if(Key_Scan(GPIOE, GPIO_Pin_2) == KEY_ON) pwmval = 100;
		
		/*设置整CCR的值*/
		// TIM_SetCompare2(TIM3,pwmval);//将PWM的值不断赋给CCR，实现调整占空比的目的
		
		for(int i=1;i<=500;i++){
			Delay_ms(4);
			TIM_SetCompare2(TIM3, i);//将PWM的值不断赋给CCR，实现调整占空比的目的
		}
		
		for(int i=500;i>=1;i--){
			Delay_ms(4);
			TIM_SetCompare2(TIM3, i);//将PWM的值不断赋给CCR，实现调整占空比的目的
		}
	}
	
}
