#include "LPC17xx.h"
#include "../inc/uart.h"
#include "lpc17xx_uart.h"

void uartConfig(void){
	LPC_PINCON->PINSEL0 |= (1<<20) | (1<<22);			//select pins 0.10 and 0.11 as UART
	LPC_PINCON->PINMODE0 |= (1<<21) | (1<<23);
	UART_CFG_Type uartConfig;							//uart configuration structure
	UART_FIFO_CFG_Type uartFIFOConfig;					//uart fifo configuration structure
	UART_ConfigStructInit(&uartConfig);					//use default values: 9600 baud rate, 8 data bits, 1 stop bit, no parity
	UART_Init(LPC_UART2, &uartConfig);					//initialize uart 2
	UART_FIFOConfigStructInit(&uartFIFOConfig);			//use default fifo values
	UART_FIFOConfig(LPC_UART2, &uartFIFOConfig);		//use fifo configuration
	UART_TxCmd(LPC_UART2, ENABLE);						//enable transmission
	UART_IntConfig(LPC_UART2,  UART_INTCFG_RBR, ENABLE);//enable interrupt on receiver buffer register
	UART_IntConfig(LPC_UART2,  UART_INTCFG_RLS, ENABLE);//enable interrupt on receiver line status
	NVIC_EnableIRQ(UART2_IRQn);							//enable interruptions on uart 2
}

