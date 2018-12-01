
#include "mLib_ADC.h"

int main(void)
{
	adc_init();
	uint16_t adc_reading = 0;

	while(1)
	{
		adc_reading = adc_read(0);
	}
}
