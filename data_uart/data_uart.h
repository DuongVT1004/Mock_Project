/*
 * data_uart.h
 *
 *  Created on: Aug 11, 2023
 *      Author: Admin
 */

#ifndef DATA_UART_H_
#define DATA_UART_H_

#include "uart.h"

typedef enum {
	OF = 0,
	ON = 1,
} fan_state_t;

typedef enum {
	AUTOMATIC = 0,
	MANUAL = 1,
} fan_mode_t;

typedef enum {
	QUICK = 2,
	MEDIUM = 1,
	SLOW = 0,

} speed_level_t;

typedef enum
 {
     SUCCESS = 0x00u,
     ERROR  = 0x01u,
     INVALID = 0xFFu,
	 OFF = 0x02
 } my_status_t;

typedef struct{
	/* start of frame */
	uint8_t sof;
	/* txrx id */
	uint8_t id;
	/* Data length */
	uint8_t length;
	/* Fixed maximum length of received data to be 12 bytes */
	uint8_t data[6];
} data_struct_t;

void receive_data_processing(uint8_t *, data_struct_t *);

void transmit_data_processing(uint8_t *, data_struct_t *);

my_status_t turn_Fan_on_off(data_struct_t*, data_struct_t*);

my_status_t mode_Selection(data_struct_t*, data_struct_t*);

my_status_t level_Selection(data_struct_t*, data_struct_t*);

my_status_t fan_State(data_struct_t*, data_struct_t*, uint32_t);


#endif /* DATA_UART_H_ */
