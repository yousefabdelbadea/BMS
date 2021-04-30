/*
 * Common_Macros.h
 *
 *  Created on: Aug 30, 2020
 *      Author: H
 */

#ifndef PROJ_COMMON_MACROS_H_
#define PROJ_COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Check if a specific bit is set in any register*/
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

/*GET BIT_NO Value*/
#define GET_BIT(REG,BIT)  ((REG>>BIT) & 0x01)

#endif /* PROJ_COMMON_MACROS_H_ */
