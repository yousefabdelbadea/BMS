#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stdint.h>

#define FIR_FILTER_LENGTH 16
#define Sample_time 7.5/(8*1000000)
#define CutOff_Freq 571428.571*2
//#define CutOff_Freq 285714.2855
typedef struct {
	float coff[2];
	float out[2];
} RCFilter;

void RCFilter_Init(RCFilter *filt  , float cutoffFreq , float sampleTime );
float RCFilter_Update(RCFilter *filt, float inp);

#endif
