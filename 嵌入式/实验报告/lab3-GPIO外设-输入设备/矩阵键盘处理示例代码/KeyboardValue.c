#include "stm32f10x.h"
#include "KeyBoard.h"
#include "SysTick.h"

#define COL_ALL GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
#define ROW_ALL GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7

void KeyBoard_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
	GPIO_InitStructure.GPIO_Pin = COL_ALL;//pa0--pa3��Ӧ�������ĸ�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//��Ϊ�������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = ROW_ALL;//pa4--pa7��Ӧ���ϵ����ĸ�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��Ϊ��������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	GPIO_SetBits(GPIOA, COL_ALL);//����ȫ����1
}

/*
   4*4�ľ������
   ���ϵ��£�������
   ��������Ϊ0-3,
             4-7��
             8,9,A,B��
             C,D,E,F
*/
s16 Read_KeyValue(void)
{
	s16 KeyValue=-1;//�ް���
	if((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f)//����ȫ����1����������ֵ������ȫ0��������м�����
	{
		Delay_ms(2);//�������
		if((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f)//��ʱ�ȴ�������������ֵ��Ȼ��ȫ����0����ȷ���м�����
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_0);//����1��������1,��鰴���Ƿ�λ�ڵ�1��
			GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);//��2��3��4��������0
			switch(GPIO_ReadInputData(GPIOA)&0xff)//��ȡPA�ڵ�8λPA[7..4]PA[3..0]
			{
				case 0x11: KeyValue = 0; break;//PA[7..4]PA[3..0]=0001_0001������1�е�1��֮��İ����պ�
				case 0x21: KeyValue = 4; break;//PA[7..4]PA[3..0]=0010_0001������2�е�1��֮��İ����պ�
				case 0x41: KeyValue = 8; break;//PA[7..4]PA[3..0]=0100_0001������3�е�1��֮��İ����պ�
				case 0x81: KeyValue = 0x0C;break;//PA[7..4]PA[3..0]=1000_0001������4�е�1��֮��İ����պ�
			}
			GPIO_SetBits(GPIOA, GPIO_Pin_1);//����2��������1����鰴���Ƿ�λ�ڵ�2��
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3);//��1��3��4��������0
			switch(GPIO_ReadInputData(GPIOA)&0xff)//��ȡPA�ڵ�8λPA[7..4]PA[3..0]
			{
				case 0x12: KeyValue = 1; break;//PA[7..4]PA[3..0]=0001_0010������1�е�2��֮��İ����պ�
				case 0x22: KeyValue = 5; break;//PA[7..4]PA[3..0]=0010_0010������2�е�2��֮��İ����պ�
				case 0x42: KeyValue = 9;break;//PA[7..4]PA[3..0]=0100_0010������3�е�2��֮��İ����պ�
				case 0x82: KeyValue = 0x0D;break;//PA[7..4]PA[3..0]=1000_0010������4�е�2��֮��İ����պ�
			}
			GPIO_SetBits(GPIOA, GPIO_Pin_2);//����3��������1����鰴���Ƿ�λ�ڵ�3��
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3);
			switch(GPIO_ReadInputData(GPIOA)&0xff)
			{
				case 0x14: KeyValue = 2; break;
				case 0x24: KeyValue = 6; break;
				case 0x44: KeyValue = 0x0A;break;
				case 0x84: KeyValue = 0x0E;break;
			}
			GPIO_SetBits(GPIOA, GPIO_Pin_3);//����4��������1����鰴���Ƿ�λ�ڵ�4��
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
			switch(GPIO_ReadInputData(GPIOA)&0xff)
			{
				case 0x18: KeyValue = 3; break;
				case 0x28: KeyValue = 7; break;
				case 0x48: KeyValue = 0x0B;break;
				case 0x88: KeyValue = 0x0F;break;
			}
			GPIO_SetBits(GPIOA, COL_ALL);//ȫ��������1
			while((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f);//�ȴ������ͷ�
			return KeyValue;
		}
	}
	return -1;//û�м�����
}
