/******************************************************************************
 *
 * Module: STP
 *
 * File Name: STP.h
 *
 * Description:  header file for STP driver
 *
 * Author: Mohamed Hamada
 *
 ********************************************************************************/
 
 #ifndef STP_H_
 #define STP_H_
 
 
 void STP_init(void);
 void STP_sendSynchronus(u8 *dataTosend);
 
 #endif
