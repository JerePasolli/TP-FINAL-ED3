#include "LPC17xx.h"
#include "../inc/eint.h"
#include "../inc/timers.h"
#include "../inc/delay.h"

//external interrupt setup

void extIntConfig(void){
	
    LPC_PINCON -> PINSEL4 |= (1<<20) | (1<<22);                     //set eint mode on pins 2.10 and 2.11
    LPC_SC -> EXTMODE |= (0x3);                                     //set eint as edge-sensitive
    LPC_SC -> EXTPOLAR |= (0x3);                                    //set eint as rising-edge sensitive
    LPC_SC -> EXTINT |= (0x3);                                      //clear flag
    NVIC_EnableIRQ(EINT0_IRQn);                                     //enable interruptions
    NVIC_EnableIRQ(EINT1_IRQn);
    return;
}

void sensorTrigger(void){
    LPC_GPIO0 -> FIOSET |= (1<<10);
    delay(1000);
    LPC_GPIO0 -> FIOCLR |= (1<<10);
}

int echo_monitor(void){
	float pulse_time = 0, distance=0;
    int detection;
	while((LPC_GPIO0->FIOPIN & (0x1<<16)) == 0x0);	//Wait till echo is low
	startTimer2();															//Initialize the echo timer
	while((LPC_GPIO0->FIOPIN & (0x1<<16)) == 0x1<<16);	//Wait till echo is high
	pulse_time = stopTimer2();										//Get count of echo timer
    distance = (0.0343*pulse_time)/2;
    if(distance > 10){
        detection = 0;
    }
    else detection = 1;
	return detection;
}