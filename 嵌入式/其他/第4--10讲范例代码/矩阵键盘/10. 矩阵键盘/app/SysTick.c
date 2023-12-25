#include "stm32f10x.h"
#include "SysTick.h"
static __IO u32 TimingDelay;
void SysTick_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	if(SysTick_Config(SystemCoreClock /1000))
	{
		while(1);
	}

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void Delay_ms(__IO u32 nTime)
{
  TimingDelay = nTime;	
  SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
  }
}
