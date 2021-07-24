/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC_Regs.h
 *
 * Description: header file for NVIC register Driver
 *
 * Author: Mohamed Hamada
 ******************************************************************************/
#ifndef NVIC_REGS_H_
#define NVIC_REGS_H_


#define NVIC_ISER0		     						(*((volatile u32 *)0xE000E100))
#define NVIC_ISER1		     						(*((volatile u32 *)0xE000E104))
#define NVIC_ISER2		     						(*((volatile u32 *)0xE000E108))
#define NVIC_ICER0		     						(*((volatile u32 *)0xE000E180))
#define NVIC_ICER1		     						(*((volatile u32 *)0xE000E184))
#define NVIC_ICER2		     						(*((volatile u32 *)0xE000E188))
#define NVIC_ISPR0		     						(*((volatile u32 *)0xE000E200))
#define NVIC_ISPR1		     						(*((volatile u32 *)0xE000E204))
#define NVIC_ISPR2		     						(*((volatile u32 *)0xE000E208))
#define NVIC_ICPR0		     						(*((volatile u32 *)0xE000E280))
#define NVIC_ICPR1		     						(*((volatile u32 *)0xE000E284))
#define NVIC_ICPR2		     						(*((volatile u32 *)0xE000E288))
#define NVIC_IABR0		     						(*((volatile u32 *)0xE000E300))
#define NVIC_IABR1		     						(*((volatile u32 *)0xE000E304))
#define NVIC_IABR2		     						(*((volatile u32 *)0xE000E308))
#define NVIC_IPR		     						(((volatile u32 *)0xE000E400))

#define SCB_AIRCR									(*((volatile u32 *)0xE000ED0C))



#define NVIC_IPR20		     						(*((volatile u32 *)0xE000E420))
//#define NVIC_STIR		     						(*((volatile u32 *)0xE000E100))






#endif
