
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "MULTIPLEXER_interface.h"
#include "MULTIPLEXER_config.h"

void HMultiplexer_voidInit(void)
{
	MGPIO_VidSetPinDirection  (  SELECTION_PORT , SELECT_0 , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_VidSetPinDirection  (  SELECTION_PORT , SELECT_1 , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_VidSetPinDirection  (  SELECTION_PORT , SELECT_2 , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_VidSetPinDirection  (  SELECTION_PORT , SELECT_3 , OUTPUT_SPEED_2MHZ_PP );

}

void HChannelSelection_void(u8 channel)
{
	switch (channel)
	{
	case 0:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , LOW );
		break;
	case 1:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , LOW );
		break;
	case 2:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , LOW );
		break;
	case 3:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , LOW );
		break;
	case 4:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , LOW );
		break;
	case 5:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , LOW );
		break;
	case 6:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , LOW );
		break;
	case 7:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , LOW );
		break;
	case 8:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , HIGH );
		break;
	case 9:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , HIGH );
		break;
	case 10:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , HIGH );
		break;
	case 11:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , HIGH );
		break;
	case 12:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , HIGH );
		break;
	case 13:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , HIGH );
		break;
	case 14:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , LOW );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , HIGH );
		break;
	case 15:
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_0 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_1 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_2 , HIGH );
		MGPIO_VidSetPinValue ( SELECTION_PORT, SELECT_3 , HIGH );
		break;
	}

}
