/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * 文件名  ：key.c
 * 描述    ：按键应用函数库
**********************************************************************************/
#include "key.h" 

 /*
 * 函数名： Delay
 * 描述  ：不精确的延时
 * 输入  ：延时参数，
 * 输出  ：无
 */
 void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

 /*
 * 函数名：Key_GPIO_Config
 * 描述  ：配置按键用到的I/O口
 */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);	/*开启按键端口（PE5）的时钟*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
  //	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//按照上述设定初始化GPIOC
	GPIO_SetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);//熄灭led1-led4(共阳)
}

 /*
 * 函数名：Key_Scan
 * 描述  ：检测是否有按键按下
 * 输入  ：GPIOx：x 可以是 A，B，C，D或者 E
 *		     GPIO_Pin：待读取的端口位 	
 * 输出  ：KEY_OFF(没按下按键)、KEY_ON（按下按键）
 */
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
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE****/
