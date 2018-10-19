// device: 	AtMega 328p
// author:  Maciej Mielcarski
// external interrupts handle - switch + LED

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL

#define BUTTON_1_PIN 	PD2
#define BUTTON_1_PORT 	PORTD
#define BUTTON_1_DDR 	DDRD
#define BUTTON_1_PIN_r 	PIND

#define LED_1_PIN 	PB5
#define LED_1_PORT 	PORTB
#define LED_1_DDR 	DDRB

int Button_1_State()
{
	if(!(BUTTON_1_PIN_r & (1<<BUTTON_1_PIN)))	return 1;
	else 										return 0;
}

int main(void)
{
	BUTTON_1_DDR &= ~(1<<DDD2);		// Clear the PD2 pin - PCINT0 is now input
	BUTTON_1_PORT |= (1<<PORTD2);	// turn on the pulllup
	EICRA |= (1<<ISC00);			// set INT0 to trigger on ANY logic change
	EIMSK |= (1<<INT0); 			// turns on INT0
	
	sei();							// turn on interrupts

	BUTTON_1_DDR |= (0<<BUTTON_1_PIN);		// button pin set as input
	BUTTON_1_PORT |= (1<<BUTTON_1_PIN); 	// button input with internal pull-up

	LED_1_DDR |= (1<<LED_1_PIN);			// led pin set as output

	while(1)
	{

	}
}
   
ISR (INT0_vect)
{
	if(Button_1_State())	LED_1_PORT |=  (1<<LED_1_PIN);
	else 					LED_1_PORT &= ~(1<<LED_1_PIN);
}
