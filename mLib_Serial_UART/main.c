#include "mLib_USART.h"

int main(void)
{
	usart_init(MYUBRR);
	int zm = 11;
	char tab[10] = "lelelelele";

	while(1)
	{
		usart_put_8bit(0x09);
		usart_putstring(tab);
		usart_put_16bit(zm);
	}
}


