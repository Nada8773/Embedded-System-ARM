

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"

#include <util/delay.h>
#include <string.h>

/***************************************************
 Description :- Display a pattern move in sinwave using lcd
****************************************************/
int main(void)
{
	u8 line=1;
    u8 flag=0;
	u8 *str="Nada";
	u8 size=0;

	while(str[size] !='\0')
	{
		size++;
	}

   PortInitialize();
   CLCD_voidInitialize();

   while(1)
   {
       flag=0;
	   for(u8 index=0;index<15;index+=size)
	   {
		   if(flag==0)
		   {
			   line=1;
			   flag=1;
		   }
		   else
		   {
			   line=2;
			   flag=0;
		   }
		   CLCD_voidGotoLocation(line,index);
		   CLCD_voidWriteString(str);
		   _delay_ms(1000);
		   CLCD_Clear();
	   }
   }
   return 0;
}
