
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void MUART_voidInit(void);

void MUART_voidTransmitSynch(u8 Copy_u8DataArray[]);
void MUART_voidTransmitByteSynch(u8 Copy_u8Data);

#endif
