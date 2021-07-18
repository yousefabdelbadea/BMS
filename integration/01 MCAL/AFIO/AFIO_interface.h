#ifndef _AFIO_INTERFACE_H
#define _AFIO_INTERFACE_H

#define MAFIO_U8_SEL_PORTA			0
#define MAFIO_U8_SEL_PORTB			1
#define MAFIO_U8_SEL_PORTC			2

/* MAFIO_voidSetEXTIConfig --> Selects the source input for EXTI Line 	*/
/* I/P:-
 * Cpy_u8Line:  - Line of EXTI for which input selection is needed
				- Type:- u8
				- Available inputs: 1 : 15

 * Cpy_u8Port:	- Port which is to be Selected as input for EXTI line
				- Type:- u8
				- Available inputs:	* GPIO_U8_PORTA
									* GPIO_U8_PORTB
									* GPIO_U8_PORTC
																		*/
/* O/P: void 															*/
void MAFIO_voidSetEXTIConfig(u8 Cpy_u8Line, u8 Cpy_u8Port);
/************************************************************************/


#endif
