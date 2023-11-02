/*
 * flash.c
 *
 *  Created on: Aug 21, 2023
 *      Author: Admin
 */

#include "flash.h"

void erase_and_write(uint8_t state, uint8_t mode, uint8_t level)
{
	//erase 4KB flash sector (the smallest entity that can be erased) at 0x0004_0000
	while((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0);	//wait if operation in progress
	FTFC->FSTAT = FTFC_FSTAT_ACCERR_MASK | FTFC_FSTAT_FPVIOL_MASK;	//clear flags if set

	FTFC->FCCOB[3] = 0x09;	//Erase Flash Sector command (0x09)
	FTFC->FCCOB[2] = 0x80;	//Flash address [23:16]
	FTFC->FCCOB[1] = 0x30;	//Flash address [15:08]
	FTFC->FCCOB[0] = 0x00;	//Flash address [7:0]

	FTFC->FSTAT = FTFC_FSTAT_CCIF_MASK;	//launch command
	while((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0);	//wait for done


	//program phrase at address 0x0004_0000
	while((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0);	//wait if operation in progress
	FTFC->FSTAT = FTFC_FSTAT_ACCERR_MASK | FTFC_FSTAT_FPVIOL_MASK;

	FTFC->FCCOB[3] = 0x07;	//Program Phrase command (0x07)
	FTFC->FCCOB[2] = 0x80;	//Flash address [23:16]
	FTFC->FCCOB[1] = 0x30;	//Flash address [15:08]
	FTFC->FCCOB[0] = 0x00;	//Flash address [7:0]

	FTFC->FCCOB[7] = 0xFE;	//data
	FTFC->FCCOB[6] = level;
	FTFC->FCCOB[5] = mode;
	FTFC->FCCOB[4] = state;
	FTFC->FCCOB[11] = 0xCA;
	FTFC->FCCOB[10] = 0xFE;
	FTFC->FCCOB[9] = 0xBE;
	FTFC->FCCOB[8] = 0xEF;

	FTFC->FSTAT = FTFC_FSTAT_CCIF_MASK;	//launch command
	while((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0);	//wait for done
}

void assign_value_from_flash(uint8_t *state_fan, uint8_t *fan_mode, uint8_t *level_manual)
{
	*state_fan = *((uint8_t *)0x10003000);
	*fan_mode = *((uint8_t *)0x10003001);
	*level_manual = *((uint8_t *)0x10003002);
}
