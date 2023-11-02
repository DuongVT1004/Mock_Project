/*
 * pwm.c
 *
 *  Created on: Aug 10, 2023
 *      Author: Admin
 */

#include "pwm.h"

void FTM_Init_Clock(uint8_t FTMindex)
{
	//SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV1(3); // FIRC = 48M -> FIRC_DIV1 = 3 -> clock timer 12M
	PCC->PCCn[FTMindex] &= ~PCC_PCCn_CGC_MASK;
	PCC->PCCn[FTMindex] |= PCC_PCCn_PCS(1); // FIRC_DIV1
	PCC->PCCn[FTMindex] |= PCC_PCCn_CGC_MASK;
}

void FTM_Init(void)
{
	FTM0->MODE |= FTM_MODE_WPDIS_MASK; /* Write protect to registers disabled (default) */
	FTM0->SC = 0x00030007; // PS = 5
	FTM0->COMBINE = 0x00000000;/* FTM mode settings used: DECAPENx, MCOMBINEx, COMBINEx=0 */
	FTM0->POL = 0x00000000; /* Polarity for all channels is active high (default) */
	FTM0->MOD = 625-1 ; // cycle = 10ms
}

void FTM_CH1_PWM_init(void) {
	FTM0->CONTROLS[1].CnSC = 0x00000028; /* FTM0 ch1: edge-aligned PWM, low true pulses */
	FTM0->CONTROLS[1].CnV = 625; // duty 90%
}

uint8_t start_FTM0_counter(void) {
	FTM0->SC |= FTM_SC_CLKS(3);
	return 0;
}

uint8_t set_pwm(uint16_t pwm_value)
{
	if(pwm_value > 625) return 1;
	FTM0->CONTROLS[1].CnV = pwm_value;
	return 0;
}

