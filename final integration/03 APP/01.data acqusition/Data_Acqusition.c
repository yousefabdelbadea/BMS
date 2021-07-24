/******************************************************************************
 *
 * Module: Data Acqusition
 *
 * File Name: Data_Acqusition.c
 *
 * Description: source file for Data Acqusition Driver
 *
 * Author: yousef abdo
		   ahmed mostafa
	
 ******************************************************************************/
  #include "STD_TYPES.h"
  #include "BIT_MATH.h"
  
  #include "DIO_interface.h"
  #include "ADC_interface.h"
  #include "SYSTICK_INTERFACE.h"

  #include "delay.h"

  #include "MULTIPLEXER_interface.h"

  #include "Data_Acqusition.h"

  #include "BMS.h"
  #include "BMS_config.h"

static f32 Get_Temp(void);
static f32 Get_Current(void);
static f32 Get_Voltage(void);

u32 ADC_Average(void);
  
 extern  Cell cells[NUM_OF_CELLS];
  u32 n;

void Data_voidAcqusitionInit(void)
{
	/*initalizing ADC_1*/
	ADC_VoidInit();
	/*start coversion of ADC_1*/
	start_coversion();
	/*initalize Multiplexer */
	HMultiplexer_voidInit();
} 
u32 ADC_Average(void){
	u32 x;
	x=0;
	for(int i=0;i<100;i++){
		x+=ADC_getValue();
	}
	return (x/100);
}

 
f32 Get_Temp()
{
	f32 x;

	x = ((ADC_Average()) * (0.08)*(0.66));

	return x;
}

f32 Get_Current()
{

	// (ADC_DR - Ref-Count) * (resolution/sensitivity)
	//Sensitivity 68 mV/A
	//resolution 3.3/4095

	f32 x = (3.3 / 4095);
	s32 z = (ADC_Average() - 3045);
	if (z<0){
		z=z*(-1);
	}
	f32 y =z*(x)/.185;

	//f32 x = (3.3 / 4095);
	//f32 y = (ADC_DR - 3200)*(x);

	//f32 y = (1.65 - (ADC_DR * (3.3 / 4095)) )/0.185;
	return y;
}

f32 Get_Voltage()
{
	/*
	Vin = Vout * (R2/(R1+R2))
	Here R1 = 30K ohm and R2 = 7.5K ohm
	Vout = (analogvalue * 5 / 1024).
	 */

	//f32 v =  ADC_DR*3.3/4095;
     f32 Vin;
	 Vin= ((ADC_Average()*3.3/4095)/(7.5*1000))*(37.5*1000);

	return Vin;

}





void Data_voidAcqusition(void)
{

	u8 counter = 0;
	f32 dummy ;

	for(u8 i=0 ; i<6 ; i++)
	{

		cells[i].name = 1 + i;
		HChannelSelection_void(i);
		_delay_ms(100);

		cells[i].Tempreture = Get_Temp();

		HChannelSelection_void(i+6);
		_delay_ms(100);
		cells[i].Voltage = Get_Voltage();
		if (i%2!=0){
			cells[i].Voltage=cells[i].Voltage-cells[i-1].Voltage;
		}
		_delay_ms(100);
	}
	for(u8 i=0 ; i<3 ; i++)
	{

		HChannelSelection_void(i+12);
		_delay_ms(100);
		dummy = Get_Current();
		cells[counter].Current = dummy;
		counter +=1;
		_delay_ms(100);
		cells[counter].Current = dummy;
		counter +=1;
	}
	counter = 0;
}
