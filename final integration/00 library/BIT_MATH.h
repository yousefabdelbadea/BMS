/*********************************************************/
/* Author      : Ahmed Assaf                             */
/* Date        : 29 JUL 2020                             */
/* Version     : V01                                     */
/*********************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR,BIT)          VAR |=  (1 << (BIT))
#define CLR_BIT(VAR,BIT)          VAR &= ~(1 << (BIT)) 
#define GET_BIT(VAR,BIT)          ((VAR >> BIT) & 1  )
#define TOG_BIT(VAR,BIT)          VAR ^=  (1 << (BIT))
#define BIT_IS_CLEAR(REG,BIT)     (!((REG)&(1<<BIT)))


 /*check bit if it is clear in certain bit in any register*/
 #define BIT_IS_CLEAR(REG,BIT)     (!((REG)&(1<<BIT)))
 
 /*check bit if it is set in certain bit in any register*/
 #define BIT_IS_SET(REG,BIT)  	    ((REG)&(1<<BIT))
 
 /* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )




#define CLR_REG(VAR)           VAR =0


#endif 
