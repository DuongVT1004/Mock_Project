/*
 * uart.c
 *
 *  Created on: Aug 7, 2023
 *      Author: Admin
 */
#include "uart.h"

LPUART_Type * const g_lpuartBase[LPUART_INSTANCE_COUNT] = LPUART_BASE_PTRS;

uint8_t UART_Clock_Init(uint8_t uartIndex)
{
	//SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV2(3);
	PCC->PCCn[uartIndex] &=~ PCC_PCCn_CGC_MASK;
    PCC->PCCn[uartIndex] |= PCC_PCCn_PCS(1);
	PCC->PCCn[uartIndex] |= PCC_PCCn_CGC_MASK;
	//PCC->PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK;
	return 0;
}

void UART_Config_Rx(PORT_MemMapPtr portRx, uint8_t pinNumber, uint8_t muxRx)
{
	PCC->PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK;
	portRx->PCR[pinNumber] |= PORT_PCR_MUX(muxRx);
	//portRx->PCR[pinNumber] |= PORT_PCR_PE(1) | PORT_PCR_PS(1);
	//return 0;
}

void UART_Config_Tx(PORT_MemMapPtr portTx, uint8_t pinNumber, uint8_t muxTx)
{
	PCC->PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK;
	portTx->PCR[pinNumber] |= PORT_PCR_MUX(muxTx);
	//return 0;
}

uint8_t UART_Config_Parity(uint8_t instance, uint32_t parityMode)
{
	LPUART_Type * base = g_lpuartBase[instance];

	//if((instance < 0) || (instance > 2)) return 1;
	if((parityMode != 0) && (parityMode != 2) && (parityMode != 3)) return 1;
	if(parityMode == 0) // No Parity
	{
		base->CTRL &= ~((uint32_t)0x03u);
	}
	if(parityMode == 2) // Even Parity
	{
		base->CTRL |= (uint32_t)0x02u;
	}
	if(parityMode == 3) // Odd Parity
	{
		base->CTRL |= (uint32_t)0x03u;
	}

	return 0;
}

uint8_t UART_Config_StopBit(uint8_t instance, uint32_t stopBit)
{
    LPUART_Type * base = g_lpuartBase[instance];

    //if((instance < 0) || (instance > 2)) return 1;
    //if((stopBit < 0) || (stopBit > 1)) return 1;
    if(stopBit == 0) // One Stop Bit
    {
        base->BAUD &= ~((uint32_t)(1 << 13));
    }else  // Two Stop Bit
    {
        base->BAUD |= (uint32_t)(1 << 13);
    }
    return 0;
}

uint8_t UART_Config_BitCountPerChar(uint8_t instance, uint32_t bitCountPerChar, bool parity)
{
    LPUART_Type * base = g_lpuartBase[instance];

    //if((instance < 0) || (instance > 2)) return 1;
    if(parity) bitCountPerChar++;
    //if(bitCountPerChar < 0 || bitCountPerChar > 2) return 1;
    if(bitCountPerChar == 2)
    {
        base->BAUD |= (uint32_t)(1 << 29) ; // 10 bit
    }
    if(bitCountPerChar == 0) // 8 bit
    {
        base->CTRL &= ~((uint32_t)(1 << 4));
        base->BAUD &= ~((uint32_t)(1 << 29));
    }
    if(bitCountPerChar == 1)  // 9 bit
    {
        base->CTRL |= (uint32_t)(1 << 4);
        base->BAUD &= ~((uint32_t)(1 << 29));
    }

    return 0;
}

uint8_t UART_Config_Baudrate(uint8_t instance, uint32_t baudRate)
{
    LPUART_Type * base = g_lpuartBase[instance];
//    uint32_t baudDiff, tempDiff, calculatedBaud;
//    uint32_t SBR_temp;
//    uint8_t i;

    uint32_t OSR_value = 16;
    uint32_t SBR_value = 8000000/(baudRate * OSR_value);
    //calculatedBaud = 12000000/(OSR_value * SBR_value);
//    if(calculatedBaud < baudRate)
//    {
//        baudDiff = baudRate - calculatedBaud;
//    }
//    else
//    {
//        baudDiff = calculatedBaud - baudRate;
//    }
//    for (i = 5; i <= 32; i++)
//    {
//        SBR_temp = 8000000/(baudRate * i);
//        calculatedBaud = 8000000/(i * SBR_temp);
//        if(calculatedBaud < baudRate)
//        {
//            tempDiff = baudRate - calculatedBaud;
//        }
//        else
//        {
//            tempDiff = calculatedBaud - baudRate;
//        }
//        if(tempDiff <= baudDiff)
//        {
//            baudDiff = tempDiff;
//            OSR_value = i;
//            SBR_value = SBR_temp;
//        }
//    }
//    if(OSR_value < 8)
//    {
//        base->BAUD = LPUART_BAUD_BOTHEDGE(1);
//    }
    OSR_value--;
    base->BAUD &= ~LPUART_BAUD_OSR_MASK;
    base->BAUD |= LPUART_BAUD_OSR(OSR_value);
    base->BAUD &= ~LPUART_BAUD_SBR_MASK;
    base->BAUD |= LPUART_BAUD_SBR(SBR_value);

    return 0;
}

uint8_t UART_ReceiveDataPolling(uint8_t instance, uint8_t *rxBuff, uint8_t rxSize)
{
	uint8_t i = 0;
//    if (instance >= LPUART_INSTANCE_COUNT)
//    {
//        return 0xFF;
//    }
//
//    if (rxBuff == NULL)
//    {
//        return 0xFF;
//    }
//
//    if (rxSize <= 0U)
//    {
//        return 0xFF;
//    }

    LPUART_Type * base = g_lpuartBase[instance];

    /* Enable the LPUART receiver */
    base->CTRL = (base->CTRL & ~LPUART_CTRL_RE_MASK) | (1UL << LPUART_CTRL_RE_SHIFT);
    /* Wait for the register write operation to complete */
    while((base->CTRL & LPUART_CTRL_RE_MASK) != LPUART_CTRL_RE_MASK) {}

    while (i < rxSize)
    {
        while((LPUART1->STAT & LPUART_STAT_RDRF_MASK)>>LPUART_STAT_RDRF_SHIFT==0);

        rxBuff[i] = base->DATA;
//        ++rxBuff;
//        --rxSize;
        i++;
    }

    /* Disable the LPUART receiver */
    base->CTRL = (base->CTRL & ~LPUART_CTRL_RE_MASK) | (0UL << LPUART_CTRL_RE_SHIFT);
    /* Wait for the register write operation to complete */
    while((base->CTRL & LPUART_CTRL_RE_MASK) == LPUART_CTRL_RE_MASK) {}

    return 0;
}

uint8_t UART_Init(uint8_t instance, uart_config_t * uartConfig)
{
    /* Use the code from Assignment 9.3 */
    LPUART_Type * base = g_lpuartBase[instance];

    /* Step 1: Check the validation of the input parameters */
    // TODO: Implement the exception catching for the input instance if needed
    //if(instance < 0 || instance > 2) return 1;
    /* Step 2: Configure all initializing parameters for LPUART */
    // TODO: Set the default oversampling ratio (16) and baud-rate divider (4)
    base->BAUD = LPUART_BAUD_OSR(0) | LPUART_BAUD_SBR(4) ;

    // TODO: Clear the error/interrupt flags
    base->STAT = 0xC01FC000;

    // TODO: Reset all features/interrupts by default
    base->CTRL = 0U;

    // TODO: Reset match addresses
    base->MATCH = 0U;

    /* Step 3: Initialize the parameters of the LPUART config structure with desired data */
    // TODO: Set baud rate for LPUART using the code from Assignment 9.2
    UART_Config_Baudrate(instance, uartConfig->baudRate);
    // TODO: Set bit count for LPUART using the code from Assignment 9.1 base on the enablement of parity mode.
    // if(uartConfig->parityMode == 0)
    // {
    //     UART_SetBitCountPerChar(instance, uartConfig->bitCountPerChar, false);
    // }else
    // {
    //     UART_SetBitCountPerChar(instance, uartConfig->bitCountPerChar, true);
    // }
    UART_Config_BitCountPerChar(instance, uartConfig->bitPerChar, false);
    // TODO: Set parity mode for LPUART using the code from Assignment 9.1
    UART_Config_Parity(instance, uartConfig->parity);
    // TODO: Set stop bit number for LPUART using the code from Assignment 9.1
    UART_Config_StopBit(instance, uartConfig->stopBit);
    // TODO: Enable interrupt for given LPUART instance using INT_SYS_EnableIRQ() function.
    //INT_SYS_EnableIRQ(g_lpuartRxTxIrqId[instance]);
    return 0;
}

uint8_t UART_SendDataPolling(uint8_t instance, uint8_t *txBuff, uint8_t txSize)
{
    uint8_t i = 0;
    LPUART_Type * base = g_lpuartBase[instance];

    // if (instance >= LPUART_INSTANCE_COUNT)
    // {
    //     return 0xFF;
    // }

    // if (txBuff == NULL)
    // {
    //     return 0xFF;
    // }

    // if (txSize <= 0U)
    // {
    //     return 0xFF;
    // }

    /* Enable the LPUART transmitter */
    base->CTRL = (base->CTRL & ~LPUART_CTRL_TE_MASK) | (1UL << LPUART_CTRL_TE_SHIFT);
    /* Wait for the register write operation to complete */
    while((base->CTRL & LPUART_CTRL_TE_MASK) != LPUART_CTRL_TE_MASK) {}

    while (i < txSize)//txSize > 0U)
    {
        while (((base->STAT & LPUART_STAT_TDRE(1)) >> LPUART_STAT_TDRE_WIDTH) == 0)//!((bool)(base->STAT & LPUART_STAT_TDRE_MASK) != 0))
        {}

        base->DATA= txBuff[i];
        // ++txBuff;
        // --txSize;
        i++;
    }

    /* Disable the LPUART transmitter */
    base->CTRL = (base->CTRL & ~LPUART_CTRL_TE_MASK) | (0UL << LPUART_CTRL_TE_SHIFT);
    /* Wait for the register write operation to complete */
    while((base->CTRL & LPUART_CTRL_TE_MASK) == LPUART_CTRL_TE_MASK) {}

    return 0;
}

