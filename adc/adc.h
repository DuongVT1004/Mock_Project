/*
 * adc.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Admin
 */

#ifndef ADC_H_
#define ADC_H_
#include "S32K144.h"
#include "stdbool.h"
#include "interrupt_manager.h"

typedef struct
{
    uint8_t clockDivide;
    uint8_t sampleTime;
    uint8_t resolution;
    uint8_t inputClock;
    uint8_t triggerType;
    uint8_t voltageRef;
    bool    dmaEnable;
} adc_config_t;

uint8_t ADC_clock_init(uint8_t);
uint8_t ADC_init_config(adc_config_t*);
uint8_t ADC_DeInit(void);
uint8_t ADC_ConfigChannel(uint8_t, uint8_t, bool);
void ADC_Complete(void);
void ADC_Start_Conversion(uint8_t channel, uint8_t inputChannel, bool ItrEnable);
uint32_t ADC_GetValue(uint8_t);
void transform_adc_tem(uint32_t *);

#endif /* ADC_H_ */
