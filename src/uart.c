#include "LPC17xx.h"
#include "../inc/uart.h"
#include "lpc17xx_uart.h"

void uartConfig(void){
	//select pins 0.10 and 0.11 as UART
	LPC_PINCON->PINSEL0 |= (1<<20) | (1<<22);
	LPC_PINCON->PINMODE0 |= (1<<21) | (1<<23);

	UART_CFG_Type uartConfig;
	UART_FIFO_CFG_Type uartFIFOConfig;

	//uartConfig.Baud_rate = 9600;
	//uartConfig.Databits = UART_DATABIT_8;
	//uartConfig.Parity = UART_PARITY_NONE;
	//uartConfig.Stopbits = UART_STOPBIT_1;
	UART_ConfigStructInit(&uartConfig);
	UART_Init(LPC_UART2, &uartConfig);
	UART_FIFOConfigStructInit(&uartFIFOConfig);
	UART_FIFOConfig(LPC_UART2, &uartFIFOConfig);
	UART_TxCmd(LPC_UART2, ENABLE);
	UART_IntConfig(LPC_UART2,  UART_INTCFG_RBR, ENABLE);
	UART_IntConfig(LPC_UART2,  UART_INTCFG_RLS, ENABLE);
	NVIC_EnableIRQ(UART2_IRQn);
}

