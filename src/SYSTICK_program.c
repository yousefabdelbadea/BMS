/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/


#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"SYSTICK_INTERFACE.h"
#include"SYSTICK_REG.h"

void ( * MSTK_CallBack ) ( void );

void SysTick_Handler(void){

	MSTK_CallBack();

}

void MSTK_VidSetCallBack( void (*ptr)(void) ){

	MSTK_CallBack = ptr;
}

void MSTK_VidInit( void ){

	// Enable Systick Interrupt  -  Clock = AHB / 8 - Stop Systic
	MSTK->CTRL = 0x00000002;

}


void MSTK_VidStart( u32 Copy_PreloadValue ){

	// AHB = EXT = 8MHZ & CLOCK OF MSTK = AHB / 8 = 8MHZ / 8 = 1MHZ = 1 Micro For Each Count
	//Load Reload Value
	MSTK->LOAD = Copy_PreloadValue - 1;
	//Clear Val Register
	MSTK->VAL  = 0 ;
	//Enable Systick
	SET_BIT( MSTK->CTRL , 0 );

}

void MSTK_VidINTStatus( u8 Copy_u8Status ){

	 MSTK->CTRL &= ~( 1 << 1 );
	 MSTK->CTRL |=  ( Copy_u8Status << 1 );

}

u8 MSTK_u8ReadFlag( void ){

	return ( GET_BIT( MSTK->CTRL , 16 ) );

}

void _delay_ms( u32 Copy_u32Time ){

	MSTK_VidInit();
	/* Disable INT */
	MSTK_VidINTStatus( MSTK_INT_DIS );
	MSTK_VidStart( Copy_u32Time * 1000 );
	/* Wiat Flag Polling */
	while( MSTK_u8ReadFlag() == 0 );

}


/* Suppose That The Clock System (AHB) = 8MHZ EXT & The Systick Clock Is = AHB/8 */
void _delay_us( u32 Copy_u32Time ){

	MSTK_VidInit();
	/* Disable INT */
	MSTK_VidINTStatus( MSTK_INT_DIS );
	MSTK_VidStart( Copy_u32Time );
	/* Wiat Flag Polling */
	while( MSTK_u8ReadFlag() == 0 );

}
