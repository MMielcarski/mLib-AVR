#include "mLib_USART.h"

void usart_init(unsigned int ubrr)		
{
   UBRR0H = (unsigned char)(ubrr>>8);	// set baud rate to 9600
   UBRR0L = (unsigned char)ubrr;		//
   UCSR0B = (1<<RXEN0)|(1<<TXEN0);		// Enable receiver and transmitter 
   UCSR0C = (1<<USBS0)|(3<<UCSZ00);		// Set frame format: 8data, 2stop bit
}

void usart_put_8bit(uint8_t data) 
{
	while ( !(UCSR0A & (1<<UDRE0)) )	 
	;
    UDR0 = data;							
}

uint8_t usart_get_8bit(void) 
{
    loop_until_bit_is_set(UCSR0A, RXC0); 	
    return UDR0;
}

void usart_putstring(char tab[])
{
	int character_number = 0;
	while (( UCSR0A & (1<<UDRE0))  == 0) {};
        while (tab[character_number] != 0x00)
		{ 
            usart_put_8bit(tab[character_number]);
			character_number++; 
        }
}

void usart_put_16bit(int16_t value)
{
	char tab[16];
	itoa(value,tab,10);
	usart_putstring(tab);
}