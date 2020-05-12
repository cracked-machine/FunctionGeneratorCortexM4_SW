/*
 * SignalManager.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_SIGNALMANAGER_H_
#define SRC_SIGNALMANAGER_SIGNALMANAGER_H_

#include "FunctionOutput.h"
#include "GainOutput.h"
#include "BiasOutput.h"
#include "FreqOutput.h"
#include "DacTimerRegistry.h"

#include "tim.h"

#define ENCODER_TIMER	TIM1
#define SM_MCLK 168000000		// MCU master clock frequency
#define SM_FSAMP 120			// sampling frequency, defined in WaveTableGeneratiom scripts

#define eDefaultFreqPreset FPRESET_1KHZ

typedef enum
{
	ENCODER_FORWARD = 0U,
	ENCODER_REVERSE

} eEncoder_Direction;

uint16_t SM_GetEncoderValue(eEncoder_Direction direction);
float SM_GetOutputInHertz();
eFreq_Preset SM_GetDefaultFreqPreset();

#endif /* SRC_SIGNALMANAGER_SIGNALMANAGER_H_ */
