#include "mLib_IO.h"

int main(void)
{
	pin_init(PD0, &DDRD, &PIND, 0, 1);
	pin_init(PD1, &DDRD, &PORTD, 1, 0);

	while(1)
	{
		if(is_pin(PD0, &PIND))	pin_set_state(PD1, &PORTD, &PIND, 1);
		else 					pin_set_state(PD1, &PORTD, &PIND, 0);

	}
}


