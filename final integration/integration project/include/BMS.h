/******************************************************************************
 *
 * Module: BMS
 *
 * File Name: BMS.h
 *
 * Description: header file for BMS Driver
 *
 * Author: my team
	
 ******************************************************************************/
 #ifndef BMS_H_
 #define BMS_H_
 

 /**************  				cell information data type 		   ************/
 
 typedef struct
 {
	u8  name;
	f32 Tempreture;
	f32 Voltage;
	f32 Current;
	f32 stateOfCharge;
 }Cell;



/**************  		 preprocessing Macros 		   ************/

#define __ENABLE_SYSTEM_CLOCK							RCC_voidInitSysClock()

/*Generate clock for GPIOA*/
#define __ENABLE_CLOCK_PORTA							RCC_voidEnableClock(RCC_APB2 , 2)

/*Generate clock for GPIOB*/
#define __ENABLE_CLOCK_PORTB							RCC_voidEnableClock(RCC_APB2 , 3)

/*Generate clock for GPIOC*/
#define __ENABLE_CLOCK_PORTC  							RCC_voidEnableClock(RCC_APB2 , 4)

/*Generate clock for ADC1*/
#define __ENABLE_CLOCK_ADC1								RCC_voidEnableClock(RCC_APB2 , 9);

/*clock of alternative function*/
#define __ENABLE_CLOCK_ALTERNATIVE_FUNCTION				RCC_voidEnableClock(RCC_APB2 , 0);


/*Enable the clock of USART2*/
#define __ENABLE_CLOCK_USART2                       	RCC_voidEnableClock( RCC_APB1, 17)



 
 
 #endif
