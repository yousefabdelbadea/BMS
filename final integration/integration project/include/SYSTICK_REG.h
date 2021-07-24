#include "STD_TYPES.h"
#include "BIT_MATH.h"


#ifndef SYSTICH_REGS_H_
 #define SYSTICH_REGS_H_

 #define STK_CTRL		     							(*((volatile u32 *)0xE000E010))
 #define STK_LOAD		     							(*((volatile u32 *)0xE000E014))
 #define STK_VAL		     							(*((volatile u32 *)0xE000E018))
 #define STK_CALIB		     							(*((volatile u32 *)0xE000E01C))


 #endif
