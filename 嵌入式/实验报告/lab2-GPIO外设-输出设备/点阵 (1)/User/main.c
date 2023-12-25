
#include "stm32f10x.h"
#include "bsp_usart.h"

#include "leddz.h"

#define speed 10000
u8 a[88] = {
			0x00, 0x00, 0x3e, 0x41, 0x41, 0x41, 0x3e, 0x00,//0
			0x00, 0x00, 0x00, 0x21, 0x7f, 0x01, 0x00, 0x00,//1
			0x00, 0x00, 0x27, 0x45, 0x45, 0x45, 0x39, 0x00,//2
			0x00, 0x00, 0x22, 0x49, 0x49, 0x49, 0x36, 0x00,//3
			0x00, 0x00, 0x0c, 0x14, 0x24, 0x7f, 0x04, 0x00,//4
			0x00, 0x00, 0x72, 0x51, 0x51, 0x51, 0x4e, 0x00,//5
			0x00, 0x00, 0x3e, 0x49, 0x49, 0x49, 0x26, 0x00,//6
			0x00, 0x00, 0x40, 0x40, 0x40, 0x4f, 0x70, 0x00,//7
			0x00, 0x00, 0x36, 0x49, 0x49, 0x49, 0x36, 0x00,//8
			0x00, 0x00, 0x32, 0x49, 0x49, 0x49, 0x3e, 0x00,//9
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00// 如果需要移动显示的话，就需加上这行，数组a[80]改成a[88]											
};
u8 b[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

int main(void) {
	u8 i = 0;
	u8 j = 0;
	u8 n = 0;
	int sum = 0;

	USART_Config();	/*初始化USART 配置模式为 115200 8-N-1，中断接收*/
	LED_DZ_Init();
	Usart_SendString(DEBUG_USARTx, "这是一个点阵屏显示实验\n");	/* 发送一个字符串 */

	while (1) {
		//	开场逐个扫描，用于判断所有LED都是好的
		GPIO_SetBits(GPIOA, 1 << i);
		GPIO_ResetBits(GPIOB, 3 << j);

		GPIO_ResetBits(GPIOA, 1 << i);
		GPIO_SetBits(GPIOB, 3 << j);
//	**********************************************************
		if (n == 0) { // 判断开场扫描是否完成
			sum++; // 扫描次数
			if (sum > 6 * speed) { // 调节跳转速度
				sum = 0;
				j++;
				if (j > 8) {
					j = 0;
					i++;
					if (i > 8) {
						i = 0;
						n = 1;   // 判断用何种方式显示数字
					}
				}
			}
		}
		if (n == 1) {
			for (i = 0; i < 8; i++) {
				GPIO_SetBits(GPIOA, a[i + j]); //PA输出高电平
				GPIO_ResetBits(GPIOB, b[i]);  //PB输出低电平
				GPIO_ResetBits(GPIOA, a[i + j]);  //PA输出低电平
				GPIO_SetBits(GPIOB, b[i]); //PA输出低电平
			}
			sum++;
			if (sum > 8 * speed) { // 调节跳转速度	
				sum = 0;
				j += 8;  //跳到下一个数字
				if (j > 80) j = 0;  //盘点是否显示完最后一个数字
			}
		}
//*******************************************************************************			
//移动显示数字的方式	
		if (n == 2) {
			for (i = 0; i < 8; i++) {
				GPIO_SetBits(GPIOA, a[i + j]);   //PA输出高电平
				GPIO_ResetBits(GPIOB, b[i]);     //PB输出低电平
				GPIO_ResetBits(GPIOA, a[i + j]); //PA输出低电平
				GPIO_SetBits(GPIOB, b[i]);       //PA输出低电平
			}
			sum++;
			if (sum > 1.5 * speed) {
				sum = 0;
				j++;
				if (j > 80) j = 0;
			}
		}

/****************************************************************************************************/
/*                        不断定义IO口扫描的方式来实现，静态扫描                                      */
/****************************************************************************************************/
//		GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_7);	//A0和A7管脚输出高电平
//		GPIO_ResetBits(GPIOB,GPIO_Pin_0);						//B0管脚输出低电平 是的回路导通
//		GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_7);//A0和A7管脚输出高电平
//		GPIO_SetBits(GPIOB,GPIO_Pin_0);							//B0管脚输出低电平 是的回路导通
//		
//		GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_6);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_6);
//		GPIO_SetBits(GPIOB,GPIO_Pin_1);
//		
//		GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_5);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_5);
//		GPIO_SetBits(GPIOB,GPIO_Pin_2);
//		
//		GPIO_SetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4);
//		GPIO_SetBits(GPIOB,GPIO_Pin_3);
//		
//		GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_3);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_4);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_3);
//		GPIO_SetBits(GPIOB,GPIO_Pin_4);
//		
//		GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_2);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_2);
//		GPIO_SetBits(GPIOB,GPIO_Pin_5);
//		
//		GPIO_SetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_1);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_1);
//		GPIO_SetBits(GPIOB,GPIO_Pin_6);
//		
//		GPIO_SetBits(GPIOA,GPIO_Pin_7|GPIO_Pin_0);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_7|GPIO_Pin_0);
//		GPIO_SetBits(GPIOB,GPIO_Pin_7);

	}
}
/*********************************************END OF FILE**********************/
