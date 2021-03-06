/*
 * FreqOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FREQOUTPUT_C_
#define SRC_SIGNALMANAGER_FREQOUTPUT_C_

#include "FreqOutput.h"
#include "SignalManager.h"
#include "DisplayManager.h"

#include "tim.h"
#include "dac.h"

/*
 *	Array of objects for Frequency Presets and their encoder positions for freq preset menu
 */
FreqProfile_t theFreqProfiles[MAX_NUM_FREQ_PRESETS] =
{
	{ 0, 	FPRESET_1HZ,	0x0016,	0,	1.0  },
	{ 1, 	FPRESET_10HZ,	0x0003,	0,	1.0  },
	{ 2, 	FPRESET_50HZ,	0x0000,	0,	1.0  },
	{ 3, 	FPRESET_100HZ,	0x0000,	0,	1.0  },
	{ 4, 	FPRESET_250HZ, 	0x0000,	0,	1.0  },
	{ 5, 	FPRESET_500HZ, 	0x0000,	0,	1.0  },
	{ 6, 	FPRESET_750HZ,	0x0000,	0,	1.0  },
	{ 7, 	FPRESET_1KHZ, 	0x0000,	0,	1.0  },
	{ 8, 	FPRESET_5KHZ, 	0x0000,	0,	1.0  },
	{ 9, 	FPRESET_10KHZ,	0x0000,	0,	1.0  },
	{ 10, 	FPRESET_25KHZ, 	0x0000,	0,	0.99 },
	{ 11, 	FPRESET_50KHZ, 	0x0000,	0,	0.99 },
	{ 12, 	FPRESET_75KHZ, 	0x0000,	0,	1.0  },
	{ 13,	FPRESET_100KHZ, 0x0000,	0,	0.95 }

};

//  default startup freq profile
FreqProfile_t *freq_profile = &theFreqProfiles[eDefaultFreqPreset];

// determine if next rotary encoder position should increase/decrease
uint16_t freq_last_encoder_value = 0;


/*
 * 	Function prototypes
 */
void 			FreqO_InitFreqProfiles();
void 			FreqO_MapEncoderPositionCoarse(uint16_t pEncValue);
void 			FreqO_ApplyProfile(eFreqSettings_t pPresetEnum);
void 			FreqO_AdjustFreq();
void 			FreqO_AdjustPrescaler();
uint32_t 		FreqO_GetOutputFreq();
void 			FreqO_ResetLastEncoderValue();
FreqProfile_t * FreqO_FindFPresetObject(eFreqSettings_t pEnum);
FreqProfile_t * FreqO_GetFPresetObject();
uint8_t 		FreqO_GetPresetEncoderPos();
uint8_t 		FreqO_GetFreqPresetEncoderRange();
FreqProfile_t* 	FreqO_GetProfileByIndex(uint32_t pIndex);


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FreqO_InitFreqProfiles()
{
	for(int i = 0; i < MAX_NUM_FREQ_PRESETS; i++)
	{
		// prevent divide by zero (prescaler)
		if(theFreqProfiles[i].psc == 0)
			theFreqProfiles[i].arr = ((SM_MCLK / theFreqProfiles[i].hertz) / SM_FSAMP) * theFreqProfiles[i].error;
		else
			theFreqProfiles[i].arr = (((SM_MCLK / theFreqProfiles[i].hertz) / theFreqProfiles[i].psc) / SM_FSAMP) * theFreqProfiles[i].error;
	}
}


/*
 *
 *	@brief	map rotary enocder position to profile
 *
 *	@param None
 *	@retval None
 *
 */
void FreqO_MapEncoderPositionCoarse(uint16_t pEncValue)
{

	uint32_t tmpFreqIndex = freq_profile->index;
	if(pEncValue > freq_last_encoder_value)
	{
		tmpFreqIndex++;
		if(tmpFreqIndex > MAX_NUM_FREQ_PRESETS-1) tmpFreqIndex = MAX_NUM_FREQ_PRESETS-1;
		FreqO_ApplyProfile( FreqO_GetProfileByIndex(tmpFreqIndex)->hertz );
	}
	else if (pEncValue < freq_last_encoder_value)
	{
		tmpFreqIndex--;
		if(tmpFreqIndex > MAX_NUM_FREQ_PRESETS-1) tmpFreqIndex = 0;
		FreqO_ApplyProfile( FreqO_GetProfileByIndex(tmpFreqIndex)->hertz );
	}
	freq_last_encoder_value = pEncValue;

}

/*
 *
 *	@brief	map rotary enocder position to profile
 *
 *	@param None
 *	@retval None
 *
 */
void FreqO_MapEncoderPositionFine(uint16_t pEncValue)
{

//	uint32_t tmpFreqIndex = freq_profile->index;
	if(pEncValue > freq_last_encoder_value)
	{
		OUTPUT_TIMER->ARR++;
//		tmpFreqIndex++;
//		if(tmpFreqIndex > MAX_NUM_FREQ_PRESETS-1) tmpFreqIndex = MAX_NUM_FREQ_PRESETS-1;
//		FreqO_ApplyProfile( FreqO_GetProfileByIndex(tmpFreqIndex)->hertz );
	}
	else if (pEncValue < freq_last_encoder_value)
	{
		OUTPUT_TIMER->ARR--;
//		tmpFreqIndex--;
//		if(tmpFreqIndex > MAX_NUM_FREQ_PRESETS-1) tmpFreqIndex = 0;
//		FreqO_ApplyProfile( FreqO_GetProfileByIndex(tmpFreqIndex)->hertz );
	}
	freq_last_encoder_value = pEncValue;

}

/*
 *
 *	@brief	map rotary enocder position to profile
 *
 *	@param None
 *	@retval None
 *
 */
void FreqO_MapEncoderPositionToPrescaler(uint16_t pEncValue)
{

//	uint32_t tmpFreqIndex = freq_profile->index;
	if(pEncValue > freq_last_encoder_value)
	{
		OUTPUT_TIMER->PSC++;

	}
	else if (pEncValue < freq_last_encoder_value)
	{
		if(OUTPUT_TIMER->PSC > 0)
			OUTPUT_TIMER->PSC--;
//		tmpFreqIndex--;
//		if(tmpFreqIndex > MAX_NUM_FREQ_PRESETS-1) tmpFreqIndex = 0;
//		FreqO_ApplyProfile( FreqO_GetProfileByIndex(tmpFreqIndex)->hertz );
	}
	freq_last_encoder_value = pEncValue;

}



/*
 *
 *	@brief Set frequency output by profile
 *
 *	@param pPresetEnum search criteria. Should be one of the following:
 *
 *	FPRESET_1HZ 	= 1U,
	FPRESET_10HZ	= 10U,
	FPRESET_50HZ	= 50U,
	FPRESET_100HZ	= 100U,
	FPRESET_250HZ	= 250U,
	FPRESET_500HZ	= 500U,
	FPRESET_750HZ	= 750U,
	FPRESET_1KHZ	= 1000U,
	FPRESET_5KHZ	= 5000U,
	FPRESET_10KHZ	= 10000U,
	FPRESET_25KHZ	= 25000U,
	FPRESET_50KHZ	= 50000U,
	FPRESET_75KHZ	= 75000U,
	FPRESET_100KHZ	= 100000U

 *	@retval None
 *
 */

void FreqO_ApplyProfile(eFreqSettings_t pPresetEnum)
{
//	DacTimeReg_t* tmpDT = DT_GetRegisterByEnum(pPresetEnum);
	FreqProfile_t* tmpFreqProfile = FreqO_FindFPresetObject(pPresetEnum);
	if(tmpFreqProfile)
	{

		OUTPUT_TIMER->PSC = tmpFreqProfile->psc;
		OUTPUT_TIMER->ARR = tmpFreqProfile->arr;

		eOutput_mode tmpOut = SM_GetOutputChannel(AUX_CHANNEL)->func_profile->func;
		if(tmpOut == PWM_FUNC_MODE)
		{
			// duty cycle of PWM require slower settings to get the
			// same frequency as normal output functions
			PWM_AUX_OUT_TIM->PSC = 256;
			PWM_AUX_OUT_TIM->ARR = tmpFreqProfile->arr/2;
			PWM_AUX_OUT_TIM->CCR1 = PWM_AUX_OUT_TIM->ARR/2;
		}

		freq_profile = tmpFreqProfile;

	}
	else
	{
		DM_SetErrorDebugMsg("FreqO_ApplyProfile() null pointer error");
	}
}



/*
 *
 *	@brief	Increment/Decrement output frequency value by hertz
 *
 *	@param None
 *	@retval None
 *
 */
void FreqO_AdjustFreq()
{
	FreqO_MapEncoderPositionFine(SM_GetEncoderValue(ENCODER_NORMAL));


	eOutput_mode tmpOut = SM_GetOutputChannel(AUX_CHANNEL)->func_profile->func;
	if(tmpOut == PWM_FUNC_MODE)
	{
		// duty cycle of PWM require slower settings to get the
		// same frequency as normal output functions
		PWM_AUX_OUT_TIM->PSC = 256;
		PWM_AUX_OUT_TIM->ARR = SM_GetEncoderValue(ENCODER_NORMAL)/2;
		PWM_AUX_OUT_TIM->CCR1 = PWM_AUX_OUT_TIM->ARR/2;

	}
}

/*
 *
 *	@brief	Increment/Decrement output frequency value by hertz
 *
 *	@param None
 *	@retval None
 *
 */
void FreqO_AdjustPrescaler()
{
	FreqO_MapEncoderPositionToPrescaler(SM_GetEncoderValue(ENCODER_NORMAL));

	// not sure about this code?!?!
	eOutput_mode tmpOut = SM_GetOutputChannel(AUX_CHANNEL)->func_profile->func;
	if(tmpOut == PWM_FUNC_MODE)
	{
		// duty cycle of PWM require slower settings to get the
		// same frequency as normal output functions
		//PWM_AUX_OUT_TIM->PSC = 256;
		PWM_AUX_OUT_TIM->ARR = SM_GetEncoderValue(ENCODER_NORMAL)/2;
		PWM_AUX_OUT_TIM->CCR1 = PWM_AUX_OUT_TIM->ARR/2;

	}
}


/*
 *
 *	@brief Get currently set freq output preset
 *
 *	@param None
 *	@retval pointer to FreqProfile_t struct
 *
 */
FreqProfile_t * FreqO_GetFPresetObject()
{
	return freq_profile;
}


/*
 *
 *	@brief Search array of preset structs
 *
 *	@param Search criteria. Should be one of the following:
 *
 *	FPRESET_1HZ 	= 1U,
	FPRESET_10HZ	= 10U,
	FPRESET_50HZ	= 50U,
	FPRESET_100HZ	= 100U,
	FPRESET_250HZ	= 250U,
	FPRESET_500HZ	= 500U,
	FPRESET_750HZ	= 750U,
	FPRESET_1KHZ	= 1000U,
	FPRESET_5KHZ	= 5000U,
	FPRESET_10KHZ	= 10000U,
	FPRESET_25KHZ	= 25000U,
	FPRESET_50KHZ	= 50000U,
	FPRESET_75KHZ	= 75000U,
	FPRESET_100KHZ	= 100000U

 *	@retval pointer to FreqProfile_t struct
 *
 */
FreqProfile_t * FreqO_FindFPresetObject(eFreqSettings_t pEnum)
{
	for(int i = 0; i < MAX_NUM_FREQ_PRESETS; i++ )
	{
		if(theFreqProfiles[i].hertz == pEnum)
		{
			return &theFreqProfiles[i];
		}
	}
	// error!
	DM_SetErrorDebugMsg("FreqO_FindFPresetObject(): no FPreset obj found");
	return 0;
}

/*
 *
 *	@brief	Get freq profile
 *
 *	@param pIndex
 *	@retval eFreqSettings_t enum
 *
 */
eFreqSettings_t _FindFPresetObjectByIndex(uint32_t pIndex)
{
	for(int i = 0; i < pIndex; i++ )
	{
		return theFreqProfiles[i].hertz;

	}
	// error!
	DM_SetErrorDebugMsg("FreqO_FindFPresetObject(): no FPreset obj found");
	return 0;
}


/*
 *
 *	@brief	Get range value for rotary encoder
 *
 *	@param None
 *	@retval uint8_t
 *
 */
uint8_t FreqO_GetFreqPresetEncoderRange()
{
	return FreqPresetEncoderRange;
}

/*
 *
 *	@brief	Get frequency of output signal
 *
 *	@param None
 *	@retval uint32_t
 *
 */
uint32_t FreqO_GetOutputFreq()
{
	return OUTPUT_TIMER->ARR;
}


/*
 *
 *	@brief	Get freq profile
 *
 *	@param pIndex
 *	@retval pointer to FreqProfile_t object
 *
 */
FreqProfile_t* FreqO_GetProfileByIndex(uint32_t pIndex)
{
	return &theFreqProfiles[pIndex];
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FreqO_ResetLastEncoderValue()
{
	freq_last_encoder_value = 0;
}




#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_C_ */
