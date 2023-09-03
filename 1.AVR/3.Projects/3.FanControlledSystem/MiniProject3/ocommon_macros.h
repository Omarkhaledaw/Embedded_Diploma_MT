/*
 * ocommon_macros.h
 *
 *  Created on: Oct 5, 2022
 *      Author: Dell
 */

#ifndef OCOMMON_MACROS_H_
#define OCOMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET(REG,BIT) (REG = REG | (1<<BIT))
/* Clear a certain bit in any register */
#define CLEAR(REG,BIT) (REG = REG & ~(1<<BIT))
/* Toggle a certain bit in any register */
#define TOGGLE(REG,BIT) (REG = REG ^ (1<<BIT))
/* Rotate right the register value with specific number of rotates */
#define RR(REG,BITS) (REG = ((REG>>BITS) | (REG<<8-BITS)) )
/* Rotate left the register value with specific number of rotates */
#define RL(REG,BITS) (REG = ((REG<<BITS) | (REG>>8-BITS)) )
/* Check if a specific bit is set in any register and return true if yes */
#define CHECK_SET(REG,BIT) ( (REG & (1<<BIT)) )
/* Check if a specific bit is cleared in any register and return true if yes */
#define CHECK_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#define GET_BIT(REG,BIT) ( ( REG & (1<<BIT) ) >> BIT )

#endif /* OCOMMON_MACROS_H_ */
