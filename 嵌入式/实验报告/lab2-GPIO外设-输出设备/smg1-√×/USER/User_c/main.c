#include"stm32f10x.h"
int main(void)
{
	// u8 i;
	int i;
	u8 one,ten;
	u8 data;
	long time;
	GPIO_InitTypeDef GPIO_InitStrc;
	// 共阳
	u8 num[7] = {0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0x82};

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);
	//PA.0-PA.7段选
	GPIO_InitStrc.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStrc.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStrc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStrc);
	//PB.0 PB.1位选
	GPIO_InitStrc.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStrc.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStrc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStrc);
	data = 0;
	
	while(1)
	{
		one = data%10;  //取个位
		ten = data/10;  //取?位
		if(data<10){
			for(time=0; time<10000; time++){
				GPIO_SetBits(GPIOE, GPIO_Pin_1);
				GPIO_ResetBits(GPIOE, GPIO_Pin_0);
				GPIO_Write(GPIOA, num[one]);
				for(i=0; i<1000; i++);
			}
		}
		if((data>=10)&&(data<=99)){
			for(time=0;time<10000;time++){
				GPIO_SetBits(GPIOE, GPIO_Pin_1);
				GPIO_ResetBits(GPIOE, GPIO_Pin_0);
				GPIO_Write(GPIOA, num[one]);
				for(i=0; i<100; i++);

				GPIO_SetBits(GPIOE, GPIO_Pin_0);
				GPIO_ResetBits(GPIOE, GPIO_Pin_1);
				GPIO_Write(GPIOA, num[ten]);
				for(i=0; i<100; i++);
			}
		}

		data++;
		if(data>99) data=0;
	}
}

