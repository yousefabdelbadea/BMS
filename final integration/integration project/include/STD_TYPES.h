/******************************************************/
/* Author    : YOUSEF                            */
/* Date      : 29 JUL 2020                            */
/* Version   : V01                                    */
/******************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H


/*     NULL pointer    */
 #ifndef NULL
 #define NULL   ((void*)0)
 #endif
 
 /*boolean data type*/
 typedef unsigned char bool;
 
 
 #ifndef ENABLE  
 #define ENABLE         1
 #endif
 
 #ifndef DISABLE  
 #define DISABLE         1
 #endif
 
  
 #ifndef TRUE 
 #define TRUE (1U)
 #endif 
 #ifndef FALSE 
 #define FALSE (0U)
 #endif

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long  int u32;

typedef signed char s8;
typedef signed short int s16;
typedef signed long  int s32;

typedef unsigned long long int u64 ;
typedef signed long long int s64 ;

typedef float  f32;
typedef double f64;


#endif
