/*!
\file   mLib_Timer.h
\author Maciej Mielcarski
\date   01.12.2018
\brief  timer handle

        tested on: Atmega328p
*/

#ifndef MLIB_TIMER_H
#define MLIB_TIMER_H

#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL

#define TIM1_PSC 1024		// TIMER 1 prescaler value 
#define TIM1_PER 1000		// TIMER 1 desired period in miliseconds 

/*!
\brief  delay workaround for high period values
\param  period - delay period in cpu ticks
\return void
*/
void delay_ms(unsigned int period);		

/*!
\brief  register initialization for Timer
\return void
*/
void timer_init(void);

#endif