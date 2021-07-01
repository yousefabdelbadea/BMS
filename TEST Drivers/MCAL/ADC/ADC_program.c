/*
 * ADC_program.c
 *
 *  Created on: Jan 17, 2021
 *      Author: Yousef
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "RCC_interface.h"

#include "ADC_private.h"
#include "ADC_interface.h"
#include "ADC_config.h"
void ADC_VoidInit(void)
{
	CLR_REG(ADC_CR1);

	/*for enable and disable scan mode*/
	if(SCAN_MODE == ENABLE_SCAN_MODE)
		SET_BIT(ADC_CR1,SCAN);
	else 
		CLR_BIT(ADC_CR1,SCAN);


	CLR_REG(ADC_CR2);	
	/*to data aligenment*/
	if(DATA_ALIGENMENT == RIGHT_ALIGNMENT)
		CLR_BIT(ADC_CR2,ALIGN);
	else
		SET_BIT(ADC_CR2,ALIGN);

	if (CONVERSION_MODE == CONTINOUS_CONVERSION)
		SET_BIT(ADC_CR2,CONT);
	else
		CLR_BIT(ADC_CR2,CONT);

	CLR_REG(ADC_SMPR2);
	/* Sampling time*/
	ADC_SMPR2 |= SAMPLING_TIME;

	/*number of conversion = 1*/
	ADC_SQR1 |= (NUMBER_CONVERSION << 20 );

	/*Channel_0 Rank_1*/
	ADC_SQR3 |= SELECTED_CHANNEL;

	/*ADC_Power_On*/
	SET_BIT(ADC_CR2,ADON);


	/*reset calibration*/
	SET_BIT(ADC_CR2,RCAL);

	/*calibration*/
	SET_BIT(ADC_CR2,CAL);

}

void start_coversion(void)
{
	/*ADC_Power_On*/
	SET_BIT(ADC_CR2,ADON);
}

f32 Get_Temp()
{
	u32 x;
	//x = ((ADC_DR) * (0.120879));
	x = ((ADC_DR) * (0.122));

	return x;
}

f32 Get_Current()
{

	// (ADC_DR - Ref-Count) * (resolution/sensitivity)
	//Sensitivity 68 mV/A
	//resolution 3.3/4095

	//f32 x = (3.3 / 278.46);
	//f32 y = (ADC_DR - 341)*(x);

	f32 x = (3.3 / 4095);
	f32 y = (ADC_DR - 3200)*(x);
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

	f32 Vin= ((ADC_DR*3.3/4095)/(7.5*1000))*(37.5*1000);

	return Vin;

}

