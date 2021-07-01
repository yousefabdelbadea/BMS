/******************************************************************************
 *
 * Module: Display
 *
 * File Name: Display.c
 *
 * Description: source file for display Driver
 *
 * Author: my team
	
 ******************************************************************************/
  #include "STD_TYPES.h"
  #include "BIT_MATH.h"
  
  #include "DIO_interface.h"
  #include "LCD.h"

 #include "BMS_config.h"
 #include "BMS.h"

 extern  Cell cells[NUM_OF_CELLS];

 extern  f32 overallStateOfCharge ;

 void Display_init()
 {
	 /*intialize LCD*/
	 LCD_init();

 }
  void Display_voidDataAcqusition(void)
{
	for (u8 i= 0 ; i<NUM_OF_CELLS;i++)
	{
		LCD_displayString("Cell_");
		LCD_intgerToString(cells[i].name);
		LCD_displayString(":");
		LCD_displayString(" T=");
		LCD_intgerToString(cells[i].Tempreture);
		LCD_displayString(" V=");

		LCD_intgerToString(cells[i].Voltage);
		LCD_displayString(" C=");

		LCD_intgerToString(cells[i].Current);

		LCD_displayStringRowColumn(1,0,"state of charge:");
		LCD_intgerToString(cells[i].stateOfCharge);
		LCD_displayCharacter('%');


		_delay_ms(1000);

		LCD_clearScreen();

	}

	  LCD_intgerToString(overallStateOfCharge);
	  _delay_ms(1000);
	  LCD_clearScreen();






}

  
  

