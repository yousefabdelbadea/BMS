/******************************************************************************
 *
 * Module: BLE
 *
 * File Name: BLE.h
 *
 * Description: header file for STM32F103C8  Microcontroller - BLE Driver
 *
 * Author: Mohamed Hamada
           mahmoud mohamed 
		   Amir abo zaid
 ******************************************************************************/
  #include "STD_TYPES.h"
  #include "BIT_MATH.h"

 #include "DIO_interface.h"
  
  #include "USART_Interface.h"



  
 #include "delay.h"

  #include "BMS.h"
  #include "BMS_config.h"
  #include "BLE.h"


extern  Cell cells[6];



 
 void BLE_init(void)
 {
	 MGPIO_VidSetPinDirection( GPIOA , PIN2 , OUTPUT_SPEED_50MHZ_AFPP );
	 MUART_voidInit();
 }
 void BLE_sendData(void)
 {
	u8 data[17];
	
	u16 nameVar =0;
	u16 tempVar =0;
	u16 currVar =0;
	u16 voltVar =0;
	u16 SOCVar  =0;

    
	for(u8 i =0;i<6;i++)
	{
		nameVar = (u16)cells[i].name;
		tempVar = (u16)  cells[i].Tempreture;
		currVar = (u16) (cells[i].Current*100 );
		voltVar = (u16) (cells[i].Voltage*10);
		SOCVar  = (u16)  cells[i].stateOfCharge;
		
		
		data[0] = '#';
		data[1] = 'C';
                data[2]	= cells[i].name+'0' ;
		data[3] = 'T';
		data[4] = tempVar /10+'0';
		data[5] = tempVar %10+'0';
		data[6] = 'A';
		data[7] = currVar/10+'0';
		data[8] = currVar%10+'0';
		data[9] = 'V';
		data[10] = voltVar/10+'0';
		data[11] = voltVar%10+'0';
		data[12] = 'S';
		data[13] = SOCVar/10+'0';
		data[14] = SOCVar%10+'0';
		data[15] = '$';
		data[16] = '\0';
	
		
	
        	MUART_voidTransmitSynch(data);
	    //  for(u32 i=0;i<8000000;i++);

		     _delay_ms(15000);

	}
	
	
	 
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
