/*
 * gpio.h
 *
 *  Created on: Aug 5, 2023
 *      Author: Admin
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "S32K144.h"
#include "stdbool.h"

uint8_t GPIO_Init(uint8_t , uint8_t , PORT_MemMapPtr, GPIO_MemMapPtr ,bool );

uint8_t Set_GPIO_Output(uint8_t ,GPIO_MemMapPtr);

uint8_t Clear_GPIO_Output(uint8_t , GPIO_MemMapPtr);

uint8_t Tonggle_GPIO_Output(uint8_t , GPIO_MemMapPtr);

uint8_t Read_GPIO_Input(uint8_t ,GPIO_MemMapPtr);

#endif /* GPIO_H_ */

