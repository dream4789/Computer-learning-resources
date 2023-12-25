#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
//#include "led.c"
#include "timer.h"

u8 cnm;


int main(void) {
    int i;
    delay_init();
    LED_Init();
    while (1) {
        for (i = 0; i < 100; i++)zero();
        for (i = 0; i < 100; i++)one();
        for (i = 0; i < 100; i++)two();
        for (i = 0; i < 100; i++)three();
        for (i = 0; i < 100; i++)four();
        for (i = 0; i < 100; i++)five();
        for (i = 0; i < 100; i++)six();
        for (i = 0; i < 100; i++)seven();
        for (i = 0; i < 100; i++)eight();
        for (i = 0; i < 100; i++)nine();
        for (i = 0; i < 100; i++)xin();
        // display();
    }
}



