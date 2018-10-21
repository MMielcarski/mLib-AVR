// device: 	AtMega 328p
// author:  Maciej Mielcarski
// ADC single and free running conversion single and multi-channel handled by timer
// TODO: voltage measurement

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define TIM1_PSC 1024		// TIMER 1 prescaler value
#define TIM1_PER 100		// TIMER 1 desired period in miliseconds
#define FOSC 16000000UL
#define BAUD 9600				// UART
#define MYUBRR FOSC/16/BAUD-1	// UART

//#define SUPPLY_VOLT 5000	// [mV]
//#define ADC_RES 1024

#include <util/setbaud.h>

	int _ADC_read_1 = 0;
	int _ADC_read_2 = 0;
	int _ADC_read_3 = 0;

// ------------------------- TIMER ----------------------------------------

void TIM1_Init()	// enable interrupts
{
    OCR1A = (((F_CPU/1000) / TIM1_PSC) * TIM1_PER) - 1;	// counter size
    TCCR1B |= (1 << WGM12);							// Mode 4, CTC on OCR1A
    TIMSK1 |= (1 << OCIE1A);						// Set interrupt on compare match	
    TCCR1B |= (1 << CS12) | (1 << CS10);			// set prescaler to 1024 and start the timer
    sei();	
}

// ------------------------- UART ----------------------------------------

void USART_Init(unsigned int ubrr)		
{
   UBRR0H = (unsigned char)(ubrr>>8);	// set baud rate to 9600
   UBRR0L = (unsigned char)ubrr;		//
   UCSR0B = (1<<RXEN0)|(1<<TXEN0);		// Enable receiver and transmitter 
   UCSR0C = (1<<USBS0)|(3<<UCSZ00);		// Set frame format: 8data, 2stop bit
}

void uart_putchar(char c) 
{
	while ( !(UCSR0A & (1<<UDRE0)) )	// Wait for empty transmit buffer 
	;
    UDR0 = c;							// Put data into buffer, sends the data 
}

char uart_getchar(void) {
    loop_until_bit_is_set(UCSR0A, RXC0); 	// Wait until data exists
    return UDR0;
}

void uart_putstring(char tab[])
{
	int i =0;
	while (( UCSR0A & (1<<UDRE0))  == 0){};
        while (tab[i] != 0x00)
		{ 
            uart_putchar(tab[i]);
			i++; 
        }
		uart_putchar('\n');
}

void uart_putint(int value)
{
	char tab[16];
	itoa(value,tab,10);
	uart_putstring(tab);
}

// ------------------------- ADC ----------------------------------------

void ADC_Init()
{
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz
	ADMUX |= (1 << REFS0); 	// Set ADC reference to AVCC
	
	ADCSRA |= (1 << ADEN);  // Enable ADC
	//ADCSRA |= (1 << ADSC);  // Start A2D Conversions
	//ADCSRA |= (1 << ADATE);	// for free running mode
}

uint16_t ADC_read(uint8_t channel)		
{
	channel &= 0x07;					// AND operation with 7 (will keep channel between 0-7) 
	ADMUX = (ADMUX & 0xF8) | channel;	// clears 3 first bits before OR

	ADCSRA |= (1 << ADSC);				// start single convesrion
	while(ADCSRA & (1 << ADSC));		// wait for conversion to complete
	return ADCW;
}

// ------------------------- MAIN ----------------------------------------

int main(void)
{
	USART_Init(MYUBRR);
	TIM1_Init();
	ADC_Init();

	//double ADC_voltage = 0;

	while(1)
	{
		//ADC_voltage = ADC_read*SUPPLY_VOLT/ADC_RES;	// problem z wysylaniem float po UART
	}
}

// -----------------------------------------------------------------

ISR(TIMER1_COMPA_vect)	// timer1 overflow interrupt
{
	_ADC_read_1 = ADC_read(0);
	_ADC_read_2 = ADC_read(1);
	_ADC_read_3 = ADC_read(2);

	//uart_putint(_ADC_read_1);
	uart_putint(_ADC_read_2);
	//uart_putint(_ADC_read_3);
}

