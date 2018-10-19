// device: 	AtMega 328p
// author:  Maciej Mielcarski
// PWM generation

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL

#define PWM1_PSC 1024		// PWM 1 prescaler value
#define PWM1_FREQ 50		// PWM 1 desired frequency
#define PWM1_TOP 

#define PWM_1_PIN 	PB1
#define PWM_1_PORT 	PORTB
#define PWM_1_DDR 	DDRB
#define PWM_1_PIN_r PINB 



int main(void)
{
	PWM_1_DDR |= (1<<PWM_1_PIN);					// PWM 1 pin set as output

	ICR1 = 0xFFFF;	// set TOP to 16bit
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);		// none-inverting mode
	TCCR1A |= (1<<WGM11);	// set Fast PWM mode using ICR1 as TOP


    OCR0A = ((F_CPU / TIM1_PSC) * TIM1_FREQ) - 1;	// (dec 15624) counter size
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
	//Toggle_LED();
	OCR1A += 1000;	// 25% duty

}
