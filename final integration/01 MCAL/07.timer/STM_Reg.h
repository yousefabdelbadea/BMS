/*
 * STM_Reg.h
 *
 *  Created on: JAN 17, 2021
 *      Author: H
 */

#ifndef DIO_DRIVER_AVR_REG_H_
#define DIO_DRIVER_AVR_REG_H_
#include "Stdandard_Types.h"

// TIMER_1 Registers
// 0x4001 2C00 - 0x4001 2FFF boundaries
#define TIM1_CR1 *((volatile uint16_t*) 0x40012C00)
#define TIM1_CR2 *((volatile uint16_t*) 0x40012C04)
#define TIM1_SMCR *((volatile uint16_t*) 0x40012C08)
#define TIM1_DIER *((volatile uint16_t*) 0x40012C0C)
#define TIM1_SR *((volatile uint16_t*) 0x40012C10)
#define TIM1_EGR *((volatile uint16_t*) 0x40012C14)
#define TIM1_CCMR1 *((volatile uint16_t*) 0x40012C18)
#define TIM1_CCMR2 *((volatile uint16_t*) 0x40012C1C)
#define TIM1_CCER *((volatile uint16_t*) 0x40012C20)
#define TIM1_CNT *((volatile uint16_t*) 0x40012C24)
#define TIM1_PSC *((volatile uint16_t*) 0x40012C28)
#define TIM1_ARR *((volatile uint16_t*) 0x40012C2C)
#define TIM1_RCR *((volatile uint16_t*) 0x40012C30)
#define TIM1_CCR1 *((volatile uint16_t*) 0x40012C34)
#define TIM1_CCR2 *((volatile uint16_t*) 0x40012C38)
#define TIM1_CCR3 *((volatile uint16_t*) 0x40012C3C)
#define TIM1_CCR4 *((volatile uint16_t*) 0x40012C40)
#define TIM1_BDTR *((volatile uint16_t*) 0x40012C44)
#define TIM1_DCR *((volatile uint16_t*) 0x40012C48)
#define TIM1_DMAR *((volatile uint16_t*) 0x40012C4C)

//Timer_2 Registers
// 0x4000 0000 - 0x4000 03FF boundaries
#define TIM2_CR1 *((volatile uint16_t*) 0x40000000)
#define TIM2_CR2 *((volatile uint16_t*) 0x40000004)
#define TIM2_SMCR *((volatile uint16_t*) 0x40000008)
#define TIM2_DIER *((volatile uint16_t*) 0x4000000C)
#define TIM2_SR *((volatile uint16_t*) 0x40000010)
#define TIM2_EGR *((volatile uint16_t*) 0x40000014)
#define TIM2_CCMR1 *((volatile uint16_t*) 0x40000018)
#define TIM2_CCMR2 *((volatile uint16_t*) 0x4000001C)
#define TIM2_CCER *((volatile uint16_t*) 0x40000020)
#define TIM2_CNT *((volatile uint16_t*) 0x40000024)
#define TIM2_PSC *((volatile uint16_t*) 0x40000028)
#define TIM2_ARR *((volatile uint16_t*) 0x4000002C)
#define TIM2_RCR *((volatile uint16_t*) 0x40000030)
#define TIM2_CCR1 *((volatile uint16_t*) 0x40000034)
#define TIM2_CCR2 *((volatile uint16_t*) 0x40000038)
#define TIM2_CCR3 *((volatile uint16_t*) 0x40000003C)
#define TIM2_CCR4 *((volatile uint16_t*) 0x40000040)
#define TIM2_BDTR *((volatile uint16_t*) 0x40000044)
#define TIM2_DCR *((volatile uint16_t*) 0x40000048)
#define TIM2_DMAR *((volatile uint16_t*) 0x4000004C)

//Timer_3 Registers
//0x4000 0400 - 0x4000 07FF boundaries
#define TIM3_CR1 *((volatile uint16_t*) 0x40000400)
#define TIM3_CR2 *((volatile uint16_t*) 0x40000404)
#define TIM3_SMCR *((volatile uint16_t*) 0x40000408)
#define TIM3_DIER *((volatile uint16_t*) 0x4000040C)
#define TIM3_SR *((volatile uint16_t*) 0x40000410)
#define TIM3_EGR *((volatile uint16_t*) 0x40000414)
#define TIM3_CCMR1 *((volatile uint16_t*) 0x40000418)
#define TIM3_CCMR2 *((volatile uint16_t*) 0x4000041C)
#define TIM3_CCER *((volatile uint16_t*) 0x40000420)
#define TIM3_CNT *((volatile uint16_t*) 0x40000424)
#define TIM3_PSC *((volatile uint16_t*) 0x40000428)
#define TIM3_ARR *((volatile uint16_t*) 0x4000042C)
#define TIM3_RCR *((volatile uint16_t*) 0x40000430)
#define TIM3_CCR1 *((volatile uint16_t*) 0x40000434)
#define TIM3_CCR2 *((volatile uint16_t*) 0x40000438)
#define TIM3_CCR3 *((volatile uint16_t*) 0x40000043C)
#define TIM3_CCR4 *((volatile uint16_t*) 0x40000440)
#define TIM3_BDTR *((volatile uint16_t*) 0x40000444)
#define TIM3_DCR *((volatile uint16_t*) 0x40000448)
#define TIM3_DMAR *((volatile uint16_t*) 0x4000044C)

// Timer_4 Registers
//0x4000 0800 - 0x4000 0BFF boundaries
#define TIM4_CR1 *((volatile uint16_t*) 0x40000800)
#define TIM4_CR2 *((volatile uint16_t*) 0x40000804)
#define TIM4_SMCR *((volatile uint16_t*) 0x40000808)
#define TIM4_DIER *((volatile uint16_t*) 0x4000080C)
#define TIM4_SR *((volatile uint16_t*) 0x40000810)
#define TIM4_EGR *((volatile uint16_t*) 0x40000814)
#define TIM4_CCMR1 *((volatile uint16_t*) 0x40000818)
#define TIM4_CCMR2 *((volatile uint16_t*) 0x4000081C)
#define TIM4_CCER *((volatile uint16_t*) 0x40000820)
#define TIM4_CNT *((volatile uint16_t*) 0x40000824)
#define TIM4_PSC *((volatile uint16_t*) 0x40000828)
#define TIM4_ARR *((volatile uint16_t*) 0x4000082C)
#define TIM4_RCR *((volatile uint16_t*) 0x40000830)
#define TIM4_CCR1 *((volatile uint16_t*) 0x40000834)
#define TIM4_CCR2 *((volatile uint16_t*) 0x40000838)
#define TIM4_CCR3 *((volatile uint16_t*) 0x40000083C)
#define TIM4_CCR4 *((volatile uint16_t*) 0x40000840)
#define TIM4_BDTR *((volatile uint16_t*) 0x40000844)
#define TIM4_DCR *((volatile uint16t*) 0x40000848)
#define TIM4_DMAR *((volatile uint16_t*) 0x4000084C)

#endif /* DIO_DRIVER_STM_REG_H_ */
