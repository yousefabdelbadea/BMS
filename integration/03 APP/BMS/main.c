/******************************************************************************
 *
 * Module: BMS
 *
 * File Name: BMS.c
 *
 * Description: source file for BMS Driver
 *
 * Author:
         Amir Abo Zaid	 (BLE module)
         Mahmoud Moahmed (charge control && Cell Balancing)
         Yousef Abdo     (Data Acqusition && Thermal Management )
         Ahmed Mostafa   (Data Acqusition && Thermal Management )
         Mohamed Hamada  (charge control && Cell Balancing)
	
 ******************************************************************************/
 
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 
 
 #include "RCC_interface.h"
 
 #include "delay.h"

 #include "Data_Acqusition.h"
 #include "Charge_Control.h"
 #include "CellBalancing.h"
 #include "BLE.h"
 #include "Display.h"

 #include "BMS.h"
 
  int main()
 {
	 
	 
    /*  Enable Clock for Perpherials  */	
	
	__ENABLE_SYSTEM_CLOCK;					
		 
	__ENABLE_CLOCK_PORTA;					

	__ENABLE_CLOCK_PORTB;

	__ENABLE_CLOCK_PORTC;  						 
		 
	__ENABLE_CLOCK_ADC1;							 
		 
	__ENABLE_CLOCK_ALTERNATIVE_FUNCTION;

        __ENABLE_CLOCK_USART2;



     /* initalize Delay Module*/
	 delay_init();

	
	
	/***************** initalize Modules  ******************/
	
    /*  Data Acqusition */ 
    Data_voidAcqusitionInit();
	/* charge control Module */
	Charge_Control_init();
	/*  BLE Module */
    BLE_init();
	/* Display Module*/
	Display_init();
	
	while(1)
	{
		Data_voidAcqusition();
		CellBalancing_CellBalancingProcessing();
		BLE_sendData();
		Display_voidDataAcqusition();

		/*	   repetition every 10 sec 		*/
		_delay_ms(10000);
	
	 }

 
 
 }
