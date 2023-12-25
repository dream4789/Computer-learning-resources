#include "SysTick.h"


static __IO u32 TimingDelay;

void SysTick_Init(void)
{
	if(SysTick_Config(SystemCoreClock/1000))
	{
		while(1);
	}
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
}

void Delay_ms(__IO uint32_t nTime)
{
	TimingDelay = nTime;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;//启动SysTick定时器
	while(TimingDelay!=0);
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭SysTick定时器
}

void SysTick_Handler(void)
{
		TimingDelay--; //每次中断，TimingDelay减1
	//减到0之后，在延时函数中判断(退出while循环)，定时器关闭
}

