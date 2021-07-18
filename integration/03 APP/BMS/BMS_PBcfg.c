/******************************************************************************
 *
 * Module: BMS
 *
 * File Name: BMS_PBcfg.c
 *
 * Description: header file for STM32F103C8  Microcontroller - BLE Driver
 *
 * Author: Mohamed Hamada
 ******************************************************************************/

 #include "STD_TYPES.h"
 #include "BIT_MATH.h"

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
