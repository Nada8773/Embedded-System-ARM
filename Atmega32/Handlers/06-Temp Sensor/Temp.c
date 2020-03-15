/*
 * Temp.c
 *
 *  Created on: Mar 2, 2020
 *      Author: Nada
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "Temp.h"


u16 Temp(void)
{
	 u16 ADC_GetReading;
	 u16 ADC_Temp;
	 ADC_GetReading=ADC_u16GetChannelReading(0);
	 ADC_Temp=(((u32)ADC_GetReading *500UL)/1024UL);

	 return  ADC_Temp;

}
