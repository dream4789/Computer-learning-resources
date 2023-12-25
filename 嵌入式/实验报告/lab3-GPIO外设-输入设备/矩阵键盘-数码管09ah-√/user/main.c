#include "stm32f10x.h"
#include "KeyBoard.h"
#include "SysTick.h"
#include "NixieTubes.h"

int main()
{
	s16 kval;
		
	SysTick_Init();     //初始化系统时钟
	KeyBoard_Init();    //初始化矩阵键盘GPIOA
	NixieTubes_Init();  //使用GPIOD、GPIOE控制数码管

  while(1)
	{
		kval = Read_KeyValue();
	  NixieDisplay(kval);	
	}
}
