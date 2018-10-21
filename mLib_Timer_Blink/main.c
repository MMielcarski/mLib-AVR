// device: 	AtMega 328p
// author:  Maciej Mielcarski
// timer
// TODO: full frequency handling

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL

#define TIM1_PSC 1024		// TIMER 1 prescaler value
#define TIM1_PER 1000		// TIMER 1 desired period in miliseconds

#define LED_1_PIN 	PB5
#define LED_1_PORT 	PORTB
#define LED_1_DDR 	DDRB
#define LED_1_PIN_r PINB

void delay_ms(int ms)		// delay error workaround
{
	volatile long unsigned int i;
	for(i=0;i<ms;i++)
	_delay_ms(1);
}

void Toggle_LED()
{
	if(LED_1_PIN_r & (1<<LED_1_PIN))	LED_1_PORT &= ~(1<<LED_1_PIN);
	else								LED_1_PORT |= (1<<LED_1_PIN);
}

int main(void)
{
	LED_1_DDR |= (1<<LED_1_PIN);					// led pin set as output

    OCR1A = (((F_CPU/1000) / TIM1_PSC) * TIM1_PER) - 1;	// (dec 15624) counter size
    TCCR1B |= (1 << WGM12);							// Mode 4, CTC on OCR1A
    TIMSK1 |= (1 << OCIE1A);						// Set interrupt on compare match	
    TCCR1B |= (1 << CS12) | (1 << CS10);			// set prescaler to 1024 and start the timer
    sei();											// enable interrupts

	while(1)
	{
		// Toggle_LED();
		// delay_ms(1000);
	}
}

ISR(TIMER1_COMPA_vect)	// timer1 overflow interrupt
{
	Toggle_LED();
}
