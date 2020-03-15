

 /****************************************************************
 * Author  : Nada Mohamed
 * Data    : 3 Mar 2020
 * Version : v01
 *****************************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define ADC_u8Channel_0       0
#define ADC_u8Channel_1       1
#define ADC_u8Channel_2       2
#define ADC_u8Channel_3       3
#define ADC_u8Channel_4       4
#define ADC_u8Channel_5       5
#define ADC_u8Channel_6       6
#define ADC_u8Channel_7       7

typedef struct {
	u8*  ptrChain ;  /* channel */
	u8   Length;
	u16* ptrResult;
}ADC_Chain;




void ADC_voidInit(void);
/************************************************************************************
 *Description  :- function start conversion By using Synchronous
 * Return Type :- ErrorStatus [E_OK: request accepted
 *                            E_NOT_OK: request not accepted ]
 *Parameter(In) :-Copy_u8Channel
					        [ADC_u8Channel_0
							 ADC_u8Channel_1
							 ADC_u8Channel_2
							 ADC_u8Channel_3
							 ADC_u8Channel_4
							 ADC_u8Channel_5
							 ADC_u8Channel_6
							 ADC_u8Channel_7 ]
 *Parameter(OUT) :- Copy_ptr16ADCReading
 *                           pointer to the ADC reading result
 *
 ************************************************************************************/
ErrorStatus ADC_u8GeChannelSynchronous(u8 Copy_u8Channel , u16* Copy_ptr16ADCReading);

/************************************************************************************
 *Description  :- function start conversion By using ASynchronous
 * Return Type :- ErrorStatus [E_OK: request accepted
 *                            E_NOT_OK: request not accepted ]
 *Parameter(In) :-Copy_u8Channel
					        [ADC_u8Channel_0
							 ADC_u8Channel_1
							 ADC_u8Channel_2
							 ADC_u8Channel_3
							 ADC_u8Channel_4
							 ADC_u8Channel_5
							 ADC_u8Channel_6
							 ADC_u8Channel_7 ]
 *Parameter(OUT) :- Copy_ptr16ADCReading
 *                           pointer to the ADC reading result
 *
 ************************************************************************************/
ErrorStatus ADC_u8GetChannelASynchronous(u8 Copy_u8Channel , u16* Copy_ptr16ADCReading);

/************************************************************************************
 *Description  :- function start chain conversion
 * Return Type :- ErrorStatus [E_OK: request accepted
 *                            E_NOT_OK: request not accepted ]
 *Parameter(In) :-Copy_u8Channel
					        [ADC_u8Channel_0
							 ADC_u8Channel_1
							 ADC_u8Channel_2
							 ADC_u8Channel_3
							 ADC_u8Channel_4
							 ADC_u8Channel_5
							 ADC_u8Channel_6
							 ADC_u8Channel_7 ]
 *Parameter(OUT) :- Copy_ptr16ADCReading
 *                           pointer to the ADC reading result
 *
 ************************************************************************************/
ErrorStatus ADC_u8ChainConversion(u8 Copy_u8Channel , u16* Copy_ptr16ADCReading);



u8 ADC_u8ChainInit(ADC_Chain* Copy_ptrChain,u8* Copy_pu8ChainArr,u8 Copy_u8Length, u16* Copy_pu16ResultArr);

u8 ADC_StartChainConversion(ADC_Chain Copy_ptrChain , void(*Copy_ptrfun));



#endif
