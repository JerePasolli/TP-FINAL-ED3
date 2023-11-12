#include "LPC17xx.h"
#include "../inc/uart.h"
#include "lpc17xx_uart.h"

void uartConfig(void){
	LPC_PINCON->PINSEL0 |= (0xA<<21);				//select pins 0.10 and 0.11 as UART
	UART_CFG_Type uartConfig;					//UART configuration structure
		uartConfig.Baud_rate = 9600;			//set baud rate to 9600 (AT1 mode)
		uartConfig.Databits = UART_DATABIT_8;	//set data bits to maximum
		uartConfig.Parity = UART_PARITY_NONE;	//disable parity selection
		uartConfig.Stopbits = UART_STOPBIT_1;	//set stop bits to 1
	UART_Init(LPC_UART2, &uartConfig);			//UART initialization: select UART2 peripheral with uartConfig settings
	UART_TxCmd(LPC_UART2, ENABLE);				//enable UART2 transmission
}

