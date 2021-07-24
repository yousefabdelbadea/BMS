/******************************************************************************
 *
 * Module: Delay
 *
 * File Name: Delay.h
 *
 * Description: header file for STM32F103C8  Microcontroller - Delay Driver
 *
 * Author: Mohamed Hamada
 ******************************************************************************/
 
 void delay_init(void);
 void _delay_us(u32 tick);
 void _delay_ms(u32 tick);