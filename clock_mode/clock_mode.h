/*
 * clock.h
 *
 *  Created on: Aug 17, 2023
 *      Author: Admin
 */

#ifndef CLOCK_MODE_H_
#define CLOCK_MODE_H_

#include "S32K144.h"

void SOSC_init_8MHz(void);
void SPLL_init_160MHz(void);
void NormalRUNmode_80MHz (void);

#endif /* CLOCK_MODE_H_ */
