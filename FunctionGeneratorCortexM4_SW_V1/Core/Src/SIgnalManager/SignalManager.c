/*
 * SignalManager.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */


#include "SignalManager.h"
#include <math.h>


sOutputChannel_t SignalChannel;
sOutputChannel_t SyncChannel;


void SM_Init()
{

	// initialise the output channels
	SignalChannel.channel = SIGNAL_CHANNEL;
	SignalChannel.ref_lut_data = theFuncProfiles[SINE_FUNC_MODE].lookup_table_data;
	SignalChannel.func_profile = &theFuncProfiles[eDefaultFuncPreset];
	for(int i = 0; i < SINE_DATA_SIZE; i++)
		SignalChannel.dsp_lut_data[i] = sine_data_table_3600[i];
	SignalChannel.amp_profile = &theAmpProfiles[eDefaultVppPreset];
	SignalChannel.gain_profile = &theGainProfiles[eDefaultGainPreset];

	SyncChannel.channel = SYNC_CHANNEL;
	SyncChannel.ref_lut_data = theFuncProfiles[SINE_FUNC_MODE].lookup_table_data;
	SyncChannel.func_profile = &theFuncProfiles[eDefaultFuncPreset];
	for(int i = 0; i < SINE_DATA_SIZE; i++)
		SyncChannel.dsp_lut_data[i] = sine_data_table_3600[i];
	SyncChannel.amp_profile = &theAmpProfiles[eDefaultVppPreset];
	SyncChannel.gain_profile = &theGainProfiles[eDefaultGainPreset];
}

sOutputChannel_t * SM_GetOutputChannel(eOutputChannel_t pChannel)
{
	if(!pChannel)
		return &SignalChannel;
	else
		return &SyncChannel;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
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

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
float SM_GetOutputInHertz()
{
	volatile float tim8_psc;
	volatile float tim8_arr;

	// safe-guard against divide by zero
	(TIM8->PSC == 0) ? (tim8_psc = 1) : (tim8_psc = TIM8->PSC);
	(TIM8->ARR == 0) ? (tim8_arr = 1) : (tim8_arr = TIM8->ARR);

	float tim8_freq = SM_MCLK / (tim8_psc * tim8_arr);


	return tim8_freq / SM_FSAMP;
}


