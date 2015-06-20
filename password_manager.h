/*
 * password_manager.h
 *
 * Create on: 22.11.2014
 * 		Author: popai
 *
 */

#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <inttypes.h>

/*

The Job of password manager is to read
and write password to/from the internal
eeprom

*/

//Writes the given 4 digit password to eeprom
void WritePassToEEPROM(uint16_t pass);

//Reads and Returns the 4 digit password from eeprom
uint16_t ReadPassFromEEPROM();


#endif
