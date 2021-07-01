/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.c
 *
 * Description: source file for NVIC Driver
 *
 * Author: Mohamed Hamada
 ******************************************************************************/
 #include "Common_Macros.h"
 #include "Std_Types.h"

 #include "NVIC.h"
 #include "NVIC_Regs.h"
 #include "NVIC_config.h"

 void NVIC_voidInit(void)
 {
	 SCB_AIRCR = NVIC_GROUP_SUB_DISTRUTION ;

 }



 void NVIC_enableInterrupt(u8 perphial)
 {
	 if (  perphial<=31 )
	 {
		 NVIC_ISER0 = (1 << perphial);

	 }
	 else if (perphial <=59)
	 {
		 perphial -=32;
		 NVIC_ISER1 = (1 << perphial);
	 }
	 else
	 {

		 /* error */
	 }

 }
 void NVIC_disableInterrupt(u8 perphial)
 {
	 if ( perphial>=0 && perphial<=31 )
	 {
		 SET_BIT(NVIC_ICER0,perphial);
	 }
	 else if (perphial >= 32 &&perphial <=59)
	 {
		 perphial -=32;
		 SET_BIT(NVIC_ICER1,perphial);
	 }
	 else
	 {

		 /* error */
	 }

 }
 void NVIC_setPendingFlag(u8 perphial)
 {
	 if (  perphial<=31 )
	 {
		 NVIC_ISPR0 = (1 << perphial);
	 }
	 else if (perphial <=59)
	 {
		 perphial -=32;
		 NVIC_ISPR1 = (1 << perphial);
	 }
	 else
	 {

		 /* error */
	 }

 }


 void NVIC_clearPendingFlag(u8 perphial)
 {
	 if ( perphial>=0 && perphial<=31 )
	 {
		 SET_BIT(NVIC_ICPR0,perphial);
	 }
	 else if (perphial >= 32 &&perphial <=59)
	 {
		 perphial -=32;
		 SET_BIT(NVIC_ICPR1,perphial);
	 }
	 else
	 {

		 /* error */
	 }

 }
 u8 NVIC_getActiveFlag(u8 perphial)
  {
	  u8 result=0;
		 if ( perphial>=0 && perphial<=31 )
	 {
		 result=GET_BIT(NVIC_IABR0,perphial);
	 }
	 else if (perphial >= 32 &&perphial <=59)
	 {
		 perphial -=32;
		 result=GET_BIT(NVIC_IABR1,perphial);
	 }
	 else
	 {

		 /* error */
	 }
	 return result;

 }

void NVIC_setPriority(s8 interruptID , u8 Priority )
{
		NVIC_IPR[interruptID] = (Priority<<4);
}
