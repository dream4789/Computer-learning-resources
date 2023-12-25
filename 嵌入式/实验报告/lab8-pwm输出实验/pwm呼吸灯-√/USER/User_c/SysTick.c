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
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;//����SysTick��ʱ��
	while(TimingDelay!=0);
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//�ر�SysTick��ʱ��
}

void SysTick_Handler(void)
{
		TimingDelay--; //ÿ���жϣ�TimingDelay��1
	//����0֮������ʱ�������ж�(�˳�whileѭ��)����ʱ���ر�
}

