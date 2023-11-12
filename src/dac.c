#include "LPC17xx.h"
#include "../inc/dac.h"
#include "lpc17xx_dac.h"

#define SINE_FREQ_IN_HZ 100
#define PCLK_DAC_IN_MHZ 25
#define NUM_SINE_SAMPLE 60
DAC_CONVERTER_CFG_Type dacCfg;													//DAC configuration structure
void dacConfig()
{	
	uint32_t tmp;								
	dacCfg.CNT_ENA = SET;														//enable timeout counter
	dacCfg.DMA_ENA = SET;														//enable DMA burst
	DAC_Init(LPC_DAC);															//initialize DAC														
	tmp = (PCLK_DAC_IN_MHZ * 1000000)/(SINE_FREQ_IN_HZ * NUM_SINE_SAMPLE);		//timeout setup
	DAC_SetDMATimeOut(LPC_DAC, tmp);											//set reload value
	DAC_ConfigDAConverterControl(LPC_DAC, &dacCfg);								//DAC enable
}
