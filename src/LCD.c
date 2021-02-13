 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: Header file for STM32F103C8  Microcontroller - LCD Driver
 *
 * Author: Mohamed Hamada
 ******************************************************************************/ 
 #include "RCC_interface.h"
 #include "DIO_interface.h"
 #include "SYSTICK_INTERFACE.h"
 #include "STD_TYPES.h"
 
 #include "LCD.h"
 #include "LCD_config.h"
 
 #include <stdlib.h>
#include <stdio.h>
 
 

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/************************************************************************************
* Service Name: LCD_init
* Service ID[hex]:
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to initialize pin in lcd .
************************************************************************************/
void LCD_init(void)
{
	  
	MGPIO_VidSetPinDirection( LCD_CTRL_PORT,EN, OUTPUT_SPEED_2MHZ_PP);/* Configure the control pin(EN) as output pins */
	MGPIO_VidSetPinDirection( LCD_CTRL_PORT,RS, OUTPUT_SPEED_2MHZ_PP);/* Configure the control pin(RS) as output pins */
	MGPIO_VidSetPinDirection( LCD_CTRL_PORT,RW, OUTPUT_SPEED_2MHZ_PP);/* Configure the control pin(RW) as output pins */
	#if (DATA_BITS_MODE == 4)
		#if (DATA_BITS_4_MODE == FIRST_4_PINS)
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN0, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 0) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN1, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 1) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN2, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 2) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN3, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 3) as output pin */
			
		#elif (DATA_BITS_4_MODE == SECOND_4_PINS)
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN4, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 4) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN5, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 5) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN6, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 6) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN7, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 7) as output pin */
		
		#elif (DATA_BITS_4_MODE == THIRD_4_PINS)
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN8 , OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 08) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN9 , OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 09) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN10, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 10) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN11, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 11) as output pin */
			
		#elif (DATA_BITS_4_MODE == FOURTH_4_PINS)
		    MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN12, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 12) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN13, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 13) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN14, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 14) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN15, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 15) as output pin */
		#endif	 
		LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
	#elif (DATA_BITS_MODE == 8)
	               /* Configure the data port as output port */
		#if (DATA_BITS_8_MODE == FIRST_8_PINS)
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN0, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 0) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN1, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 1) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN2, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 2) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN3, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 3) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN4, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 4) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN5, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 5) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN6, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 6) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN7, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 7) as output pin */
		#elif (DATA_BITS_8_MODE == SECOND_8_PINS)
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN8 , OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 08) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN9 , OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 09) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN10, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 10) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN11, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 11) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN12, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 12) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN13, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 13) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN14, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 14) as output pin */
			MGPIO_VidSetPinDirection( LCD_DATA_PORT,PIN15, OUTPUT_SPEED_2MHZ_PP);/* Configure the data pin(pin 15) as output pin */
		#endif
	    LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	#endif
	
	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

/************************************************************************************
* Service Name: LCD_sendCommand
* Service ID[hex]:
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): u8
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to send command to lcd .
************************************************************************************/

void LCD_sendCommand(u8 command)
{
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,RS, LOW); /* Instruction Mode RS=0 */
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,RW, LOW); /* write data to LCD so RW=0 */
	for(u32 i =0;i<1000;i++); /* delay for processing Tas = 50ns */
	
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,EN, HIGH); /* Enable LCD Enable=1 */
	for(u32 i =0;i<1000;i++); /* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
          
		           
		

	#if (DATA_BITS_4_MODE == FIRST_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFFFF0)|((command & 0xF0)>>4);
	#elif (DATA_BITS_4_MODE == SECOND_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFFF0F) | ((command & 0xF0));
	#elif (DATA_BITS_4_MODE == THIRD_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFF0FF) | ((command & 0xF0) <<4);
	#elif (DATA_BITS_4_MODE == FOURTH_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFF0FFF) | ((command & 0xF0) <<8);
	#endif
	

		for(u32 i =0;i<1000;i++); /* delay for processing Tdsw = 100ns */
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,EN, LOW); /* disable LCD E=0 */
	for(u32 i =0;i<1000;i++); /* delay for processing Th = 13ns */
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,EN, HIGH); /* Enable LCD E=1 */
	for(u32 i =0;i<1000;i++); /* delay for processing Tpw - Tdws = 190ns */


	#if (DATA_BITS_4_MODE == FIRST_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFFFF0)|((command & 0x0F));
	#elif (DATA_BITS_4_MODE == SECOND_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFFF0F) | ((command & 0x0F)<<4);
	#elif (DATA_BITS_4_MODE == THIRD_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFF0FF) | ((command & 0x0F) <<8);
	#elif (DATA_BITS_4_MODE == FOURTH_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFF0FFF) | ((command & 0x0F) <<12);
	#endif

		for(u32 i =0;i<1000;i++); /* delay for processing Tdsw = 100ns */
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,EN, LOW); /* disable LCD E=0 */
	for(u32 i =0;i<1000;i++); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	 #if (DATA_BITS_8_MODE == FIRST_8_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFFF00) | (command);/* out the required command to the data bus D0 --> D7 */
	 
	 #elif  (DATA_BITS_8_MODE == SECOND_8_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFF00FF) | (command);/* out the required command to the data bus D8 --> D15 */
	 
	 #endif 
	 
		for(u32 i =0;i<1000;i++);/* delay for processing Tdsw = 100ns */
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,EN, LOW); /* disable LCD E=0 */
	for(u32 i =0;i<1000;i++); /* delay for processing Th = 13ns */
#endif
}

/************************************************************************************
* Service Name: LCD_displayCharacter
* Service ID[hex]:
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): u8
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to send char to lcd .
************************************************************************************/

void LCD_displayCharacter(u8 data)
{
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,RS, HIGH); /* Instruction Mode RS=0 */
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,RW, LOW); /* write data to LCD so RW=0 */
	for(u32 i =0;i<1000;i++); /* delay for processing Tas = 50ns */
	
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,EN, HIGH); /* Enable LCD Enable=1 */
	for(u32 i =0;i<1000;i++); /* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
          
		           
		

	#if (DATA_BITS_4_MODE == FIRST_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFFFF0)|((data & 0xF0)>>4);
	#elif (DATA_BITS_4_MODE == SECOND_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFFF0F) | ((data & 0xF0));
	#elif (DATA_BITS_4_MODE == THIRD_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFF0FF) | ((data & 0xF0) <<4);
	#elif (DATA_BITS_4_MODE == FOURTH_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFF0FFF) | ((data & 0xF0) <<8);
	#endif
	

		for(u32 i =0;i<1000;i++); /* delay for processing Tdsw = 100ns */
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,EN, LOW); /* disable LCD E=0 */
	for(u32 i =0;i<1000;i++); /* delay for processing Th = 13ns */
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,EN, HIGH); /* Enable LCD E=1 */
	for(u32 i =0;i<1000;i++); /* delay for processing Tpw - Tdws = 190ns */


	#if (DATA_BITS_4_MODE == FIRST_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFFFF0)|((data & 0x0F));
	#elif (DATA_BITS_4_MODE == SECOND_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFFF0F) | ((data & 0x0F)<<4);
	#elif (DATA_BITS_4_MODE == THIRD_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFF0FF) | ((data & 0x0F) <<8);
	#elif (DATA_BITS_4_MODE == FOURTH_4_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFF0FFF) | ((data & 0x0F) <<12);
	#endif

		for(u32 i =0;i<1000;i++); /* delay for processing Tdsw = 100ns */
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,EN, LOW); /* disable LCD E=0 */
	for(u32 i =0;i<1000;i++); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	 #if (DATA_BITS_8_MODE == FIRST_8_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFFFF00) | (data);/* out the required command to the data bus D0 --> D7 */
	 
	 #elif  (DATA_BITS_8_MODE == SECOND_8_PINS)
		LCD_DATA_REG = (LCD_DATA_REG & 0xFFFF00FF) | (data);/* out the required command to the data bus D8 --> D15 */
	 
	 #endif 
	 
		for(u32 i =0;i<1000;i++); /* delay for processing Tdsw = 100ns */
	MGPIO_VidSetPinValue(LCD_CTRL_PORT,EN, LOW); /* disable LCD E=0 */
	for(u32 i =0;i<1000;i++); /* delay for processing Th = 13ns */
#endif
}
/************************************************************************************
* Service Name: LCD_displayString
* Service ID[hex]:
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): pointer to string
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to send string to lcd .
************************************************************************************/
void LCD_displayString(const char *Str)
{
	u8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}


/************************************************************************************
* Service Name: LCD_goToRowColumn
* Service ID[hex]:
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): u8 row,u8 col
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to LCD_go To Row Column .
************************************************************************************/
void LCD_goToRowColumn(u8 row,u8 col)
{
	u8 Address=0;
	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION); 
}


/************************************************************************************
* Service Name: LCD_displayStringRowColumn
* Service ID[hex]:
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): u8 row,u8 colum
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to display String Row Column.
************************************************************************************/
void LCD_displayStringRowColumn(u8 row,u8 col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}


/************************************************************************************
* Service Name: LCD_intgerToString
* Service ID[hex]:
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): int
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to convert intger To String .
************************************************************************************/
void LCD_intgerToString(u32 data)
{
   char buff[16]; /* String to hold the ascii result */
	
  itoa(data,buff,10); /* 10 for decimal */
	//sprintf(buff,"%d",data);
   LCD_displayString(buff);
}




/************************************************************************************
* Service Name: LCD_clearScreen
* Service ID[hex]:
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to clear screen .
************************************************************************************/
void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display 
}


void LCD_vidWriteNumber(s32 Number)
{
	s32 reverse_Number=1;
	if(Number < 0)
	{
		Number *= -1;
		LCD_displayCharacter('-');
	}
	if(Number==0)
	{
		LCD_displayCharacter('0');
	}

	while(Number!=0)
	{
		reverse_Number=Number%10+reverse_Number*10;
		Number/=10;
	}
	while(reverse_Number!=1)
	{
		LCD_displayCharacter(reverse_Number%10+48);//+'0'
		reverse_Number/=10;
	}

}

