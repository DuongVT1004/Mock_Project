/*
 * fan.h
 *
 *  Created on: Aug 18, 2023
 *      Author: Admin
 */

#ifndef FAN_H_
#define FAN_H_

#include "S32K144.h"
#include "clock_mode.h"
#include "gpio.h"
#include "adc.h"
#include "lpit.h"
#include "pwm.h"
#include "uart.h"
#include "data_uart.h"
#include "flash.h"


speed_level_t speed_mode(uint32_t);
uint32_t getADC_and_transform(void);
void speed_manual(uint8_t);
void clock_fan_init(void);
void uart_fan_init(uart_config_t);
void adc_fan_init(adc_config_t);
void gpio_fan_init(void);
void pwm_fan_init(void);
void write_to_flash();
void read_from_flash();
void fan_set_off(void);
void fan_set_on(void);
uint32_t ADC_process(void);
void fan_process(void);


#endif /* FAN_H_ */
