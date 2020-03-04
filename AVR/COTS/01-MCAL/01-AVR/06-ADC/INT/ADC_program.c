#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_register.h"

#define ADC     *((volatile u16*)0x24)

void ADC_voidInit(void)
{
  /* Resolution 8 or 10 bit*/
  
  /* Vref */
  
  /* Prescaler */
  
  /* Left ,Right Adjustment  */
  

}


void ADC_StartConversion( channel)
{
	
	/*start conversion for first channel */
	/* Set flag to 1 conve */
	
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
void ADC_GetBlocking (channel , pointer to data) //Synchronous
{
	/* Set Channel number */
	/* start Conversion */
	 /* Polling */
	 /* Set pointer with digital value */
	   /* Clear Flag */
}


void ADC_GetNonBlocking(channel , pointer to data) //Asynchronous
{
  //check if flag conversion
      flag =0
  p	  
  // else 
	ptrToCallBack = ADC_Array_Data[channel]
	
}
void (*GPFun)(void);

u16 ADC_Array_Channel[];
u16 ADC_Array_Data[];
u8 index;
void ADC_SetCallBack(void(*PFun)(void))
{
	GPFun =PFun;
	
}


ISR()
{
	if(index<channel)
	{
	ADC_Array_Data[index]=ADC;
	index++;
	
	//StartConversion //next channel
    ADMUX 	= ADC_Array_Channel[index];
	}else{
		
		PFun();
		flag_con
	}

}






