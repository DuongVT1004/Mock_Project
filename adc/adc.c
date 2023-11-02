/*
 * adc.c
 *
 *  Created on: Aug 14, 2023
 *      Author: Admin
 */

#include "adc.h"

uint8_t ADC_clock_init(uint8_t portIndex)
{
	/* ADC init port */
	//port->PCR[pinNumber] |= PORT_PCR_MUX(muxNumber);
	/* ADC init clock pheripheral */
	//SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV2(3);
	PCC->PCCn[portIndex] &=~ PCC_PCCn_CGC_MASK;
	PCC->PCCn[portIndex] |= PCC_PCCn_PCS(1); //FIDRCLK
	PCC->PCCn[portIndex] |= PCC_PCCn_CGC_MASK;
	return 0;
}

uint8_t ADC_init_config(adc_config_t* adc)
{
	ADC0->CFG1 &= (uint32_t)(0x6F);
	ADC0->CFG1 |= (ADC_CFG1_ADIV(adc->clockDivide) | ADC_CFG1_MODE(adc->resolution) | ADC_CFG1_ADICLK(adc->inputClock));

	ADC0->CFG2 &= ~((uint32_t)0xFF);
	ADC0->CFG2 |= ADC_CFG2_SMPLTS(adc->sampleTime);

	ADC0->SC2 &= ~((uint32_t)0x47);
	ADC0->SC2 |= (ADC_SC2_ADTRG(adc->triggerType) | ADC_SC2_REFSEL(adc->voltageRef)| ADC_SC2_DMAEN(adc->dmaEnable));

	return 0;
}

uint8_t ADC_DeInit(void)
{
    uint8_t i = 0;
    ADC0->CFG1 = (uint32_t)0;
    ADC0->CFG2 = (uint32_t)0x0C;
    for (i = 0; i < ADC_SC1_COUNT; i++)
    {
        ADC0->SC1[i] = (uint32_t)0x3F;
    }
    ADC0->SC2 = (uint32_t)0;
    ADC0->SC3 = (uint32_t)0;

    return 0;
}

uint8_t ADC_ConfigChannel(uint8_t channel, uint8_t inputChannel, bool ItrEnable)
{
	uint32_t tempVal;
	tempVal  = ADC0->SC1[channel];
	tempVal &= ~((uint32_t)0x3F);
	tempVal |= (ADC_SC1_AIEN(ItrEnable) | ADC_SC1_ADCH(inputChannel));
	if(ItrEnable == true)
	{
		INT_SYS_EnableIRQ(ADC0_IRQn);
	}
	ADC0->SC1[channel] = tempVal;
	return 0;
}

void ADC_Complete(void) {
	uint32_t regValue = ADC0->SC2;
	    regValue = (regValue & ADC_SC2_ADACT_MASK);

	    while (regValue != 0x00U)
	    {
	        /* Wait for conversion to finish */
	        regValue = (uint32_t)ADC0->SC2;
	        regValue = (regValue & ADC_SC2_ADACT_MASK);
	    }
}

void ADC_Start_Conversion(uint8_t channel, uint8_t inputChannel, bool ItrEnable)
{
	ADC_ConfigChannel(channel, inputChannel, ItrEnable);
	ADC_Complete();
}

uint32_t ADC_GetValue(uint8_t channel)
{
	uint32_t value;
	value = ADC0->R[channel] & ADC_R_D_MASK;
	return value;
}

void transform_adc_tem(uint32_t *adc_value)
{
	uint32_t temp;
	temp = (uint32_t)((50 * (*adc_value))/4096);
	*adc_value = temp;
}
