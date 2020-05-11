/*
 * SignalManager.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */


#include "SignalManager.h"
#include <math.h>

#define MCLK 168000000		// MCU master clock frequency
#define FSAMP 120			// sampling frequency, defined in WaveTableGeneratiom scripts

uint16_t SM_GetEncoderValue(eEncoder_Direction direction)
{
	if(direction)
	{
		return ENCODER_TIMER->ARR - ENCODER_TIMER->CNT;
	}
	else
	{
		return ENCODER_TIMER->CNT;
	}
}

float SM_GetOutputInHertz()
{
	volatile float tim8_psc;
	volatile float tim8_arr;

	// safe-guard against divide by zero
	(TIM8->PSC == 0) ? (tim8_psc = 1) : (tim8_psc = TIM8->PSC);
	(TIM8->ARR == 0) ? (tim8_arr = 1) : (tim8_arr = TIM8->ARR);

	float tim8_freq = MCLK / (tim8_psc * tim8_arr);


	return tim8_freq / FSAMP;
}

