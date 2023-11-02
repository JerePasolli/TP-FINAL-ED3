#ifdef
#include "LPC17xx.h"
#include "inc/adc.h"
#include "inc/dca.h"
#include "inc/dma.h"
#include "inc/eint.h"
#include "inc/gpio.h"
#include "inc/timers.h"
#include "inc/uart.h"
#endif

//insert defines
void delay (uint32_t time);

int main(void) {
    //initial settings
    gpioconfig();
    gpioIntConfig();
    extIntConfig();

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