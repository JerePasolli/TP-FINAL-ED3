#include "LPC17xx.h"
#include "../inc/adc.h"
#include "lpc17xx_adc.h"

void adcConfig(void){
	//adc is located in pin 0.23, set function to ADC
	LPC_PINCON -> PINSEL1 |= (1<<14);
	//remove pull up/down resistors
	LPC_PINCON -> PINMODE1 |= (1<<15);
	//set adc to maximum rate
	ADC_Init(LPC_ADC,200000);
	//enable burst mode
	ADC_BurstCmd(LPC_ADC,DISABLE);
	//selecting match channel 1
	ADC_StartCmd(LPC_ADC,ADC_START_ON_MAT01);
	//enable adc channel 0
	ADC_ChannelCmd(LPC_ADC,0,ENABLE);
	//choosing
	ADC_EdgeStartConfig(LPC_ADC,ADC_START_ON_RISING);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN0,ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
}
