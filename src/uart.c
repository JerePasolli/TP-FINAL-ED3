#include "LPC17xx.h"
#include "../inc/uart.h"
#include "lpc17xx_uart.h"

void uartConfig(void){
	//select pins 2.0 and 2.1 as UART
	LPC_PINCON->PINSEL4 |= (0xA);

	UART_CFG_Type uartConfig;
	uartConfig.Baud_rate = 9600;
	uartConfig.Databits = UART_DATABIT_8;
	uartConfig.Parity = UART_PARITY_NONE;
	uartConfig.Stopbits = UART_STOPBIT_1;

	UART_Init(LPC_UART1, &uartConfig);
	UART_TxCmd(LPC_UART1, ENABLE);
}

