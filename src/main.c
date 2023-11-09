#include "LPC17xx.h"
#include "../inc/adc.h"
//#include "../inc/dca.h"
#include "../inc/delay.h"
//#include "../inc/dma.h"
//#include "../inc/eint.h"
#include "../inc/gpio.h"
#include "../inc/timers.h"
//#include "../inc/uart.h"

//insert defines
//char password[4] = {'1','2','3','4'};
char key;
uint8_t status = 0;
//uint8_t position = 0;

int main(void) {
	//char inputPassword[4] ={'z','z','z','z'};


    //initial settings
    gpioConfig();
    //gpioIntConfig();
    //extIntConfig();

    while(1){
    	key = readKeyboard();
    	        if (key != '\0') {
    	            // to do: process input
    	            /*inputPassword[position] = key;
    	            if (inputPassword[3] != 'z'){

    	            	for (uint8_t i = 0; i<4; i++){
							if (inputPassword[i] != password[i]){
								break;
							}
							if (i == 3){
								status = 1;
							}
    	            	}


    	            	position = 0;
    	            	inputPassword = {'z','z','z','z'};
    	            }
    	            else if (inputPassword[2] != 'z'){
    	            	position = 3;
    	            }
    	            else if (inputPassword[1] != 'z'){
    	            	position = 2;
    	            }
    	            else {
    	            	position = 1;
    	            }


    	        }

    	        //passCounter++;*/
    	        }
    }
    return 0;
}
