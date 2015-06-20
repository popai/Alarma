/*
 * pinDef.c
 *
 *  Created on: Apr 14, 2013
 *      Author: popai
 */
#include <avr/io.h>
#include "pinDef.h"

void pinSetUp()
{
	//DDRC  = 0b00000111; // PC0, PC1, PC2 OUT for keybord; PC3 IN panick button; PC4 and PC5 IN pins DELL and DEBUG
	//PORTC = 0b11111000;
	DDRC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2);
	DDRC &= ~((1 << DDC3) | (1 << DDC4) | (1 << DDC5));
	PORTC |= (1 << PD3) | (1 << PD4) | (1 << PD5); // internal Pull UP switch on

	//DDRB  = 0b00110000; // PB0, BP1, PB2, PB3 IN for keybord; PB4, PB5 OUT for LED
	//PORTB = 0b11001111;
	DDRB &= ~((1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3));
	DDRB |= (1 << DDB4) | (1 << DDB5);
	PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3); // internal Pull UP switch on

	//DDRD = 0b10001010; // PD2 senzor intarziat PD4, PD5 senzori rapizi, PD3 OUT sunet.
	//PORTD = 0b01110101;
	DDRD |= (1 << DDD1) | (1 << DDD3) | (1 << DDD7);
	DDRD &= ~((1 << DDD0) | (1 << DDD2) | (1 << DDD4) | (1 << DDD5)
			| (1 << DDD6));
	PORTD |= (1 << PD0) | (1 << PD2) | (1 << PD4) | (1 << PD5) | (1 << PD6); // internal Pull UP switch on
	//PORTD &= ~(1 << PD6);
	/*
	 //setup External Interrupt INT0
	 cli();		// disable global interrupts
	 //DDRD |= 1 << PD2; 			// Set PD2 as input (Using for interupt INT0)
	 //PORTD |= 1 << PD2;		 	// Enable PD2 pull-up resistor
	 EIMSK |= (1 << INT0); 			// Enable INT0 interrupt
	 MCUCR |= (1 << ISC00);			// Any logical change on INT0 generates an interrupt request
	 sei();		//Enable Global Interrupt
	 */

}

