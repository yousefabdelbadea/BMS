/******************************************************************************
 *
 * Module: Charge Control
 *
 * File Name: Charge_Control.h
 *
 * Description: source file for Charge Control Driver
 *
 * Author: 
			Mahmoud benyamin
			Mohamed Hamada
	
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include"DIO_interface.h"

 #include "STP.h"
 #include "delay.h"


#include "Charge_Control_config.h"

#include "Charge_Control.h"




 #include "BMS.h"

 #include "BMS_config.h"


/*************** global variable *****************/
 extern  Cell cells[NUM_OF_CELLS];
 extern  f32 stateOfBranchCharge[NUM_OF_BRANCHES];
 extern  f32 overallStateOfCharge ;


 u8 isCharge[NUM_OF_BRANCHES];
 u8 isDisCharge[NUM_OF_BRANCHES];

 u8 charge_control_data[2*NUM_OF_BRANCHES];




/********************************************************/

 void Charge_Control_init(void)
 {

	for (u8 i= 0 ; i<NUM_OF_BRANCHES;i++)
	{
		isCharge[i] =CHARGE_CONTROL_LOW;
		isDisCharge[i]=CHARGE_CONTROL_LOW;

	}

	  STP_init();

 }


 void charge_control_sendData(void)
 {

	 u8 charge_control_data[2*NUM_OF_BRANCHES];
	 for(u8 i=0;i<NUM_OF_BRANCHES;i++)
	 {
		 charge_control_data[i]=isCharge[i];
	 }


	 for(u8 i=0;i<NUM_OF_BRANCHES;i++)
	 {
		 charge_control_data[i+NUM_OF_BRANCHES]=isDisCharge[i];
	 }


	 STP_sendSynchronus(charge_control_data);

 }




 void Charge_Control_calcStateOfCharge(void)
 {
	float SOC=0;





	for(u8 i =0 ;i<NUM_OF_CELLS;i++)
	{

		/*******************************************************/
		 SOC = (float)(132.3*(cells[i].Voltage + cells[i].Current*INTERNAL_RESISTANCE)-450.8);
		cells[i].stateOfCharge=SOC;


		overallStateOfCharge+=cells[i].stateOfCharge;

		if (i%2==1)
		{
			stateOfBranchCharge[i/2]=(f32)((cells[i-1].stateOfCharge+cells[i].stateOfCharge)/((float)2)) ;
		}
	}
	overallStateOfCharge = ((f32)overallStateOfCharge/NUM_OF_CELLS);

 }

 void charge_control_stop_charging()
 {

	 for (u8 i= 0 ; i<NUM_OF_BRANCHES;i++)
	 {
	 		isCharge[i] =CHARGE_CONTROL_LOW;
	 }

	  charge_control_sendData();

	  _delay_us(100);
 }












