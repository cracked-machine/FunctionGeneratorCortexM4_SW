/*
 * BiasOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_BIASOUTPUT_H_
#define SRC_SIGNALMANAGER_BIASOUTPUT_H_

#include <stdint.h>
#include "SignalManager.h"

typedef enum
{
	INVERSEBIAS = 0x00U,
	NORMALBIAS

} eBias_Polarity;

// dc bias constants
#define BIAS_MAG 10						// adjustment speed
#define BIAS_MAX 8000/BIAS_MAG			// The encoder max value: top=max pos bias, 0=max neg bias
#define BIAS_CENTER	4000/BIAS_MAG		// the encoder center value: zero crossing point

void BO_MapEncoderPositionToSignalOutput(uint16_t pEncoderValue);
uint32_t BO_GetOutputBias();
eBias_Polarity BO_GetBiasPolarity();
uint16_t BO_GetDcBiasEncoderValue();
//void BO_SetPwmSignalOffsetForGain(eGainSettings_t temp_gain);
//void BO_SetPwmSignalOffsetForDuty(uint32_t tim3_arr);

#endif /* SRC_SIGNALMANAGER_BIASOUTPUT_H_ */
