/*
 * pwm.h
 *
 *  Created on: Aug 10, 2023
 *      Author: Admin
 */

#ifndef PWM_H_
#define PWM_H_

#include "S32K144.h"

void FTM_Init_Clock(uint8_t);
void FTM_Init(void);
void FTM_CH1_PWM_init(void);
uint8_t start_FTM0_counter(void);
uint8_t set_pwm(uint16_t);

#endif /* PWM_H_ */
