#include "LPC17xx.h"
#include "../inc/adc.h"
#include "lpc17xx_adc.h"

void adcConfig(void){
	
	LPC_PINCON -> PINSEL1 |= (1<<14);							//adc is located in pin 0.23, set function to ADC
	LPC_PINCON -> PINMODE1 |= (1<<15);							//remove pull up/down resistors
	ADC_Init(LPC_ADC,200000);									//set adc to maximum rate
	ADC_BurstCmd(LPC_ADC,DISABLE);								//disable burst mode
	ADC_StartCmd(LPC_ADC,ADC_START_ON_MAT01);					//select match channel 1
	ADC_ChannelCmd(LPC_ADC,0,ENABLE);							//enable adc channel 0
	LPC_ADC->ADGDR &= LPC_ADC->ADGDR;
	ADC_EdgeStartConfig(LPC_ADC,ADC_START_ON_RISING);			//choose rising edge
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN0,SET);
	NVIC_SetPriority(ADC_IRQn, 2);
	NVIC_EnableIRQ(ADC_IRQn);									//enable interruptions for adc in NVIC
}
