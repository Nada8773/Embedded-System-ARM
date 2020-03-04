/*
 * EXTI_program.c
 *
 *  Created on: Jan 28, 2020
 *      Author: Esraa Awad
 */

#include "BIT_MATHS.h"
#include "STD_TYPES.h"
#include "Delay_interface.h"
#include "DIO_interface.h"
#include "port_interface.h"
#include "EXTI_register.h"
#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"



static void (*EXTI_pvcallBackFunc[3]) (void) = {NULL,NULL,NULL};
void EXTI_voidInit (void)
{
  #if EXTI_u8_INT0_SENSE == LOW_LEVEL
    CLR_BIT(MCUCR,MCUCR_ISC00);
    CLR_BIT(MCUCR,MCUCR_ISC01);
  #elif EXTI_u8_INT0_SENSE == ON_CHANGE
    SET_BIT(MCUCR,MCUCR_ISC00);
    CLR_BIT(MCUCR,MCUCR_ISC01);  
  #elif EXTI_u8_INT0_SENSE == FALLING_EDGE
    CLR_BIT(MCUCR,MCUCR_ISC00);
    SET_BIT(MCUCR,MCUCR_ISC01); 
   #elif EXTI_u8_INT0_SENSE == RISING_EDGE
    SET_BIT(MCUCR,MCUCR_ISC00);
    SET_BIT(MCUCR,MCUCR_ISC01); 
  #else
    #error "Wrong EXTI_u8_INT0_SENSE Configuration"
  #endif
  
  
  #if EXTI_u8_INT1_SENSE == LOW_LEVEL
    CLR_BIT(MCUCR,MCUCR_ISC10);
    CLR_BIT(MCUCR,MCUCR_ISC11);
  #elif EXTI_u8_INT1_SENSE == ON_CHANGE
    SET_BIT(MCUCR,MCUCR_ISC10);
    CLR_BIT(MCUCR,MCUCR_ISC11);  
  #elif EXTI_u8_INT1_SENSE == FALLING_EDGE
    CLR_BIT(MCUCR,MCUCR_ISC10);
    SET_BIT(MCUCR,MCUCR_ISC11); 
   #elif EXTI_u8_INT1_SENSE == RISING_EDGE
    SET_BIT(MCUCR,MCUCR_ISC10);
    SET_BIT(MCUCR,MCUCR_ISC11); 
  #else
    #error "Wrong EXTI_u8_INT1_SENSE Configuration"
  #endif
  
  
 
  #if EXTI_u8_INT2_SENSE == FALLING_EDGE
    CLR_BIT(MCUCSR,MCUCSR_ISC2);
    
   #elif EXTI_u8_INT2_SENSE == RISING_EDGE
    SET_BIT(MCUCSR,MCUCSR_ISC2);
     
  #else
    #error "Wrong EXTI_u8_INT2_SENSE Configuration"
  #endif
  
 
  
  
  #if EXTI_u8_INT0_CONTROL == ENABLED
    SET_BIT(GICR,GICR_INT0);
  #elif EXTI_u8_INT0_CONTROL == DISABLED
    SET_BIT(GICR,GICR_INT0);
  #else
    #error "Wron EXTI_u8_INT0_CONTROL Configuration"
  #endif
  
  
  
  
   #if EXTI_u8_INT1_CONTROL == ENABLED
    SET_BIT(GICR,GICR_INT0);
  #elif EXTI_u8_INT1_CONTROL == DISABLED
    SET_BIT(GICR,GICR_INT0);
  #else
    #error "Wron EXTI_u8_INT0_CONTROL Configuration"
  #endif
  
  
   #if EXTI_u8_INT2_CONTROL == ENABLED
    SET_BIT(GICR,GICR_INT0);
  #elif EXTI_u8_INT2_CONTROL == DISABLED
    SET_BIT(GICR,GICR_INT0);
  #else
    #error "Wron EXTI_u8_INT2_CONTROL Configuration"
  #endif
}

/*
* Description: A function to Set enable of external interrupts Int0 ,Int1,Int2
* Input : interrupt index ,Ranges are 
             1- EXTI_u8INT0
             2- EXTI_u8INT1
             3- EXTI_u8INT2
* output: Error Status
*/
ErrorStatus EXTI_errIntEnable(u8 Copy_u8Idx)     // cant use #if as these parameters passes in run time nor preprocessor

{
  ErrorStatus Local_Error =OK;
  
  switch (Copy_u8Idx)
  {
    case EXTI_u8INT0: SET_BIT(GICR,GICR_INT0); break;
    case EXTI_u8INT1: SET_BIT(GICR,GICR_INT1); break;
    case EXTI_u8INT2: SET_BIT(GICR,GICR_INT2); break;
    default: Local_Error=NOK;
    
  }
  
  return Local_Error;
  
  

}

/*
* Description: A function to Set disable of external interrupts Int0 ,Int1,Int2
* Input : interrupt index ,Ranges are 
             1- EXTI_u8INT0
             2- EXTI_u8INT1
             3- EXTI_u8INT2
* output: Error Status
*/
ErrorStatus EXTI_errIntDisable(u8 Copy_u8Idx)
{
  ErrorStatus Local_Error =OK;
  
  switch (Copy_u8Idx)
  {
    case EXTI_u8INT0: CLR_BIT(GICR,GICR_INT0); break;
    case EXTI_u8INT1: CLR_BIT(GICR,GICR_INT1); break;
    case EXTI_u8INT2: CLR_BIT(GICR,GICR_INT2); break;
    default: Local_Error=NOK;
    
  }
  
  return Local_Error;
  

}

/*
* Description: A function to Set the required sense level of externl interrupt 
               int0 ,int1,int2
* Input : 1-interrupt index ,Ranges are 
             1- EXTI_u8INT0
             2- EXTI_u8INT1
             3- EXTI_u8INT2
             
          2- required sense level
             1-EXTI_u8_LOW_LEVEL
             2-EXTI_u8_FALLING_EDGE
             3-EXTI_u8_RISING_EDGE
             4-EXTI_u8_ON_CHANGE             
* output: Error Status
*/
ErrorStatus EXTI_errSetSenseLevel(u8 Copy_u8Idx,u8 Copy_u8Senselevel)
{
  ErrorStatus Local_Error =OK;
  
  switch (Copy_u8Idx)
  {
    case  EXTI_u8INT0:
      if (Copy_u8Idx == EXTI_u8_LOW_LEVEL)
      { 
        CLR_BIT(MCUCR,MCUCR_ISC00);
        CLR_BIT(MCUCR,MCUCR_ISC01);
      }
      
      else if (Copy_u8Idx == EXTI_u8_ON_CHANGE)
      {
        SET_BIT(MCUCR,MCUCR_ISC00);
        SET_BIT(MCUCR,MCUCR_ISC01);
      }
      
      else if (Copy_u8Idx  == EXTI_u8_FALLING_EDGE)
      {
        CLR_BIT(MCUCR,MCUCR_ISC00);
        SET_BIT(MCUCR,MCUCR_ISC01); 
      }
      else if (Copy_u8Idx  == EXTI_u8_RISING_EDGE)
       {
    	  SET_BIT(MCUCR,MCUCR_ISC00);
    	  SET_BIT(MCUCR,MCUCR_ISC01);
       }
        
      else
      {
        Local_Error = NOK;
      }
      break;
      
      
      case  EXTI_u8INT1:
      if (Copy_u8Idx == EXTI_u8_LOW_LEVEL)
      { 
        CLR_BIT(MCUCR,MCUCR_ISC10);
        CLR_BIT(MCUCR,MCUCR_ISC11);
      }
      
      else if (Copy_u8Idx == EXTI_u8_ON_CHANGE)
      {
        SET_BIT(MCUCR,MCUCR_ISC10);
        SET_BIT(MCUCR,MCUCR_ISC11);
      }
      
      else if (Copy_u8Idx  == EXTI_u8_FALLING_EDGE)
      {
        CLR_BIT(MCUCR,MCUCR_ISC10);
        SET_BIT(MCUCR,MCUCR_ISC11); 
      }
      else if (Copy_u8Idx  == EXTI_u8_RISING_EDGE)
       {
    	  SET_BIT(MCUCR,MCUCR_ISC10);
        
    	  SET_BIT(MCUCR,MCUCR_ISC11);
       }
      else
      {
        Local_Error = NOK;
      }
      break;
      
      
      case  EXTI_u8INT2:
      
      if (Copy_u8Idx  == EXTI_u8_FALLING_EDGE)
      {
        CLR_BIT(MCUCSR,MCUCSR_ISC2);
       
      }
      else if (Copy_u8Idx  == EXTI_u8_RISING_EDGE)
       SET_BIT(MCUCSR,MCUCSR_ISC2);
       
        
      else
      {
        Local_Error = NOK;
      }
      break;

  }
  
  return Local_Error;
}

ErrorStatus EXTI_errSetCallBack (u8 Copy_u8Idx, void (*Copy_pvcallback)(void))
{
  
  ErrorStatus Local_Error =  OK;
   
   
  if (Copy_pvcallback != NULL)
  {
    if (Copy_u8Idx <3 )
    {
      EXTI_pvcallBackFunc[Copy_u8Idx]=Copy_pvcallback;
    }
    else
    {
      Local_Error=NOK;
    }
  }
  
  else 
    
    {
      Local_Error=NULLPOINTER;
    }
  
  
  
  return Local_Error;
  
    
}

void __vector_1  (void)
{
  if (EXTI_pvcallBackFunc[ EXTI_u8INT0]!=NULL)
  {
    EXTI_pvcallBackFunc[ EXTI_u8INT0]();
  }
 
}

void __vector_2  (void)
{
  if (EXTI_pvcallBackFunc[ EXTI_u8INT1]!= NULL)
  {
    EXTI_pvcallBackFunc[ EXTI_u8INT1]();
  }
 
}

void __vector_3  (void)
{
  if (EXTI_pvcallBackFunc[ EXTI_u8INT2]!= NULL)
  {
    EXTI_pvcallBackFunc[ EXTI_u8INT2]();
  }

}

