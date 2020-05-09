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

#include "tim.h"

#define ENCODER_TIMER	TIM1

typedef enum
{
	ENCODER_FORWARD = 0U,
	ENCODER_REVERSE

} eEncoder_Direction;

uint16_t SM_GetEncoderValue(eEncoder_Direction direction);

#endif /* SRC_SIGNALMANAGER_SIGNALMANAGER_H_ */
