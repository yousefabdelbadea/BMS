/*
 * USART_Program.c
 *
 *  Created on: May 16, 2021
 *      Author: Yousef
 */

#include "USART_Config.h"
#include "USART_Private.h"
#include "USART_Interface.h"
#include "DIO_interface.h"
#include "AFIO_interface.h"

#include "STD_TYPES.h"
#include "BIT_MATH.h"

typedef struct
{
	u32 volatile SR;
	u32 volatile DR;
	u32 volatile BRR;
	u32 volatile CR[3];
	u32 volatile GTPR;
} USART_t;

#define USART2 ((volatile USART_t*) 0x40004400)


void MUART_voidInit(void)
{
	/*Baud Rate 9600*/
	USART2 -> BRR = 0x341;
	/*Enable Uart Recieve*/
	SET_BIT(USART2 -> CR[0], 2);
	/*Enable Uart Transmit*/
	SET_BIT(USART2 -> CR[0], 3);
	/*Enable Uart*/
	SET_BIT(USART2 -> CR[0],13);
}


void MUART_voidTransmitSynch(u8 word[])
{

	u8 Local_u8Currentletter = 0;
	while(word[Local_u8Currentletter] != '\0')
	{
		while( (GET_BIT((USART2 -> SR), 7)) == 0 );
		USART2 -> DR = word[Local_u8Currentletter];
		Local_u8Currentletter++;
	}

}

void MUART_voidTransmitByteSynch(u8 Copy_u8Data)
{
	/*0: Data is not transferred to the shift register*/
	/*1: Data is transferred to the shift register*/
	while( (GET_BIT((USART2 -> SR), 7)) == 0 ){};

	USART2 ->DR = Copy_u8Data;
}



