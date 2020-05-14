/******************************************************************************
 * @file     Flash.c
 * @author   Nada Mohamed
 * @version  V1.0.1
 * @date     3-May-2020
 * @Platform STM32F10X
 * @brief    This file is to be used as an implementation of the Flash .
 ******************************************************************************/
#include "STD_TYPES.h"
#include "Flash.h"


/***** Macros  ************************/
#define FLASH_CR_LOCK      (u32)0x80
#define FLASH_CR_PER       (u32)0x2
#define FLASH_CR_STRT      (u32)0x40
#define FLASH_SR_BSY       (u32)0x1
#define FLASH_CR_MER       (u32)0x4
#define FLASH_CR_PG        (u32)0x1
#define FLASH_SR_EOP       (u32)0x20
#define FLASH_ACR_HLFCYA   (u32)0x8
#define WORD_SIZE           16U
#define HALF_WORD_SIZE      8U

/**************************************/
typedef struct
{
	u32 ACR 		;
	u32 KEYR 		;
	u32 OPTKEYR 	;
	u32 SR 			;
	u32 CR			;
	u32 AR		    ;
	u32 Reserved    ;
	u32 OBR         ;
	u32 WRPR        ;
}Flash_t ;

volatile Flash_t* const Flash = (Flash_t*)0x40022000 ;

/***************************************************************
 * @brief This function to unlock the flash (unlock the FPEC.)
 * @param void
 * @return Std_ReturnType
 *                  E_OK     :- The request is accepted
 *                  E_NOT_OK :- The request is not accepted
 ***************************************************************/
Std_ReturnType Flash_Unlock(void)
{
	Std_ReturnType Flash_Status = E_OK;
	Flash->KEYR = 0x45670123 ;
	Flash->KEYR = 0xCDEF89AB ;

	if(Flash->CR & FLASH_CR_LOCK )
	{
		Flash_Status = E_NOT_OK;
	}
	else
	{
		/* Nothing */
	}
	return Flash_Status;
}

/****************************************************************
 * @brief This function to lock the flash
 *         (t indicates that the FPEC and FLASH_CR are locked.)
 * @param void
 * @return void
 *****************************************************************/
void Flash_lock(void)
{
	Flash->CR |= FLASH_CR_LOCK ;
}

/****************************************************************
 * @brief This function to erase the specific page
 * @param Flash_PageAdress
 *            the page address to erase it
 * @return void
 *****************************************************************/
extern void Flash_ErasePage(u32 Flash_PageAdress)
{
	Flash->CR |= FLASH_CR_PER ;      /* Page erase */
	Flash->AR =  Flash_PageAdress ;  /* page Address to erase  */
	Flash->CR |= FLASH_CR_STRT ;     /* triggers an ERASE operation  */

	while(Flash->SR & FLASH_SR_BSY);
	Flash->CR &= ~(FLASH_CR_PER) ;
	Flash->SR |= FLASH_SR_EOP ;     /* Reset End of operation */
}

/****************************************************************
 * @brief This function to erase all the flash
 * @param void
 * @return void
 *****************************************************************/
void Flash_EraseMass(void)
{
	Flash->CR |= FLASH_CR_MER  ;      /* Page erase */

	Flash->CR |= FLASH_CR_STRT ;     /* triggers an ERASE operation  */

	Flash->SR |= FLASH_SR_EOP ;     /* Reset End of operation */
}

/****************************************************************
 * @brief This function to write word(4bytes) in flash
 * @param Flash_Address -> Destination flash address
 *        Flash_Data    -> Data To store in flash
 * @return Std_ReturnType
 *                  E_OK     :- The request is accepted
 *                  E_NOT_OK :- The request is not accepted
 *****************************************************************/
Std_ReturnType Flash_WriteWord(void* Flash_Address, u32 Flash_Data)
{
	Std_ReturnType Flash_Status ;

	Flash->CR |= FLASH_CR_PG ;

	*((u16*)Flash_Address) = (u16)Flash_Data ;
	while(Flash->SR & FLASH_SR_BSY);
	Flash->SR |= FLASH_SR_EOP ;     /* Reset End of operation */


	*((u16*)Flash_Address+1) = (u16)(Flash_Data >> WORD_SIZE) ;
	while(Flash->SR & FLASH_SR_BSY);
	Flash->SR |= FLASH_SR_EOP ;     /* Reset End of operation */

	Flash->CR &= ~(FLASH_CR_PG) ;

	if(*((u32*)Flash_Address) ==Flash_Data)
	{
		Flash_Status = E_OK;
	}
	else
	{
		Flash_Status = E_NOT_OK;
	}
	return Flash_Status;
}

/****************************************************************
 * @brief This function to write half word (2bytes)in flash
 * @param Flash_Address -> Destination flash address
 *        Flash_Data    -> Data To store in flash
 * @return Std_ReturnType
 *                  E_OK     :- The request is accepted
 *                  E_NOT_OK :- The request is not accepted
 *****************************************************************/
Std_ReturnType Flash_WriteHalfWord(void* Flash_Address, u16 Flash_Data)
{
	Std_ReturnType Flash_Status ;

	Flash->CR   |= FLASH_CR_PG ;

	*((u16*)Flash_Address) = (u16)Flash_Data ;

	while(Flash->SR & FLASH_SR_BSY);

	Flash->SR |= FLASH_SR_EOP ;     /* Reset End of operation */
	Flash->CR   &= ~(FLASH_CR_PG) ;

	if(*((u16*)Flash_Address) ==Flash_Data)
	{
		Flash_Status = E_OK;
	}
	else
	{
		Flash_Status = E_NOT_OK;
	}
	return Flash_Status;
}

/****************************************************************
 * @brief This function to write (1bytes)in flash
 * @param *Flash_DesAddress -> Destination flash address
 *         Data_Address     -> source Address from RAM
 *         Number_Of_Byte   -> Number of bytes to transmit
 * @return Std_ReturnType
 *                  E_OK     :- The request is accepted
 *                  E_NOT_OK :- The request is not accepted ( the sector may not erased)
 *****************************************************************/

Std_ReturnType Flash_WriteProgram(void* Flash_DesAddress,void* Data_Address , u32 Number_Of_Byte)
{
	Std_ReturnType Flash_Status =E_OK;

	Flash->CR   |= FLASH_CR_PG ;

	for(u8 idx =0 ;idx < Number_Of_Byte/2 ;idx++)
	{
		if(*((u16*)Flash_DesAddress+idx) != 0xFFFF)
		{
			Flash_Status =E_NOT_OK;
			break;
		}
		*((u16*)Flash_DesAddress+idx) = (u16)*((u16*)Data_Address+idx) ;
		while(Flash->SR & FLASH_SR_BSY);
		Flash->SR |= FLASH_SR_EOP ;     /* Reset End of operation */
	}

	Flash->CR   &= ~(FLASH_CR_PG) ;

	return 	Flash_Status ;
}

