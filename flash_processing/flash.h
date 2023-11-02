/*
 * flash.h
 *
 *  Created on: Aug 21, 2023
 *      Author: Admin
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "S32K144.h"

void erase_and_write(uint8_t, uint8_t , uint8_t ); // 0x1000E000, 0x1000E001, 0x1000E002
void assign_value_from_flash();

#endif /* FLASH_H_ */
