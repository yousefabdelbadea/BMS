
#include"RCC_interface.h"
#include"DIO_interface.h"
#include"SYSTICK_INTERFACE.h"


int main()
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);
	MSTK_VidInit();
	MGPIO_VidSetPinDirection  ( GPIOA , PIN1 , OUTPUT_SPEED_2MHZ_PP  );
	while(1)
	{
		MGPIO_VidSetPinValue ( GPIOA , PIN1 , HIGH );
		_delay_ms(2000);
	    MGPIO_VidSetPinValue ( GPIOA , PIN1 , LOW );
	    _delay_ms(2000);
	}

}


