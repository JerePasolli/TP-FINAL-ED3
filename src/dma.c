#include "LPC17xx.h"
#include "../inc/dma.h"
#include "lpc17xx_gpdma.h"
#include "../inc/alarm_sound.h"


GPDMA_LLI_Type linked_list_array[24];
GPDMA_Channel_CFG_Type dma_config;

void dmaConfig(){

	for (int i = 0; i < 24; i++)
	{
		linked_list_array[i].Control = 4095 | (1 << 18) // source width 16 bit
									   | 1 << 22		// dest width = word 32 bits
									   | 1 << 26;		// incremento automatico
		linked_list_array[i].DstAddr = (uint32_t) & (LPC_DAC->DACR);
		linked_list_array[i].SrcAddr = (uint32_t)(alarma1 + i * 4095);
		linked_list_array[i].NextLLI = i == (24 - 1) ? (uint32_t)&linked_list_array[0] : (uint32_t)&linked_list_array[i + 1];
	}

	dma_config.ChannelNum = 0;
	dma_config.TransferSize = 4095;
	dma_config.TransferWidth = 0; // no se usa
	dma_config.TransferType = GPDMA_TRANSFERTYPE_M2P;
	dma_config.SrcConn = 0;
	dma_config.DstConn = GPDMA_CONN_DAC;
	dma_config.SrcMemAddr = (uint32_t)alarma1;
	dma_config.DstMemAddr = 0;
	dma_config.DMALLI = (uint32_t)&linked_list_array[0];

	GPDMA_Init();

	GPDMA_Setup(&dma_config);

	return;

}
