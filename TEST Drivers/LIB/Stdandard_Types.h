/*
 * Std_Types.h
 *
 *  Created on: Aug 30, 2020
 *      Author: H
 */

#ifndef DIO_DRIVER_STD_TYPES_H_
#define DIO_DRIVER_STD_TYPES_H_

#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

/*From 0 TO 255*/
typedef unsigned char     uint8_t;

/*From -128 TO 127*/
typedef char     sint8_t;

/*From 0 to 65535 */
typedef unsigned short    uint16_t;

/*From -32768 TO. +32767*/
typedef short      sint16_t;


/* From 0 TO 4294967295      */
typedef unsigned long         uint32_t;

/* -2147483648 .. +2147483647     */
typedef signed long           sint32_t;

/*       0..18446744073709551615  */
typedef unsigned long long    uint64_t;

typedef signed long long      sint64_t;


typedef float                 float32_t;


typedef double                float64_t;



#endif /* DIO_DRIVER_STD_TYPES_H_ */
