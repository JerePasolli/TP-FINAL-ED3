#include "LPC17xx.h"
#include "../inc/eint.h"

//external intererupt setup

uint8_t interruptAid;

void extIntConfig(void){
	//setting eint mode on pins
    LPC_PINCON -> PINSEL4 |= (1<<20) | (1<<22);
    //setting eint as edge-sensitive
    LPC_SC -> EXTMODE |= (0x3);
    //setting eint as rising-edge sensitive
    LPC_SC -> EXTPOLAR |= (0x3);
    //clearing flag
    LPC_SC -> EXTINT |= (0x3); 
    //enable interruptions
    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    return;
}

