/******************************************************************************
 *
 * Module: thermal control
 *
 * File Name: ThermalManagment.c
 *
 * Description: source file for Thermal Managment Driver
 *
 * Author: ahmed mostafa / youssef abdo
	
 ******************************************************************************/
  #include "STD_TYPES.h"
  #include "BIT_MATH.h"
  
  #include "DIO_interface.h" 
  #include "TIMER_interface.h"
  
  #include "delay.h"
  #include "LCD.h"
  
  #include "ThermalManagment.h"
  
  #include "BMS.h"
  #include "BMS_config.h"

 extern  Cell cells[6];
  
static void timer3Init(void);
static void PWMTimeInit(void);


  u8  count_t1 = 0,count_t2 = 0,count_t3 = 0,count_t4 =0,count_t5 =0,count_t6 = 0;
  u32 timer_exitinson = 0 ;
  u8 Duty_Cycle = 0;
  
  u32 n;


TIM_HandleTypeDef Timer_3;
TIM_HandleTypeDef Timer_2;
TIM_PWM_Config Timer_PWM;
uint32_t flag=0;


  

void ThermalManagment_init(void)
{
		/*Intialize NVIC*/
//	NVIC_voidInit();
	/*Interupt Of Timer3*/
//	NVIC_setPriority(29 , 1 );
	//NVIC_enableInterrupt(29);
	// Initialize timer 3 As periodic timer
	timer3Init();
	// Initialize PWM
	//PWMTimeInit();
	 PWMTimeInit();
	// Start periodic timer
	Tim_Start(&Timer_3);
	Tim_Start(&Timer_2);
	// Test Pin
	MGPIO_VidSetPinDirection( GPIOA , PIN1 , OUTPUT_SPEED_10MHZ_PP );
	
}

void ThermalManagment(void)
{


	u32 dummy,x;
	if( cells[0].Tempreture > 30  && cells[0].Tempreture >= cells[1].Tempreture  && cells[0].Tempreture >= cells[2].Tempreture
			&& cells[0].Tempreture >= cells[3].Tempreture  && cells[0].Tempreture >= cells[4].Tempreture
			&& cells[0].Tempreture >= cells[5].Tempreture)
	{
		count_t1 ++;
		LCD_clearScreen();
		if(count_t1  > 5)
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("cell-1 in danger");
			Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed= 100 %");
			MGPIO_VidSetPinValue( GPIOB, PIN7 , HIGH );
			/**/
			MGPIO_VidSetPinValue( GPIOA, PIN1 , HIGH );

		}
		else
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("Cell-1 Overheating");

			dummy = (cells[0].Tempreture - 30) * 10;
			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed=");

			if(dummy > 100)
			{
				Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
				LCD_intgerToString(100);
				LCD_displayString("%of Max");
			}
			else
			{
				x =100-dummy;
				Set_DutyCycle(&Timer_2,x,TIM_Channel_4);
				LCD_intgerToString(dummy);
				LCD_displayString("%of Max");
			}
		}
	}

	if(cells[1].Tempreture > 30  && cells[1].Tempreture >= cells[0].Tempreture  && cells[1].Tempreture >= cells[2].Tempreture
			&& cells[1].Tempreture >= cells[3].Tempreture  && cells[1].Tempreture >= cells[4].Tempreture
			&& cells[1].Tempreture >= cells[5].Tempreture)
	{
		count_t2 ++;
		LCD_clearScreen();
		if(count_t2  > 5)
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("cell-2 in danger");
			Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed= 100 %");

			MGPIO_VidSetPinValue( GPIOB, PIN7 , HIGH );
		}
		else
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("Cell-2 Overheating");

			dummy = (cells[1].Tempreture - 30) * 10;
			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed=");

			if(dummy > 100)
			{
				Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
				LCD_intgerToString(100);
				LCD_displayString("%of Max");
			}
			else
			{
				x =100-dummy;
				Set_DutyCycle(&Timer_2,x,TIM_Channel_4);
				LCD_intgerToString(dummy);
				LCD_displayString("%of Max");
			}
		}
	}
	if( cells[2].Tempreture > 30  && cells[2].Tempreture >= cells[1].Tempreture  && cells[2].Tempreture >= cells[0].Tempreture
			&& cells[2].Tempreture >= cells[3].Tempreture  && cells[2].Tempreture >= cells[4].Tempreture
			&& cells[2].Tempreture >= cells[5].Tempreture)
	{
		count_t3 ++;
		LCD_clearScreen();
		if(count_t3  > 5)
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("cell-3 in danger");
			Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed= 100 %");

			MGPIO_VidSetPinValue( GPIOB, PIN7 , HIGH );
		}
		else
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("Cell-3 Overheating");

			dummy = (cells[2].Tempreture - 30) * 10;
			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed=");

			if(dummy > 100)
			{
				Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
				LCD_intgerToString(100);
				LCD_displayString("%of Max");
			}
			else
			{
				x =100-dummy;
				Set_DutyCycle(&Timer_2,x,TIM_Channel_4);
				LCD_intgerToString(dummy);
				LCD_displayString("%of Max");
			}
		}
	}
	if( cells[3].Tempreture > 30  && cells[3].Tempreture >= cells[1].Tempreture  && cells[3].Tempreture >= cells[2].Tempreture
			&& cells[3].Tempreture >= cells[0].Tempreture  && cells[3].Tempreture >= cells[4].Tempreture
			&& cells[3].Tempreture >= cells[5].Tempreture)
	{
		count_t4 ++;
		LCD_clearScreen();
		if(count_t3  > 5)
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("cell-4 in danger");
			Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed= 100 %");

			MGPIO_VidSetPinValue( GPIOB, PIN7 , HIGH );
		}
		else
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("Cell-4 Overheating");

			dummy = (cells[3].Tempreture - 30) * 10;
			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed=");

			if(dummy > 100)
			{
				Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
				LCD_intgerToString(100);
				LCD_displayString("%of Max");
			}
			else
			{
				x =100-dummy;
				Set_DutyCycle(&Timer_2,x,TIM_Channel_4);
				LCD_intgerToString(dummy);
				LCD_displayString("%of Max");
			}
		}
	}
	if( cells[4].Tempreture > 30  && cells[4].Tempreture >= cells[1].Tempreture  && cells[4].Tempreture >= cells[2].Tempreture
			&& cells[4].Tempreture >= cells[3].Tempreture  && cells[4].Tempreture >= cells[0].Tempreture
			&& cells[4].Tempreture >= cells[5].Tempreture)
	{
		count_t5 ++;
		LCD_clearScreen();
		if(count_t5  > 5)
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("cell-5 in danger");
			Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed= 100 %");

			MGPIO_VidSetPinValue( GPIOB, PIN7 , HIGH );
		}
		else
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("Cell-5 Overheating");

			dummy = (cells[4].Tempreture - 30) * 10;

			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed=");

			if(dummy > 100)
			{
				Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
				LCD_intgerToString(100);
				LCD_displayString("%of Max");
			}
			else
			{
				x =100-dummy;
				Set_DutyCycle(&Timer_2,x,TIM_Channel_4);
				LCD_intgerToString(dummy);
				LCD_displayString("%of Max");
			}
		}
	}
	if( cells[5].Tempreture > 30  && cells[5].Tempreture >= cells[1].Tempreture  && cells[5].Tempreture >= cells[2].Tempreture
			&& cells[5].Tempreture >= cells[3].Tempreture  && cells[5].Tempreture >= cells[4].Tempreture
			&& cells[5].Tempreture >= cells[0].Tempreture)
	{
		count_t6 ++;
		LCD_clearScreen();
		if(count_t6  > 5)
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("cell-6 in danger");
			Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed= 100 %");

			MGPIO_VidSetPinValue( GPIOB, PIN7 , HIGH );
		}
		else
		{
			LCD_goToRowColumn(0,0);
			LCD_displayString("Cell-6 Overheating");


			dummy = (cells[5].Tempreture - 30) * 10;

			LCD_goToRowColumn(1,0);
			LCD_displayString("Fan Speed=");

			if(dummy > 100)
			{
				Set_DutyCycle(&Timer_2,0,TIM_Channel_4);
				LCD_intgerToString(100);
				LCD_displayString("%of Max");
			}
			else
			{
				x =100-dummy;
				Set_DutyCycle(&Timer_2,x,TIM_Channel_4);
				LCD_intgerToString(dummy);
				LCD_displayString("%of Max");
			}
		}
	}
	if (cells[0].Tempreture <= 25 && cells[1].Tempreture <= 25 && cells[2].Tempreture <= 25 && cells[3].Tempreture <= 25 && cells[4].Tempreture <= 25 && cells[5].Tempreture <= 25  )
	{
		count_t1 = 0,count_t2 = 0,count_t3 = 0,count_t4 =0,count_t5 =0,count_t6 = 0;
		Set_DutyCycle(&Timer_2,100,TIM_Channel_4);
		MGPIO_VidSetPinValue( GPIOB ,PIN7 , LOW );
		LCD_clearScreen();
		LCD_goToRowColumn(0,0);
		LCD_displayString("Battery In Safe Mode ");
		LCD_goToRowColumn(1,0);
		LCD_displayString("Fan Turn Off ");


	}

}
void timer3Init(void)
{

	Timer_3.Count_Mode = UP_COUNTER;
	Timer_3.Timer = TIM3;
	Timer_3.Prescaler =1 ;
	Timer_3.Period = 8000;
	Timer_3.Interrupt = INTERRUPT;
	Tim_Init(&Timer_3);
   TIM3_CNT=0;

}

void PWMTimeInit(void)
{

	Timer_2.Count_Mode = UP_COUNTER;
	Timer_2.Timer = TIM2;
	Timer_2.Prescaler = 1;
	Timer_2.Period = 60000;
	Timer_2.Interrupt = POLLING;
	Tim_Init(&Timer_2);

	Timer_PWM.Channel = TIM_Channel_4;
	Timer_PWM.Mode = PWM1;
	Timer_PWM.Duty_Cycle = 0;
	PWM_ChannelConfig(&Timer_2,&Timer_PWM);

}



void TIM3_IRQHandler(void)
{
	flag+=1;
	if (flag>3000){

		flag=1;
		timer_exitinson = 1 ;
		Duty_Cycle+=20;
		if (Duty_Cycle>100){
			Duty_Cycle=0;
		}
	}

	TIM3_SR=0;
	SET_BIT(TIM3_DIER,6);
}




  
  
  
