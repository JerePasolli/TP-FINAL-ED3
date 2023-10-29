#ifdef
#include "LPC17xx.h"
#include "adc.h"
#include "dca.h"
#include "dma.h"
#include "eint.h"
#include "gpio.h"
#include "timers.h"
#include "uart.h"
#endif

//insert defines
void delay (uint32_t time);

int main(void) {
    //initial settings
    gpioconfig();
    gpioIntConfig();

    while(1){
       //insert main code 
    }
    return 0;
}

void delay (uint32_t time){
    uint32_t counter;
    for(counter = 0; counter <time; counter++){};
    return;
}