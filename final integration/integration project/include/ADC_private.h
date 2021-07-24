
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#ifndef _ADC_PRIVATE_H
#define _ADC_PRIVATE_H

/* Register Definitions FOR ADC_1*/
//BASE ADDRESS 0x4001 2400
                    
#define  ADC_SR      *((volatile u32*)0x40012400)
#define  ADC_CR1     *((volatile u32*)0x40012404)
#define  ADC_CR2     *((volatile u32*)0x40012408)
#define  ADC_SMPR1   *((volatile u32*)0x4001240c)
#define  ADC_SMPR2   *((volatile u32*)0x40012410)
#define  ADC_JOFR1   *((volatile u32*)0x40012414)
#define  ADC_JOFR2   *((volatile u32*)0x40012418)
#define  ADC_JOFR3   *((volatile u32*)0x4001241c)
#define  ADC_JOFR4   *((volatile u32*)0x40012420)
#define  ADC_HTR     *((volatile u32*)0x40012424)
#define  ADC_LTR     *((volatile u32*)0x40012428)
#define  ADC_SQR1    *((volatile u32*)0x4001242c)
#define  ADC_SQR2    *((volatile u32*)0x40012430)
#define  ADC_SQR3    *((volatile u32*)0x40012434)
#define  ADC_JSQR    *((volatile u32*)0x40012438)
#define  ADC_JDR1    *((volatile u32*)0x4001243c)
#define  ADC_JDR2    *((volatile u32*)0x40012440)
#define  ADC_JDR3    *((volatile u32*)0x40012444)
#define  ADC_JDR4    *((volatile u32*)0x40012448)
#define  ADC_DR      *((volatile u32*)0x4001244c)
	
/*Bits Defintion*/
#define    SCAN        8
#define    ALIGN       11
#define    CONT        1
#define    CAL         2
#define    RCAL        3
#define    ADON        0

#endif
