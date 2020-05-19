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
void _InitOutputChannels();
void _InitNegGainCoefficients();
void _InitGainInDecibels();

void SM_Init()
{

	_InitOutputChannels();
	_InitNegGainCoefficients();
	_InitGainInDecibels();

}

void _InitGainInDecibels()
{

	// =20*LOG10(TARGETVPP/0.001)
	for(int i = 0; i < MAX_VPP_PRESETS; i++)
	{
		float decibel_mvolt_ref = 0.001;
		float this_amp_value = theAmpProfiles[i].amp_value;
		float new_gain_decibels = 20 * log10( this_amp_value / decibel_mvolt_ref );
		theAmpProfiles[i].gain_decibels = new_gain_decibels;

	}
}

void _InitNegGainCoefficients()
{

	// =(TARGETVPP/LUTVPP)/GAIN
	for(int i = 0; i < MAX_VPP_PRESETS; i++)
	{
		float this_amp_value = theAmpProfiles[i].amp_value;
		float this_lut_vpp = LUT_VPP;
		float this_gain_preset = (float)theAmpProfiles[i].gain_preset;
		float new_ngc = ( (this_amp_value / this_lut_vpp) / this_gain_preset);
		theAmpProfiles[i].neg_gain_coeff = new_ngc;
	}
}

void _InitOutputChannels()
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


float SM_ConvertPeriodToHertz(uint32_t period, uint16_t psc)
{
	(psc == 0) ? (psc = 1) : psc;

	return (float)SM_MCLK / ( (float)psc * (float)period );
}


uint16_t SM_ConvertHertzToPeriod(float hertz, uint16_t psc)
{
	(psc == 0) ? (psc = 1) : psc;

	return (SM_MCLK / hertz) / psc;
}

