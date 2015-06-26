/*
 * keypad.c
 *
 * Create on: 18.06.2015
 * 		Author: popai
 *
 */

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "../../pinDef.h"

#include "keypad.h"

/************************************************
 KEYPAD CONNECTIONS
 	 	PC0 PC1 PC2
 PB0 ----1---2---3---
 PB1 ----4---5---6---
 PB2 ----7---8---9---
 PB3 ----*---0---#---
 PB AR INPUT AND PC AR OUTPUT
 *************************************************/

/**
 * @breaf 4x3 keybord function
 * on this aplication foR 4 lines it is use port B first 4 pins as input pins
 * and for 3 colons it is use port C first 3 pins as out pins.
 *
 * @param no parameter
 */
static uint8_t notpress = 100;

uint8_t GetKeyPressed()
{

	PORTC |= (1 << PC1) | (1 << PC2);
	PORTC &= ~(1 << PC0);
	_delay_ms(10);
	if (!(PINB & (1 << PB3)) && (notpress == 100)) //(PINB & (1 << PB3)) == 0
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 10;
		return 10;
	}
	if((PINB & (1 << PB3)) && (notpress == 10))
		notpress = 100;


	if (!(PINB & (1 << PB2)) && (notpress == 100))
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 7;
		return 7;
	}
	if((PINB & (1 << PB2)) && (notpress == 7))
		notpress = 100;

	if (!(PINB & (1 << PB1)) && (notpress == 100))
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 4;
		return 4;
	}
	if((PINB & (1 << PB1)) && (notpress == 4))
		notpress = 100;

	if (!(PINB & (1 << PB0)) && (notpress == 100)) //(PINB & (1 << PB3)) == 0
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 1;
		return 1;
	}
	if((PINB & (1 << PB0)) && (notpress == 1))
		notpress = 100;

	PORTC |= (1 << PC0) | (1 << PC2);
	PORTC &= ~(1 << PC1);
	_delay_ms(10);
	if (!(PINB & (1 << PB3)) && (notpress == 100)) //(PINB & (1 << PB3)) == 0
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 0;
		return 0;
	}
	if((PINB & (1 << PB3)) && (notpress == 0))
		notpress = 100;


	if (!(PINB & (1 << PB2)) && (notpress == 100))
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 8;
		return 8;
	}
	if((PINB & (1 << PB2)) && (notpress == 8))
		notpress = 100;

	if (!(PINB & (1 << PB1)) && (notpress == 100))
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 5;
		return 5;
	}
	if((PINB & (1 << PB1)) && (notpress == 5))
		notpress = 100;

	if (!(PINB & (1 << PB0)) && (notpress == 100)) //(PINB & (1 << PB3)) == 0
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 2;
		return 2;
	}
	if((PINB & (1 << PB0)) && (notpress == 2))
		notpress = 100;

	PORTC |= (1 << PC0) | (1 << PC1);
	PORTC &= ~(1 << PC2);
	_delay_ms(10);
	if (!(PINB & (1 << PB3)) && (notpress == 100)) //(PINB & (1 << PB3)) == 0
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 11;
		return 11;
	}
	if((PINB & (1 << PB3)) && (notpress == 11))
		notpress = 100;


	if (!(PINB & (1 << PB2)) && (notpress == 100))
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 9;
		return 9;
	}
	if((PINB & (1 << PB2)) && (notpress == 9))
		notpress = 100;

	if (!(PINB & (1 << PB1)) && (notpress == 100))
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 6;
		return 6;
	}
	if((PINB & (1 << PB1)) && (notpress == 6))
		notpress = 100;

	if (!(PINB & (1 << PB0)) && (notpress == 100)) //(PINB & (1 << PB3)) == 0
	{
		BUZER_PORT |= (1 << BUZER_PIN);
		_delay_ms(50);
		BUZER_PORT &= (~(1 << BUZER_PIN));
		notpress = 3;
		return 3;
	}
	if((PINB & (1 << PB0)) && (notpress == 3))
		notpress = 100;

	return 255; //Indicate No key pressed
}

