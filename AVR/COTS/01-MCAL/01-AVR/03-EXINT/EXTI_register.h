/**********************************************/
/* Author: Alzahraa Elsallakh                 */
/* Version: V01                               */
/* Date: 4 Feb 2020                           */ 
/* Layer: MCAL                                */  
/* Component: EXTI                            */                
/* File Name: EXTI_register.h                 */ 
/**********************************************/

/* Preporcessor File Guard */
#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_

#define MCUCR         * ( (volatile u8*) 0x55)    /* Control Register */
#define MCUCR_ISC00   0                           /* Int0 Sense Control Bit 0 */
#define MCUCR_ISC01   1                           /* Int0 Sense Control Bit 1 */
#define	MCUCR_ISC10   2                           /* Int1 Sense Control Bit 0 */
#define MCUCR_ISC11   3                           /* Int1 Sense Control Bit 1 */

#define MCUCSR        * ( (volatile u8*) 0x54)    /* Control and Status Register */
#define MCUCSR_ISC2   6

#define GICR          * ( (volatile u8*) 0x5B)    /* General Control Register */
#define GICR_INT0     6                           /* Int0 Enable */
#define GICR_INT1     7                           /* Int1 Enable */
#define GICR_INT2     5                           /* Int2 Enable */

#define GIFR          * ( (volatile u8*) 0x5A)    /* Control Flag Register */

#define SREG          * ( (volatile u8*) 0x5F)

#endif
