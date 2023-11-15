#include "LPC17xx.h"
#include "../inc/dac.h"
#include "lpc17xx_dac.h"

#define TIMEOUT 1200

void dacConfig(void)
{
	LPC_PINCON->PINSEL1 |= (1<<21);						//dac pin configuration
	LPC_PINCON->PINMODE1 |= (1<<21);
	DAC_CONVERTER_CFG_Type dacCfg;						//dac configuration structure
		dacCfg.DBLBUF_ENA = 0;							//disable double buffering
		dacCfg.CNT_ENA = ENABLE;						//enable timeout counter
		dacCfg.DMA_ENA = ENABLE;						//enable DMA burst
	DAC_SetDMATimeOut(LPC_DAC, (uint32_t)TIMEOUT);		//set reload value
	DAC_ConfigDAConverterControl(LPC_DAC, &dacCfg);		//DMA enable as per the configuration structure
	DAC_Init(LPC_DAC);									//initialize DAC 
	DAC_UpdateValue(LPC_DAC, 0);						//update DAC back to 0
}
