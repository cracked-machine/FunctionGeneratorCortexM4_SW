/*
 * SignalManager.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */


#include "SignalManager.h"


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
