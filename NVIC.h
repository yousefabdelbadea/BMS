/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.h
 *
 * Description: header file for NVIC Driver
 *
 * Author: Mohamed Hamada
 ******************************************************************************/
#ifndef NVIC_H_
#define NVIC_H_

#define GROUP_4_SUBGROUP_0 			0x05FA0300
#define GROUP_3_SUBGROUP_1 			0x05FA0400
#define GROUP_2_SUBGROUP_2 			0x05FA0500
#define GROUP_1_SUBGROUP_3 			0x05FA0600
#define GROUP_0_SUBGROUP_4 			0x05FA0700

void NVIC_voidInit(void);

void  NVIC_enableInterrupt(u8 perphial);
void  NVIC_disableInterrupt(u8 perphial);
void  NVIC_setPendingFlag(u8 perphial);
void  NVIC_clearPendingFlag(u8 perphial);
u8 NVIC_getActiveFlag(u8 perphial);
void  NVIC_setPriority(s8 interruptID , u8 Priority );






#endif
