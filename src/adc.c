#include "LPC17xx.h"
#include "adc.h"
#include "lpc17xx_adc.h"

void adcConfig(void){
	LPC_PINCON -> PINSEL1 |= (1<<14);
	//removing resistors
	LPC_PINCON -> PINMODE1 |= (1<<15);
	ADC_init(LPC_ADC,200000);
	ADC_BurstCmd(LPC_ADC,DISABLE);
	ADC_StartCmd(LPC_ADC,ADC_START_ON_MATCH01);
	ADC_ChannelCmd(LPC_ADC,0,ENABLE);
	ADC_EdgeStartConfig(LPC_ADC,ADC_START_ON_RISING);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN0,ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_IRQHandler(void){
	uint16_t aux;
	aux = ((LPC_ADC->ADDR0)>>4)&0xFFF;
	LPC_GPIO0->FIOPIN = ADC0Value;
	LPC_ADC->ADGDR &= LPC_ADC->ADGDR;
	return;
}