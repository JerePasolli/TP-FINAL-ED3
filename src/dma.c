#include "LPC17xx.h"
#include "../inc/dma.h"
#include "lpc17xx_gpdma.h"

#define DMA_SIZE 60
#define NUM_SINE_SAMPLE 60

/*uint32_t sin[NUM_SINE_SAMPLE]={32768, 36160, 39552, 42880, 46080, 49152, 51968, 54656, 57088, 59264
, 61120, 62656, 63872, 64768, 65344, 65472, 65344, 64768, 63872, 62656, 61120, 59264
, 57088, 54656, 51968, 49152, 46080, 42880, 39552, 36160, 32768, 29376, 25984, 22656
, 19456, 16384, 13568, 10880, 8448, 6272, 4416, 2880, 1664, 768, 192, 0, 192, 768, 1664
, 2880, 4416, 6272, 8448, 10880, 13568, 16384, 19456, 22656, 25984, 29376};							//sample sine function
*/

uint32_t sin_part[16]= {0, 1045, 2079, 3090, 4067, 5000, 5877, 6691, 7431, 8090, 8660,
                                9135, 9510, 9781, 9945, 10000};

uint32_t dac_sin[NUM_SINE_SAMPLE];


void dmaConfig(){

	for (uint32_t i = 0; i < NUM_SINE_SAMPLE; i++) {
		if(i<=15){
			dac_sin[i] = 512 + 512*sin_part[i]/10000;
			if(i==15)
				dac_sin[i] = 1023;
		}
		else if(i<=30){
			dac_sin[i] = 512 + 512*sin_part[30-i]/10000;
		}
		else if(i<=45){
			dac_sin[i] = 512 - 512*sin_part[i-30]/10000;
		}
		else{
			dac_sin[i] = 512 - 512*sin_part[60-i]/10000;
		}
		dac_sin[i] = (dac_sin[i]<<6);
		dac_sin[i] &= ~(0x1<<16);
	}
	dac_sin[50] = 1023;
	dac_sin[51] = 1023;
	dac_sin[52] = 1023;
	dac_sin[53] = 1023;
	dac_sin[54] = 1023;
	dac_sin[55] = 1023;
	dac_sin[56] = 1023;
	dac_sin[57] = 1023;
	dac_sin[58] = 1023;
	dac_sin[59] = 1023;

	GPDMA_LLI_Type LLI1;									//Linked List Item structure
	LLI1.SrcAddr = (uint32_t) dac_sin;							//source address
	LLI1.DstAddr = (uint32_t) &LPC_DAC->DACR;				//destination address
	LLI1.NextLLI = (uint32_t) &LLI1;						//next LLI address
	LLI1.Control = DMA_SIZE
				   | (2<<18) 								//source width 32 bits
				   | (2<<21) 								//destination width 32 bits
				   | (1<<26); 								//source increment
	GPDMA_Init();											//initialize GPDMA

	GPDMA_Channel_CFG_Type GPDMACfg;						//GPDMA configuration structure
	GPDMACfg.ChannelNum = 0;								//choose channel 0
	GPDMACfg.SrcMemAddr = (uint32_t) dac_sin;					//source physical memory address
	GPDMACfg.DstMemAddr = 0;								//blank destination memory address because it's not p2m
	GPDMACfg.TransferSize = DMA_SIZE;						//size of transfer
	GPDMACfg.TransferWidth = 0;								//blank transfer width because it's not m2m
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;			//set transfer type as m2p
	GPDMACfg.SrcConn = 0;									//blank peripheral source connection type because it's not p2m or p2p
	GPDMACfg.DstConn = GPDMA_CONN_DAC;						//peripheral destination connection type as DAC
	GPDMACfg.DMALLI = (uint32_t)&LLI1;						//set linked list to the structure LLI1
	GPDMA_Setup(&GPDMACfg);									//set up the channel according to the structure GPDMACfg

}
