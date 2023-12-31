#include "LPC17xx.h"
#include "../inc/gpio.h"
#include "../inc/delay.h"

#define INPUT1 (1<<4)
#define INPUT2 (1<<5)
#define INPUT3 (1<<6)
#define OUTPUT1 (1)
#define OUTPUT2 (1<<1)
#define OUTPUT3 (1<<2)
#define OUTPUT4 (1<<3)
#define LED (1<<18)
#define ROWS 4
#define COLS 3
uint32_t ROW_PINS[4] = {OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4};
uint32_t COL_PINS[3] = {INPUT1, INPUT2, INPUT3};

void gpioConfig(void){
    LPC_PINCON -> PINSEL4 &= ~(0xFF);                               //keyboard inputs and outputs as gpio
    LPC_PINCON -> PINMODE4 &= ~(0XFF<<8);                           //keyboard inputs with pullup
    LPC_PINCON -> PINMODE4 |= (0xAA);                               //keyboard outputs without pullup or pulldown
    LPC_GPIO2 -> FIODIR &= ~(INPUT1);                               //keyboard inputs
    LPC_GPIO2 -> FIODIR &= ~(INPUT2);
    LPC_GPIO2 -> FIODIR &= ~(INPUT3);

    LPC_GPIO0 -> FIODIR |= (1<<18);                                 //P0.18 as digital output for led
    LPC_PINCON -> PINMODE1 |= (1<<5);
    LPC_GPIO0 -> FIOCLR |= (1<<18);

    LPC_GPIO0-> FIODIR |= (1<<4);
    LPC_PINCON -> PINMODE0 |= (1<<9);
    LPC_GPIO0 -> FIOCLR |= (1<<4);

    LPC_GPIO2 -> FIODIR |= OUTPUT1 | OUTPUT2 | OUTPUT3 | OUTPUT4;   //numberpad outputs
    LPC_GPIO2 -> FIOSET |= OUTPUT1 | OUTPUT2 | OUTPUT3 | OUTPUT4;   //set all inputs and outputs
    LPC_GPIO2 -> FIOSET |= INPUT1 | INPUT2 | INPUT3;
    return;
}

char readKeyboard(void) {
    char keys[ROWS][COLS] = {                                       //keyboard layout
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
    };
    for (int row = 0; row < ROWS; row++) {
        LPC_GPIO2->FIOCLR |= ROW_PINS[row];                         // row enable
        for (int col = 0; col < COLS; col++) {                      // check columns
            if (!(LPC_GPIO2->FIOPIN & COL_PINS[col])) {
            	delay(1000000*3);
                return keys[row][col];
            }
        }
        LPC_GPIO2->FIOSET |= ROW_PINS[row];                         // row disable
    }
    return '\0';                                                    //if empty, return empty
}
