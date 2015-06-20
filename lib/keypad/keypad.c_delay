/*
 * keypad.c
 *
 * Create on: 22.11.2014
 * 		Author: popai
 *
 */

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#include "keypad.h"
//#include "../timer/timer.h"

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
uint8_t GetKeyPressed()
{
	//uint8_t getkb = 255;	//Indicate No key pressed

	PORTC |= (1 << PC1) | (1 << PC2);
	PORTC &= ~(1 << PC0);
	_delay_ms(10);
	if (!(PINB & (1 << PB3))) //(PINB & (1 << PB3)) == 0
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 10;
	}

	if (!(PINB & (1 << PB2)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 7;
	}

	if (!(PINB & (1 << PB1)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 4;
	}

	if (!(PINB & (1 << PB0)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 1;
	}

	PORTC |= (1 << PC0) | (1 << PC2);
	PORTC &= ~(1 << PC1);
	_delay_ms(10);
	if (!(PINB & (1 << PB3)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 0;
	}

	if (!(PINB & (1 << PB2)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 8;
	}

	if (!(PINB & (1 << PB1)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 5;
	}
	if (!(PINB & (1 << PB0)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 2;
	}

	PORTC |= (1 << PC0) | (1 << PC1);
	PORTC &= ~(1 << PC2);
	_delay_ms(10);
	if (!(PINB & (1 << PB3)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 11; //getkb = 11;
	}
	if (!(PINB & (1 << PB2)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 9;
	}
	if (!(PINB & (1 << PB1)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 6;
	}
	if (!(PINB & (1 << PB0)))
	{
		PORTC |= (1 << PC3); //buzer on
		_delay_ms(50);
		PORTC &= ~(1 << PC3); //buzer off
		_delay_ms(50);
		return 3;
	}

	return 255; //Indicate No key pressed
}

/*
 uint8_t GetKeyPressed()
 {
 uint8_t r,c;
 UWriteString("key");

 KEYPAD_PORT|= 0X0F;

 for(c=0;c<4;c++)
 {
 KEYPAD_DDR &= ~(0XFF);

 KEYPAD_DDR|=(0X80>>c);
 for(r=0;r<3;r++)
 {
 if(!(KEYPAD_PIN & (0X08>>r)))
 {
 return (r*3+c);
 UWriteString("pres?");
 _delay_ms(10);
 }
 }
 }
 return 0XFF;//Indicate No key pressed
 }

 */
