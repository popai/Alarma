/*
 * timer.c
 *
 *  Created on: Dec 18, 2013
 *      Author: popai
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"

//global variable
volatile uint8_t seconds;
volatile uint8_t minutes;
volatile uint8_t houers;

volatile uint8_t contor_s ;
volatile uint8_t contor_m ;
//volatile uint8_t senzor_pull;

/**
 * @file timer.c
 *
 * @breaf initialize Timer1
 *
 * Sistem frecvet 16MHz clock
 * Wi wse Clear Timer on Compare Match (CTC)
 * Prescaler 1024, time target 1s
 * (# timer counts + 1) = (target time) / (timer resolution)
 * (# timer counts + 1) = (1 s) / (6.4e-5 s)
 * (# timer counts + 1) = 15625
 * (# timer counts) = 15625 - 1 = 15624
 *
 * @param void
 */
void Timer1_Init(void)
{

	cli();
	// disable global interrupts
	TCCR1A = 0; // set entire TCCR1A register to 0
	TCCR1B = 0; // same for TCCR1B
	TCNT1 = 0; // contor value
	OCR1A = 15624; // set compare match register to desired timer count:

	// turn on CTC mode:
	TCCR1B |= (1 << WGM12);

	// Set CS10 and CS12 bits for 1024 prescaler:
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);

	// enable timer compare interrupt:
	TIMSK1 |= (1 << OCIE1A);

	seconds = 0;
	minutes = 0;
	contor_s = 0;
	contor_m  = 0;

	sei();
	// enable global interrupts
}
/*
void Timer0_Init(void)
{
	// disable global interrupts
	cli();

	TCCR0A = 0; // set entire TCCR1A register to 0
	TCCR0B = 0; // same for TCCR1B
	TCNT0 = 0; // contor value
	OCR0A = 255; // set compare match register to desired timer count:

	// turn on CTC mode:
	TCCR0A |= (1 << WGM01);

	// Set CS10 and CS12 bits for 1024 prescaler:
	TCCR0B |= (1 << CS00);
	TCCR0B |= (1 << CS02);

	// enable timer compare interrupt:
	TIMSK0 |= (1 << OCIE0A);

	// enable global interrupts
	sei();
	/*
	 DDRD = ((1<<PD5)|(1<<PD6));						//Set pwm pins from timer 0 as outputs
	 TCCR0A = ((1<<COM0A1)|(1<<WGM01)|(1<<WGM00));	//Enable pwm mode in pin PD6 and set the WGM bits to Fast pwm mode
	 TCCR0A |= (1<<COM0B1);							//Enable pwm mode in pin PD5
	 TCCR0B = ((1<<CS01)|(1<<CS00));					//Set prescaler to 32

}
*/
uint8_t GetSeconds()
{
	cli();
	//Disable all interrupts so we can read our long variable atomically
	//This is to ensure that no interrupt is fired while reading the long variable
	//And possibly trash the readed value
	uint8_t s_value = seconds; //Copy the value and return it
	sei();
	//Enable all interrupt again
	return s_value;
}

uint8_t GetMinutes()
{
	cli();
	//Disable all interrupts so we can read our long variable atomically
	//This is to ensure that no interrupt is fired while reading the long variable
	//And possibly trash the readed value
	uint8_t min_value = minutes; //Copy the value and return it
	sei();
	//Enable all interrupt again
	return min_value;
}

uint8_t GetHouers()
{
	cli();
	//Disable all interrupts so we can read our long variable atomically
	//This is to ensure that no interrupt is fired while reading the long variable
	//And possibly trash the readed value
	uint8_t h_value = houers; //Copy the value and return it
	sei();
	//Enable all interrupt again

	return h_value;
}

ISR(TIMER1_COMPA_vect)
{
	TCNT1 = 0; // contor value
	++seconds;
	++contor_s;
	if (seconds == 60)
	{
		seconds = 0;
		++minutes;
		++contor_m;
	}

	if (minutes == 60)
	{
		minutes = 0;
		++houers;
	}

	if (houers == 24)
		houers = 0;
}

/*
 void WeitS(uint8_t s)
 {
 uint8_t tmp = 0;
 tmp = seconds;
 while(s)
 {
 if(tmp == seconds)
 {
 ++tmp;
 --s;
 }
 }
 }



 void timer2_init(void){
 DDRD |= (1<<PD3);								//Set pwm pin OC2B from timer 2 as output
 TCCR2A = ((1<<COM2B1)|(1<<WGM21)|(1<<WGM20));	//Enable pwm mode in PD3 and set the WGM bits for fast pwm mode
 TCCR2B = ((1<<CS21)|(1<<CS20));					//Set prescaler to 32
 //As you can see, the code for timer 0 and 2 is very similiar, and even almost registers are identical, this is equal also for timer 1
 }
 */
