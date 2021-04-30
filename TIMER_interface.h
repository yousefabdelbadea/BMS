/*
 * timer.h
 *
 *  Created on: Jan 17, 2021
 *      Author: future
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "timer_config.h"


// Register Bits
#define DIR_BIT                               4   // This bit is in TIMx_CR1
#define CEN                                   0   // This bit is in TIMx_CR1
#define Output_Compare_Channel_1_Mode_Bit_6   6   // This bit is in TIMx_CCMR1
#define Output_Compare_Channel_1_Mode_Bit_5   5   // This bit is in TIMx_CCMR1
#define Output_Compare_Channel_1_Mode_Bit_4   4   // This bit is in TIMx_CCMR1
#define Output_Compare_Channel_2_Mode_Bit_14  14  // This bit is in TIMx_CCMR1
#define Output_Compare_Channel_2_Mode_Bit_13  13  // This bit is in TIMx_CCMR1
#define Output_Compare_Channel_2_Mode_Bit_12  12  // This bit is in TIMx_CCMR1
#define Output_Compare_Channel_3_Mode_Bit_6   6   // This bit is in TIMx_CCMR2
#define Output_Compare_Channel_3_Mode_Bit_5   5   // This bit is in TIMx_CCMR2
#define Output_Compare_Channel_3_Mode_Bit_4   4   // This bit is in TIMx_CCMR2
#define Output_Compare_Channel_4_Mode_Bit_14  14  // This bit is in TIMx_CCMR2
#define Output_Compare_Channel_4_Mode_Bit_13  13  // This bit is in TIMx_CCMR2
#define Output_Compare_Channel_4_Mode_Bit_12  12  // This bit is in TIMx_CCMR2



typedef struct{
uint8_t Timer;
uint16_t Period;
uint16_t Prescaler;
uint8_t Count_Mode;
uint8_t Interrupt;
}TIM_HandleTypeDef;

typedef struct{
uint8_t Channel;
uint8_t Mode;
uint8_t Duty_Cycle;
}TIM_PWM_Config;

// Timers
#define TIM1 0
#define TIM2 1
#define TIM3 2
#define TIM4 3

//Timer Channels
#define TIM_Channel_1 0
#define TIM_Channel_2 1
#define TIM_Channel_3 2
#define TIM_Channel_4 3

//POLARIY
#define NORMAL_POLARITY   0
#define INVERTED_POLARITY 1

// Counting Modes
#define UP_COUNTER   0
#define DOWN_COUNTER 1

// Output Mode
#define PWM1 0
#define PWM2 1

/*  Interrupt */
#define INTERRUPT 1
#define POLLING   0

//Clock Bits
#define TIM1_CLOCK_ENABLE   11
#define TIM2_CLOCK_ENABLE   0
#define TIM3_CLOCK_ENABLE   1
#define TIM4_CLOCK_ENABLE   2


/*
 * This function is used to initialize timer base unit it takes pointer to structure
 * in Timer--> we choose between TIM1 or TIM2 or TIM3 or TIM4
 * in Period--> write the period from 0-->65535
 * in Prescaler--> we write the clock prescaler value from 0-->65535
 * in Count_Mode --> we choose between UP_COUNTER and DOWN_COUNTER
 * */
void Tim_Init(TIM_HandleTypeDef *htimer);
/***************************************************************************************************/

/*
 * This function is used to start the timer
 *
 * */
void Tim_Start(TIM_HandleTypeDef *htimer);
/****************************************************************************************************/


/*
 * This function is used to stop the timer
 *
 * */
void Tim_Stop(TIM_HandleTypeDef *htimer);
/****************************************************************************************************/
/*
 * This function is used to initialize timer PWM it takes pointer to structure
 * in Polarity--> we choose between NORMAL_POLARITY or INVERTED_POLARITY
 * in Channel--> we choose between TIM_Channel_1 or TIM_Channel_2 or TIM_Channel_3 or TIM_Channel_4
 * in Mode--> we choose PWM1-->NORMAL_POLARITY or PWM2-->INVERTED_POLARITY
 * in Duty_Cycle--> we write the pulse duty cycle as a number from (0-->100)
 * */
void PWM_ChannelConfig(TIM_HandleTypeDef *htimer,TIM_PWM_Config* pwm_config);
/****************************************************************************************************/
/*
 * This function is used to set the duty cycle during run time
 * it takes 2 parameters pointer to timer structure to detect the timer
 * in Duty_Cycle--> we write the pulse duty cycle as a number from (0-->100)
 * in Channel--> we choose between TIM_Channel_1 or TIM_Channel_2 or TIM_Channel_3 or TIM_Channel_4
 * */
void Set_DutyCycle(TIM_HandleTypeDef *htimer,uint8_t Duty_Cycle,uint8_t Channel);

#endif /* TIMER_H_ */
