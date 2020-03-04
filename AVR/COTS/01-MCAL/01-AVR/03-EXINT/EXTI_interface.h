/*
 * EXTI_interface.h
 *
 *  Created on: Jan 28, 2020
 *      Author: Esraa Awad
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_



#define EXTI_u8INT0     0
#define EXTI_u8INT1     1
#define EXTI_u8INT2     2

#define EXTI_u8_LOW_LEVEL 0
#define EXTI_u8_ON_CHANGE 1
#define EXTI_u8_FALLING_EDGE 2
#define EXTI_u8_RISING_EDGE 3



/*
* Description: A function to init external interrupts int0, int1, int2
*                according to he precompiled configuatuons 
*      Input: void
*      output: void
*/  
  
void EXTI_voidInit (void);


/*
* Description: A function to Set enable of external interrupts Int0 ,Int1,Int2
* Input : interrupt index ,Ranges are 
             1- EXTI_u8INT0
             2- EXTI_u8INT1
             3- EXTI_u8INT2
* output: Error Status
*/
ErrorStatus EXTI_errIntEnable(u8 Copy_u8Idx);

/*
* Description: A function to Set disable of external interrupts Int0 ,Int1,Int2
* Input : interrupt index ,Ranges are 
             1- EXTI_u8INT0
             2- EXTI_u8INT1
             3- EXTI_u8INT2
* output: Error Status
*/
ErrorStatus EXTI_errIntDisable(u8 Copy_u8Idx);

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
ErrorStatus EXTI_errSetSenseLevel(u8 Copy_u8_Idx,u8 Copy_u8Senselevel);

ErrorStatus EXTI_errSetCallBack (u8 Copy_u8Idx, void (*Copy_pvcallback)(void));

#endif /* EXTI_INTERFACE_H_ */
