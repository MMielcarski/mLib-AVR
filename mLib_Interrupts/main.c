#include "mLib_Interrupts.h"

int main(void)
{
	ext_intrr_init(PD2, DDRD, PORTD);

	while(1)
	{

	}
}
   
ISR (INT0_vect)
{

}
