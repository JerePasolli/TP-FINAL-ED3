#include "LPC17xx.h"
#include "../inc/delay.h"

void delay (uint32_t time){
    uint32_t counter;
    for(counter = 0; counter <time; counter++){};
    return;
}
