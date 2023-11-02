/*
 * lpit.c
 *
 *  Created on: Aug 14, 2023
 *      Author: Admin
 */

#include "lpit.h"


uint8_t lpit_clock_init(void)
{
	//SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV2(1);
	PCC->PCCn[PCC_LPIT_INDEX] &=~ PCC_PCCn_CGC_MASK;
	PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_PCS(1); //FIDRCLK
	PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_CGC_MASK;
	return 0;
}

void LPIT_Init(void)
{
    LPIT0->MCR |=  LPIT_MCR_SW_RST_MASK;

    uint8_t delay = 4;
    uint8_t i;

    for(i = 0; i < delay; i++);

    LPIT0->MCR &= ~LPIT_MCR_SW_RST_MASK;

    LPIT0->MCR |= (uint32_t)0x01u;

    for(i = 0; i < delay; i++);
}

void LPIT_Deinit(void)
{
    LPIT0->MCR &= ~((uint32_t)0x01u);
}

uint8_t LPIT_ConfigChannel(uint8_t channel,
                 bool isInterruptEnabled)
{
    const IRQn_Type lpitIrqId[] = LPIT_IRQS;

    uint8_t retVal = STATUS_SUCCESS;

    if(channel > 3)
    {
        retVal = STATUS_ERROR;
        return retVal;
    }

    LPIT0->TMR[channel].TCTRL &= ~((uint32_t)0xC);
    LPIT0->TMR[channel].TCTRL |=  LPIT_TMR_TCTRL_MODE(0);

    if (isInterruptEnabled)
    {
         INT_SYS_EnableIRQ(lpitIrqId[channel]);
         LPIT0->MIER |= (uint32_t)(1 << channel);
    }
    else
    {
        INT_SYS_DisableIRQ(lpitIrqId[channel]);
        LPIT0->MIER &= ~((uint32_t)(1 << channel));
    }

    return retVal;
}

uint8_t enable_lpit(uint32_t milisec)
{
	uint64_t count = 0;
	count = (uint64_t)48000*milisec;
	if(count-1 > MAX_PERIOD_COUNT) return STATUS_ERROR;
	LPIT_Init();
	LPIT_ConfigChannel(1, true);
	LPIT0->TMR[1].TVAL = (uint32_t)(count-1);
	LPIT0->SETTEN |= (uint32_t)(2u);
	return 0;
}
