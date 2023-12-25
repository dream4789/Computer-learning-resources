#include "tim.h"
#include "led.h"

/*定时器3时基单元初始化函数
 *参数arr为自动装载值
 *参数psc为分频值
 *固定使用向上计数
 *定时时间为 T =(arr+1)*(psc+1)/72M
 *未开启定时器计数功能
*/

void myTIM_Tim3BaseInit(u16 _arr, u16 _psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimBaseStructure;//时基初始化结构体
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	/* 时钟使能 */
	TIM_DeInit(TIM3);	/* 复位定时器3 */
	TIM_InternalClockConfig(TIM3);	/* 选择内部时钟 */
	
	/* 定时器TIM3初始化 */
	TIM_TimBaseStructure.TIM_Period = _arr;  // 设置在下一个更新事件装入活动的自动重装载寄存器
	TIM_TimBaseStructure.TIM_Prescaler = _psc;  // 设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // TIM向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimBaseStructure);  // 根据指定的参数初始化TIMx的时间基数单位
	
	TIM_Cmd(TIM3,DISABLE);  // 失能TIM3
}

void myTIM_TimingItInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;//NVIC初始化结构体
	
	/* 使能更新中断，并清除更新中断标志位 */
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//使能指定的TIM3中断
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除TIMx更新中断标志
	
	/* 中断优先级NVIC设置 */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void myTIM_Tim3PWM2Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;//输出比较结构体变量
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//Timer3 定时器3部分引脚重映射
	//PB5初始化 设置该引脚为复用输出功能，输出TIM3 CH2的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化GPIO
	
	/* 初始化TIM3 Channel2 PWM 模式 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能Timer3在CCR上的定时器预装载功能
}

/* 使能定时器x的计数器 */
void myTIM_TimxStart(TIM_TypeDef* TIMx)
{
	TIM_Cmd(TIMx,ENABLE);//使能定时器3
}
