

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KEYPAD_interface.h"

#include "KEYPAD_config.h"

#include <util/delay.h>
#include <string.h>
/*****************************************************
 Description :- moving a pattern left - right - up -down 
                By using keypad 
*****************************************************/
int main(void)
{
	u8 Get_Key;
	u8 line=1;
	s8 index=0;
	u8 size=0;
	u8 *str="Nada";

	while(str[size] !='\0')
	{
		size++;
	}


   PortInitialize();
   CLCD_voidInitialize();



	   CLCD_voidGotoLocation(line,index);
	   CLCD_voidWriteString(str);

   while(1)
   {

	  Get_Key=KEYPAD_GetPressedKey();
	     if(Get_Key==5) //left
	     {
             index--;
             if(index<0)index=0;
             CLCD_Clear();
   	         CLCD_voidGotoLocation(line,index);
   	         CLCD_voidWriteString(str);
	     }
	     if(Get_Key==7) //right
	     {
             index++;
             if(index>15-size)index=15-size;
             CLCD_Clear();
   	         CLCD_voidGotoLocation(line,index);
   	         CLCD_voidWriteString(str);
	     }
	     if(Get_Key==2) //line1
	     {
	    	 line=1;
		      CLCD_Clear();
		      CLCD_voidGotoLocation(line,index);
		      CLCD_voidWriteString(str);

	     }
	     if(Get_Key==10) //line2
	     {
	    	 line=2;
		      CLCD_Clear();
		      CLCD_voidGotoLocation(line,index);
		      CLCD_voidWriteString(str);

	     }





	   }
   return 0;
}
