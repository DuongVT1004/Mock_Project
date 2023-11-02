/*!
** Copyright 2020 NXP
** @file main.c
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including necessary configuration files. */
#include "fan.h"

uint8_t rxBuf[10];
uint8_t txBuf[10];

data_struct_t rxFrame;
data_struct_t txFrame;

extern fan_state_t state_fan;
extern fan_mode_t fan_mode;
extern speed_level_t level_manual;

volatile uint32_t tem_value;

//void LPIT0_Ch0_IRQHandler(void)
//{
//	LPIT0->MSR |= (uint32_t)(1 << 0);
//	ADC_ConfigChannel(0, 12, true);
//}

void ADC0_IRQHandler(void)
{
	tem_value = ADC_process();
}

int main(void)
{
	//clock
	clock_fan_init();

	//uart
	uart_config_t uart1;
	uart_fan_init(uart1);

	// pwm
	pwm_fan_init();

	//gpio
	gpio_fan_init();

	// ADC init
	adc_config_t adc;
	adc_fan_init(adc);

	//lpit init
	//lpit_clock_init();
	//enable_lpit(1000);

	//S32_NVIC->IP[49] = 15;
	//S32_NVIC->IP[39] = 14;
	fan_set_off();
	read_from_flash();

	while(1)
	{
		memset(rxBuf, 0, 10);
	    memset(txBuf, 0, 10);
	    UART_ReceiveDataPolling(1, rxBuf, 5);
		receive_data_processing(rxBuf, &rxFrame);
		switch(rxFrame.id)
		{
	    	case 0x01:
			   	turn_Fan_on_off(&rxFrame, &txFrame);
			   	transmit_data_processing(txBuf, &txFrame);
			   	UART_SendDataPolling(1, txBuf, 5);
			   	if(rxFrame.data[0] == 0) state_fan = OF;
			   	if(rxFrame.data[0] == 1) state_fan = ON;
			    break;
			case 0x02:
			    mode_Selection(&rxFrame, &txFrame);
			   	transmit_data_processing(txBuf, &txFrame);
			   	UART_SendDataPolling(1, txBuf, 5);
			   	if(rxFrame.data[0] == 0) fan_mode = AUTOMATIC;
			   	if(rxFrame.data[0] == 1) fan_mode = MANUAL;
			    break;
			case 0x03:
			   	level_Selection(&rxFrame, &txFrame);
			   	transmit_data_processing(txBuf, &txFrame);
			   	UART_SendDataPolling(1, txBuf, 5);
			   	if(rxFrame.data[0] == 0) level_manual = SLOW;
			   	if(rxFrame.data[0] == 1) level_manual = MEDIUM;
			   	if(rxFrame.data[0] == 2) level_manual = QUICK;
			    break;
			case 0x04:
				fan_State(&rxFrame, &txFrame, tem_value);
				transmit_data_processing(txBuf, &txFrame);
				UART_SendDataPolling(1, txBuf, 9);
			    break;
			default:
			    break;
		}
		write_to_flash();
		fan_process();

	}
	return 0;
}



