
/****************************************************************
 * Author  : Nada Mohamed
 * Data    : 3 Mar 2020
 * Version : v01
 *****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_register.h"
#include "ADC_private.h"
#include "ADC_config.h"

/*************************** Macros *****************************/
#define MAX_NUM_CHANNEL   32

/********************* Global variable ***************************/
static void(*GptrFun)(void);
static u16* ADC_ptr16ReadingADC =NULL ;
static u8   ADC_u8ADCState = ADC_u8_STATE_IDLE;
static u8   ADC_u8ISRStatus = ADC_u8_SINGLE_CONVERSION;
static u8*  ADC_ChainArr = NULL;
static u8   ADC_ChainLength ;
static u8   ADC_u8Index=0 ;


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



ErrorStatus ADC_u8GeChannelSynchronous(u8 Copy_u8Channel , u16* Copy_ptr16ADCReading)
{
	ErrorStatus Local_u8Status=STD_TYPES_ERROR_OK ;
	u32 Local_u32TimeOut=0;

	/* check pointer is not NULL */
	if(Copy_ptr16ADCReading == NULL || Copy_u8Channel >MAX_NUM_CHANNEL)
	{
		Local_u8Status=STD_TYPES_ERROR_NOK ;
	}
	else
	{
		/* Set the channel ADMUX */
		ADMUX &=0b11100000;
		ADMUX |=Copy_u8Channel;

		/* Start Conversion */
		SET_BIT(ADCSRA,ADC_ADCSRA_ADSC);

		/* check if conversion finish and the conversion time less than the timeout */
		while (!(GET_BIT(ADCSRA,ADC_ADCSRA_ADIF)) && Local_u32TimeOut < ADC_u32TIMEOUT)
		{
			Local_u32TimeOut++;
		}
		if(Local_u32TimeOut < ADC_u32TIMEOUT)
		{
#if  ADC_u8_RESOLUTION == ADC_u8_16BIT_RESOLUTION
			Copy_ptr16ADCReading = ADC;
#elif ADC_u8_RESOLUTION == ADC_u8_10BIT_RESOLUTION
			Copy_ptr16ADCReading = ADCH;
#endif

			/* Clear Flag */
			SET_BIT(ADCSRA,ADC_ADCSRA_ADIF);
		}
		else
		{
			Local_u8Status = STD_TYPES_ERROR_NOK ;
		}
	}
	return Local_u8Status;
}


ErrorStatus ADC_u8GetChannelASynchronous(u8 Copy_u8Channel ,void(*Copy_ptrfun)(void), u16* Copy_ptr16ADCReading)
{
	ErrorStatus Local_u8Status=STD_TYPES_ERROR_OK ;

	/* check pointer is not NULL */
	if(Copy_ptr16ADCReading == NULL || Copy_u8Channel >MAX_NUM_CHANNEL || Copy_ptrfun==NULL ||ADC_u8ADCState == ADC_u8_STATE_BUSY )
	{
		Local_u8Status = STD_TYPES_ERROR_NOK ;
	}
	else
	{
		if(ADC_u8ADCState == ADC_u8_STATE_IDLE)
		{
			/* Init objects */
			ADC_u8ADCState = ADC_u8_STATE_BUSY;
			GptrFun=Copy_ptrfun;
			ADC_u8ISRStatus=ADC_u8_SINGLE_CONVERSION;
			ADC_ptr16ReadingADC= Copy_ptr16ADCReading;

			/* Set the channel ADMUX */
			ADMUX &=0b11100000;
			ADMUX |=Copy_u8Channel;

			/* enable interrupt */
			SET_BIT(ADCSRA,ADC_ADCSRA_ADIE);

			/* start conversion */
			SET_BIT(ADCSRA,ADC_ADCSRA_ADSC);
		}
	}
	return Local_u8Status;
}


u8 ADC_u8ChainInit(ADC_Chain* Copy_ptrChain,u8* Copy_pu8ChainArr,u8 Copy_u8Length, u16* Copy_pu16ResultArr)
{
	ErrorStatus Local_u8Status=STD_TYPES_ERROR_OK ;

	/* check pointer is not NULL */
	if( Copy_ptrChain == NULL || Copy_pu16ResultArr==NULL ||Copy_pu8ChainArr == NULL )
	{
		Local_u8Status = STD_TYPES_ERROR_NOK ;
	}
	else
	{
		Copy_ptrChain->ptrChain  = Copy_pu8ChainArr;
		Copy_ptrChain->Length    = Copy_u8Length;
		Copy_ptrChain->ptrResult = Copy_pu16ResultArr;
	}
	return Local_u8Status;
}


ErrorStatus ADC_StartChainConversion(ADC_Chain* Copy_ptrChain , void(*Copy_ptrfun))
{
	ErrorStatus Local_u8Status=STD_TYPES_ERROR_OK ;

	/* check pointer is not NULL */
	if(Copy_ptrChain==NULL || Copy_ptrfun==NULL || ADC_u8ADCState == ADC_u8_STATE_BUSY)
	{
		Local_u8Status = STD_TYPES_ERROR_NOK ;
	}
	else
	{
		/* Init objects */
		ADC_u8ADCState      = ADC_u8_STATE_BUSY;
		ADC_u8ISRStatus     = ADC_u8_CHAIN_CONVERSION;
		GptrFun             = Copy_ptrfun;
		ADC_ChainArr        = Copy_ptrChain->ptrChain ;
		ADC_ChainLength     = Copy_ptrChain->Length;
		ADC_ptr16ReadingADC = Copy_ptrChain->ptrResult;

		/*Start converion for channel */

		/* Set the channel ADMUX */
		ADMUX &=0b11100000;
		ADMUX |=ADC_ChainArr[ADC_u8Index];

		/* enable interrupt */
		SET_BIT(ADCSRA,ADC_ADCSRA_ADIE);

		/* start conversion */
		SET_BIT(ADCSRA,ADC_ADCSRA_ADSC);

	}
	return Local_u8Status;
}

/************ ISR ***************************************************************************/
void __vector_16(void)  __attribute__((signal));

void __vector_16(void)
{
	if(ADC_u8ISRStatus == ADC_u8_SINGLE_CONVERSION)
	{
#if  ADC_u8_RESOLUTION == ADC_u8_16BIT_RESOLUTION
		ADC_ptr16ReadingADC = ADC;
#elif ADC_u8_RESOLUTION == ADC_u8_10BIT_RESOLUTION
		ADC_ptr16ReadingADC = ADCH;
#endif

		/* IDLE ADC state */
		ADC_u8ADCState = ADC_u8_STATE_IDLE;

		/*Disable interrupt */
		CLR_BIT(ADCSRA,ADC_ADCSRA_ADIE);

		/* Call Notification function */
		GptrFun();
	}
	else if(ADC_u8ISRStatus == ADC_u8_CHAIN_CONVERSION)
	{
#if  ADC_u8_RESOLUTION == ADC_u8_16BIT_RESOLUTION
		ADC_ptr16ReadingADC[ADC_u8Index] = ADC;
#elif ADC_u8_RESOLUTION == ADC_u8_10BIT_RESOLUTION
		ADC_ptr16ReadingADC[ADC_u8Index] = ADCH;
#endif

		ADC_u8Index++;
		if(ADC_u8Index == ADC_ChainLength)
		{
			/* IDLE ADC state */
			ADC_u8ADCState = ADC_u8_STATE_IDLE;

			/*Disable interrupt */
			CLR_BIT(ADCSRA,ADC_ADCSRA_ADIE);

			/* Call Notification function */
			GptrFun();
		}
		else
		{
			/* Set the channel ADMUX */
			ADMUX &=0b11100000;
			ADMUX |=ADC_ChainArr[ADC_u8Index];
		}

	}

}





