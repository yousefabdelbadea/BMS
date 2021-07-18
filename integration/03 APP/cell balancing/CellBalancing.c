/******************************************************************************
 *
 * Module: charge control && cell Balancing
 *
 * File Name: CellBalancing.c
 *
 * Description: source file for Cell Balancing Driver
 *
 * Author: my team
	
 ******************************************************************************/
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 
 #include "Charge_Control.h"

#include "CellBalancing.h"
 
 #include "BMS_config.h"
 #include "BMS.h"

 extern  Cell cells[NUM_OF_CELLS];
 extern  f32 stateOfBranchCharge[NUM_OF_BRANCHES];
 extern  f32 overallStateOfCharge ;

 
 extern u8 isCharge[NUM_OF_BRANCHES];
 extern u8 isDisCharge[NUM_OF_BRANCHES];
 
 

  
 
 static u8 flag=0;
 

 void CellBalancing_CellBalancingProcessing(void)
 {
	Charge_Control_calcStateOfCharge();

	flag = ((stateOfBranchCharge[0] >= overallStateOfCharge))&&((stateOfBranchCharge[1] >= overallStateOfCharge))&&((stateOfBranchCharge[2] >= overallStateOfCharge));
	
	for(u8 i =0;i<NUM_OF_BRANCHES;i++)
	{
		if ((stateOfBranchCharge[i]- CHARGE_CONTROL_MARGIN) <MIN_STATE_OF_CHARGE)
	    {
		isCharge[i] =CHARGE_CONTROL_HIGH;
		isDisCharge[i]=CHARGE_CONTROL_LOW;

		/*alarm*/

		}
		else if ((stateOfBranchCharge[i]-CHARGE_CONTROL_MARGIN) >MAX_STATE_OF_CHARGE)
		{
					isCharge[i] =CHARGE_CONTROL_LOW;
					isDisCharge[i]=CHARGE_CONTROL_HIGH;

		}
		else if(((stateOfBranchCharge[i]+ CHARGE_CONTROL_MARGIN) < overallStateOfCharge))
		{
			isCharge[i] =CHARGE_CONTROL_HIGH;
			isDisCharge[i]=CHARGE_CONTROL_HIGH;


		}
		else if((stateOfBranchCharge[i] >= overallStateOfCharge)&& !flag)
		{
					isCharge[i] =CHARGE_CONTROL_LOW;
					isDisCharge[i]=CHARGE_CONTROL_HIGH;


		}
		else
		{
			isCharge[i] =CHARGE_CONTROL_HIGH;
			isDisCharge[i]=CHARGE_CONTROL_HIGH;

		}



	}
	flag=0;
		
	charge_control_sendData();

 }
 
 
 
 
 
 
 
 
 
 
 
 
 
