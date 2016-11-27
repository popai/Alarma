/*
 * password_manager.c
 *
 * Create on: 22.11.2014
 * 		Author: popai
 *
 */


#include "lib/eeprom/eeprom.h"
#include "password_manager.h"

void WritePassToEEPROM(uint16_t pass)
{

	EEPROMWrite(0000, (pass % 100));
	EEPROMWrite(0001, (pass / 100));
}

uint16_t ReadPassFromEEPROM()
{

	return (EEPROMRead(0001) * 100 + EEPROMRead(0000));
}
