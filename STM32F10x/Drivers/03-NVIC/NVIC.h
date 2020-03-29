/*******************************************************************************
**  FILENAME     : NVIC.h         			                                  **
**  VERSION      : 1.0                                                        **
**  DATE         : 27 Feb 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/


#ifndef NVIC_H
#define NVIC_H


#define E_OK   0
#define E_NOK  1

/******************************************************************
 * Function To Enable Interrupt .
 * return Type :- Std_ReturnType |E_OK: request accepted
							     |E_NOT_OK: request not accepted
 * Input Argument :- IRQNumber   from 0 to 80
 *****************************************************************/
Std_ReturnType NVIC_EnableIRQ(u8 IRQNumber);


/******************************************************************
 * Function To Disable Interrupt .
 * return Type :- Std_ReturnType |E_OK: request accepted
							     |E_NOT_OK: request not accepted
 * Input Argument :- IRQNumber   from 0 to 80
 *****************************************************************/
Std_ReturnType NVIC_DisableIRQ(u8 IRQNumber);


/******************************************************************
 * Function To Changes interrupt state to pending
 * return Type :- Std_ReturnType |E_OK: request accepted
							     |E_NOT_OK: request not accepted
 * Input Argument :- IRQNumber   from 0 to 80
 *****************************************************************/
Std_ReturnType NVIC_SetPendingIRQ(u8 IRQNumber);


/******************************************************************
 * Function To  Removes the pending state of an interrupt
 * return Type :- Std_ReturnType |E_OK: request accepted
							     |E_NOT_OK: request not accepted
 * Input Argument :- IRQNumber   from 0 to 80
 *****************************************************************/
Std_ReturnType NVIC_ClearPendingIRQ(u8 IRQNumber);

/******************************************************************
 * Function return status if the corresponding interrupt is active or not.
 * return Type :- Std_ReturnType |E_OK    : request accepted     (Active)
							     |E_NOT_OK: request not accepted (NOT Active)
 * Input Argument :- IRQNumber   from 0 to 80
 *****************************************************************/
Std_ReturnType NVIC_ISActive(u8 IRQNumber);

/**********************************************************************************************
 * Function return status if the corresponding interrupt is active or not.
 * return Type :- Std_ReturnType |E_OK    : request accepted     (Priority number correct)
							     |E_NOT_OK: request not accepted (NOT Priority number out of range)
 * Input Argument :- IRQNumber   from 0 to 80
 *                   Priority    from 0 t0
 *************************************************************************************************/
Std_ReturnType NVIC_SetPriority (u8 IRQNumber, u8 Priority);

/**********************************************************************************************
 * Function to generate interrupt software.
 * return Type :- Std_ReturnType |E_OK    : request accepted     (interrupt request number correct)
							     |E_NOT_OK: request not accepted (interrupt request number out of range)
 * Input Argument :- IRQNumber   from 0 to 80
 *************************************************************************************************/
Std_ReturnType NVIC_SoftwareInterrupt(u8 IRQNumber);

/**********************************************************************************************
 * Function to Enable IRQ Interrupts.
 * return Type :- void
 * Input Argument :- void
 *************************************************************************************************/
void NVIC_EnableAllInterrupt(void);

/**********************************************************************************************
 * Function to Disable IRQ Interrupts.
 * return Type :- void
 * Input Argument :- void
 *************************************************************************************************/
void NVIC_DisableAllInterrupt(void);

/**********************************************************************************************
 * Function to Disable all fault exceptions.
 * return Type :- void
 * Input Argument :- void
 *************************************************************************************************/
void NVIC_DisableAllFaults(void);


void NVIC_SetPriorityGrouping(u32 priority_grouping);




#endif
