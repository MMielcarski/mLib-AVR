#include "mLib_Timer.h"

void delay_ms(unsigned int period)		
{
	volatile long unsigned int cpu_tick;
	for(cpu_tick=0;cpu_tick<period;cpu_tick++)
	_delay_ms(1);
}

void timer_init(void)
{
	OCR1A = (((F_CPU/1000) / TIM1_PSC) * TIM1_PER) - 1;	// (dec 15624) counter size
    TCCR1B |= (1 << WGM12);							// Mode 4, CTC on OCR1A
    TIMSK1 |= (1 << OCIE1A);						// Set interrupt on compare match	
    TCCR1B |= (1 << CS12) | (1 << CS10);			// set prescaler to 1024 and start the timer
    sei();											// enable interrupts
}
