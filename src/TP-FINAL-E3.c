#include "LPC17xx.h"
#include "../inc/adc.h"
#include "../inc/dac.h"
#include "../inc/delay.h"
#include "../inc/dma.h"
#include "../inc/eint.h"
#include "../inc/gpio.h"
#include "../inc/adc.h"
#include "../inc/timers.h"
#include "../inc/uart.h"
//Drivers
#include "lpc17xx_gpdma.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_uart.h"
//#include "lpc17xx_"

//Global Variables
#define OFF 0
#define ACTIVE 1
#define RINGING 2
#define EINT0 (1<<0)
#define EINT1 (1<<1)
volatile char password[4] = {'1','2','3','4'};
volatile char inputPassword[4];
//volatile char dataReceived[4];
volatile char key;
volatile uint8_t status = 0;
volatile uint8_t position = 0;
volatile uint8_t incorrectPassword = 0;
volatile uint16_t adc0Value;
//volatile uint32_t bytesReceived;
//Functions
void ADC_IRQHandler(void);
void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);

int main(void) {

    //initial settings
    gpioConfig();
    //adcConfig();
    //timerConfig();
    //dmaConfig();
    //dacConfig();

    uartConfig();
    //gpioIntConfig();
    //extIntConfig();

    while(1){
    	if((status == ACTIVE)||(status == RINGING)){
    		LPC_GPIO0 -> FIOSET |= (1<<18);
    	}
    	else{
    		LPC_GPIO0 -> FIOCLR |= (1<<18);
    	}
    	//bytesReceived = UART_Receive((LPC_UART_TypeDef*)LPC_UART1,(uint8_t*)dataReceived,sizeof(dataReceived),NONE_BLOCKING);
    	key = readKeyboard();
		if (key != '\0') {
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
					if(status == OFF){
						status = ACTIVE;
						UART_Send(LPC_UART1, status, sizeof(status), NONE_BLOCKING);
					}
					else{
						status = OFF;
						UART_Send(LPC_UART1, status, sizeof(status), NONE_BLOCKING);
						//GPDMA_ChannelCmd(0,DISABLE);
						//DAC_UpdateValue(LPC_DAC, 0);
					}
				}
			}
			position ++;
			if(position == 4){
				position = 0;
			}
		}
    }
    return 0;
}

void ADC_IRQHandler(void){
	adc0Value = ((LPC_ADC->ADDR0)>>4)&0xFFF;
	if(adc0Value > 0x8F7){ // 1,85V sensed from MQ135 aprox
		if(status == ACTIVE)
			status = RINGING;
		//UART_SendByte((LPC_UART_TypeDef*)LPC_UART1,2);
		//GPDMA_ChannelCmd(0,ENABLE);
	}
	LPC_ADC->ADGDR &= LPC_ADC->ADGDR; // clean flag
	return;
}

//external interrupt on EINT0
void EINT0_IRQHandler(void){
    //insert code
	if(status == ACTIVE){
		status = RINGING;
		//UART_SendByte((LPC_UART_TypeDef*)LPC_UART1,2);
		//GPDMA_ChannelCmd(0,ENABLE);
	}
    LPC_SC -> EXTINT |= EINT0; //clearing flag
    return;
}

//external interrupt on EINT1
void EINT1_IRQHandler(void){
	if(status == ACTIVE){
		status = RINGING;
		//UART_SendByte((LPC_UART_TypeDef*)LPC_UART1,2);
		//GPDMA_ChannelCmd(0,ENABLE);
	}
    //insert code
	LPC_SC -> EXTINT |= EINT1; //clearing flag
    return;
}
