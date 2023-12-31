#include "dz.h"
#include "SysTick.h"
// 数码管编码表 
const uint8_t seg_tab[16][8] ={ 
  {0xFF,0xE3,0xDD,0xDD,0xDD,0xDD,0xE3,0xFF}, // 0 
  {0xEF,0xE7,0xE3,0xE7,0xE7,0xE7,0xE7,0x81}, // 1 
  {0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE}, // 2 
  {0xFF,0x83,0xDD,0xDD,0xE3,0xDD,0xDD,0xFF}, // 3 
  {0xFF,0xDD,0xDD,0xDD,0xEF,0xFB,0xDD,0xDD}, // 4 
  {0xFF,0xDD,0xDD,0xDD,0xF3,0xDD,0xDD,0xFF}, // 5 
  {0xFF,0xF3,0xDD,0xDD,0xF3,0xDD,0xDD,0xFF}, // 6 
  {0x7F,0xEF,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD}, // 7 
  {0xFF,0xE3,0xDD,0xDD,0xE3,0xDD,0xDD,0xFF}, // 8 
  {0xFF,0xE3,0xDD,0xDD,0xF3,0xDD,0xDD,0xFF}, // 9 
  {0xFF,0xE3,0xDD,0xDD,0xFB,0xDD,0xDD,0xFF}, // A 
  {0xF7,0xDD,0xDD,0xF7,0xDD,0xDD,0xDD,0xFF}, // B 
  {0xFF,0xF3,0xDD,0xDD,0xDD,0xDD,0xF3,0xFF}, // C 
  {0xEF,0xDD,0xDD,0xDD,0xDD,0xDD,0xE7,0xFF}, // D 
  {0xFF,0xF3,0xDD,0xDD,0xF3,0xDD,0xF3,0xFF}, // E 
  {0xFF,0xF3,0xDD,0xDD,0xF3,0xDD,0xDD,0xDD}  // F 
};

// 控制8个行 
const uint16_t rows[8]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7};

// 控制8个列 
const uint16_t cols[8]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7};

// 点阵初始化 
void LED_Init(void){ 
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE); // 使能PE口时钟 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOE,&GPIO_InitStructure); 
  GPIO_SetBits(GPIOE,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); // 使能PA口时钟 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA,&GPIO_InitStructure); 
  GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); 
}

// 简单的延时函数 
void Delay(__IO u32 nCount){ for(; nCount != 0; nCount--); }

// 数码管循环显示 
void led_display(void){ 
  for(int k = 0 ; k < 16 ; k++){ // 表示16个数字（0-F） 
    for(int i = 0 ; i < 100 ; i++){  // 每个数字循环100次 
      for(int v = 0 ; v < 8 ; v++){  // 控制8行 
        GPIO_Write(GPIOE ,seg_tab[k][v]); // 输出对应的列显示 
        GPIO_ResetBits(GPIOA,rows[v]); // 已选的行亮起 
        Delay(100);                    // 视觉暂停，调节速度 
        GPIO_SetBits(GPIOA,rows[v]);   // 行熄灭 
      } 
    } 
  } 
}