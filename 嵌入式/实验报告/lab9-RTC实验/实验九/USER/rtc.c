/*******************************************************************************
 * 文件名  ：rtc.c
 * 描述    ：利用STM32的RTC实现一个简易的电子时钟。
 *           显示格式为 Time: XX : XX : XX(时：分：秒)。         
 * 实验平台：野火STM32开发板
 * 硬件连接：-------------------
 *          |                   |
 *          | VBAT引脚需外接电池|
 *          |                   |
 *           -----------------
 * 库版本  ：ST3.5.0
 * 作者    ：保留 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "rtc.h"
#include "stdio.h"

uint8_t a[8];
int b[8]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7};//数码管位选端口


/* 秒中断标志，进入秒中断时置1，当时间被刷新之后清0 */
__IO uint32_t TimeDisplay;	

void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
}

/*
 * 函数名：NVIC_Configuration
 * 描述  ：配置RTC秒中断的主中断优先级为1，次优先级为0
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
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
 * 函数名：RTC_Configuration
 * 描述  ：配置RTC
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void RTC_Configuration(void)
{
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);//启动电源控制和后备区域时钟
	
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);//允许后备区域的访问
	
	/* Reset Backup Domain */
	BKP_DeInit();//将备份寄存器恢复为默认值
	
	/* Enable LSE */
	RCC_LSEConfig(RCC_LSE_ON);//允许LSE
	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)//检查RCC标志，等待LSE就绪
	{}
	
	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//选择LSE作为RTC时钟
	
	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);//允许RTC时钟
	
	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();//等待RTC时钟与ASP时钟同步
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成
	
	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);//允许RCT秒中断
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成
	
	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */ //设置RTC预分频值
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成
}


/*
 * 函数名：Time_Regulate
 * 描述  ：返回用户在超级终端中输入的时间值，并将值储存在
 *         RTC 计数寄存器中。
 * 输入  ：无
 * 输出  ：用户在超级终端中输入的时间值，单位为 s
 * 调用  ：内部调用
 */
uint32_t Time_Regulate(void)
{
	uint32_t Tmp_HH = 0xFF, Tmp_MM = 0xFF, Tmp_SS = 0xFF;//时-分-秒
	
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
 * 函数名：Time_Adjust
 * 描述  ：时间调节
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Time_Adjust(void)
{
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成
	/* Change the current time */
	RTC_SetCounter(Time_Regulate());//设置RTC计数器起始值
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成
}


/*
 * 函数名：Time_Display
 * 描述  ：显示当前时间值
 * 输入  ：-TimeVar RTC计数值，单位为 s
 * 输出  ：无
 * 调用  ：内部调用
 */	
void Time_Display(uint32_t TimeVar)
{
	uint32_t THH = 0, TMM = 0, TSS = 0;
	int i,j;
	/* Compute  hours */
	THH = TimeVar / 3600;        	//时
	a[0]=THH/10;
	a[1]=THH%10;
	a[2]=10;
	/* Compute minutes */
	TMM = (TimeVar % 3600) / 60;	//分
	a[3]=TMM/10;
	a[4]=TMM%10;
	a[5]=10;
	/* Compute seconds */
	TSS = (TimeVar % 3600) % 60;	//秒
	a[6]=TSS/10;
	a[7]=TSS%10;
	
	//printf(" Time: %0.2d:%0.2d:%0.2d\r", THH, TMM, TSS);	
	
	if(TSS==0&&TMM==0)
	{
		GPIO_ResetBits(GPIOF,GPIO_Pin_All);//输出0，打开蜂鸣器输出
		Delay(0x3FFFFF);
		GPIO_SetBits(GPIOF,GPIO_Pin_All);//输出1，关闭蜂鸣器输出
	}
	
	for(j=0;j<1100;j++)
	{
		for(i=0;i<8;i++)
		{
			Display(a[i]);//写入段选端口
			GPIO_ResetBits(GPIOD,b[i]);//第i位亮
			Delay(0x0000FF);//短暂延时
			GPIO_SetBits(GPIOD,b[i]);//第i位灭	
		}
		i=0;
	}
	
	//printf(" Time: %0.2d:%0.2d:%0.2d\r", THH, TMM, TSS);
}


/*
 * 函数名：Time_Show
 * 描述  ：在超级终端中显示当前时间值
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
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
			Time_Display(RTC_GetCounter());//获取RTC计数器的值
			TimeDisplay = 0;
		}
	}
}


/*
 * 函数名：USART_Scanf
 * 描述  ：串口从超级终端中获取数值
 * 输入  ：- value 用户在超级终端中输入的数值
 * 输出  ：无
 * 调用  ：内部调用
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
		// 从串口终端里面输进去的数是ASCII码值
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
