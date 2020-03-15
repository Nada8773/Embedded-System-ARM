/*******************************************************************************
**  FILENAME     : NVIC.c         			                                  **
**  VERSION      : 1.0                                                        **
**  DATE         : 27 Feb 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/

#include "STD_TYPE.h"
#include "NVIC.h"

#define MAX_IRQNUMBER      80
#define MIN_IRQNUMBER      0
#define NUMBER_OF_BITS     32
#define INTERRUPR_ID_SGI   240
#define MAX_PRIORITY       256
#define PRI_SHIFTING       4


/***************************************** System control block (SCB) ****************************/
#define AIRCR_Access_Key           (u32)0x5FA00000
#define AIRCR_PRIGROUP_Mask        (u32)0x00000700
#define AIRCR_Access_Key_Mask      (u32)0xFFFF0000

#define SCB_AIRCR                  *((volatile u32*)0xE000ED0C)

/***************************************** NVIC **************************************************/
#define BASE_Address_NVIC (u32)0xE000E000

typedef struct
{
	u32 Padding_0[64];  /* (0xE000E000 - 0xE000E0FC)  */
	u32 ISER[8];       /*Interrupt Set Enable Registers (0xE000E100-0xE000E11C)*/

	u32 Padding_1[24]; /* (0xE000E120 - 0xE000E17C) */
	u32 ICER[8];       /* Interrupt Clear Enable Registers (0xE000E180-0xE000E19C)*/

	u32 Padding_2[24];  /* (0xE000E1A0 - 0xE000E1FC) */
	u32 ISPR[8];       /* Interrupt Set-Pending Registers (0xE000E200-0xE000E21C)*/

	u32 Padding_3[24]; /* (0xE000E220 - 0xE000E27C) */
	u32 ICPR[8];       /*Interrupt Clear-Pending Registers ( 0xE000E280-0xE000E29C)*/

	u32 Padding_4[24]; /* (0xE000E2A0 - 0xE00E2FC) */
	u32 IABR[8];      /*Interrupt Active Status Registers (0xE000E300-0xE000E31C)*/

	u32 Padding_5[56]; /* (0xE000E320 - 0xE000E3FC)*/
	u8  IPR[240];     /*Interrupt Priority-Level Registers (0xE000E400-0xE000E4EF) */

	u32 Padding_6[644]; /* (0xE000E4F3 - 0xE000EEFC ) */
    u32 STIR; /*Software Trigger Interrupt Register (0xE000EF00) */
}NVIC_Reg;

volatile NVIC_Reg*   const    NVIC_t    = (NVIC_Reg*)BASE_Address_NVIC;



/******************************************************************
 * Function To Enable Interrupt .
 * return Type :- Std_ReturnType |E_OK: request accepted
							     |E_NOT_OK: request not accepted
 * Input Argument :- IRQNumber   from 0 to
 *****************************************************************/
Std_ReturnType NVIC_EnableIRQ(u8 IRQNumber)
{
	Std_ReturnType State =E_OK;
	if(IRQNumber<=MAX_IRQNUMBER )
	{
	  NVIC_t->ISER[IRQNumber/NUMBER_OF_BITS] = (1<<(IRQNumber % NUMBER_OF_BITS));

	}
	else
	{
	  State =E_NOK;
	}
	return State;
}


/******************************************************************
 * Function To Disable Interrupt .
 * return Type :- Std_ReturnType |E_OK: request accepted
							     |E_NOT_OK: request not accepted
 * Input Argument :- IRQNumber   from 0 to 80
 *****************************************************************/
Std_ReturnType NVIC_DisableIRQ (u8 IRQNumber)
{
	Std_ReturnType State =E_OK;
	if (IRQNumber<=MAX_IRQNUMBER )
	{
	  NVIC_t->ICER[IRQNumber/NUMBER_OF_BITS] = (1<<(IRQNumber % NUMBER_OF_BITS));
	}
	else
	{
	  State =E_NOK;
	}
	return State;
}


/******************************************************************
 * Function To  Removes the pending state of an interrupt
 * return Type :- Std_ReturnType |E_OK: request accepted
							     |E_NOT_OK: request not accepted
 * Input Argument :- IRQNumber   from 0 to 80
 *****************************************************************/
Std_ReturnType NVIC_SetPendingIRQ(u8 IRQNumber)
{
	Std_ReturnType State =E_OK;
	if( IRQNumber<=MAX_IRQNUMBER )
	{
	  NVIC_t->ISPR[IRQNumber/NUMBER_OF_BITS] = (1<<(IRQNumber % NUMBER_OF_BITS));
	}
	else
	{
	  State =E_NOK;
	}
	return State;
}



/******************************************************************
 * Function To  Removes the pending state of an interrupt
 * return Type :- Std_ReturnType |E_OK: request accepted
							     |E_NOT_OK: request not accepted
 * Input Argument :- IRQNumber   from 0 to
 *****************************************************************/
Std_ReturnType NVIC_ClearPendingIRQ(u8 IRQNumber)
{
	Std_ReturnType State =E_OK;
	if(IRQNumber<=MAX_IRQNUMBER )
	{
	  NVIC_t->ICPR[IRQNumber/NUMBER_OF_BITS] = (1<<(IRQNumber % NUMBER_OF_BITS));

	}
	else
	{
	  State =E_NOK;
	}
	return State;
}


/******************************************************************
 * Function return status if the corresponding interrupt is active or not.
 * return Type :- Std_ReturnType |E_OK    : request accepted     (Active)
							     |E_NOT_OK: request not accepted (NOT Active)
 * Input Argument :- IRQNumber   from 0 to
 *****************************************************************/
Std_ReturnType NVIC_ISActive(u8 IRQNumber)
{
	Std_ReturnType State =E_OK;
	if(!((NVIC_t->IABR[IRQNumber/NUMBER_OF_BITS]>>(IRQNumber % NUMBER_OF_BITS)) ==1))
	//if(!(NVIC_t->IABR[IRQNumber/NumberOfBits] & (1<<(IRQNumber % NumberOfBits))))
	{
		  State =E_NOK;
	}
	return State;
}


/**********************************************************************************************
 * Function Set periority.
 * return Type :- Std_ReturnType |E_OK    : request accepted     (Priority number correct)
							     |E_NOT_OK: request not accepted (NOT Priority number out of range)
 * Input Argument :- IRQNumber   from 0 to 56
 *                   Priority    from 0 to 255
 *************************************************************************************************/
Std_ReturnType NVIC_SetPriority (u8 IRQNumber, u8 Priority)
{
	Std_ReturnType State =E_OK;

    NVIC_t->IPR[IRQNumber] = Priority <<PRI_SHIFTING  ;

	return State;
}


/**********************************************************************************************
 * Function to generate interrupt software.
 * return Type :- Std_ReturnType |E_OK    : request accepted     (interrupt request number correct)
							     |E_NOT_OK: request not accepted (interrupt request number out of range)
 * Input Argument :- IRQNumber   from 0 to 239
 *************************************************************************************************/
Std_ReturnType NVIC_SoftwareInterrupt(u8 IRQNumber)
{

	Std_ReturnType State =E_OK;
	if( IRQNumber < INTERRUPR_ID_SGI )
	{
		NVIC_t->STIR =IRQNumber;
	}
	else
	{
		State =E_NOK;
	}
  return State;
}

/**********************************************************************************************
 * Function to Disable IRQ Interrupts ( Disable all exception except NMI and hard fault)
 * return Type :- void
 * Input Argument :- void
 *************************************************************************************************/
void NVIC_DisableAllInterrupt(void)
{
	 __asm ("CPSID i");
}

/**********************************************************************************************
 * Function to Enable IRQ Interrupts.
 * return Type :- void
 * Input Argument :- void
 *************************************************************************************************/
void NVIC_EnableAllInterrupt(void)
{
	__asm ("CPSIE i");
}

/**********************************************************************************************
 * Function to Disable all fault exceptions.
 * return Type :- void
 * Input Argument :- void
 *************************************************************************************************/
void NVIC_DisableAllFaults(void)
{

	__asm ("CPSID f");

}


void NVIC_SetPriorityGrouping(u32 priority_grouping)
{
	 u32 Local_u32Temp;
	 Local_u32Temp =SCB_AIRCR;
	// Local_u32Temp &= ~(AIRCR_Access_Key_Mask|AIRCR_PRIGROUP_Mask);
	 Local_u32Temp=0x0;
	 Local_u32Temp |= priority_grouping <<8;

	 SCB_AIRCR = AIRCR_Access_Key | Local_u32Temp;


}


