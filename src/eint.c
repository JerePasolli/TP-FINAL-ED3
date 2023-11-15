#include "LPC17xx.h"
#include "eint.h"

//external intererupt setup

#define EINT0 (1<<0)
#define EINT1 (1<<1)

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

//external interrupt on EINTX
void EINT0_IRQHandler(void){
    //insert code
    LPC_SC -> EXTINT |= EINT0; //clearing flag
    return;
}

//external interrupt on EINTX
void EINT1_IRQHandler(void){
    //insert code
	LPC_SC -> EXTINT |= EINT1; //clearing flag
    return;
}

//gpio interrupting on EINT3
void EINT3_IRQHandler(void){
    //insert code
    //LPC_GPIOINT -> IO0IntClr |= (X); //clearing flag
    return;
}
