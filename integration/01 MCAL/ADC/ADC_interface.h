
#include "STD_TYPES.h"
#ifndef _ADC_INTERFACE_H
#define _ADC_INTERFACE_H



void ADC_VoidInit(void);
void start_coversion(void);
u32 ADC_getADC(void);




#define CHANNEL_0   0
#define CHANNEL_1   1
#define CHANNEL_2   2
#define CHANNEL_3   3
#define CHANNEL_4   4
#define CHANNEL_5   5
#define CHANNEL_6   6
#define CHANNEL_7   7
#define CHANNEL_8   8
#define CHANNEL_9   9

#define ENABLE_SCAN_MODE   1
#define DISABLE_SCAN_MODE  0

#define RIGHT_ALIGNMENT       0
#define LEFT_ALIGNMENT        1

#define SINGLE_CONVERSION     1
#define CONTINOUS_CONVERSION  0

#define SAMPLING_TIME_1_5    0
#define SAMPLING_TIME_7_5    1
#define SAMPLING_TIME_13_5   2
#define SAMPLING_TIME_28_5   3
#define SAMPLING_TIME_41_5   4
#define SAMPLING_TIME_55_5   5
#define SAMPLING_TIME_71_5   6
#define SAMPLING_TIME_239_5  7

#define  NUM_CONVERSION_0     0
#define  NUM_CONVERSION_1     1
#define  NUM_CONVERSION_2     2
#define  NUM_CONVERSION_3     3
#define  NUM_CONVERSION_4     4
#define  NUM_CONVERSION_5     5
#define  NUM_CONVERSION_6     6
#define  NUM_CONVERSION_7     7
#define  NUM_CONVERSION_8     8
#define  NUM_CONVERSION_9     9
#define  NUM_CONVERSION_10    10
#define  NUM_CONVERSION_11    11
#define  NUM_CONVERSION_12    12
#define  NUM_CONVERSION_13    13
#define  NUM_CONVERSION_14    14
#define  NUM_CONVERSION_15    15
#define  NUM_CONVERSION_16    16




#endif
