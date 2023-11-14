#include "LPC17xx.h"
#include "../inc/dac.h"
#include "lpc17xx_dac.h"

#define SINE_FREQ_IN_HZ 10000
#define PCLK_DAC_IN_MHZ 25
#define NUM_SINE_SAMPLE 60


void dacConfig(void)
{
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINMODE1 |= (1<<21);
    //DAC configuration structure
	DAC_Init(LPC_DAC);
	DAC_UpdateValue(LPC_DAC, 0);
	DAC_CONVERTER_CFG_Type dacCfg;
	dacCfg.CNT_ENA = ENABLE;														//enable timeout counter
	dacCfg.DMA_ENA = ENABLE;														//enable DMA burst
	//initialize DAC
	uint32_t tmp;																	//timeout setup
	tmp = (PCLK_DAC_IN_MHZ * 1000000)/(SINE_FREQ_IN_HZ * NUM_SINE_SAMPLE);
	DAC_SetDMATimeOut(LPC_DAC, tmp);												//set reload value
	DAC_ConfigDAConverterControl(LPC_DAC, &dacCfg);									//DAC enable
}
