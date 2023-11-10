#include "LPC17xx.h"
#include "../inc/eint.h"

void extIntConfig(void){
	
    LPC_PINCON -> PINSEL4 |= (1<<20) | (1<<22);                     //set eint mode on pins
    LPC_SC -> EXTMODE |= (0x3);                                     //set eint as edge-sensitive
    LPC_SC -> EXTPOLAR |= (0x3);                                    //set eint as rising-edge sensitive
    LPC_SC -> EXTINT |= (0x3);                                      //clear flag
    NVIC_EnableIRQ(EINT0_IRQn);                                     //enable interruptions
    NVIC_EnableIRQ(EINT1_IRQn);
    return;
}

