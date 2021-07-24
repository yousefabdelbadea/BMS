/******************************************************************************
 *
 * Module: Delay
 *
 * File Name: Delay.c
 *
 * Description: Source file for STM32F103C8  Microcontroller - Delay Driver
 *
 * Author: Mohamed Hamada
 ******************************************************************************/
 
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"

 #include "SYSTICK_INTERFACE.h"

#include "delay.h"
 
 void delay_init(void)
 {
	 Systick_init();
	 
 }
 void _delay_us(u32 tick)
 {
	Systick_setBusyWait(tick); 
	 
 }
 void _delay_ms(u32 tick)
 {
	 
	Systick_setBusyWait(tick*1000); 
	 
	 
 }
