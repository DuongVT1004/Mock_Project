/*
 * data_uart.c
 *
 *  Created on: Aug 11, 2023
 *      Author: Admin
 */
#include "data_uart.h"

fan_state_t state_fan = OF;
fan_mode_t fan_mode = AUTOMATIC;
speed_level_t level_manual = SLOW;

void receive_data_processing(uint8_t *receive, data_struct_t *rxFrame)
{
	if(receive[1] == 0x01 || receive[1] == 0x02 || receive[1] == 0x03)
	{
		rxFrame->sof = receive[0];
		rxFrame->id = receive[1];
		rxFrame->length = receive[2];
		rxFrame->data[0] = receive[3];
		rxFrame->data[1] = receive[4];
	}

	if(receive[1] == 0x04)
	{
		rxFrame->sof = receive[0];
		rxFrame->id = receive[1];
		rxFrame->length = receive[2];
		rxFrame->data[0] = receive[3];
		//rxFrame->data[1] = receive[4];
	}

	if(receive[1] < 0x01 || receive[1] > 0x04)
	{
		rxFrame->sof = receive[0];
		rxFrame->id = receive[1];
		rxFrame->length = receive[2];
		rxFrame->data[0] = receive[3];
		rxFrame->data[1] = receive[4];
	}
}

void transmit_data_processing(uint8_t *transmit, data_struct_t *txFrame)
{
	if(txFrame->length == 1)
	{
		transmit[0] = txFrame->sof;
		transmit[1] = txFrame->id;
		transmit[2] = txFrame->length;
		transmit[3] = txFrame->data[0];
		transmit[4] = txFrame->data[1];
	}

	if(txFrame->length == 5)
    {
	    transmit[0] = txFrame->sof;
		transmit[1] = txFrame->id;
		transmit[2] = txFrame->length;
		transmit[3] = txFrame->data[0];
		transmit[4] = txFrame->data[1];
		transmit[5] = txFrame->data[2];
		transmit[6] = txFrame->data[3];
		transmit[7] = txFrame->data[4];
		transmit[8] = txFrame->data[5];
	}
}

my_status_t turn_Fan_on_off(data_struct_t* rxFrame, data_struct_t* txFrame)
{
	txFrame->data[0] = 0;
	txFrame->sof = 0x02;
	txFrame->id = 0x81;
	txFrame->length = 1;
	txFrame->data[1] = 0x03;
	if(rxFrame->data[0] == 1) state_fan = 1;
	if(rxFrame->sof != 0x02 || rxFrame->id != 0x01 || rxFrame->length != 1 || rxFrame->data[1] != 0x03)
	{
		txFrame->data[0] = 0xFF;
		return INVALID;
	}
	if(rxFrame->data[0] > 1)
	{
		txFrame->data[0] = 1;
		return ERROR;
	}
//	if(rxFrame->data[0] == 0) state_fan = OF;
//	if(rxFrame->data[0] == 1) state_fan = ON;

	return SUCCESS;
}

my_status_t mode_Selection(data_struct_t* rxFrame, data_struct_t* txFrame)
{
	txFrame->data[0] = 0;
	txFrame->sof = 0x02;
	txFrame->id = 0x82;
	txFrame->length = 1;
	txFrame->data[1] = 0x03;
	if(rxFrame->sof != 0x02 || rxFrame->id != 0x02 || rxFrame->length != 1 || rxFrame->data[1] != 0x03)
	{
		txFrame->data[0] = 0xFF;
		return INVALID;
	}
	if(rxFrame->data[0] > 1)
	{
		txFrame->data[0] = 1;
		return ERROR;
	}
//	if(rxFrame->data[0] == 0) fan_mode = AUTOMATIC;
//	if(rxFrame->data[0] == 1) fan_mode = MANUAL;
	if(state_fan == 0)
	{
		txFrame->data[0] = 2;
		return OFF;
	}
	return SUCCESS;
}

my_status_t level_Selection(data_struct_t *rxFrame, data_struct_t *txFrame)
{
	txFrame->data[0] = 0;
	txFrame->sof = 0x02;
	txFrame->id = 0x83;
	txFrame->length = 1;
	txFrame->data[1] = 0x03;
	if(rxFrame->sof != 0x02 || rxFrame->id != 0x03 || rxFrame->length != 1 || rxFrame->data[1] != 0x03)
	{
		txFrame->data[0] = 0xFF;
		return INVALID;
	}
	if(rxFrame->data[0] > 2)
	{
		txFrame->data[0] = 1;
		return ERROR;
	}
//	if(rxFrame->data[0] == 0) level_manual = SLOW;
//	if(rxFrame->data[0] == 1) level_manual = MEDIUM;
//	if(rxFrame->data[0] == 2) level_manual = QUICK;
	if(state_fan == 0)
	{
		txFrame->data[0] = 2;
		return OFF;
	}
	return SUCCESS;
}

my_status_t fan_State(data_struct_t *rxFrame, data_struct_t *txFrame, uint32_t adc_value)
{
	txFrame->sof = 0x02;
	txFrame->id = 0x84;
	txFrame->length = 5;
//	txFrame->data[0] = 0x03;
	txFrame->data[0] = 0;
	if(rxFrame->sof != 0x02 || rxFrame->id != 0x04 || rxFrame->length != 0 || rxFrame->data[0] != 0x03)
	{
		txFrame->data[0] = 0xFF;
		txFrame->length = 1;
		txFrame->data[1] = 0x03;
		return INVALID;
	}
	txFrame->data[1] = state_fan;
	txFrame->data[2] = fan_mode;
	txFrame->data[3] = level_manual;
	if(adc_value < 5)
	{
		txFrame->data[4] = 0;
	}
	else if(adc_value >= 5 && adc_value <= 50)
	{
		txFrame->data[4] = adc_value;
	}
	else
	{
		txFrame->data[4] = 0xFF;
	}
	txFrame->data[5] = 0x03;
	return SUCCESS;
}


/*
 * data_uart.c
 *
 *  Created on: Aug 18, 2023
 *      Author: Admin
 */


