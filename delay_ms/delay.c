/*
 * delay.c
 *
 *  Created on: Aug 20, 2023
 *      Author: Admin
 */

#include "delay.h"

void Set_SysTick()
{
	S32_SysTick -> RVR |= 79999;
	S32_SysTick-> CVR |= 0;
	S32_SysTick -> CSR |= (uint32_t)0x05;
}

void delay_SysTick(uint32_t a)
{
	uint32_t time = 0;
	Set_SysTick();
	while(time != a)
	{
		while(((S32_SysTick -> CSR) & (1 << 16)) == 0);
		time++;
	}
}
