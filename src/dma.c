#include "LPC17xx.h"
#include "../inc/dma.h"
#include "lpc17xx_gpdma.h"
#include "../inc/alarm_sound.h"

#define ARRAY_SIZE 24
#define TRANSFER_SIZE 4095
GPDMA_LLI_Type linked_list_array[ARRAY_SIZE];
GPDMA_Channel_CFG_Type dma_config;

void dmaConfig(){
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		linked_list_array[i].Control = TRANSFER_SIZE | (1 << 18) 		// source width 16 bit
									   | 1 << 22						// dest width = word 32 bits
									   | 1 << 26;						// automatic increase
		linked_list_array[i].DstAddr = (uint32_t) & (LPC_DAC->DACR);	// destination address is DAC register
		linked_list_array[i].SrcAddr = (uint32_t)(alarma1 + i * TRANSFER_SIZE);	// source address is a position in the array of samples
		linked_list_array[i].NextLLI = i == (ARRAY_SIZE - 1) ? (uint32_t)&linked_list_array[0] : (uint32_t)&linked_list_array[i + 1]; 
		// if it is the last element, the next element is the first one, otherwise it is the next one
	}
	dma_config.ChannelNum = 0;							//dma channel 0
	dma_config.TransferSize = TRANSFER_SIZE;			
	dma_config.TransferWidth = 0; 						//not used (m2m only)
	dma_config.TransferType = GPDMA_TRANSFERTYPE_M2P;	//memory to peripheral dma type
	dma_config.SrcConn = 0;								//not used (p2p/p2m only)
	dma_config.DstConn = GPDMA_CONN_DAC;				//connect to DAC
	dma_config.SrcMemAddr = (uint32_t)alarma1;			//get sample sound from header file
	dma_config.DstMemAddr = 0;							//not used (m2m/p2m only)
	dma_config.DMALLI = (uint32_t)&linked_list_array[0];//linked list array
	GPDMA_Init();										//enable DMA
	GPDMA_Setup(&dma_config);							//use the defined configuration
	return;
}
