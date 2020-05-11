/*
 * GainOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_GAINOUTPUT_H_
#define SRC_SIGNALMANAGER_GAINOUTPUT_H_

#include <stdint.h>

// signal output gain settings
typedef enum
{
	Zero_Gain = 0U,
	One_Gain,
	Two_Gain,
	Three_Gain,
	Four_Gain,
	Five_Gain,
	Six_Gain,
	Seven_Gain

} eOutput_gain;

void GO_SetOutputToEncoder(uint8_t pGain);
void GO_SetOutputGain(uint8_t pGain, uint8_t reverse);
uint8_t GO_GetOutputGain();
int8_t GO_GetGainInDecibels(eOutput_gain pGain);

#endif /* SRC_SIGNALMANAGER_GAINOUTPUT_H_ */
