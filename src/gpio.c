#include "LPC17xx.h"
#include "gpio.h"

#define INPUT1 (1<<18)
#define INPUT2 (1<<17)
#define INPUT3 (1<<15)
#define INPUT4 (1<<16)
#define OUTPUT1 (1<<21)
#define OUTPUT2 (1<<22)
#define OUTPUT3 (1<<2)
#define OUTPUT4 (1<<3)

void gpioConfig(void){

    //GPIO configurations
	//numberpad inputs as gpio
    LPC_PINCON -> PINSEL0 &= ~(0x3<<30);
    LPC_PINCON -> PINSEL1 &= ~(0x3F);
    //numberpad outputs as gpio
    LPC_PINCON -> PINSEL1 &= ~(0xF<<10);
    LPC_PINCON -> PINSEL1 &= ~(0xF<<4);
    //numberpad inputs with pullup
    LPC_PINCON -> PINMODE0 &= ~(0X3<<30);
    LPC_PINCON -> PINMODE1 &= ~(0x3F);
    //numberpad outputs with pulldown
    LPC_PINCON -> PINMODE1 |= (0xA<<10);
    LPC_PINCON -> PINMODE0 |= (0xA<<4);
    //numberpad inputs
    LPC_GPIO0 -> FIODIR &= ~(INPUT1);
    LPC_GPIO0 -> FIODIR &= ~(INPUT2);
    LPC_GPIO0 -> FIODIR &= ~(INPUT3);
    LPC_GPIO0 -> FIODIR &= ~(INPUT4);
    //numberpad outputs
    LPC_GPIO0 -> FIODIR |= OUTPUT1 | OUTPUT2 | OUTPUT3 | OUTPUT4;

    return;
}


void gpioIntConfig(void){
    //GPIO interrupt configuration
	//falling edge for inputs
    LPC_GPIOINT -> IO0IntEnF |= INPUT1 | INPUT2 | INPUT3 | INPUT4;


    //check keyboard setup (4x4 w 4 outputs)

    //clear flags
    LPC_GPIOINT -> IO0IntClr |= INPUT1 | INPUT2 | INPUT3 | INPUT4;
    //enable interruption
    NVIC_Enable(EINT3_IRQn);

    return;
}