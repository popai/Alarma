/*
 * user_input.h
 *
 * Create on: 22.11.2014
 * 		Author: popai
 *
 */

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <inttypes.h>


#define ON	1
#define OFF 0

/**
 * @breaf Prompts the user to enter a 4 digit number
 *
 * @param
 */
//uint16_t InputNumber();
uint8_t GetPassword();
void ALARMOn();
void ALARMOff();
void ARMOn();
void ARMOff();
void Buzer_PassOK();
void Buzer_PassNotOK();
//uint8_t GetArmat();
//uint8_t GetAlarm();

#endif
