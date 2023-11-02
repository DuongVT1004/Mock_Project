/*
 * fan.c
 *
 *  Created on: Aug 18, 2023
 *      Author: Admin
 */

#include "fan.h"

volatile extern fan_state_t state_fan;
volatile extern fan_mode_t fan_mode;
volatile extern speed_level_t level_manual;

static volatile speed_level_t value_pre;

speed_level_t speed_mode(uint32_t tem)
{
	if(tem < 16)
	{
		set_pwm(625);
		return SLOW;
	}
	else if(tem <= 30)
	{
		set_pwm(250);
		return MEDIUM;
	}
	else
	{
		set_pwm(125);
		return QUICK;
	}
}

uint32_t getADC_and_transform()
{
	uint32_t tem_value = ADC_GetValue(0);
	transform_adc_tem(&tem_value);
	return tem_value;
}

void speed_manual(speed_level_t level_manual)
{
	if(level_manual == SLOW)
	{
		set_pwm(625);
	}
	else if(level_manual == MEDIUM)
	{
		set_pwm(250);
	}
	else
	{
		set_pwm(125);
	}
}

void clock_fan_init()
{
	SOSC_init_8MHz();
	SPLL_init_160MHz();
	NormalRUNmode_80MHz();
}

void uart_fan_init(uart_config_t uart1)
{
	UART_Clock_Init(PCC_LPUART1_INDEX);
	UART_Config_Rx(PORTC, 6, 2);
	UART_Config_Tx(PORTC, 7, 2);
	uart1.baudRate = 9600;
	uart1.bitPerChar = 0;
	uart1.parity = 0;
	uart1.stopBit = 0;
	UART_Init(1, &uart1);
}

void adc_fan_init(adc_config_t adc)
{
	ADC_clock_init(PCC_ADC0_INDEX);
	adc.clockDivide = 0x01;
	adc.dmaEnable = false;
	adc.inputClock = 0x00;
	adc.resolution = 0x01;
	adc.sampleTime = 0xFF;
	adc.triggerType = 0x00;
	adc.voltageRef = 0x00;
	ADC_init_config(&adc);
	ADC_ConfigChannel(0, 12, true);
}

void gpio_fan_init()
{
	GPIO_Init(15, PCC_PORTD_INDEX, PORTD, PTD, true);
	GPIO_Init(0, PCC_PORTD_INDEX, PORTD, PTD, true);
	Set_GPIO_Output(0, PTD);
	Set_GPIO_Output(15, PTD);
}

void pwm_fan_init()
{
	PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
	PORTD->PCR[16] |= PORT_PCR_MUX(2);
	FTM_Init_Clock(PCC_FTM0_INDEX);
	FTM_Init_Clock(PCC_FTM0_INDEX);
	FTM_Init();
	FTM_CH1_PWM_init();
	start_FTM0_counter();
}

void write_to_flash()
{
	erase_and_write(state_fan, fan_mode, level_manual);
}

void read_from_flash()
{
	assign_value_from_flash(&state_fan, &fan_mode, &level_manual);
}

void fan_set_off()
{
	INT_SYS_DisableIRQ(ADC0_IRQn);
	FTM0->CONTROLS[1].CnV = 625;
	Set_GPIO_Output(0, PTD);
	Clear_GPIO_Output(15, PTD);
}

void fan_set_on()
{
	Set_GPIO_Output(15, PTD);
	Clear_GPIO_Output(0, PTD);
}

uint32_t ADC_process()
{
	uint32_t value = getADC_and_transform();
	if(speed_mode(value) == SLOW)
	{
		level_manual = SLOW;
	}
	else if(speed_mode(value) == MEDIUM)
	{
		level_manual = MEDIUM;
	}
	else
	{
		level_manual = QUICK;
	}
	if(value_pre != level_manual)
	{
		write_to_flash();
	}
	value_pre = level_manual;
	ADC_ConfigChannel(0, 12, true);
	return value;
}

void fan_process()
{
	if(state_fan == 0)
	{
		fan_set_off();
	}
	else
	{
		fan_set_on();
	    if(fan_mode == 0)
	    {
	    	INT_SYS_EnableIRQ(ADC0_IRQn);
	    }
	    else
	    {
	    	INT_SYS_DisableIRQ(ADC0_IRQn);
	    	speed_manual(level_manual);
	    }
	}
}

