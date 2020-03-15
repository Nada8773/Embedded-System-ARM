
 /****************************************************************
 * Author  : Nada Mohamed 
 * Data    : 18 December ‎2019
 * Version : v01
 *****************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef  unsigned char           u8 ; 
typedef  unsigned short int      u16;
typedef  unsigned long int       u32;
									
typedef  signed char             s8 ;
typedef  signed short int        s16;
typedef  signed long int         s32;
									
typedef  float                   f32;
typedef  double                  f64;
typedef  long double             f96;
	  

#define  ERROR_STATUS            u8
#define  STD_TYPES_ERROR_OK     (ERROR_STATUS)1
#define  STD_TYPES_ERROR_NOK    (ERROR_STATUS)2

#define  NULL                   ((void *)0)

#endif	  
	  
	  
