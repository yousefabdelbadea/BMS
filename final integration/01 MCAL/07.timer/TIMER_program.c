/*
 * timer.c
 *
 *  Created on: Jan 17, 2021
 *      Author: future
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "DIO_interface.h"


void Tim_Init(TIM_HandleTypeDef *htimer){
	if(htimer->Timer==TIM1){
		SET_BIT(RCC_APB2ENR,TIM1_CLOCK_ENABLE);
		TIM1_ARR=htimer->Period;
		TIM1_PSC=htimer->Prescaler;
		if(htimer->Count_Mode==UP_COUNTER){
			CLR_BIT(TIM1_CR1,DIR_BIT);
		}
		else if(htimer->Count_Mode==DOWN_COUNTER){
			SET_BIT(TIM1_CR1,DIR_BIT);
		}
		if(htimer->Interrupt==INTERRUPT){
			SET_BIT(TIM1_DIER,0);
		}
	}
	else if(htimer->Timer==TIM2){
		SET_BIT(RCC_APB1ENR,TIM2_CLOCK_ENABLE);
		TIM2_ARR=htimer->Period;
		TIM2_PSC=htimer->Prescaler;
		if(htimer->Count_Mode==UP_COUNTER){
			CLR_BIT(TIM2_CR1,DIR_BIT);
		}
		else if(htimer->Count_Mode==DOWN_COUNTER){
			SET_BIT(TIM2_CR1,DIR_BIT);
		}
		if(htimer->Interrupt==INTERRUPT){
			SET_BIT(TIM2_DIER,0);
		}
	}
	else if(htimer->Timer==TIM3){
		SET_BIT(RCC_APB1ENR,TIM3_CLOCK_ENABLE);
		TIM3_ARR=htimer->Period;
		TIM3_PSC=htimer->Prescaler;
		if(htimer->Count_Mode==UP_COUNTER){
			CLR_BIT(TIM3_CR1,DIR_BIT);
		}
		else if(htimer->Count_Mode==DOWN_COUNTER){
			SET_BIT(TIM3_CR1,DIR_BIT);
		}
		if(htimer->Interrupt==INTERRUPT){
			SET_BIT(TIM3_DIER,0);
		}
	}
	else if(htimer->Timer==TIM4){
		SET_BIT(RCC_APB1ENR,TIM4_CLOCK_ENABLE);
		TIM4_ARR=htimer->Period;
		TIM4_PSC=htimer->Prescaler;
		if(htimer->Count_Mode==UP_COUNTER){
			CLR_BIT(TIM4_CR1,DIR_BIT);
		}
		else if(htimer->Count_Mode==DOWN_COUNTER){
			SET_BIT(TIM4_CR1,DIR_BIT);
		}
		if(htimer->Interrupt==INTERRUPT){
			SET_BIT(TIM4_DIER,0);
		}
	}

}
/********************************************************************************************************/
void Tim_Start(TIM_HandleTypeDef *htimer){

	if(htimer->Timer==TIM1){
		SET_BIT(TIM1_CR1,CEN);
	}
	else if(htimer->Timer==TIM2){
		SET_BIT(TIM2_CR1,CEN);
	}
	else if(htimer->Timer==TIM3){
		SET_BIT(TIM3_CR1,CEN);
	}
	else if(htimer->Timer==TIM4){
		SET_BIT(TIM4_CR1,CEN);
	}
}
/********************************************************************************************************/
void Tim_Stop(TIM_HandleTypeDef *htimer){

	if(htimer->Timer==TIM1){
		CLEAR_BIT(TIM1_CR1,CEN);
	}
	else if(htimer->Timer==TIM2){
		CLEAR_BIT(TIM2_CR1,CEN);
	}
	else if(htimer->Timer==TIM3){
		CLEAR_BIT(TIM3_CR1,CEN);
	}
	else if(htimer->Timer==TIM4){
		CLEAR_BIT(TIM4_CR1,CEN);
	}
}
/********************************************************************************************************/
void PWM_ChannelConfig(TIM_HandleTypeDef *htimer,TIM_PWM_Config* pwm_config){
	if(htimer->Timer==TIM1){

		if(pwm_config->Channel==TIM_Channel_1){
			TIM1_CCR1=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM1_CCMR1,Output_Compare_Channel_1_Mode_Bit_6);
				SET_BIT(TIM1_CCMR1,Output_Compare_Channel_1_Mode_Bit_5);
				CLR_BIT(TIM1_CCMR1,Output_Compare_Channel_1_Mode_Bit_4);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM1_CCMR1,Output_Compare_Channel_1_Mode_Bit_6);
				SET_BIT(TIM1_CCMR1,Output_Compare_Channel_1_Mode_Bit_5);
				SET_BIT(TIM1_CCMR1,Output_Compare_Channel_1_Mode_Bit_4);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_2){
			TIM1_CCR2=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM1_CCMR1,Output_Compare_Channel_2_Mode_Bit_14);
				SET_BIT(TIM1_CCMR1,Output_Compare_Channel_2_Mode_Bit_13);
				CLR_BIT(TIM1_CCMR1,Output_Compare_Channel_2_Mode_Bit_12);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM1_CCMR1,Output_Compare_Channel_2_Mode_Bit_14);
				SET_BIT(TIM1_CCMR1,Output_Compare_Channel_2_Mode_Bit_13);
				SET_BIT(TIM1_CCMR1,Output_Compare_Channel_2_Mode_Bit_12);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_3){
			TIM1_CCR3=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM1_CCMR2,Output_Compare_Channel_3_Mode_Bit_6);
				SET_BIT(TIM1_CCMR2,Output_Compare_Channel_3_Mode_Bit_5);
				CLR_BIT(TIM1_CCMR2,Output_Compare_Channel_3_Mode_Bit_4);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM1_CCMR2,Output_Compare_Channel_3_Mode_Bit_6);
				SET_BIT(TIM1_CCMR2,Output_Compare_Channel_3_Mode_Bit_5);
				SET_BIT(TIM1_CCMR2,Output_Compare_Channel_3_Mode_Bit_4);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_4){
			TIM1_CCR4=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM1_CCMR2,Output_Compare_Channel_4_Mode_Bit_14);
				SET_BIT(TIM1_CCMR2,Output_Compare_Channel_4_Mode_Bit_13);
				CLR_BIT(TIM1_CCMR2,Output_Compare_Channel_4_Mode_Bit_12);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM1_CCMR2,Output_Compare_Channel_4_Mode_Bit_14);
				SET_BIT(TIM1_CCMR2,Output_Compare_Channel_4_Mode_Bit_13);
				SET_BIT(TIM1_CCMR2,Output_Compare_Channel_4_Mode_Bit_12);
			}

		}
	}
	else if(htimer->Timer==TIM2){
		if(pwm_config->Channel==TIM_Channel_1){
			TIM2_CCR1=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM2_CCMR1,Output_Compare_Channel_1_Mode_Bit_6);
				SET_BIT(TIM2_CCMR1,Output_Compare_Channel_1_Mode_Bit_5);
				CLR_BIT(TIM2_CCMR1,Output_Compare_Channel_1_Mode_Bit_4);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM2_CCMR1,Output_Compare_Channel_1_Mode_Bit_6);
				SET_BIT(TIM2_CCMR1,Output_Compare_Channel_1_Mode_Bit_5);
				SET_BIT(TIM2_CCMR1,Output_Compare_Channel_1_Mode_Bit_4);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_2){
			TIM2_CCR2=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM2_CCMR1,Output_Compare_Channel_2_Mode_Bit_14);
				SET_BIT(TIM2_CCMR1,Output_Compare_Channel_2_Mode_Bit_13);
				CLR_BIT(TIM2_CCMR1,Output_Compare_Channel_2_Mode_Bit_12);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM2_CCMR1,Output_Compare_Channel_2_Mode_Bit_14);
				SET_BIT(TIM2_CCMR1,Output_Compare_Channel_2_Mode_Bit_13);
				SET_BIT(TIM2_CCMR1,Output_Compare_Channel_2_Mode_Bit_12);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_3){
			TIM2_CCR3=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM2_CCMR2,Output_Compare_Channel_3_Mode_Bit_6);
				SET_BIT(TIM2_CCMR2,Output_Compare_Channel_3_Mode_Bit_5);
				CLR_BIT(TIM2_CCMR2,Output_Compare_Channel_3_Mode_Bit_4);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM2_CCMR2,Output_Compare_Channel_3_Mode_Bit_6);
				SET_BIT(TIM2_CCMR2,Output_Compare_Channel_3_Mode_Bit_5);
				SET_BIT(TIM2_CCMR2,Output_Compare_Channel_3_Mode_Bit_4);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_4){
			TIM2_CCR4=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			MGPIO_VidSetPinDirection( GPIOA , PIN3 ,OUTPUT_SPEED_50MHZ_AFPP );
			SET_BIT(TIM2_CCER,12);
			CLR_BIT(TIM2_CCER,13);

			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM2_CCMR2,Output_Compare_Channel_4_Mode_Bit_14);
				SET_BIT(TIM2_CCMR2,Output_Compare_Channel_4_Mode_Bit_13);
				CLR_BIT(TIM2_CCMR2,Output_Compare_Channel_4_Mode_Bit_12);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM2_CCMR2,Output_Compare_Channel_4_Mode_Bit_14);
				SET_BIT(TIM2_CCMR2,Output_Compare_Channel_4_Mode_Bit_13);
				SET_BIT(TIM2_CCMR2,Output_Compare_Channel_4_Mode_Bit_12);
			}

		}

	}
	else if(htimer->Timer==TIM3){
		if(pwm_config->Channel==TIM_Channel_1){
			TIM3_CCR1=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM3_CCMR1,Output_Compare_Channel_1_Mode_Bit_6);
				SET_BIT(TIM3_CCMR1,Output_Compare_Channel_1_Mode_Bit_5);
				CLR_BIT(TIM3_CCMR1,Output_Compare_Channel_1_Mode_Bit_4);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM3_CCMR1,Output_Compare_Channel_1_Mode_Bit_6);
				SET_BIT(TIM3_CCMR1,Output_Compare_Channel_1_Mode_Bit_5);
				SET_BIT(TIM3_CCMR1,Output_Compare_Channel_1_Mode_Bit_4);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_2){
			TIM3_CCR2=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM3_CCMR1,Output_Compare_Channel_2_Mode_Bit_14);
				SET_BIT(TIM3_CCMR1,Output_Compare_Channel_2_Mode_Bit_13);
				CLR_BIT(TIM3_CCMR1,Output_Compare_Channel_2_Mode_Bit_12);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM3_CCMR1,Output_Compare_Channel_2_Mode_Bit_14);
				SET_BIT(TIM3_CCMR1,Output_Compare_Channel_2_Mode_Bit_13);
				SET_BIT(TIM3_CCMR1,Output_Compare_Channel_2_Mode_Bit_12);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_3){
			TIM3_CCR3=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM3_CCMR2,Output_Compare_Channel_3_Mode_Bit_6);
				SET_BIT(TIM3_CCMR2,Output_Compare_Channel_3_Mode_Bit_5);
				CLR_BIT(TIM3_CCMR2,Output_Compare_Channel_3_Mode_Bit_4);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM3_CCMR2,Output_Compare_Channel_3_Mode_Bit_6);
				SET_BIT(TIM3_CCMR2,Output_Compare_Channel_3_Mode_Bit_5);
				SET_BIT(TIM3_CCMR2,Output_Compare_Channel_3_Mode_Bit_4);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_4){
			TIM3_CCR4=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM3_CCMR2,Output_Compare_Channel_4_Mode_Bit_14);
				SET_BIT(TIM3_CCMR2,Output_Compare_Channel_4_Mode_Bit_13);
				CLR_BIT(TIM3_CCMR2,Output_Compare_Channel_4_Mode_Bit_12);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM3_CCMR2,Output_Compare_Channel_4_Mode_Bit_14);
				SET_BIT(TIM3_CCMR2,Output_Compare_Channel_4_Mode_Bit_13);
				SET_BIT(TIM3_CCMR2,Output_Compare_Channel_4_Mode_Bit_12);
			}

		}
	}
	else if(htimer->Timer==TIM4){
		if(pwm_config->Channel==TIM_Channel_1){
			TIM4_CCR1=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM4_CCMR1,Output_Compare_Channel_1_Mode_Bit_6);
				SET_BIT(TIM4_CCMR1,Output_Compare_Channel_1_Mode_Bit_5);
				CLR_BIT(TIM4_CCMR1,Output_Compare_Channel_1_Mode_Bit_4);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM4_CCMR1,Output_Compare_Channel_1_Mode_Bit_6);
				SET_BIT(TIM4_CCMR1,Output_Compare_Channel_1_Mode_Bit_5);
				SET_BIT(TIM4_CCMR1,Output_Compare_Channel_1_Mode_Bit_4);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_2){
			TIM4_CCR2=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM4_CCMR1,Output_Compare_Channel_2_Mode_Bit_14);
				SET_BIT(TIM4_CCMR1,Output_Compare_Channel_2_Mode_Bit_13);
				CLR_BIT(TIM4_CCMR1,Output_Compare_Channel_2_Mode_Bit_12);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM4_CCMR1,Output_Compare_Channel_2_Mode_Bit_14);
				SET_BIT(TIM4_CCMR1,Output_Compare_Channel_2_Mode_Bit_13);
				SET_BIT(TIM4_CCMR1,Output_Compare_Channel_2_Mode_Bit_12);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_3){
			TIM4_CCR3=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM4_CCMR2,Output_Compare_Channel_3_Mode_Bit_6);
				SET_BIT(TIM4_CCMR2,Output_Compare_Channel_3_Mode_Bit_5);
				CLR_BIT(TIM4_CCMR2,Output_Compare_Channel_3_Mode_Bit_4);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM4_CCMR2,Output_Compare_Channel_3_Mode_Bit_6);
				SET_BIT(TIM4_CCMR2,Output_Compare_Channel_3_Mode_Bit_5);
				SET_BIT(TIM4_CCMR2,Output_Compare_Channel_3_Mode_Bit_4);
			}
		}
		else if(pwm_config->Channel==TIM_Channel_4){
			TIM4_CCR4=((pwm_config->Duty_Cycle)*(htimer->Period))/100;
			MGPIO_VidSetPinDirection( GPIOB , PIN9 ,OUTPUT_SPEED_50MHZ_AFPP );
			SET_BIT(TIM4_CCER,12);
			CLR_BIT(TIM4_CCER,13);
			if(pwm_config->Mode==PWM1){
				SET_BIT(TIM4_CCMR2,Output_Compare_Channel_4_Mode_Bit_14);
				SET_BIT(TIM4_CCMR2,Output_Compare_Channel_4_Mode_Bit_13);
				CLR_BIT(TIM4_CCMR2,Output_Compare_Channel_4_Mode_Bit_12);
			}
			else if(pwm_config->Mode==PWM2){
				SET_BIT(TIM4_CCMR2,Output_Compare_Channel_4_Mode_Bit_14);
				SET_BIT(TIM4_CCMR2,Output_Compare_Channel_4_Mode_Bit_13);
				SET_BIT(TIM4_CCMR2,Output_Compare_Channel_4_Mode_Bit_12);
			}

		}
	}

}
/*************************************************************************************************************/
void Set_DutyCycle(TIM_HandleTypeDef *htimer,uint8_t Duty_Cycle,uint8_t Channel){
	if(htimer->Timer==TIM1){
		if(Channel==TIM_Channel_1){
			TIM1_CCR1=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_2){
			TIM1_CCR2=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_3){
			TIM1_CCR3=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_4){
			TIM1_CCR4=((Duty_Cycle)*(htimer->Period))/100;}
	}
	else if(htimer->Timer==TIM2){
		if(Channel==TIM_Channel_1){
			TIM2_CCR1=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_2){
			TIM2_CCR2=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_3){
			TIM2_CCR3=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_4){
			TIM2_CCR4=((Duty_Cycle)*(htimer->Period))/100;}
	}
	else if(htimer->Timer==TIM3){
		if(Channel==TIM_Channel_1){
			TIM3_CCR1=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_2){
			TIM3_CCR2=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_3){
			TIM3_CCR3=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_4){
			TIM3_CCR4=((Duty_Cycle)*(htimer->Period))/100;}
	}
	else if(htimer->Timer==TIM4){
		if(Channel==TIM_Channel_1){
			TIM4_CCR1=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_2){
			TIM4_CCR2=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_3){
			TIM4_CCR3=((Duty_Cycle)*(htimer->Period))/100;}
		else if(Channel==TIM_Channel_4){
			TIM4_CCR4=((Duty_Cycle)*(htimer->Period))/100;};
	}


}
