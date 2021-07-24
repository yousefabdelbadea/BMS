/******************************************************************************
 *
 * Module: STP
 *
 * File Name: STP.h
 *
 * Description:  header file for STP driver
 *
 * Author: Mohamed Hamada
 *
 ********************************************************************************/
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"

 #include"DIO_interface.h"
 #include "SYSTICK_INTERFACE.h"

 #include "delay.h"
 
 #include "STP.h"
 #include "STP_config.h"
 
 
 void STP_init(void)
 {
	Systick_init();
	
    MGPIO_VidSetPinDirection(STP_SERIAL_DATA_PORT,STP_SERIAL_DATA_PIN,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(STP_STORE_CLOCK_PORT,STP_STORE_CLOCK_PIN,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(STP_SHIFT_CLOCK_PORT,STP_SHIFT_CLOCK_PIN,OUTPUT_SPEED_2MHZ_PP);


 }

 void STP_sendSynchronus(u8 *dataTosend)
 {
	s8 counter ;
    u8 bit ;
	
    MGPIO_VidSetPinValue(STP_SERIAL_DATA_PORT,STP_SERIAL_DATA_PIN, LOW);
    MGPIO_VidSetPinValue(STP_STORE_CLOCK_PORT,STP_STORE_CLOCK_PIN, LOW);
    MGPIO_VidSetPinValue(STP_SHIFT_CLOCK_PORT,STP_SHIFT_CLOCK_PIN, LOW);

    for(counter =5 ;counter >=0;counter--)
	{
		bit = dataTosend[counter];
		MGPIO_VidSetPinValue(STP_SERIAL_DATA_PORT,STP_SERIAL_DATA_PIN, bit);
		
		  _delay_us(10);
		//for(uint32 i =0;i<10;i++);
		MGPIO_VidSetPinValue(STP_SHIFT_CLOCK_PORT,STP_SHIFT_CLOCK_PIN, HIGH);
		  _delay_us(10);
		//for(uint32 i =0;i<10;i++);

		MGPIO_VidSetPinValue(STP_SHIFT_CLOCK_PORT,STP_SHIFT_CLOCK_PIN, LOW);
		  _delay_us(10);
		//for(uint32 i =0;i<10;i++);

	}	
	
	MGPIO_VidSetPinValue(STP_STORE_CLOCK_PORT,STP_STORE_CLOCK_PIN,HIGH);
	  _delay_us(10);
	//for(uint32 i =0;i<10;i++);

	MGPIO_VidSetPinValue(STP_STORE_CLOCK_PORT,STP_STORE_CLOCK_PIN,LOW);
 }

 
 
