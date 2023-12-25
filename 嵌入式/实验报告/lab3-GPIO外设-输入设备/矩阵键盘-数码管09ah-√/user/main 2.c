#include "stm32f10x.h"
#include "KeyBoard.h"
#include "SysTick.h"
#include "NixieTubes.h"

int main()
{
	u16 kval;
	u16 kdis;
	SystemInit();
	SysTick_Init();     //��ʼ��ϵͳʱ��
	KeyBoard_Init();    //��ʼ���������GPIOA
	NixieTubes_Init();  //ʹ��GPIOD��GPIOE����

  kdis=0;                //�������δ������ʾΪ0
	while(1)
	{
		kval = Read_KeyValue();
	  
		if(kval == 0)			
			NixieDisplay(kdis);
		else
		{
			kdis=kval;
			NixieDisplay(kdis);
		}		
	}
	
}
