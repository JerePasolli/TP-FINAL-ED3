#include "LPC17xx.h"
#include "../inc/adc.h"
#include "../inc/dac.h"
#include "../inc/delay.h"
#include "../inc/dma.h"
//#include "../inc/eint.h"
#include "../inc/gpio.h"
#include "../inc/adc.h"
#include "../inc/timers.h"
//#include "../inc/uart.h"

//insert defines
char password[4] = {'1','2','3','4'};
char inputPassword[4];
char key;
uint8_t status = 0;
uint8_t position = 0;
uint8_t incorrectPassword = 0;

//uint8_t position = 0;

int main(void) {
	//char inputPassword[4] ={'z','z','z','z'};


    //initial settings
    gpioConfig();
    adcConfig();
    timerConfig();
    dacConfig();
    dmaConfig();
    //gpioIntConfig();
    //extIntConfig();

    while(1){
    	/*if(status == 1){
    		LPC_GPIO0 -> FIOSET |= 1;
    	}
    	else{
    		LPC_GPIO0 -> FIOCLR |= 1;
    	}*/
    	key = readKeyboard();
    	        if (key != '\0') {
    	        	LPC_GPIO0->FIOSET |= 1;
    	            inputPassword[position] = key;
    	            if (position == 3){
    	            	for(uint8_t i = 0; i < 4; i++){
    	            		if(inputPassword[i] != password[i]){
    	            			incorrectPassword = 1;
    	            		}
    	            	}
    	            	if(incorrectPassword){
    	            		incorrectPassword = 0;
    	            	}
    	            	else{
    	            		if(status == 0)
    	            			status = 1;
    	            		else
    	            			status = 0;
    	            	}
    	            }
    	            position ++;
    	            if(position == 4){
    	            	position = 0;
    	            }
    	            LPC_GPIO0->FIOCLR |= 1;
    	        }
    }
    return 0;
}
