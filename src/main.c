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
#include "lpc17xx_timer.h"

//Global Variables
#define OFF 0
#define ACTIVE 1
#define RINGING 2
#define EINT0 (1<<0)
#define EINT1 (1<<1)
volatile uint8_t password[4] = {'1','2','3','4'};
volatile uint8_t inputPassword[4];
volatile uint8_t key;
volatile uint8_t status = 0;
uint8_t message1[] = "Alarm off\n\r";
uint8_t message2[] = "Alarm on\n\r";
uint8_t message3[] = "Alarm ringing\n\r";
uint8_t message4[] = "Wrong Password\n\r";
uint8_t message5[] = "Uart reception error\n\r";
uint8_t message6[] = "Smoke detected\n\r";
uint8_t message7[] = "Movement detected\n\r";
volatile uint8_t received[1] = "";
volatile uint8_t uartPassword[4];
volatile uint8_t movement = 0;
volatile int8_t position = 0;
volatile uint8_t incorrectPassword = 0;
volatile uint16_t adc0Value;
//Functions
void ADC_IRQHandler(void);
void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);
void TIMER1_IRQHandler(void);
void UART2_IRQHandler(void);

int main(void) {
    gpioConfig();
    timerConfig();
    adcConfig();
    dacConfig();
    dmaConfig();
    uartConfig();
    extIntConfig();

    while(1){

    	if((status == ACTIVE)||(status == RINGING)){				//if the alarm is active or ringing
    		LPC_GPIO0 -> FIOSET |= (1<<18);								//turn on the led
    	}
    	else{														//if the alarm is off
    		LPC_GPIO0 -> FIOCLR |= (1<<18);								//turn off the led
    	}
    	
    	key = readKeyboard();
		if (key != '\0') {											//ignore if null character
			LPC_GPIO0 -> FIOSET |= (1<<4);
			TIM_Cmd(LPC_TIM1, ENABLE);
			inputPassword[position] = key;							//save the key pressed
			TIM_Cmd(LPC_TIM2, ENABLE);
			if(inputPassword[position] == inputPassword[position-1])
				if(inputPassword[position] == '*'){
					status = RINGING;
					position = -1;
					UART_Send(LPC_UART2, message3, sizeof(message3), BLOCKING);
				}
			if (position == 3){										//check if correct at the end of the password
				for(uint8_t i = 0; i < 4; i++){
					if(inputPassword[i] != password[i]){
						incorrectPassword = 1;
					}
				}
				if(incorrectPassword){				
					incorrectPassword = 0;
					UART_Send(LPC_UART2, message4, sizeof(message4), BLOCKING);
				}
				else{
					if(status == OFF){									//if the password is correct, turn on the alarm
						status = ACTIVE;
						UART_Send(LPC_UART2, message2, sizeof(message2), BLOCKING);
					}
					else{
						status = OFF;
						UART_Send(LPC_UART2, message1, sizeof(message1), BLOCKING);
						GPDMA_ChannelCmd(0,DISABLE);
						DAC_UpdateValue(LPC_DAC, 0);
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
	if(adc0Value > 0x744){ 	//1,5V sensed from MQ135 aprox
		if(status == ACTIVE){
			status = RINGING;

			UART_Send(LPC_UART2, message3, sizeof(message3), BLOCKING);
		    GPDMA_ChannelCmd(0,ENABLE);
		    UART_Send(LPC_UART2, message6, sizeof(message6), BLOCKING);
		}
	}
	LPC_ADC->ADGDR &= LPC_ADC->ADGDR; 		// clear flag
	return;
}

//external interrupt on EINT0
void EINT0_IRQHandler(void){
	if(status == ACTIVE){
		status = RINGING;

		UART_Send(LPC_UART2, message3, sizeof(message3), BLOCKING);
		GPDMA_ChannelCmd(0,ENABLE);
		UART_Send(LPC_UART2, message7, sizeof(message7), BLOCKING);
	}
    LPC_SC -> EXTINT |= EINT0; 				//clear flag
    return;
}

//external interrupt on EINT1
void EINT1_IRQHandler(void){
	if(status == ACTIVE){
		status = RINGING;

		UART_Send(LPC_UART2, message3, sizeof(message3), BLOCKING);
		GPDMA_ChannelCmd(0,ENABLE);
		UART_Send(LPC_UART2, message7, sizeof(message7), BLOCKING);
	}
	LPC_SC -> EXTINT |= EINT1; 				//clear flag
    return;
}

void TIMER1_IRQHandler(void){

	LPC_GPIO0 -> FIOCLR |= (1<<4);
	TIM_Cmd(LPC_TIM1, DISABLE);
	TIM_ClearIntPending(LPC_TIM1, TIM_MR1_INT);

	return;
}

void TIMER2_IRQHandler(void){
	position = 0;
	TIM_Cmd(LPC_TIM2, DISABLE);
	TIM_ClearIntPending(LPC_TIM2, TIM_MR1_INT);

	return;
}

void UART2_IRQHandler(void){
	uint32_t intsrc, tmp, tmp1;
	static uint8_t counter;
	intsrc = UART_GetIntId(LPC_UART2);
	tmp = intsrc & UART_IIR_INTID_MASK;

	if(tmp == UART_IIR_INTID_RLS){
		tmp1 = UART_GetLineStatus(LPC_UART2);
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE | UART_LSR_BI | UART_LSR_RXFE);
		if(tmp1){
			UART_Send(LPC_UART2, message5, sizeof(message5), NONE_BLOCKING);			//UART error handling code
		}
	}

	if((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
		UART_Receive(LPC_UART2, received, sizeof(received), NONE_BLOCKING);
		uartPassword[counter] = received[0];
		counter ++;
		if(counter == 4){
			counter = 0;
			for(uint8_t i = 0; i < 4; i++){
				if(password[i] != uartPassword[i])
					return;
			}
			if(status == OFF){
				status = ACTIVE;
				UART_Send(LPC_UART2, message2, sizeof(message2), NONE_BLOCKING);
			}
			else{
				status = OFF;
				UART_Send(LPC_UART2, message1, sizeof(message1), NONE_BLOCKING);
				GPDMA_ChannelCmd(0,DISABLE);
				DAC_UpdateValue(LPC_DAC, 0);
			}

		}

	}
	return;
}
