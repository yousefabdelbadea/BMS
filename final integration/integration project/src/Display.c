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
#include "TIMER_interface.h"

  #include "delay.h"
  #include "LCD.h"

 #include "Data_Acqusition.h"
 #include "ThermalManagment.h"

 #include "BMS_config.h"
 #include "BMS.h"

 extern  Cell cells[NUM_OF_CELLS];

 extern  f32 overallStateOfCharge ;

 extern TIM_HandleTypeDef Timer_3;
 extern TIM_HandleTypeDef Timer_2;

 void Display_init()
 {
	 /*intialize LCD*/
	 LCD_init();

 }
void Display_voidDataAcqusition(void)
{
	LCD_clearScreen();

	u8 index =1 ;

	for (u8 i= 0 ; i<6 ;i++)
	{   LCD_goToRowColumn(0,0);
		LCD_displayString("C");
		FloatToString(cells[i].name);
		LCD_displayString(":");
		LCD_displayString("T=");
		FloatToString(cells[i].Tempreture);

		LCD_displayString(" V=");
		FloatToString(cells[i].Voltage);
        LCD_goToRowColumn(1,0);
        LCD_displayString("B");
        LCD_intgerToString(index);
        if(i%2 != 0)
        {
        	index+=1;

        }

        LCD_displayString("_I:");
		FloatToString(cells[i].Current);

		LCD_displayString(" S:");

		LCD_intgerToString((u32)cells[i].stateOfCharge);



		_delay_ms(10000);
		LCD_clearScreen();

	}


}

void Display_thermalData(void)
{

	//    	LCD_goToRowColumn(0,0);
	//    	LCD_displayString("Battery In Safe Mode ");
	//    	LCD_goToRowColumn(1,0);
	//    	LCD_displayString("Fan Turn Off ");
	    	Display_voidDataAcqusition();
	    	LCD_goToRowColumn(0,0);
	    	LCD_displayString("Cell-1 Overheating");
	    	LCD_goToRowColumn(1,0);
	    	LCD_displayString("Fan Speed=");
	    	LCD_intgerToString(50);
	    	 Set_DutyCycle(&Timer_2,50,TIM_Channel_4);
	    	 LCD_goToRowColumn(0,0);
	    	  LCD_displayString("Cell-1 Overheating");
	    	  LCD_goToRowColumn(1,0);
	    	  LCD_displayString("Fan Speed=");
	    	  LCD_intgerToString(100);
	    	  Set_DutyCycle(&Timer_2,100,TIM_Channel_4);
	    	  LCD_clearScreen();
	    	  LCD_goToRowColumn(0,0);
	    	  LCD_displayString("cell-1 in danger");

		  Set_DutyCycle(&Timer_2,100,TIM_Channel_4);

		    /*if (timer_exitinson == 1 ){
		    	//TOGGLE_BIT(GPIOA_ODR,1);
		    	//ThermalManagment();
		    	Set_DutyCycle(&Timer_2,Duty_Cycle,TIM_Channel_4);
		    	//MGPIO_VidSetPinValue( GPIOA, PIN1 , HIGH );
		    	timer_exitinson=0;
		    }
	*/}
  

