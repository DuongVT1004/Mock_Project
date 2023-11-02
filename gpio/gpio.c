/*
 * gpio.c
 *
 *  Created on: Aug 5, 2023
 *      Author: Admin
 */

#include "gpio.h"

uint8_t GPIO_Init(uint8_t pinNumber, uint8_t portIndex, PORT_MemMapPtr port, GPIO_MemMapPtr gpio, bool direction)
{
	PCC->PCCn[portIndex] = PCC_PCCn_CGC_MASK;
	port->PCR[pinNumber] |= PORT_PCR_MUX(1);
	if(direction == true)
	{
		gpio->PDDR |= (uint32_t)(1 << pinNumber);
	}
	else
	{
		gpio->PDDR &= ~(uint32_t)(1 << pinNumber);
	}
	return 0;
}

uint8_t Set_GPIO_Output(uint8_t pinNumber, GPIO_MemMapPtr gpio)
{
	gpio->PSOR |= (uint32_t)(1 << pinNumber);
	return 0;
}

uint8_t Clear_GPIO_Output(uint8_t pinNumber, GPIO_MemMapPtr gpio)
{
	gpio->PCOR |= (uint32_t)(1 << pinNumber);
	return 0;
}

uint8_t Tonggle_GPIO_Output(uint8_t pinNumber, GPIO_MemMapPtr gpio)
{
	gpio->PTOR |= (uint32_t)(1 << pinNumber);
	return 0;
}

uint8_t Read_GPIO_Input(uint8_t pinNumber, GPIO_MemMapPtr gpio)
{
	if( (gpio->PDIR & (uint32_t)(1 << pinNumber)) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}





