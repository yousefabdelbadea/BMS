#include "RCC_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "LCD.h"
#include "SYSTICK_INTERFACE.h"
#include "MULTIPLEXER_interface.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

u32 temp_sensors[6] ;
u32 current_senssors[3];
u32 n;

void Data_voidAcqusition(void);

int main()
{
	RCC_voidInitSysClock();
	/*Generate clock for GPPIOA*/
	RCC_voidEnableClock(RCC_APB2 , 2);
	/*Set direction of GPIOA pin 0 as input analog*/
	MGPIO_VidSetPinDirection( GPIOA , PIN0 , INPUT_ANLOG );
	/*Generate clock for GPPIOB*/
	RCC_voidEnableClock(RCC_APB2 , 3);
	/*Generate clock for ADC1*/
	RCC_voidEnableClock(RCC_APB2 , 9);
	/*initalizing ADC_1*/
	ADC_VoidInit();
	/*start coversion of ADC_1*/
	start_coversion();
	/*intialize LCD*/
	LCD_init();
	/*initalize Multiplexer */
	HMultiplexer_voidInit();

	for(u32 n =0 ; n<500000 ; n++){}
	while(1)
	{
		Data_voidAcqusition();

		for( n =0 ; n<500000 ; n++){}
	}
	return 1;
}

void Data_voidAcqusition(void)
{

	u8 i,k;
	u8 counter = 0;
	for(i=0 ; i<6 ;i++)
	{
		HChannelSelection_void(counter);
		for( n =0 ; n<100 ; n++){}
		temp_sensors[i] = Get_Temp();
		LCD_displayString("TEMP_");
		LCD_intgerToString(i+1);
		LCD_displayString(": ");
		LCD_intgerToString(temp_sensors[i]);
		for( n =0 ; n<500000 ; n++){}
		LCD_clearScreen();
		counter++;
	}

	for( k=0 ; k<3 ;k++)
	{
		HChannelSelection_void(counter);
		for( n =0 ; n<100 ; n++){}
		current_senssors[k] = Get_Current();
		LCD_displayString("Current_");
		LCD_intgerToString(k+1);
		LCD_displayString(": ");
		LCD_intgerToString(current_senssors[k]);
		for( n =0 ; n<500000 ; n++){}
		LCD_clearScreen();
		counter++;
	}
	counter = 0;


	/*
	HChannelSelection_void(8);
	current_senssors[0] = Get_Current();
	LCD_displayString("Current_");
	LCD_intgerToString(1);
	LCD_displayString(": ");
	LCD_intgerToString(current_senssors[0]);
	for( n =0 ; n<500000 ; n++){}
	LCD_clearScreen();
*/
}
