/*
 * FreqOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FREQOUTPUT_C_
#define SRC_SIGNALMANAGER_FREQOUTPUT_C_

#include "FreqOutput.h"

#include "tim.h"

#include "SignalManager.h"


/*
 *
 *
 *
 */
void FreqO_ModifyOutput()
{
	TIM8->ARR = SM_GetEncoderValue(ENCODER_FORWARD) * FREQ_ENCODER_MAG;
}

/*
 *
 *
 *
 */
uint32_t FreqO_GetOutputFreq()
{
	return TIM8->ARR;
}

/*
 *
 *
 *
 */
void FreqO_ApplyPreset(eFreq_Preset pPreset)
{
	switch(pPreset)
	{
		case FPRESET_1HZ:
			TIM8->PSC = 0x0002;
			TIM8->ARR = 0xb5ff;
			ENCODER_TIMER->CNT = TIM8->ARR;
			break;
		case FPRESET_100HZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x36bf;
			ENCODER_TIMER->CNT = TIM8->ARR;
			break;
		case FPRESET_1KHZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x0570;
			ENCODER_TIMER->CNT = TIM8->ARR;
			break;
		case FPRESET_100KHZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x0008;
			ENCODER_TIMER->CNT = TIM8->ARR;
			break;
	}
}

#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_C_ */
