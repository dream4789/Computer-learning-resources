/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：串口1(USART1)向电脑的超级终端以1s为间隔打印当前ADC1的转换电压值         
**********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "adc.h"
#include <math.h>


// 软件延时
void Delay(__IO uint32_t nCount) {
    for (; nCount != 0; nCount--);
}

// 0-9 A-E
int showNumTable[16] = {
	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 
	0x92, 0x82, 0xf8, 0x80, 0x90, 
	0x77, 0x7C, 0x39, 0x5E, 0x79};

int showNum[8] = {0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff};

// {0xc0, 0xf9, 0xf9, 0xb0, 0xf9, 0x92, 0x82, 0xf8, 0x80, 0x90};
// ..12 2345
// 0111 1111
// 1010 0100


// 0011 
int showNum3[8] = {0x7f,0x7f, 0xf9,0xa4, 0xa4,0xb0, 0x99, 0x92};
int showNum44[8] = {0x7f,0x7f, 0xf9,0x24, 0xa4,0x30, 0x99, 0x92};
	
// 0143,0725
int showNum443[8] = { 0xc0, 0xf9, 0x99, 0xb0, 0xc0, 0xf8, 0xf9, 0x92 };
								//  a    h    u    t   2    0     2     3
int showNum2[8] = {0x88,0x89,0xc1,0xf8,0xa4,0xc0, 0xa4, 0xb0};


int smg(void) {
	int i, j, k;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);    
	//disable JTAG
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE); 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	// GPIO_E
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	//while (1) {
		for (k = 0; k < 300; ++k) {
			for (i = 0; i < 8; ++i) {
				for (j = 0; j < 1000; ++j) {
					GPIOA->ODR = ~showNum[i];  // shape
					GPIOE->ODR = 0xff - (1 << i); // postion
				}				
			}
		}
		Delay(0x0fffee);
	//}
} 


int main1(void)
{
    int ADC_ConvertedValue;
    float voltage;
    /* USART1 config */
    USART1_Config();
	
		// ADC1_Init1();

    printf("ADC1转换结果\r\n");
    while (1) {
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);  // wait until conversion complete
        ADC_ConvertedValue = ADC_GetConversionValue(ADC1);
        voltage = (float) ADC_ConvertedValue / 4096 * 3.3;  // calculate voltage
        printf("\r\n当前电压数字量：0x%04X \r\n", ADC_ConvertedValue);
        printf("\r\n当前电压模拟值：%f V \r\n", voltage);
			
				int adcValue = (ADC_ConvertedValue >> 8) & 0x0F;
				if (adcValue <= 9) {
						showNum[4] = showNumTable[adcValue];
				} else {
						showNum[4] = showNumTable[adcValue - 10 + 0x0A];
				}
			
				showNum[1] = voltage;
				int voltValue = floor(voltage * 10000);
				int pos = 4; 
				for (int i = 4; i < 8; ++i) {
						int digit = voltValue % 10;
						showNum[pos--] = showNumTable[digit];
						voltValue /= 10;
				}

			
        // Delay(0xffffee);
    }
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

				smg();

        // Delay(0x5fffee);                              // 延时 
    }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
