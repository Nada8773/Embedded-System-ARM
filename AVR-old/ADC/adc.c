#include "adc.h"
void ADC_init()
{
	ADMUX=0;
	ADCSRA=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1);

}

uint16 adc_readchannel (uint8 channel)
{
	channel &=0x07;

	ADMUX &=0xE0;
	ADMUX=channel;
 ADCSRA =(1<<ADSC);

 return ADC;

}
