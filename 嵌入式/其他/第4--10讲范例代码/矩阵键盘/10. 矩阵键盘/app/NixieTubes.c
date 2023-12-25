 #include "stm32f10x.h"
 #include "NixieTubes.h"
 #include "SysTick.h"
 
 void NixieTubes_Init(void)
 {

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = 0xff;//ʹ��Pin0--Pin7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);  //GPIOD��Ϊλѡ
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //GPIOE��Ϊ��ѡ
 }
 
  void NixieDisplay(s16 value)
 {
	 //DP G F E D C B A
	 //0  0 1 1 1 1 1 1
	 //����Ϊ�ʺϹ����ӷ��� 0 ��������
	u16 num[16] = {0x3f, 0x06, 0x5b, 0x4f, 
		             0x66, 0x6d, 0x7d, 0x07, 
		             0x7f, 0x6F, 0x77, 0x7c, 
	               0x39, 0x5e, 0x79, 0x71};
	s16 j;
	j=value;

	if(j>=0)
	{	
//PD[7..0]��Ӧѡ������ҵ�8������ܣ��͵�ƽѡ�ã��ߵ�ƽ����		
    GPIOD->ODR = 0xff;//�ر�ȫ����ʾ		
		GPIOE->ODR = ~num[j];//���α�񰴹����ӷ���ƣ����ڹ����ӷ���ȡ��ʹ��
		GPIOD->ODR = 0x00;//ѡ��ȫ������
		Delay_ms(2);
	}
 }
