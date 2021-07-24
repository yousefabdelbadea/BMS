/******************************************************************************
 *
 * Module: BMS
 *
 * File Name: BMS.c
 *
 * Description: source file for BMS Driver
 *
 * Author:
         Amir Abo Zaid	 (BLE module && Battery Backup)
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
 #include "ThermalManagment.h"
 #include "Battery_Backup.h"


 #include "BMS.h"
 #include "BMS_config.h"


 
 /**********************			global variable		*******************************/
 
 volatile Cell cells[NUM_OF_CELLS] = 
 {
 {/*name*/1,/*Tempreture*/0,/*Voltage*/0,/*Current */0,/*stateOfCharge*/0},
 {/*name*/2,/*Tempreture*/0,/*Voltage*/0,/*Current */0,/*stateOfCharge*/0},
 {/*name*/3,/*Tempreture*/0,/*Voltage*/0,/*Current */0,/*stateOfCharge*/0},
 {/*name*/4,/*Tempreture*/0,/*Voltage*/0,/*Current */0,/*stateOfCharge*/0},
 {/*name*/5,/*Tempreture*/0,/*Voltage*/0,/*Current */0,/*stateOfCharge*/0},
 {/*name*/6,/*Tempreture*/0,/*Voltage*/0,/*Current */0,/*stateOfCharge*/0}
 };
 volatile f32 stateOfBranchCharge[NUM_OF_BRANCHES] = {0 , 0 , 0 };
 volatile f32 overallStateOfCharge = 0;
 
 volatile u8 Battery_Backup_flag[6]={0,0,0,0,0,0};

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
	/*Battery Backup Module */
	Battery_Backup_init();
	/* Thermal Management Module*/
	ThermalManagment_init();
	
	while(1)
	{

		/*
		 * initialize with data acquisition module
		 * most modules depends on it
		 * in this module we obtain current , voltage , temperature for each cell
		 */
		Data_voidAcqusition();
		/*
		 *this function is responsible  for calculate the state of charge for each cell
		 * by using data which we obtain it from data acquisition
		   we can calculate the state if charge for each cells and overall state of charge
		 * adding to voltage , current and temperature for each cell , we add the state of charge
		   , for modules used
		 */
		Charge_Control_calcStateOfCharge();

		/*
		 * cell balancing try cells to be equal in the level of state of charge
		 * this module prevent occurring over charge for any cell
		 * after calculate the state of charge for each cell
		 * we benefit from state of charge for deciding any cell needs to charge , any cell needs of discharge.
		 */
		CellBalancing_CellBalancingProcessing();
		/*
		 * this module try to prevent occurring over heating in the system
		 * this module is responsible for coiling the system
		 * without this module , the system is in danger because of over heating
		 *
		 * */
		ThermalManagment();
		/*
		 * this module send data by ESP32 to mobile App
		 * we could achieve IOT concept by using this module
		 * by showing data in mobile App and web sever and store data in database
		   , it makes maintenance easier and discovers faults is easier
		 */
		BLE_sendData();
		/*
		 * this function display the thermal data if there is danger.
		 * it is more imprtant than cells data displaying so it's displayed first
		 */
		Display_thermalData();
		/*
		 * this function is responsible for display cells data for the user in lcd screen
		 * it make user / driver follow the battery management system actions
		 */
		Display_voidDataAcqusition();

		/*	   repetition every 10 sec 		*/
		_delay_ms(10000);
	
	 }

 
 
 }
