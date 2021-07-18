/******************************************************************************
 *
 * Module: Charge Control
 *
 * File Name: Charge_Control.h
 *
 * Description: header file for Charge Control Driver
 *
 * Author: 
			Mahmoud benyamin
			Mohamed Hamada
	
 *****************************************************************************/
 #ifndef CHARGE_CONTROL_H_
 #define CHARGE_CONTROL_H_
 

 /************** function prototypes   *************/
 
 
 
 void Charge_Control_init(void);
 //void Charge_Control_startCharging(void);
 void Charge_Control_calcStateOfCharge(void);
 //void Charge_Control_DisCharging(void);
 void charge_control_sendData(void);

 void charge_control_stop_charging();

 
 #endif
 
 
 
