/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_INTERFACE.h"
#include "SYSTICK_REG.h"
#include "SYSTICK_CONFIG.h"

static void (*callBackPtr)(void)= 0;

static u8 modeOfInterval = 0;


void Systick_init(void)
{

#if Systick_TIMER_FREQ == Systick_SRC_AHB
	STK_CTRL=0X00000004;
#elif Systick_TIMER_FREQ == Systick_SRC_AHB_8
	STK_CTRL = 0;
#endif


}
void Systick_setBusyWait(u32 tick)
{
	STK_LOAD =tick;
	SET_BIT(STK_CTRL, 0);

	while(BIT_IS_CLEAR(STK_CTRL,16));
	CLR_BIT(STK_CTRL, 0);
	STK_LOAD =0;
	STK_VAL=0;
}
void Systick_setIntervalSingle(u32 tick, void (*ptr)(void))
{
	STK_LOAD =tick;
	SET_BIT(STK_CTRL, 0);
	modeOfInterval=Systick_SINGLE_INTERVAL;
	callBackPtr =ptr;
	SET_BIT(STK_CTRL, 1);

}

void Systick_setIntervalPeriodic(u32 tick, void (*ptr)(void))
{
	STK_LOAD =tick;
	SET_BIT(STK_CTRL, 0);

	modeOfInterval=Systick_PERIOD_INTERVAL;

	callBackPtr =ptr;
	SET_BIT(STK_CTRL, 1);

}
void Systick_stopInterval(void)
{
	CLR_BIT(STK_CTRL, 1);

	SET_BIT(STK_CTRL, 0);
	STK_LOAD =0;
	STK_VAL=0;

}
u32 Systick_getElapsedTime(void)
{
	return STK_LOAD - STK_VAL;
}
u32 Systick_getRemainingTime(void)
{
	return  STK_VAL;

}

void SysTick_Handler(void)
{
	volatile u8 temp=0;
	if (modeOfInterval == Systick_SINGLE_INTERVAL)
	{
		CLR_BIT(STK_CTRL, 1);
		SET_BIT(STK_CTRL, 0);
		STK_LOAD = 0;
		STK_VAL  = 0;
	}

	if(callBackPtr!=0)
		callBackPtr();

	temp = GET_BIT(STK_CTRL,16);
}


