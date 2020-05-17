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

//uint16_t min_arr = 3555;		//50KHz if SM_CLKC=168000000 and SWEEP_TIMER->PSC=0
uint16_t min_arr = 16800;		//10KHz if SM_CLKC=168000000 and SWEEP_TIMER->PSC=0
//uint16_t min_arr = 33600;		//5KHz if SM_CLKC=168000000 and SWEEP_TIMER->PSC=0
//uint16_t min_arr = 84000;		//2KHz if SM_CLKC=168000000 and SWEEP_TIMER->PSC=0
//uint16_t min_arr = 16800;		//1KHz if SM_CLKC=168000000 and SWEEP_TIMER->PSC=0

uint32_t max_arr = 0xFFFF;


void SM_Init()
{

	// initialise the SIGNAL output channel
	SignalChannel.channel = SIGNAL_CHANNEL;
	SignalChannel.ref_lut_data = theFuncProfiles[SINE_FUNC_MODE].lookup_table_data;
	SignalChannel.func_profile = &theFuncProfiles[eDefaultFuncPreset];

	for(int i = 0; i < SINE_DATA_SIZE; i++)
		SignalChannel.dsp_lut_data[i] = sine_data_table_3600[i];

	SignalChannel.amp_profile = &theAmpProfiles[eDefaultVppPreset];
	SignalChannel.gain_profile = &theGainProfiles[eDefaultGainPreset];

	// initialise the SYNC output channel
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
	volatile float output_tm_psc;
	volatile float output_tm_arr;

	// safe-guard against divide by zero
	(OUTPUT_TIMER->PSC == 0) ? (output_tm_psc = 1) : (output_tm_psc = OUTPUT_TIMER->PSC);
	(OUTPUT_TIMER->ARR == 0) ? (output_tm_arr = 1) : (output_tm_arr = OUTPUT_TIMER->ARR);

	float output_tm_freq = SM_MCLK / (output_tm_psc * output_tm_arr);


	return output_tm_freq / SM_FSAMP;
}


