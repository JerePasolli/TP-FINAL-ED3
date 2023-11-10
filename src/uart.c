#include "LPC17xx.h"
#include "../inc/uart.h"
#include "lpc17xx_uart.h"

void uartConfig(void){
	LPC_PINCON->PINSEL4 |= (0xA);				//select pins 2.0 and 2.1 as UART
	UART_CFG_Type uartConfig;					//UART configuration structure
		uartConfig.Baud_rate = 9600;			//set baud rate to 9600 (AT1 mode)
		uartConfig.Databits = UART_DATABIT_8;	//set data bits to maximum
		uartConfig.Parity = UART_PARITY_NONE;	//disable parity selection
		uartConfig.Stopbits = UART_STOPBIT_1;	//set stop bits to 1
	UART_Init(LPC_UART1, &uartConfig);			//UART initialization: select UART1 peripheral with uartConfig settings
	UART_TxCmd(LPC_UART1, ENABLE);				//enable UART1 transmission
}

