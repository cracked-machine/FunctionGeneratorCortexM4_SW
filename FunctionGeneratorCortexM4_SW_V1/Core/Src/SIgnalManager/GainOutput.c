/*
 * GainOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#include "GainOutput.h"
#include "DisplayManager.h"
#include "dac.h"


uint16_t gain_last_encoder_value = 0;

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void GO_ResetLastEncoderValue()
{
	gain_last_encoder_value = 0;
}

/*
 *	Array of objects for Gain Presets and their encoder positions for gain preset menu
 */
GainProfile_t theGainProfiles[MAX_NUM_GAIN_PRESETS] =
{
	{ ZERO_GAIN,	-1, 28 },
	{ ONE_GAIN,		0,  24 },
	{ TWO_GAIN,		6,  20 },
	{ THREE_GAIN,	9,  16 },
	{ FOUR_GAIN, 	12, 12 },
	{ FIVE_GAIN, 	14, 8  },
	{ SIX_GAIN,		16, 4  },
	{ SEVEN_GAIN, 	18, 0  }

};

uint8_t GainPresetEncoderRange = 28;




/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void GO_MapEncoderPositionToSignalOutput(uint16_t pEncoderValue)
{
	eGainSettings_t temp_gain = SM_GetOutputChannel(SIGNAL_CHANNEL)->gain_profile->gain;
	if(pEncoderValue > gain_last_encoder_value)
	{
		temp_gain++;
		if(temp_gain > MAX_NUM_GAIN_PRESETS-1) temp_gain = SEVEN_GAIN;
		GO_ApplyPresetToSignal(temp_gain);

	}
	else if (pEncoderValue < gain_last_encoder_value)
	{
		temp_gain--;
		if(temp_gain > MAX_NUM_GAIN_PRESETS-1) temp_gain = ZERO_GAIN;
		GO_ApplyPresetToSignal(temp_gain);
	}
	gain_last_encoder_value = pEncoderValue;

	// artifically offset PWM signal above DC
	//BO_SetPwmSignalOffsetForGain(temp_gain);

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void GO_ApplyPresetToSignal(eGainSettings_t pPresetEnum)
{




	SM_GetOutputChannel(SIGNAL_CHANNEL)->gain_profile = &theGainProfiles[pPresetEnum];

	switch(pPresetEnum)
	{
		case ZERO_GAIN:
			HAL_GPIO_WritePin(CH1_GAIN_A_GPIO_Port, CH1_GAIN_A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CH1_GAIN_B_GPIO_Port, CH1_GAIN_B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CH1_GAIN_C_GPIO_Port, CH1_GAIN_C_Pin, GPIO_PIN_RESET);
			break;

		case ONE_GAIN:
			HAL_GPIO_WritePin(CH1_GAIN_A_GPIO_Port, CH1_GAIN_A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CH1_GAIN_B_GPIO_Port, CH1_GAIN_B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CH1_GAIN_C_GPIO_Port, CH1_GAIN_C_Pin, GPIO_PIN_RESET);
			break;

		case TWO_GAIN:
			HAL_GPIO_WritePin(CH1_GAIN_A_GPIO_Port, CH1_GAIN_A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CH1_GAIN_B_GPIO_Port, CH1_GAIN_B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CH1_GAIN_C_GPIO_Port, CH1_GAIN_C_Pin, GPIO_PIN_RESET);
			break;

		case THREE_GAIN:
			HAL_GPIO_WritePin(CH1_GAIN_A_GPIO_Port, CH1_GAIN_A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CH1_GAIN_B_GPIO_Port, CH1_GAIN_B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CH1_GAIN_C_GPIO_Port, CH1_GAIN_C_Pin, GPIO_PIN_RESET);
			break;

		case FOUR_GAIN:
			HAL_GPIO_WritePin(CH1_GAIN_A_GPIO_Port, CH1_GAIN_A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CH1_GAIN_B_GPIO_Port, CH1_GAIN_B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CH1_GAIN_C_GPIO_Port, CH1_GAIN_C_Pin, GPIO_PIN_SET);
			break;

		case FIVE_GAIN:
			HAL_GPIO_WritePin(CH1_GAIN_A_GPIO_Port, CH1_GAIN_A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CH1_GAIN_B_GPIO_Port, CH1_GAIN_B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CH1_GAIN_C_GPIO_Port, CH1_GAIN_C_Pin, GPIO_PIN_SET);
			break;

		case SIX_GAIN:
			HAL_GPIO_WritePin(CH1_GAIN_A_GPIO_Port, CH1_GAIN_A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CH1_GAIN_B_GPIO_Port, CH1_GAIN_B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CH1_GAIN_C_GPIO_Port, CH1_GAIN_C_Pin, GPIO_PIN_SET);
			break;

		case SEVEN_GAIN:
			HAL_GPIO_WritePin(CH1_GAIN_A_GPIO_Port, CH1_GAIN_A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CH1_GAIN_B_GPIO_Port, CH1_GAIN_B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CH1_GAIN_C_GPIO_Port, CH1_GAIN_C_Pin, GPIO_PIN_SET);
			break;
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
GainProfile_t * GO_FindGPresetObject(eGainSettings_t pEnum)
{

	for(int i = 0; i < MAX_NUM_GAIN_PRESETS; i++ )
	{
		if(theGainProfiles[i].gain == pEnum)
		{
			return &theGainProfiles[i];
		}
	}
	// error!
	DM_SetErrorDebugMsg("GO_FindGPresetObject(): no GPreset obj found");
	return 0;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
uint8_t GO_GetGainPresetEncoderRange()
{
	return GainPresetEncoderRange;
}

