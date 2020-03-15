#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_register.h"


void ADC_voidInit(void)
{

	/* AVCC Reference Voltage */
	CLR_BIT(ADMUX,7);
	SET_BIT(ADMUX,6);
	/* Active Left adjust mode */
	//SET_BIT(ADMUX,5);
	/* ADC Enable */
	SET_BIT(ADCSRA,7);
	/* prescaler division by  128  */
	SET_BIT(ADCSRA,2);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,0);
}




u16 ADC_u16GetChannelReading(u8 Channel)
{
	/* Set the channel ADMUX */
   ADMUX &=0b11100000;
   ADMUX |=Channel;

   /* Start Conversion */
   SET_BIT(ADCSRA,6);

   /* Polling */
   while((GET_BIT(ADCSRA,4))==0);

   /* Clear Flag */
   SET_BIT(ADCSRA,4);

   /* get result */
   return ADC;

}





