/*
 * FunctionOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */


#include "FunctionOutput.h"

#include "EventManager.h"
#include "DisplayManager.h"
#include "SignalManager.h"

#include "dac.h"
#include "tim.h"





// dummy lookup table for PWM_FUNC_MODE
uint32_t empty_table[10] = {};


/*
 *	Array of objects for Function Presets, their encoder positions for func preset menu and LUT data for the function
 */
FunctionProfile_t theFuncProfiles[MAX_NUM_FUNC_PRESETS] =
{
	{ SINE_FUNC_MODE,		 sine_data_table_3600 		},
	{ SQUARE_FUNC_MODE,		 square_data_table_3600 		},
	{ SAW_FUNC_MODE,		 saw_data_table_3600 		},
	{ REV_SAW_FUNC_MODE,	 saw_rev_data_table_3600 	},
	{ TRIANGLE_FUNC_MODE, 	 triangle_data_table_3600 	},
	{ IMPULSE_FUNC_MODE, 	 unitimpulse_data_table_3600 },
	{ PWM_FUNC_MODE,	 	 empty_table					}			// no lookup table used

};

uint8_t last_output_mode_was_pwm = 0;
uint16_t func_last_encoder_value = 0;

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FuncO_ResetLastEncoderValue()
{
	func_last_encoder_value = 0;
}


/*
 *
 *	@brief	multiplex encoder input -> preset function
 *
 *	@param pEncoderValue rotary encoder value
 *	@retval None
 *
 */
void FuncO_MapEncoderPositionToSignalOutput(uint16_t pEncoderValue)
{
	eOutput_mode tmpFunc = SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile->func;
	if(pEncoderValue > func_last_encoder_value)
	{
		tmpFunc++;
		if(tmpFunc > MAX_NUM_FUNC_PRESETS-2) tmpFunc = IMPULSE_FUNC_MODE;
		FuncO_ApplyProfileToSignal(tmpFunc);
	}
	else if (pEncoderValue < func_last_encoder_value)
	{
		tmpFunc--;
		if(tmpFunc > MAX_NUM_FUNC_PRESETS-1) tmpFunc = SINE_FUNC_MODE;
		FuncO_ApplyProfileToSignal(tmpFunc);
	}
	func_last_encoder_value = pEncoderValue;
}

/*
 *
 *	@brief multiplex encoder input -> preset function
 *
 *	@param pEncoderValue rotary encoder value
 *	@retval None
 *
 */
void FuncO_MapEncoderPositionToAuxOutput(uint16_t pEncoderValue)
{
	eOutput_mode tmpFunc = SM_GetOutputChannel(AUX_CHANNEL)->func_profile->func;
	if(pEncoderValue > func_last_encoder_value)
	{
		tmpFunc++;
		if(tmpFunc > MAX_NUM_FUNC_PRESETS-1) tmpFunc = PWM_FUNC_MODE;
		FuncO_ApplyProfileToAux(tmpFunc);
	}
	else if (pEncoderValue < func_last_encoder_value)
	{
		tmpFunc--;
		if(tmpFunc > MAX_NUM_FUNC_PRESETS-1) tmpFunc = SINE_FUNC_MODE;
		FuncO_ApplyProfileToAux(tmpFunc);
//		if(tmpFunc == SINE_FUNC_MODE)
//			ENCODER_TIMER->CNT = 20;
	}
	func_last_encoder_value = pEncoderValue;
}


/*
 *
 *	@brief	Modify the function and gain of the main Signal output (DAC1/CH1)
 *
 *	@param pPresetEnum the enum literal for the preset. Should be one of the following:
 *
 *	SINE_FUNC_MODE,
	SQUARE_FUNC_MODE,
	SAW_FUNC_MODE,
	REV_SAW_FUNC_MODE,
	TRIANGLE_FUNC_MODE,
	IMPULSE_FUNC_MODE

 *	@retval None
 *
 */
void FuncO_ApplyProfileToSignal(eOutput_mode pPresetEnum)
{

		// set the next function output
		SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile = &theFuncProfiles[pPresetEnum];


		// copy the lookup table for the next output function in to SignalChannel object
		printf("SM_GetOutputChannel\n");
		SM_GetOutputChannel(SIGNAL_CHANNEL)->ref_lut_data = theFuncProfiles[pPresetEnum].lookup_table_data;

		// set preset for PGA gain and dsp amplitude adjustment
		eAmpSettings_t eTmpVppPreset = SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile->amp_setting;
		VPP_ApplyProfileToSignal(eTmpVppPreset);

		// pause timer to reAux both outputs
		OUTPUT_TIMER->CR1 &= ~(TIM_CR1_CEN);
		//HAL_TIM_Base_Stop(&htim8);

		// restart the DAC with the new data
		HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
		HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)SM_GetOutputChannel(SIGNAL_CHANNEL)->dsp_lut_data, SINE_DATA_SIZE, DAC_ALIGN_12B_R);

		// restart the the other DAC
		HAL_DAC_Stop_DMA(&hdac2, DAC1_CHANNEL_1);
		HAL_DAC_Start_DMA(&hdac2, DAC1_CHANNEL_1, (uint32_t*)SM_GetOutputChannel(AUX_CHANNEL)->dsp_lut_data, SINE_DATA_SIZE, DAC_ALIGN_12B_R);

		// resume timer to reAux both outputs
		//HAL_TIM_Base_Start(&htim8);
		OUTPUT_TIMER->CR1 |= (TIM_CR1_CEN);



}

/*
 *
 *	@brief	Modify the function and gain of the aux Aux output (DAC2/CH1)
 *
 *	@param pPresetEnum the enum literal for the preset. Should be one of the following:
 *
 *	SINE_FUNC_MODE,
	SQUARE_FUNC_MODE,
	SAW_FUNC_MODE,
	REV_SAW_FUNC_MODE,
	TRIANGLE_FUNC_MODE,
	IMPULSE_FUNC_MODE

 *	@retval None
 *
 */
void FuncO_ApplyProfileToAux(eOutput_mode pPresetEnum)
{
	HAL_StatusTypeDef res;

	// set the next output function
	SM_GetOutputChannel(AUX_CHANNEL)->func_profile = &theFuncProfiles[pPresetEnum];


	if(pPresetEnum == PWM_FUNC_MODE)
	{
		printf("FuncO_ApplyProfileToAux PWM_FUNC_MODE\n");
		// switch output signal from DAC to PWM

		SM_DisableDacToAux();
		SM_EnablePwmToAux();

		last_output_mode_was_pwm = 1;

	}
	else if(last_output_mode_was_pwm)
	{
		printf("FuncO_ApplyProfileToAux NOT PWM_FUNC_MODE\n");
		// switch output signal from PWM to DAC
		SM_DisablePwmToAux();
		SM_EnableDacToAux();

		// copy the lookup table for the next output function in to AuxChannel object
		printf("FuncO_ApplyProfileToAux SM_GetOutputChannel\n");
		SM_GetOutputChannel(AUX_CHANNEL)->ref_lut_data = theFuncProfiles[pPresetEnum].lookup_table_data;

		// set preset PGA gain and dsp amplitude adjustment
		printf("FuncO_ApplyProfileToAux SM_GetOutputChannel\n");
		eAmpSettings_t eTmpVppPreset = SM_GetOutputChannel(AUX_CHANNEL)->amp_profile->amp_setting;
		printf("VPP_ApplyProfileToAux");
		VPP_ApplyProfileToAux(eTmpVppPreset);

		// pause timer to reAux both outputs
		printf("FuncO_ApplyProfileToAux HAL_TIM_Base_Stop(&htim2)\n");
		res = HAL_TIM_Base_Stop(&htim2);
		//OUTPUT_TIMER->CR1 &= ~(TIM_CR1_CEN);
		printf("Result:%u\n",res);


		// CAN CAUSE HARDFAULT! Add delays if hard faults occur
		// restart the DAC with the new data
		printf("FuncO_ApplyProfileToAux HAL_DAC_Stop_DMA(&hdac2, DAC1_CHANNEL_1)\n");
		res = HAL_DAC_Stop_DMA(&hdac2, DAC1_CHANNEL_1);
		printf("Result:%u\n",res);

		printf("FuncO_ApplyProfileToAux HAL_DAC_Start_DMA(&hdac2, DAC1_CHANNEL_1)\n");
		res = HAL_DAC_Start_DMA(&hdac2, DAC1_CHANNEL_1, (uint32_t*)SM_GetOutputChannel(AUX_CHANNEL)->dsp_lut_data, SINE_DATA_SIZE, DAC_ALIGN_12B_R);
		printf("Result:%u\n",res);


		// restart the the other DAC
		printf("FuncO_ApplyProfileToAux HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1)\n");
		res = HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
		printf("Result:%u\n",res);

		printf("FuncO_ApplyProfileToAux HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1)\n");
		res = HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)SM_GetOutputChannel(SIGNAL_CHANNEL)->dsp_lut_data, SINE_DATA_SIZE, DAC_ALIGN_12B_R);
		printf("Result:%u\n",res);

		// resume timer to reAux both outputs
		printf("FuncO_ApplyProfileToAux HAL_TIM_Base_Start(&htim2)\n");
		res = HAL_TIM_Base_Start(&htim2);
		//OUTPUT_TIMER->CR1 |= (TIM_CR1_CEN);
		printf("Result:%u\n",res);


		last_output_mode_was_pwm = 0;
	}
	else
	{

		// copy the lookup table for the next output function in to AuxChannel object
		printf("FuncO_ApplyProfileToAux SM_GetOutputChannel\n");
		SM_GetOutputChannel(AUX_CHANNEL)->ref_lut_data = theFuncProfiles[pPresetEnum].lookup_table_data;

		// set preset PGA gain and dsp amplitude adjustment
		printf("FuncO_ApplyProfileToAux SM_GetOutputChannel\n");
		eAmpSettings_t eTmpVppPreset = SM_GetOutputChannel(AUX_CHANNEL)->amp_profile->amp_setting;
		printf("VPP_ApplyProfileToAux");
		VPP_ApplyProfileToAux(eTmpVppPreset);

		// pause timer to reAux both outputs
		printf("FuncO_ApplyProfileToAux HAL_TIM_Base_Stop(&htim2)\n");
		res = HAL_TIM_Base_Stop(&htim2);
		printf("Result:%u\n",res);
		//OUTPUT_TIMER->CR1 &= ~(TIM_CR1_CEN);

		// CAN CAUSE HARDFAULT! Add delays if hard faults occur
		// restart the DAC with the new data
		printf("FuncO_ApplyProfileToAux HAL_DAC_Stop_DMA(&hdac2, DAC1_CHANNEL_1)\n");
		res = HAL_DAC_Stop_DMA(&hdac2, DAC1_CHANNEL_1);
		printf("Result:%u\n",res);

		printf("FuncO_ApplyProfileToAux HAL_DAC_Start_DMA(&hdac2, DAC1_CHANNEL_1)\n");
		res = HAL_DAC_Start_DMA(&hdac2, DAC1_CHANNEL_1, (uint32_t*)SM_GetOutputChannel(AUX_CHANNEL)->dsp_lut_data, SINE_DATA_SIZE, DAC_ALIGN_12B_R);
		printf("Result:%u\n",res);


		// restart the the other DAC
		printf("FuncO_ApplyProfileToAux HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1)\n");
		res = HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
		printf("Result:%u\n",res);

		printf("FuncO_ApplyProfileToAux HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1)\n");
		res = HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)SM_GetOutputChannel(SIGNAL_CHANNEL)->dsp_lut_data, SINE_DATA_SIZE, DAC_ALIGN_12B_R);
		printf("Result:%u\n",res);

		// resume timer to reAux both outputs
		printf("FuncO_ApplyProfileToAux HAL_TIM_Base_Start(&htim2)\n");
		res = HAL_TIM_Base_Start(&htim2);
		printf("Result:%u\n",res);
		//OUTPUT_TIMER->CR1 |= (TIM_CR1_CEN);
	}

}


/*
 *
 *	@brief Search array of structs for preset
 *
 *	@param Search criteria. Should be one of the following:
 *
 *	SINE_FUNC_MODE,
	SQUARE_FUNC_MODE,
	SAW_FUNC_MODE,
	REV_SAW_FUNC_MODE,
	TRIANGLE_FUNC_MODE,
	IMPULSE_FUNC_MODE

 *	@retval pointer to FunctionProfile_t struct
 *
 */
FunctionProfile_t * FuncO_FindFPresetObject(eOutput_mode pEnum)
{
	for(int i = 0; i < MAX_NUM_FUNC_PRESETS; i++ )
	{
		if(theFuncProfiles[i].func == pEnum)
		{
			return &theFuncProfiles[i];
		}
	}
	// error!
	DM_SetErrorDebugMsg("FuncO_FindFPresetObject(): no FPreset obj found");
	return 0;
}





