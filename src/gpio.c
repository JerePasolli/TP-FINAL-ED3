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
    LPC_GPIO2 -> FIODIR |= OUTPUT1 | OUTPUT2 | OUTPUT3 | OUTPUT4;   //keyboard outputs
    LPC_GPIO2 -> FIOSET |= (0xF);                                   //set all the rows
    LPC_PINCON -> PINMODE1 |= (1<<5);                               //led without pullup or pulldown
    LPC_GPIO0 -> FIODIR |= (LED);                                   //set led pin as output 
    LPC_GPIO0 -> FIOCLR |= 1;                                       //clear led
    return;
}

char readKeyboard(void) {
    char keys[ROWS][COLS] = {                                       //keyboard layout
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
    };

    for (int row = 0; row < ROWS; row++) {                          //check which key has been pressed
        LPC_GPIO2->FIOCLR |= ROW_PINS[row];                         //enable row
        for (int col = 0; col < COLS; col++) {                      //check columns
            if (!(LPC_GPIO2->FIOPIN & COL_PINS[col])) {             //check if there are a key pressed in the selected column
            	delay(10000000);
                return keys[row][col];                              //return the key pressed
            }
        }
        LPC_GPIO2->FIOSET |= ROW_PINS[row];                         // row disable
    }
    return '\0';                                                    //if empty, return empty
}
