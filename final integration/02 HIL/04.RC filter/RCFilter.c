/*
 * RCFilter.c
 *
 *  Created on: May 24, 2021
 *      Author: Yousef
 */


#include "RCFilter_interface.h"


void RCFilter_Init(RCFilter *filt  , float cutoffFreq , float sampleTime )
 {
   /*compute the equavelant RC constant from cut-off freq */
   /*cut-off freq = 1 / 2*pi*RC*/

	float RC =1.0f /(6.283185f * cutoffFreq);

	/*filters cofficients*/
	filt->coff[0] = sampleTime / (sampleTime + RC);
	filt->coff[1] = RC / (sampleTime + RC);

}

float RCFilter_Update(RCFilter *filt, float inp)
{
    /*shift output sample*/
    filt->out[1] = filt->out[0];

	/*compute new output sample*/
	filt->out[0] = filt->coff[0]*inp + filt->coff[1]* filt->out[1];

	/*Return Output*/
	return (filt->out[0]);

}



