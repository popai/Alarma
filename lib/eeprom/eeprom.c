/*
 * eeprom.c
 *
 * Create on: 22.11.2014
 * 		Author: popai
 *
 */


#include <avr/io.h>
#include <inttypes.h>

#include "eeprom.h"

uint8_t EEPROMRead(uint16_t uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

void EEPROMWrite(uint16_t uiAddress, uint8_t ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	/* Set up address and data registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEPE);
}
