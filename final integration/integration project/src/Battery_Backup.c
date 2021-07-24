/******************************************************************************
 *
 * Module: Battery Backup
 *
 * File Name: Battery_Backup.c
 *
 * Description: source file for BMS  - Battery Backup Driver
 *
 * Author: Amir abo zaid 
 *
 *******************************************************************************/


 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 
 
 
#include "DIO_interface.h"
  
 #include "BMS_config.h"
 #include "BMS.h"
 

 #include "Battery_Backup.h"
 #include "Battery_Backup_config.h"


extern  Cell cells[6];

extern u8 Battery_Backup_flag[6];



static u8 Battery_Backup_FaultFound(u8 index);




void Battery_Backup_init(void)
{
	
    MGPIO_VidSetPinDirection(PORT_DECODER_A0,DECODER_A0,OUTPUT_SPEED_2MHZ_PP);    
	MGPIO_VidSetPinDirection(PORT_DECODER_A1,DECODER_A1,OUTPUT_SPEED_2MHZ_PP);	
    MGPIO_VidSetPinDirection(PORT_DECODER_A2,DECODER_A2,OUTPUT_SPEED_2MHZ_PP);

    
	
	
		
	MGPIO_VidSetPinValue(PORT_DECODER_A0,DECODER_A0, LOW);
    MGPIO_VidSetPinValue(PORT_DECODER_A1,DECODER_A1, LOW);
    MGPIO_VidSetPinValue(PORT_DECODER_A2,DECODER_A2, LOW);

}
static u8 Battery_Backup_FaultFound(u8 index)
{
	if((cells[index].Tempreture >=MAX_TEMP) )
	{
		Battery_Backup_flag[index]=1;
		return 1;
	}
	
	else if ((cells[index].Tempreture <=MIN_TEMP))
	{
		Battery_Backup_flag[index] =2;
		return 1;


	}

	else if (cells[index].Voltage >=MAX_VOLT)
	{
		Battery_Backup_flag[index] =3;
		return 1;
	}
	else if ((cells[index].Voltage <=MIN_VOLT))
	{
		Battery_Backup_flag[index]=4;
		return 1;

	}

	else if (cells[index].Current >=MAX_CURRENT  )
	{
		Battery_Backup_flag[index]=5;
		return 1;
	}

	else if (cells[index].Current <=MIN_CURRENT)
	{
		Battery_Backup_flag[index] = 6;
		return 1;

	}

	else if ((cells[index].stateOfCharge) <=(MIN_STATE_OF_CHARGE) )
	{
		Battery_Backup_flag[index]=7;
		return 1;
	}

	return 0;

	}




void Battery_Backup_check()
{

for (u8 i =0;i<NUM_OF_CELLS;i++)
{

if (Battery_Backup_FaultFound(i))
{
	
	switch (i)
	{
	case 0 : 
		
		
		MGPIO_VidSetPinValue(PORT_DECODER_A0,DECODER_A0, HIGH);
        MGPIO_VidSetPinValue(PORT_DECODER_A1,DECODER_A1, LOW);
        MGPIO_VidSetPinValue(PORT_DECODER_A2,DECODER_A2, LOW);
		
		break;
		
	case 1 : 
		
		
		MGPIO_VidSetPinValue(PORT_DECODER_A0,DECODER_A0, LOW);
        MGPIO_VidSetPinValue(PORT_DECODER_A1,DECODER_A1, HIGH);
        MGPIO_VidSetPinValue(PORT_DECODER_A2,DECODER_A2, LOW);
		
		break;
		
	case 2 : 
		
		
		MGPIO_VidSetPinValue(PORT_DECODER_A0,DECODER_A0, HIGH);
        MGPIO_VidSetPinValue(PORT_DECODER_A1,DECODER_A1, HIGH);
        MGPIO_VidSetPinValue(PORT_DECODER_A2,DECODER_A2, LOW);
		
		break;
		
	case 3 : 
		
		
		MGPIO_VidSetPinValue(PORT_DECODER_A0,DECODER_A0, LOW);
        MGPIO_VidSetPinValue(PORT_DECODER_A1,DECODER_A1, LOW);
        MGPIO_VidSetPinValue(PORT_DECODER_A2,DECODER_A2, HIGH);
		
		break;
		
	case 4 : 
	
		
		MGPIO_VidSetPinValue(PORT_DECODER_A0,DECODER_A0, HIGH);
        MGPIO_VidSetPinValue(PORT_DECODER_A1,DECODER_A1, LOW);
        MGPIO_VidSetPinValue(PORT_DECODER_A2,DECODER_A2, HIGH);
		
		break;
		
	case 5 : 
		
		
		MGPIO_VidSetPinValue(PORT_DECODER_A0,DECODER_A0, LOW);
        MGPIO_VidSetPinValue(PORT_DECODER_A1,DECODER_A1, HIGH);
        MGPIO_VidSetPinValue(PORT_DECODER_A2,DECODER_A2, HIGH);
		
		break;
		
	default :
	
		
		MGPIO_VidSetPinValue(PORT_DECODER_A0,DECODER_A0, LOW);
        MGPIO_VidSetPinValue(PORT_DECODER_A1,DECODER_A1, LOW);
        MGPIO_VidSetPinValue(PORT_DECODER_A2,DECODER_A2, LOW);
		
		break;
	


		
	}
}
else
{
	
	/*		no thing		*/
}


}


}
