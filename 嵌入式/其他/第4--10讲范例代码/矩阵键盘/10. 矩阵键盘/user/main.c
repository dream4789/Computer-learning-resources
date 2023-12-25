#include "stm32f10x.h"
#include "KeyBoard.h"
#include "SysTick.h"
#include "NixieTubes.h"

int main()
{
	s16 kval;
		
	SysTick_Init();     //��ʼ��ϵͳʱ��
	KeyBoard_Init();    //��ʼ���������GPIOA
	NixieTubes_Init();  //ʹ��GPIOD��GPIOE���������

  while(1)
	{
		kval = Read_KeyValue();
	  NixieDisplay(kval);	
	}
	
}
