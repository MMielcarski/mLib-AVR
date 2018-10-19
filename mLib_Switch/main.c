// device: 	AtMega 328p
// author:  Maciej Mielcarski
// switch with LED

#include <avr/io.h>

#define F_CPU 16000000UL

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
	BUTTON_1_DDR |= (0<<BUTTON_1_PIN);		// button pin set as input
	BUTTON_1_PORT |= (1<<BUTTON_1_PIN); 	// button input with internal pull-up

	LED_1_DDR |= (1<<LED_1_PIN);		// led pin set as output
	//LED_1_PORT | = (1<<LED_1_PIN);

	while(1)
	{
		if(Button_1_State())	LED_1_PORT |=  (1<<LED_1_PIN);
		else 					LED_1_PORT &= ~(1<<LED_1_PIN);
	}
}


