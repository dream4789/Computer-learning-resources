#include "led.h"

/*初始化PC0引脚
 *推挽式输出,翻转速度2M
 *默认输出低电平
*/

void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 
 
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);	/*开启按键端口（PE5）的时钟*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*初始化PB5引脚
 *推挽式输出,翻转速度2M
 *默认输出高电平
*/
void myLED2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	LED2(1);
}

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin) == KEY_ON ) 
	{	   
		/*延时消抖*/
		Delay(10000);		
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin) == KEY_ON )  
		{	 
			/*等待按键释放 */
			while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin) == KEY_ON);   
			return 	KEY_ON;	 
		}
		else
			return KEY_OFF;
	}
	else
		return KEY_OFF;
}
