#include "LPC17xx.h"
#include "adc.h"
#include "lpc17xx_adc.h"

uint16_t adc0Value;

void adcConfig(void){
	LPC_PINCON -> PINSEL1 |= (1<<14);
	//removing resistors
	LPC_PINCON -> PINMODE1 |= (1<<15);
	ADC_Init(LPC_ADC,200000);
	ADC_BurstCmd(LPC_ADC,DISABLE);
	ADC_StartCmd(LPC_ADC,ADC_START_ON_MAT01);
	ADC_ChannelCmd(LPC_ADC,0,ENABLE);
	ADC_EdgeStartConfig(LPC_ADC,ADC_START_ON_RISING);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN0,ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_IRQHandler(void){
	adc0Value = ((LPC_ADC->ADDR0)>>4)&0xFFF;
	if(adc0Value > 0x9B0){ // 2V sensed from MQ135 aprox
		if(state == 1){ // state == 1 means alarm is activated
			//play alarm sound (init dac)
		}


	}
	LPC_ADC->ADGDR &= LPC_ADC->ADGDR; // clean flag
	return;
}
