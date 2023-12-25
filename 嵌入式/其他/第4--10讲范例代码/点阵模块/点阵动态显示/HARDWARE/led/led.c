#include "led.h"
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//?????????,??????,??????????
//ALIENTEK??STM32???
//LED????	   
//????@ALIENTEK
//????:www.openedv.com
//????:2012/9/2
//??:V1.0
//????,?????
//Copyright(C) ????????????? 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

u8 seg_tab[88] = {0xff, 0x99, 0x66, 0x7e, 0x7e, 0xbd, 0xdb, 0xe7,      //心
									//0xe7, 0xdb, 0x99, 0x99, 0x99, 0x99, 0xdb, 0xe7,      //0
	                0xe7,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xe7,//0
									0xe7, 0xc7, 0xa7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,      //1
									0xc3, 0x99, 0x99, 0xf1, 0xe3, 0xc7, 0x8f, 0x81,      //2
									0xc3, 0x99, 0xf9, 0xe3, 0xe3, 0xf9, 0x99, 0xc3,      //3
									0xf3, 0xe3, 0xc3, 0x93, 0xb3, 0x81, 0xf3, 0xf3,      //4
									0xc3, 0x9f, 0x9f, 0x83, 0xc1, 0xf9, 0xf9, 0xc3,      //5
									0xc3, 0x9f, 0x9f, 0x83, 0x81, 0x99, 0x99, 0xc3,      //6
									0x81, 0x81, 0xf9, 0xf1, 0xe3, 0xe7, 0xe7, 0xe7,      //7
									0xc3, 0x99, 0x99, 0x81, 0x81, 0x99, 0x99, 0xc3,      //8
									0xc3, 0x99, 0x99, 0x81, 0xc1, 0xf9, 0xf9, 0xc3       //9					
};

void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOA, &GPIO_InitStructure);				
	 GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);


	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//??PORTA,PORTE??

	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//KEY0-KEY2
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //???????
 	 GPIO_Init(GPIOE, &GPIO_InitStructure);//???GPIOE2,3,4
	 GPIO_ResetBits(GPIOE,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

}

void Display(u8 index)	//从字模数组中取出数据，处理某一行的8列
{
	DX0 = seg_tab[index]&0x01;//pa处理列值
	DX1 = (seg_tab[index]>>1)&0x01;
	DX2 = (seg_tab[index]>>2)&0x01;
	DX3 = (seg_tab[index]>>3)&0x01;
	DX4 = (seg_tab[index]>>4)&0x01;
	DX5 = (seg_tab[index]>>5)&0x01;
	DX6 = (seg_tab[index]>>6)&0x01;
	DX7 = (seg_tab[index]>>7)&0x01;
	

}
void xin(void)
{
				Display(0);
    		D0=0;
				delay_ms(1);
				D0=1;
		
				Display(1);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(2);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(3);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(4);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(5);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(6);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(7);
    		D7=0;
				delay_ms(1);
				D7=1;
}

void zero(void)
{
				Display(8);
    		D0=0;//pe处理行值，先擦
				delay_ms(1);
				D0=1;//pe处理行值，后显示
		
				Display(9);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(10);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(11);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(12);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(13);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(14);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(15);
    		D7=0;
				delay_ms(1);
				D7=1;
}
void one(void)
{
				Display(16);
    		D0=0;
				delay_ms(1);
				D0=1;
		
				Display(17);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(18);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(19);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(20);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(21);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(22);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(23);
    		D7=0;
				delay_ms(1);
				D7=1;
}
void two(void)
{
				Display(24);
    		D0=0;
				delay_ms(1);
				D0=1;
		
				Display(25);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(26);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(27);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(28);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(29);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(30);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(31);
    		D7=0;
				delay_ms(1);
				D7=1;
}
void three(void)
{
				Display(32);
    		D0=0;
				delay_ms(1);
				D0=1;
		
				Display(33);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(34);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(35);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(36);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(37);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(38);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(39);
    		D7=0;
				delay_ms(1);
				D7=1;
}
void four(void)
{
				Display(40);
    		D0=0;
				delay_ms(1);
				D0=1;
		
				Display(41);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(42);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(43);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(44);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(45);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(46);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(47);
    		D7=0;
				delay_ms(1);
				D7=1;
}
void five(void)
{
				Display(48);
    		D0=0;
				delay_ms(1);
				D0=1;
		
				Display(49);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(50);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(51);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(52);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(53);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(54);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(55);
    		D7=0;
				delay_ms(1);
				D7=1;
}
void six(void)
{
				Display(56);
    		D0=0;
				delay_ms(1);
				D0=1;
		
				Display(57);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(58);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(59);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(60);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(61);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(62);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(63);
    		D7=0;
				delay_ms(1);
				D7=1;
}
void seven(void)
{
				Display(64);
    		D0=0;
				delay_ms(1);
				D0=1;
		
				Display(65);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(66);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(67);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(68);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(69);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(70);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(71);
    		D7=0;
				delay_ms(1);
				D7=1;
}
void eight(void)
{
				Display(72);
    		D0=0;
				delay_ms(1);
				D0=1;
		
				Display(73);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(74);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(75);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(76);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(77);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(78);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(79);
    		D7=0;
				delay_ms(1);
				D7=1;
}
void nine(void)
{
				Display(80);
    		D0=0;
				delay_ms(1);
				D0=1;
		
				Display(81);
    		D1=0;
				delay_ms(1);
				D1=1;
		
				Display(82);
    		D2=0;
				delay_ms(1);
				D2=1;
		
			  Display(83);
    		D3=0;
				delay_ms(1);
				D3=1;
		
				Display(84);
    		D4=0;
				delay_ms(1);
				D4=1;
				
				Display(85);
    		D5=0;
				delay_ms(1);
				D5=1;
				
				Display(86);
    		D6=0;
				delay_ms(1);
				D6=1;
				
				Display(87);
    		D7=0;
				delay_ms(1);
				D7=1;
}
