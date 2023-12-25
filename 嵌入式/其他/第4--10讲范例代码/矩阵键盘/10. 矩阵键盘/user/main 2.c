#include "stm32f10x.h"
#include "KeyBoard.h"
#include "SysTick.h"
#include "NixieTubes.h"

int main()
{
	u16 kval;
	u16 kdis;
	SystemInit();
	SysTick_Init();     //初始化系统时钟
	KeyBoard_Init();    //初始化矩阵键盘GPIOA
	NixieTubes_Init();  //使用GPIOD、GPIOE控制

  kdis=0;                //矩阵键盘未输入显示为0
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
