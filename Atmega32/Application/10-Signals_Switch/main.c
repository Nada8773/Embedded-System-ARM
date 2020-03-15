
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "INTGLB_interface.h"
#include "avr/io.h"

u8 flag;

/****************************************************************************
  Description :- 
               using interrupt for 3 switchs 
			   switch1 -> display SINWAVE signal on the Oscilloscope
			   switch2 -> display PWM     signal on the Oscilloscope
			   switch3 -> display SWTOOTH signal on the Oscilloscope

*******************************************************************************/

void Signal_SinWave()
{
	PORTA=0;
   flag=1;
}

void Signal_Swtooth()
{

	PORTA=0;
	flag=2;

}

void Signal_Pwm()
{
	PORTA=0;

  flag=3;
}

int main(void)

{

	for(u8 i=0;i<8;i++)
	{
	SetPinDir('A',i,1);   // Output Signal
	SetPinVal('A',i,1);   // Output Signal
	}
	SetPinDir('C',0,1);   // out led
	SetPinVal('C',0,0);

	SetPinDir('D',2,0);   // input sw 1 INT0
	SetPinVal('D',2,1); /* sw1 pull up */

	SetPinDir('D',3,0);   // input sw 2 INT1
	SetPinVal('D',3,1); /* sw2 pull up */

	SetPinDir('B',2,0);   // input sw 3  INT2
	SetPinVal('B',2,1); /* sw3 pull up */

	INT_voidEnableGlobal();
    EXTI_voidInit ();
	EXTI_errSetSenseLevel(EXTI_u8INT0,EXTI_u8_FALLING_EDGE);
	EXTI_errSetSenseLevel(EXTI_u8INT1,EXTI_u8_FALLING_EDGE);
	EXTI_errSetSenseLevel(EXTI_u8INT2,EXTI_u8_FALLING_EDGE);

	EXTI_errIntEnable(EXTI_u8INT0);
	EXTI_errIntEnable(EXTI_u8INT1);
	EXTI_errIntEnable(EXTI_u8INT2);

	EXTI_errSetCallBack (EXTI_u8INT0,Signal_SinWave);
	EXTI_errSetCallBack (EXTI_u8INT1,Signal_Swtooth);
	EXTI_errSetCallBack (EXTI_u8INT2, Signal_Pwm);

    /** Sinwave **/
	u8 sines[255]={127,130,133,136,139,143,146,149,152,155,158
			,161,164,167,170,173,176,179,181,184,187,190,193,195,198,200,203,205,
			208,210,213,215,217,219,221,223,225,227,229,231,233,235,236,238,239,241,
			242,243,245,246,247,248,249,250,250,251,252,252,253,253,253,254,254,254,254,254,254
			,254,253,253,252,252,251,251,250,249,248,247,246,245,244,243,241,240,239,237,235,234,
			232,230,228,226,224,222,220,218,216,214,211,209,207,204,202,199,196,194,191,188,186,
			183,180,177,174,171,168,166,163,159,156,153,150,147,144,141,138,135,132,129,125,122,
			119,116,113,110,107,104,101,98,95,91,88,86,83,80,77,74,71,68,66,63,60,58,55,52,50,47,
			45,43,40,38,36,34,32,30,28,26,24,22,20,19,17,15,14,13,11,10,9,8,7,6,5,4,3,3,2,2,1,1,
			0,0,0,0,0,0,0,1,1,1,2,2,3,4,4,5,6,7,8,9,11,12,13,15,16,18,19,21,23,25,27,29,31,33,35,37,
			39,41,44,46,49,51,54,56,59,61,64,67,70,73,75,78,81,84,87,90,93,96,99,102,105,108,111,115,
			118,121,124,127};

	while(1)
	{

        if(flag==3)
        {
        	SetPinVal('C',0,1); /* sw1 pull up */

        	for(u16 loop =0 ;loop<255;loop++)
        		{
        			PORTA=loop;
        		}
        		for(u16 loop =0 ;loop<=255;loop++)
        		{
        			PORTA=255-loop;
        		}
        }
        if(flag==2)
        {

        		for(u16 loop =0 ;loop<=255;loop++)
        		{
        			PORTA=0xff;
        		}
        		for(u16 loop =0 ;loop<=255;loop++)
        		{
        			PORTA=0;
        		}
        }
       if(flag==1)
        {
        		for(u16 loop =0 ;loop<=255;loop++)
        		{
        			PORTA=sines[loop];
        		}

        }


	}
}
