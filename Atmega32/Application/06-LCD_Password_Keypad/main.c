

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KEYPAD_interface.h"

#include "KEYPAD_config.h"

#include <util/delay.h>
#include <string.h>

#include <stdlib.h>
#define line2 2
#define line1 1

/**************************************************************************
 Description :- Password door 
                take input number from keypad if correct Display Correct
				if not display wrong on lcd
****************************************************************************/
int main(void)
{
	u8 state=0;
	s8 index=0;
	u8 Get_key;
	u8 pass[4]={1,2,3,4};
	u8 buffer[5];
	u8 wrong_count=0;
	
   PortInitialize();
   CLCD_voidInitialize();
   
   while(1)
   {
	   index=0;
	   state=0;
	   CLCD_voidGotoLocation(line1,index);
	   CLCD_voidWriteString("Enter Pass :");

	   while(index<4)
	   {
		  Get_key=KEYPAD_GetPressedKey();
     if(KEYPAD_NO_KeyPressed != Get_key )
       {
		 if(Get_key != pass[index])
		 {
			 state=1;
		 }
		   CLCD_voidGotoLocation(line2,index);
		   CLCD_voidWriteString("*");
		   index++;
       }
	   }


   if(state==0)
    {
	   CLCD_Clear();
	   CLCD_voidGotoLocation(line1,0);
	   CLCD_voidWriteString("Correct");
    }
   else
   {
	   CLCD_Clear();
	   CLCD_voidGotoLocation(line1,0);
	   CLCD_voidWriteString("Wrong");
   }


     _delay_ms(2000);


	   }
   return 0;
}
