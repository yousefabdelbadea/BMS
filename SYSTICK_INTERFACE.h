
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#ifndef SYSTICH_H_
#define SYSTICH_H_

#define     Systick_SRC_AHB_8           0
#define     Systick_SRC_AHB             1

#define    Systick_SINGLE_INTERVAL      0
#define    Systick_PERIOD_INTERVAL      1

#define    one_sec   8000000

/******* Function prototypes *******/

void Systick_init(void);
void Systick_setBusyWait(u32 tick);
void Systick_setIntervalSingle(u32 tick, void (*ptr)(void));
void Systick_setIntervalPeriodic(u32 tick, void (*ptr)(void));
void Systick_stopInterval(void);
u32 Systick_getElapsedTime(void);
u32 Systick_getRemainingTime(void);

#endif
