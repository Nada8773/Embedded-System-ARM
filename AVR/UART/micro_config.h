/*
 * micro_config.h
 *
 *  Created on: ٢٦‏/١٠‏/٢٠١٦
 *      Author: ZAS
 */

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

#define CPU_F 1000000UL

typedef unsigned char uint8 ;

#define Bit_is_clear(Reg,num) (!(Reg&(1<<num)))
/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )


#endif /* MICRO_CONFIG_H_ */
