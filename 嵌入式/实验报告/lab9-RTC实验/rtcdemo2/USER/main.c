/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：利用STM32的RTC实现一个简易的电子时钟。在超级终端中显示时间值。
 *           显示格式为 Time: XX:XX:XX(时：分：秒)，当时间
 *           计数为：23：59：59 时将刷新为：00：00：00。         
**********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "rtc.h"


int main(void) {
    USART1_Config(); /* USART1 config */
    NVIC_Configuration();  /* 配置RTC秒中断优先级 */
    printf("\r\n This is a RTC demo...... \r\n");

    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5) {
        /* Backup data register value is not correct or not yet programmed (when
        the first time the program is executed) */
        printf("\r\nThis is a RTC demo!\r\n");
        printf("\r\n\n RTC not yet configured....");

  
        RTC_Configuration();      /* RTC Configuration */

        printf("\r\n RTC configured....");

        /* Adjust time by values entred by the user on the hyperterminal */
        Time_Adjust();

        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    } else {
        /* Check if the Power On Reset flag is set */
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET) {
            printf("\r\n\n Power On Reset occurred....");
        }
        /* Check if the Pin Reset flag is set */
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET) {
            printf("\r\n\n External Reset occurred....");
        }

        printf("\r\n No need to configure RTC....");
        /* Wait for RTC registers synchronization */
        RTC_WaitForSynchro();
        RTC_ITConfig(RTC_IT_SEC, ENABLE);  /* Enable the RTC Second */

        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();
    }

#ifdef RTCClockOutput_Enable
    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    
    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);
    
    /* Disable the Tamper Pin */
    BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
	             functionality must be disabled */
    
    /* Enable RTC Clock Output on Tamper Pin */
    BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif

    RCC_ClearFlag();    /* Clear reset flags */
    Time_Show();    /* Display time in infinite loop */

    while (1) {
				
    }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
