/*******************************************************************************
 * �ļ���  ��rtc.c
 * ����    ������STM32��RTCʵ��һ�����׵ĵ���ʱ�ӡ�
 *           ��ʾ��ʽΪ Time: XX : XX : XX(ʱ���֣���)��         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�-------------------
 *          |                   |
 *          | VBAT��������ӵ��|
 *          |                   |
 *           -----------------
 * ��汾  ��ST3.5.0
 * ����    ������ 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "rtc.h"
#include "stdio.h"

uint8_t a[8];
int b[8]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7};//�����λѡ�˿�


/* ���жϱ�־���������ж�ʱ��1����ʱ�䱻ˢ��֮����0 */
__IO uint32_t TimeDisplay;	

void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
}

/*
 * ��������NVIC_Configuration
 * ����  ������RTC���жϵ����ж����ȼ�Ϊ1�������ȼ�Ϊ0
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* Enable the RTC Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*
 * ��������RTC_Configuration
 * ����  ������RTC
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void RTC_Configuration(void)
{
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);//������Դ���ƺͺ�����ʱ��
	
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);//���������ķ���
	
	/* Reset Backup Domain */
	BKP_DeInit();//�����ݼĴ����ָ�ΪĬ��ֵ
	
	/* Enable LSE */
	RCC_LSEConfig(RCC_LSE_ON);//����LSE
	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)//���RCC��־���ȴ�LSE����
	{}
	
	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//ѡ��LSE��ΪRTCʱ��
	
	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);//����RTCʱ��
	
	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();//�ȴ�RTCʱ����ASPʱ��ͬ��
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������
	
	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);//����RCT���ж�
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������
	
	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */ //����RTCԤ��Ƶֵ
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������
}


/*
 * ��������Time_Regulate
 * ����  �������û��ڳ����ն��������ʱ��ֵ������ֵ������
 *         RTC �����Ĵ����С�
 * ����  ����
 * ���  ���û��ڳ����ն��������ʱ��ֵ����λΪ s
 * ����  ���ڲ�����
 */
uint32_t Time_Regulate(void)
{
	uint32_t Tmp_HH = 0xFF, Tmp_MM = 0xFF, Tmp_SS = 0xFF;//ʱ-��-��
	
	printf("\r\n==============Time Settings=====================================");
	printf("\r\n  Please Set Hours");
	
	while (Tmp_HH == 0xFF)
	{
		Tmp_HH = USART_Scanf(23);
	}
	printf(":  %d", Tmp_HH);
	printf("\r\n  Please Set Minutes");
	while (Tmp_MM == 0xFF)
	{
		Tmp_MM = USART_Scanf(59);
	}
	printf(":  %d", Tmp_MM);
	printf("\r\n  Please Set Seconds");
	while (Tmp_SS == 0xFF)
	{
		Tmp_SS = USART_Scanf(59);
	}
	printf(":  %d\r\n", Tmp_SS);
	
	/* Return the value to store in RTC counter register */
	return((Tmp_HH*3600 + Tmp_MM*60 + Tmp_SS));
}


/*
 * ��������Time_Adjust
 * ����  ��ʱ�����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void Time_Adjust(void)
{
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������
	/* Change the current time */
	RTC_SetCounter(Time_Regulate());//����RTC��������ʼֵ
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������
}


/*
 * ��������Time_Display
 * ����  ����ʾ��ǰʱ��ֵ
 * ����  ��-TimeVar RTC����ֵ����λΪ s
 * ���  ����
 * ����  ���ڲ�����
 */	
void Time_Display(uint32_t TimeVar)
{
	uint32_t THH = 0, TMM = 0, TSS = 0;
	int i,j;
	/* Compute  hours */
	THH = TimeVar / 3600;        	//ʱ
	a[0]=THH/10;
	a[1]=THH%10;
	a[2]=10;
	/* Compute minutes */
	TMM = (TimeVar % 3600) / 60;	//��
	a[3]=TMM/10;
	a[4]=TMM%10;
	a[5]=10;
	/* Compute seconds */
	TSS = (TimeVar % 3600) % 60;	//��
	a[6]=TSS/10;
	a[7]=TSS%10;
	
	//printf(" Time: %0.2d:%0.2d:%0.2d\r", THH, TMM, TSS);	
	
	if(TSS==0&&TMM==0)
	{
		GPIO_ResetBits(GPIOF,GPIO_Pin_All);//���0���򿪷��������
		Delay(0x3FFFFF);
		GPIO_SetBits(GPIOF,GPIO_Pin_All);//���1���رշ��������
	}
	
	for(j=0;j<1100;j++)
	{
		for(i=0;i<8;i++)
		{
			Display(a[i]);//д���ѡ�˿�
			GPIO_ResetBits(GPIOD,b[i]);//��iλ��
			Delay(0x0000FF);//������ʱ
			GPIO_SetBits(GPIOD,b[i]);//��iλ��	
		}
		i=0;
	}
	
	//printf(" Time: %0.2d:%0.2d:%0.2d\r", THH, TMM, TSS);
}


/*
 * ��������Time_Show
 * ����  ���ڳ����ն�����ʾ��ǰʱ��ֵ
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */   
void Time_Show(void)
{
	printf("\n\r");
	
	/* Infinite loop */
	while (1)
	{
		/* If 1s has paased */
		if (TimeDisplay == 1)
		{
			/* Display current time */
			Time_Display(RTC_GetCounter());//��ȡRTC��������ֵ
			TimeDisplay = 0;
		}
	}
}


/*
 * ��������USART_Scanf
 * ����  �����ڴӳ����ն��л�ȡ��ֵ
 * ����  ��- value �û��ڳ����ն����������ֵ
 * ���  ����
 * ����  ���ڲ�����
 */ 
uint8_t USART_Scanf(uint32_t value)
{
	uint32_t index = 0;
	uint32_t tmp[2] = {0, 0};
	
	while (index < 2)
	{
		/* Loop until RXNE = 1 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
		{}
		tmp[index++] = (USART_ReceiveData(USART1));
		// �Ӵ����ն��������ȥ������ASCII��ֵ
		if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
		{
			printf("\n\rPlease enter valid number between 0 and 9");
			index--;
		}
	}
	/* Calculate the Corresponding value */
	index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);
	/* Checks */
	if (index > value)
	{
		printf("\n\rPlease enter valid number between 0 and %d", value);
		return 0xFF;
	}
	return index;
}

/*****************************END OF FILE******************************/
