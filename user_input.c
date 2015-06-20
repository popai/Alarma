/*
 * user_input.c
 *
 * Create on: 22.11.2014
 * 		Author: popai
 *
 */

#include <avr/io.h>

#include "lib/sound/sound.h"
#include "user_input.h"
#include "pinDef.h"


uint8_t armat = ON;
uint8_t alarm = OFF;

/**
 * @breaf start the alarm
 * and signal a led on bord
 * @param
 */
void ALARMOff()
{
	alarm = OFF;
	ALARM_PORT &= (~(1 << ALARM_PIN));
}

/**
 * @breaf stop the alarm
 *
 * @param none
 */
void ALARMOn()
{
		alarm = ON;
		ALARM_PORT |= (1 << ALARM_PIN);
}

/**
 * @breaf activate the alarma
 *
 * @param none
 */
void ARMOn()
{
	armat = ON;
	ARMLED_PORT |= (1 << ARMLED_PIN);
	//WriteStateToEEPROM(armat);
	//eeprom_update_byte((uint8_t*) 3, armat);
}

/**
 * @breaf dezactivate the alarma
 *
 * @param none
 */
void ARMOff()
{
	armat = OFF;
	ARMLED_PORT &= (~(1 << ARMLED_PIN));
	//WriteStateToEEPROM(armat);
	//eeprom_update_byte((uint8_t*) 3, armat);
	//SENZOR_PINS &= (~(1 << SENZOR_PIN));
}
/*
uint8_t GetArmat()
{
	return armat;
}

uint8_t GetAlarm()
{
	return alarm;
}
*/
/**
 * @breaf System initialization function
 * 	on this functin init posrts, usart, timer amd...
 *
 * @param no parameter
 * bach = "!T110 L8 a gafaeada c+adaeafa >aa>bac#ada c#adaeaf4";
 * guminam = "!T160 L2 a1aa1age+ e1rd>cb-a4b-4 b-1rd>cb-4b-.a4b-4 b-rd.e.f a1b-g1f1 g1. rffe4d.ff1.";
 * cmajor = "!T110 L16 cdefgab>cbagfedc";
 *
 */

void Buzer_PassOK()
{
	play("T240 L8 >ac#adaeaf4");
}

void Buzer_PassNotOK()
{
	play("L16 <a<a<a<a<a<a");

}

