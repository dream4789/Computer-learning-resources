#include "stm32f10x.h"
#include "led.h"
#include "SysTick.h"
#include "tim.h"

/*ʵ��PB5���ŵ�PWM���
 *�������ʹ���߼������ǲ鿴�������ͼ��CCR�� -898֮��
 *Ӳ��ʵ�飬PB5����LED�ƣ�ʵ�ֺ�����Ч����CRR��0-300֮��仯
*/

int main(void)
{
	u16 pwmval = 0;//��CCR��ֵ-
	
	SysTick_Init();//ϵͳ��ʱ������ʼ��
	myLED2_Init();
	Key_GPIO_Config();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2:2��ռ���ȼ�
	myTIM_Tim3BaseInit(600,0);//ʱ����Ԫ��ʼ����arr=899,psc=0
	myTIM_Tim3PWM2Init();//��ʱ��3ͨ��2PWM��ʼ��
	myTIM_TimxStart(TIM3);//������ʱ��3
		
	while (1)
	{
		// if(Key_Scan(GPIOE, GPIO_Pin_1) == KEY_ON) pwmval = 500;
		// if(Key_Scan(GPIOE, GPIO_Pin_2) == KEY_ON) pwmval = 100;
		
		/*������CCR��ֵ*/
		// TIM_SetCompare2(TIM3,pwmval);//��PWM��ֵ���ϸ���CCR��ʵ�ֵ���ռ�ձȵ�Ŀ��
		
		for(int i=1;i<=500;i++){
			Delay_ms(4);
			TIM_SetCompare2(TIM3, i);//��PWM��ֵ���ϸ���CCR��ʵ�ֵ���ռ�ձȵ�Ŀ��
		}
		
		for(int i=500;i>=1;i--){
			Delay_ms(4);
			TIM_SetCompare2(TIM3, i);//��PWM��ֵ���ϸ���CCR��ʵ�ֵ���ռ�ձȵ�Ŀ��
		}
	}
	
}
