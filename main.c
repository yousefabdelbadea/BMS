#include "RCC_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "LCD.h"
#include "SYSTICK_INTERFACE.h"
#include "MULTIPLEXER_interface.h"
#include "TIMER_interface.h"
#include "NVIC.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

void ThermalManagment(void);
void Data_voidAcqusition(void);
void Display_voidDataAcqusition (void);
void timer3Init(void);
void TimeInit(void);

u8  count_t1 = 0,count_t2 = 0,count_t3 = 0,count_t4 =0,count_t5 =0,count_t6 = 0;
u32 timer_exitinson = 0 ;
u8 timer_flag = 0;




typedef struct {
	u8 name;
	f32 Tempreture;
	f32 Voltage;
	f32 Current;
} Cell;

Cell cells[6];

u32 n;


TIM_HandleTypeDef Timer_3;
TIM_HandleTypeDef Timer_2;
TIM_PWM_Config Timer_PWM;




int main()
{
	RCC_voidInitSysClock();
	/*Generate clock for GPPIOA*/
	RCC_voidEnableClock(RCC_APB2 , 2);
	/*Set direction of GPIOA pin 0 as input analog*/
	MGPIO_VidSetPinDirection( GPIOA , PIN0 , INPUT_ANLOG );
	/*Generate clock for GPPIOB*/
	RCC_voidEnableClock(RCC_APB2 , 3);
	/*Generate clock for ADC1*/
	RCC_voidEnableClock(RCC_APB2 , 9);
	/*clock of alternative function*/
	RCC_voidEnableClock(RCC_APB2 , 0);
	/*initalizing ADC_1*/
	ADC_VoidInit();
	/*start coversion of ADC_1*/
	start_coversion();
	/*intialize LCD*/
	LCD_init();
	/*initalize Multiplexer */
	HMultiplexer_voidInit();
	/*Intialize Systick Timer*/
	Systick_init();
	/*Intialize NVIC*/
	//NVIC_voidInit();
	/*Interupt Of Timer3*/
	//NVIC_setPriority(29 , 1 );
	//NVIC_enableInterrupt(29);

	//MGPIO_VidSetPinDirection( GPIOB , PIN7 , OUTPUT_SPEED_10MHZ_PP );
	/*
	TimeInit();
	Tim_Start(&Timer_2);
	timer3Init();
	Tim_Start(&Timer_3);

	while(1)
	{
		if (timer_flag == 1)
		{
			Data_voidAcqusition();
			ThermalManagment();
			timer_flag = 0;
		}
	}
	 */
	while(1)
	{
		LCD_goToRowColumn(0,0);

		LCD_displayString("CURRENT=");
		FloatToString(Get_Temp());

		//LCD_clearScreen();
	}



	return 1;
}

void timer3Init(void)
{
	Timer_3.Count_Mode = UP_COUNTER;
	Timer_3.Timer = TIM3;
	Timer_3.Prescaler = 1;
	Timer_3.Period = 8000;
	Timer_3.Interrupt = INTERRUPT;
	Tim_Init(&Timer_3);

}

void TimeInit(void)
{

	Timer_2.Count_Mode = UP_COUNTER;
	Timer_2.Timer = TIM2;
	Timer_2.Prescaler = 1;
	Timer_2.Period = 60000;
	Timer_2.Interrupt = POLLING;
	Tim_Init(&Timer_2);

	Timer_PWM.Channel = TIM_Channel_4;
	Timer_PWM.Mode = PWM1;
	Timer_PWM.Duty_Cycle = 100;
	PWM_ChannelConfig(&Timer_2,&Timer_PWM);

}



void TIM3_IRQHandler(void)
{
	timer_exitinson++;
	if(timer_exitinson > 2000)
	{
		timer_exitinson = 0;
		timer_flag = 1;
	}
}


void Data_voidAcqusition(void)
{

	u8 counter = 0;
	u32 dummy ;

	for(u8 i=0 ; i<6 ; i++)
	{
		cells[i].name = 1 + i;
		HChannelSelection_void(i);
		for( n =0 ; n<100 ; n++){}
		cells[i].Tempreture = Get_Temp();

		HChannelSelection_void(i+9);
		for( n =0 ; n<100 ; n++){}
		cells[i].Voltage = Get_Voltage();

	}
	for(u8 i=0 ; i<3 ; i++)
	{

		HChannelSelection_void(i+6);
		for( n =0 ; n<100 ; n++){}
		dummy = Get_Current();
		cells[counter].Current = dummy;
		counter +=1;
		for( n =0 ; n<100 ; n++){}
		cells[counter].Current = dummy;
		counter +=1;
	}
	counter = 0;
}

void Display_voidDataAcqusition(void)
{
	for (u8 i= 0 ; i<6 ;i++)
	{
		LCD_displayString("Cell_");
		LCD_intgerToString(cells[i].name);
		LCD_displayString(":");
		LCD_displayString(" T=");
		LCD_intgerToString(cells[i].Tempreture);
		LCD_displayString(" V=");

		LCD_intgerToString(cells[i].Voltage);
		LCD_displayString(" C=");

		LCD_intgerToString(cells[i].Current);
		for( n =0 ; n<1000000 ; n++){}
		LCD_clearScreen();

	}
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


