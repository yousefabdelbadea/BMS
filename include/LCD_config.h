 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD_config.h
 *
 * Description: header file for config STM32F103C8  Microcontroller - LCD Driver
 *
 * Author: Mohamed Hamada
 ******************************************************************************/
 #ifndef LCD_CONFIG_H_
 #define LCD_CONFIG_H_
 #include "DIO_interface.h"
 #include "DIO_private.h"
 
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Data bits mode configuration */

/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 		4

#if (DATA_BITS_MODE == 4)

/*
options :
		FIRST_4_PINS           
		SECOND_4_PINS          
		THIRD_4_PINS           
		FOURTH_4_PINS
*/
#define DATA_BITS_4_MODE         FOURTH_4_PINS

#elif (DATA_BITS_MODE == 8)

/*
options : 
		FIRST_8_PINS           
		SECOND_8_PINS
*/
#define DATA_BITS_8_MODE         FIRST_8_PINS

#endif


/* LCD HW Pins */
#define RS PIN3
#define RW PIN2
#define EN PIN1
#define LCD_CTRL_PORT GPIOA
#define LCD_CTRL_REG  GPIOA_ODR

#define LCD_DATA_PORT GPIOA
#define LCD_DATA_REG  GPIOA_ODR
 
#endif
