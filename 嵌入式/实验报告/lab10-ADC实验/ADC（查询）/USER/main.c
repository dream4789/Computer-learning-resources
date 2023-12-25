/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：串口1(USART1)向电脑的超级终端以1s为间隔打印当前ADC1的转换电压值         
**********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "adc.h"


// 软件延时
void Delay(__IO uint32_t nCount) {
    for (; nCount != 0; nCount--);
}

int main(void) {
    int ADC_ConvertedValue;
    float voltage;
    /* USART1 config */
    USART1_Config();
    /* enable adc1 and config adc1 to dma mode */
    ADC1_Init();
    printf("ADC1转换结果\r\n");
    while (1) {
        /* 由于没有采用外部触发，所以使用软件触发ADC转换 */
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        /* 等待转换结束 */
        while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
        ADC_ConvertedValue = ADC_GetConversionValue(ADC1);
        voltage = (float) ADC_ConvertedValue / 4096 * 3.3; // 读取转换的AD值
        printf("\r\n当前电压数字量：0x%04X \r\n", ADC_ConvertedValue);
        printf("\r\n当前电压模拟值：%f V \r\n", voltage);
        //Delay(0xffffee);                              // 延时 
    }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
