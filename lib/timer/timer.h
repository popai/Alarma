/*
 * timer.h
 *
 *  Created on: Dec 18, 2013
 *      Author: popai
 */

#ifndef TIMER_H_
#define TIMER_H_

extern volatile uint8_t contor_s ;
extern volatile uint8_t contor_m ;
//extern volatile uint8_t senzor_pull;

void Timer1_Init(void);
void Timer0_Init(void);
//void Timer2_Init(void);

uint8_t GetSeconds();
uint8_t GetMinutes();
uint8_t GetHouers();


#endif /* TIMER_H_ */
