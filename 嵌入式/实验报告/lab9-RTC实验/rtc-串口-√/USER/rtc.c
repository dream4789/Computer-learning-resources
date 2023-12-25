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

/* 秒中断标志，进入秒中断时置1，当时间被刷新之后清0 */
__IO uint32_t
TimeDisplay;

/*
 * 函数名：NVIC_Configuration
 * 描述  ：配置RTC秒中断的主中断优先级为1，次优先级为0
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void NVIC_Configuration(void) {
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
void RTC_Configuration(void) {
    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset Backup Domain */
    BKP_DeInit();

    /* Enable LSE */
    RCC_LSEConfig(RCC_LSE_ON);
    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {}

    /* Select LSE as RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

    /* Enable RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Set RTC prescaler: set RTC period to 1sec */
    RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}


/*
 * 函数名：Time_Regulate
 * 描述  ：返回用户在超级终端中输入的时间值，并将值储存在
 *         RTC 计数寄存器中。
 * 输入  ：无
 * 输出  ：用户在超级终端中输入的时间值，单位为 s
 * 调用  ：内部调用
 */
uint32_t Time_Regulate(void) {
    uint32_t Tmp_HH = 0xFF, Tmp_MM = 0xFF, Tmp_SS = 0xFF;

    printf("\r\n=================================================================================");
    printf("\r\n================================= Time Settings =================================");
    printf("\r\n=================================================================================");
    printf("\r\n  Please Set Hours: ");

    while (Tmp_HH == 0xFF) {
        Tmp_HH = USART_Scanf(23);
    }
    printf(":  %d", Tmp_HH);
    printf("\r\n  Please Set Minutes: ");
    while (Tmp_MM == 0xFF) {
        Tmp_MM = USART_Scanf(59);
    }
    printf(":  %d", Tmp_MM);
    printf("\r\n  Please Set Seconds: ");
    while (Tmp_SS == 0xFF) {
        Tmp_SS = USART_Scanf(59);
    }
    printf(":  %d", Tmp_SS);

    /* Return the value to store in RTC counter register */
    return ((Tmp_HH * 3600 + Tmp_MM * 60 + Tmp_SS));
}


/*
 * 函数名：Time_Adjust
 * 描述  ：时间调节
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Time_Adjust(void) {
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Change the current time */
    RTC_SetCounter(Time_Regulate());
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}


/*
 * 函数名：Time_Display
 * 描述  ：显示当前时间值
 * 输入  ：-TimeVar RTC计数值，单位为 s
 * 输出  ：无
 * 调用  ：内部调用
 */
void Time_Display(uint32_t TimeVar) {
    uint32_t THH = 0, TMM = 0, TSS = 0;

    /* Compute  hours */
    THH = TimeVar / 3600;
    /* Compute minutes */
    TMM = (TimeVar % 3600) / 60;
    /* Compute seconds */
    TSS = (TimeVar % 3600) % 60;

    printf("\n Time: %0.2d:%0.2d:%0.2d\r\n", THH, TMM, TSS);
}


/*
 * 函数名：Time_Show
 * 描述  ：在超级终端中显示当前时间值
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Time_Show(void) {
    printf("\n\r");

    /* Infinite loop */
    while (1) {
        /* If 1s has paased */
        if (TimeDisplay == 1) {
            /* Display current time */
            Time_Display(RTC_GetCounter());
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
uint8_t USART_Scanf(uint32_t value) {
    uint32_t index = 0;
    uint32_t tmp[2] = {0, 0};

    // 循环读取两位数字并进行校验
    while (index < 2) {
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) {}        // 等待串口接收到数据
        tmp[index++] = (USART_ReceiveData(USART1));        // 读取接收缓冲区中的数据，注意此时获取到的是ASCII码值
				// printf("\n--< %d >--\n", tmp[index - 1]);
        // 校验输入是否为数字
        //if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39)) { // 如果输入不是数字则提示重新输入
        //   printf("\n\r Please enter valid number between 0 and 9: < %d >< %d >< %d >", tmp[index - 1], tmp[0], tmp[1]);
        //   index--;
        //}
				if ((tmp[index - 1] < 1) || (tmp[index - 1] > 60)) { // 如果输入不是数字则提示重新输入
           printf("\n\r Please enter valid number between 0 and 9 < %d >==< %d >==< %d >\n",tmp[index - 1], tmp[0], tmp[1]);
					 // printf("\n\r Please enter valid number between 0 and 9");
           index--;
        }
				
    }
    index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);    // 计算输入的数字对应的十进制整数
		
		// printf("\n\r< %d >\n", index);

    // 进行额外校验，确保输入的数字在有效范围内
    if (index > value) {
        // 如果输入数字超出范围则提示重新输入
        printf("\n\rPlease enter valid number between 0 and %d \n", value);
        return 0xFF;
    }
    return index;    // 返回输入数字对应的十进制整数
}


/*****************************END OF FILE******************************/
