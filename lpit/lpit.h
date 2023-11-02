/*
 * lpit.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Admin
 */

#ifndef LPIT_H_
#define LPIT_H_

#include "S32K144.h"
#include "stdbool.h"
#include "interrupt_manager.h"

#define MAX_PERIOD_COUNT 0xFFFFFFFF     /* For checking overflow */
#define STATUS_SUCCESS 0
#define STATUS_ERROR 1

uint8_t lpit_clock_init(void);
void LPIT_Init(void);
void LPIT_Deinit(void);
uint8_t LPIT_ConfigChannel(uint8_t ,bool);
uint8_t enable_lpit(uint32_t );

#endif /* LPIT_H_ */
