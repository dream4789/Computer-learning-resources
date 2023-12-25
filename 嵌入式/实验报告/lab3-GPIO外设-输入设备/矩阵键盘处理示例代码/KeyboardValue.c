#include "stm32f10x.h"
#include "KeyBoard.h"
#include "SysTick.h"

#define COL_ALL GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
#define ROW_ALL GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7

void KeyBoard_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
	GPIO_InitStructure.GPIO_Pin = COL_ALL;//pa0--pa3对应从左到右四根列线
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//置为推挽输出模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = ROW_ALL;//pa4--pa7对应从上到下四根行线
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//置为下拉输入模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	GPIO_SetBits(GPIOA, COL_ALL);//列线全部置1
}

/*
   4*4的矩阵键盘
   从上到下，从左到右
   键号依次为0-3,
             4-7，
             8,9,A,B，
             C,D,E,F
*/
s16 Read_KeyValue(void)
{
	s16 KeyValue=-1;//无按键
	if((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f)//列线全部置1后读入的行线值不等于全0，则表明有键按下
	{
		Delay_ms(2);//软件消抖
		if((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f)//延时等待后如果读入的行值仍然不全等于0，则确认有键按下
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_0);//仅第1列列线置1,检查按键是否位于第1列
			GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);//第2、3、4列列线置0
			switch(GPIO_ReadInputData(GPIOA)&0xff)//获取PA口低8位PA[7..4]PA[3..0]
			{
				case 0x11: KeyValue = 0; break;//PA[7..4]PA[3..0]=0001_0001表明第1行第1列之间的按键闭合
				case 0x21: KeyValue = 4; break;//PA[7..4]PA[3..0]=0010_0001表明第2行第1列之间的按键闭合
				case 0x41: KeyValue = 8; break;//PA[7..4]PA[3..0]=0100_0001表明第3行第1列之间的按键闭合
				case 0x81: KeyValue = 0x0C;break;//PA[7..4]PA[3..0]=1000_0001表明第4行第1列之间的按键闭合
			}
			GPIO_SetBits(GPIOA, GPIO_Pin_1);//仅第2列列线置1，检查按键是否位于第2列
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3);//第1、3、4列列线置0
			switch(GPIO_ReadInputData(GPIOA)&0xff)//获取PA口低8位PA[7..4]PA[3..0]
			{
				case 0x12: KeyValue = 1; break;//PA[7..4]PA[3..0]=0001_0010表明第1行第2列之间的按键闭合
				case 0x22: KeyValue = 5; break;//PA[7..4]PA[3..0]=0010_0010表明第2行第2列之间的按键闭合
				case 0x42: KeyValue = 9;break;//PA[7..4]PA[3..0]=0100_0010表明第3行第2列之间的按键闭合
				case 0x82: KeyValue = 0x0D;break;//PA[7..4]PA[3..0]=1000_0010表明第4行第2列之间的按键闭合
			}
			GPIO_SetBits(GPIOA, GPIO_Pin_2);//仅第3列列线置1，检查按键是否位于第3列
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3);
			switch(GPIO_ReadInputData(GPIOA)&0xff)
			{
				case 0x14: KeyValue = 2; break;
				case 0x24: KeyValue = 6; break;
				case 0x44: KeyValue = 0x0A;break;
				case 0x84: KeyValue = 0x0E;break;
			}
			GPIO_SetBits(GPIOA, GPIO_Pin_3);//仅第4列列线置1，检查按键是否位于第4列
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
			switch(GPIO_ReadInputData(GPIOA)&0xff)
			{
				case 0x18: KeyValue = 3; break;
				case 0x28: KeyValue = 7; break;
				case 0x48: KeyValue = 0x0B;break;
				case 0x88: KeyValue = 0x0F;break;
			}
			GPIO_SetBits(GPIOA, COL_ALL);//全部列线置1
			while((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f);//等待按键释放
			return KeyValue;
		}
	}
	return -1;//没有键按下
}
