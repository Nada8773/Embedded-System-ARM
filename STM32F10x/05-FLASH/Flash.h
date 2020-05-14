/******************************************************************************
 * @file     Flash.h
 * @author   Nada Mohamed
 * @version  V1.0.1
 * @date     3-May-2020
 * @Platform STM32F10X
 * @brief    This file is to be used as an implementation of the Flash .
 ******************************************************************************/


/***** Functions Prototype */
extern void Flash_lock(void);
extern Std_ReturnType Flash_Unlock(void);
extern void Flash_ErasePage(u32 Flash_PageAdress);
extern void Flash_EraseMass(void);
extern Std_ReturnType Flash_WriteWord(void* Flash_Address, u32 Flash_Data);
extern Std_ReturnType Flash_WriteHalfWord(void* Flash_Address, u16 Flash_Data);
extern Std_ReturnType Flash_WriteProgram(void* Flash_DesAddress,void* Data_Address , u32 Number_Of_Byte);

