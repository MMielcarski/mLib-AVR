// device: 	AtMega 328p
// author:  Maciej Mielcarski
// serial communication

#include <avr/io.h>

#define F_CPU 16000000UL
#define FOSC 16000000UL
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <util/setbaud.h>

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
}

void uart_putint(int value)
{
	char tab[16];
	itoa(value,tab,10);
	uart_putstring(tab);
}

int main(void)
{
	USART_Init(MYUBRR);
	int zm = 1666;

	while(1)
	{
		uart_putchar('K');
		uart_putint(zm);
	}
}


