/*
 * uart.h
 *
 *  Created on: Aug 7, 2023
 *      Author: Admin
 */

#ifndef UART_H_
#define UART_H_
#include "S32K144.h"
#include "stdbool.h"

typedef struct
{
	uint8_t parity;
	uint8_t stopBit;
	uint8_t bitPerChar;
	uint32_t baudRate;
} uart_config_t;

uint8_t UART_Clock_Init(uint8_t);
void UART_Config_Rx(PORT_MemMapPtr, uint8_t, uint8_t);
void UART_Config_Tx(PORT_MemMapPtr, uint8_t, uint8_t);
uint8_t UART_Config_Parity(uint8_t, uint32_t);
uint8_t UART_Config_StopBit(uint8_t, uint32_t);
uint8_t UART_Config_BitCountPerChar(uint8_t, uint32_t, bool);
uint8_t UART_Config_Baudrate(uint8_t, uint32_t);
uint8_t UART_Config_Interrupt(uint8_t, bool);
uint8_t UART_ReceiveDataPolling(uint8_t , uint8_t *, uint8_t);
uint8_t UART_Init(uint8_t , uart_config_t *);
uint8_t UART_SendDataPolling(uint8_t, uint8_t *, uint8_t);
#endif /* UART_H_ */

