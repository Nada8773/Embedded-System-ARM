#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "DIO_interface.h"




void main(void)
{
	u8 SwitchState;
	/* Set C0 Direction to input */
	SetPinDir('C',0,0);
	
	/* Set C1 Direction to output */
	SetPinDir('C',1,1);

	while(1)
	{
	SwitchState=GetPinVal('C',0);
	if(SwitchState ==0)
	{
		/* Set Led On */
		SetPinVal('C',1,1);
	}
	else
	{
		/* Set Led Off */
		SetPinVal('C',1,0);
	}

	}
}
