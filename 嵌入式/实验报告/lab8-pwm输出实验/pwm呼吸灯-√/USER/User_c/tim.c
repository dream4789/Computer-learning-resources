#include "tim.h"
#include "led.h"

/*��ʱ��3ʱ����Ԫ��ʼ������
 *����arrΪ�Զ�װ��ֵ
 *����pscΪ��Ƶֵ
 *�̶�ʹ�����ϼ���
 *��ʱʱ��Ϊ T =(arr+1)*(psc+1)/72M
 *δ������ʱ����������
*/

void myTIM_Tim3BaseInit(u16 _arr, u16 _psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimBaseStructure;//ʱ����ʼ���ṹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	/* ʱ��ʹ�� */
	TIM_DeInit(TIM3);	/* ��λ��ʱ��3 */
	TIM_InternalClockConfig(TIM3);	/* ѡ���ڲ�ʱ�� */
	
	/* ��ʱ��TIM3��ʼ�� */
	TIM_TimBaseStructure.TIM_Period = _arr;  // ��������һ�������¼�װ�����Զ���װ�ؼĴ���
	TIM_TimBaseStructure.TIM_Prescaler = _psc;  // ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3,&TIM_TimBaseStructure);  // ����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_Cmd(TIM3,DISABLE);  // ʧ��TIM3
}

void myTIM_TimingItInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;//NVIC��ʼ���ṹ��
	
	/* ʹ�ܸ����жϣ�����������жϱ�־λ */
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//ʹ��ָ����TIM3�ж�
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//���TIMx�����жϱ�־
	
	/* �ж����ȼ�NVIC���� */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void myTIM_Tim3PWM2Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;//����ȽϽṹ�����
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//Timer3 ��ʱ��3����������ӳ��
	//PB5��ʼ�� ���ø�����Ϊ����������ܣ����TIM3 CH2��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//��ʼ��GPIO
	
	/* ��ʼ��TIM3 Channel2 PWM ģʽ */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//ʹ��Timer3��CCR�ϵĶ�ʱ��Ԥװ�ع���
}

/* ʹ�ܶ�ʱ��x�ļ����� */
void myTIM_TimxStart(TIM_TypeDef* TIMx)
{
	TIM_Cmd(TIMx,ENABLE);//ʹ�ܶ�ʱ��3
}
