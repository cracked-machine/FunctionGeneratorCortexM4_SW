/*
 * FunctionOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */


#include "FunctionOutput.h"
#include "EventManager.h"
#include "DisplayManager.h"

#include "dac.h"
#include "tim.h"


#include "DacChannel.h"

#include "SignalManager.h"

uint32_t *pOriginalSignalDataTable = sine_data_table_3600;


void FuncO_Init()
{
	for(int i = 0; i < SINE_DATA_SIZE; i++)
		aProcessedSignalDataTable[i] = sine_data_table_3600[i];

	for(int i = 0; i < SINE_DATA_SIZE; i++)
		aProcessedSyncDataTable[i] = sine_data_table_3600[i];
}


/*
 *	Array of objects for Function Presets and their encoder positions for func preset menu
 */
Func_Preset_Encoder_Pos_t aFuncPresetEncoderPos[MAX_NUM_FUNC_PRESETS] =
{
	{ SINE_FUNC_MODE,		20 },
	{ SQUARE_FUNC_MODE,		16 },
	{ SAW_FUNC_MODE,		12 },
	{ REV_SAW_FUNC_MODE,	8 },
	{ TRIANGLE_FUNC_MODE, 	4 },
	{ IMPULSE_FUNC_MODE, 	0 }

};


// pointer to eDefaultFuncPreset used by Signal output
Func_Preset_Encoder_Pos_t *pSignalFuncPresetEncoderPos = &aFuncPresetEncoderPos[eDefaultFuncPreset];

// pointer to eDefaultFuncPreset used by Signal output
Func_Preset_Encoder_Pos_t *pSyncFuncPresetEncoderPos = &aFuncPresetEncoderPos[eDefaultFuncPreset];


uint8_t FuncPresetEncoderRange = 20;

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FuncO_ModifySignalOutput(uint16_t pEncoderValue)
{


	switch(pEncoderValue)
	{
		case 0:
		case 1:
		case 2:

			FuncO_ApplyPresetToSignal(SINE_FUNC_MODE);
			break;
		case 3:
		case 4:
		case 5:
		case 6:

			FuncO_ApplyPresetToSignal(SQUARE_FUNC_MODE);

			break;
		case 7:
		case 8:
		case 9:
		case 10:

			FuncO_ApplyPresetToSignal(SAW_FUNC_MODE);
			break;
		case 11:
		case 12:
		case 13:
		case 14:

			FuncO_ApplyPresetToSignal(REV_SAW_FUNC_MODE);
			break;
		case 15:
		case 16:
		case 17:
		case 18:

			FuncO_ApplyPresetToSignal(TRIANGLE_FUNC_MODE);
			break;
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:

			FuncO_ApplyPresetToSignal(IMPULSE_FUNC_MODE);
			break;
	}
}



/*
 *
 *	@brief	Set function output preset by index
 *
 *	@param pPresetEnum the enum literal for the preset. Should be one of the following:
 *
 *

 *	@retval None
 *
 */
void FuncO_ApplyPresetToSignal(eOutput_mode pPresetEnum)
{

	switch(pPresetEnum)
	{
		case SINE_FUNC_MODE:

			pOriginalSignalDataTable = sine_data_table_3600;
			//pOriginalSignalDataTable = sine_data_table_1300;

			VPP_ApplyPresetToSignal(VPP_GetVppPresetObject(SIGNAL_OUTPUT_PRESET)->Vpp_literal);

			pSignalFuncPresetEncoderPos = &aFuncPresetEncoderPos[0];

			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)aProcessedSignalDataTable, SINE_DATA_SIZE, DAC_ALIGN_12B_R);
			break;

		case SQUARE_FUNC_MODE:

			pOriginalSignalDataTable = square_data_table_3600;

			VPP_ApplyPresetToSignal(VPP_GetVppPresetObject(SIGNAL_OUTPUT_PRESET)->Vpp_literal);

			pSignalFuncPresetEncoderPos = &aFuncPresetEncoderPos[1];
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)aProcessedSignalDataTable, SQUARE_DATA_SIZE, DAC_ALIGN_12B_R);
			break;

		case SAW_FUNC_MODE:

			pOriginalSignalDataTable = saw_data_table_3600;

			VPP_ApplyPresetToSignal(VPP_GetVppPresetObject(SIGNAL_OUTPUT_PRESET)->Vpp_literal);

			pSignalFuncPresetEncoderPos = &aFuncPresetEncoderPos[2];
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)aProcessedSignalDataTable, SAW_DATA_SIZE, DAC_ALIGN_12B_R);
			break;

		case REV_SAW_FUNC_MODE:

			pOriginalSignalDataTable = saw_rev_data_table_3600;

			VPP_ApplyPresetToSignal(VPP_GetVppPresetObject(SIGNAL_OUTPUT_PRESET)->Vpp_literal);

			pSignalFuncPresetEncoderPos = &aFuncPresetEncoderPos[3];
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)aProcessedSignalDataTable, SAW_REV_DATA_SIZE, DAC_ALIGN_12B_R);
			break;

		case TRIANGLE_FUNC_MODE:

			pOriginalSignalDataTable = triangle_data_table_3600;

			VPP_ApplyPresetToSignal(VPP_GetVppPresetObject(SIGNAL_OUTPUT_PRESET)->Vpp_literal);

			pSignalFuncPresetEncoderPos = &aFuncPresetEncoderPos[4];
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)aProcessedSignalDataTable, TRIANGLE_DATA_SIZE, DAC_ALIGN_12B_R);
			break;

		case IMPULSE_FUNC_MODE:

			pOriginalSignalDataTable = unitimpulse_data_table_3600;

			VPP_ApplyPresetToSignal(VPP_GetVppPresetObject(SIGNAL_OUTPUT_PRESET)->Vpp_literal);

			pSignalFuncPresetEncoderPos = &aFuncPresetEncoderPos[5];
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)aProcessedSignalDataTable, UNITIMPULSE_DATA_SIZE,  DAC_ALIGN_12B_R);
			break;

	//
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

 *	@retval pointer to Func_Preset_Encoder_Pos_t struct
 *
 */
Func_Preset_Encoder_Pos_t * FuncO_FindFPresetObject(eOutput_mode pEnum)
{
	for(int i = 0; i < MAX_NUM_FUNC_PRESETS; i++ )
	{
		if(aFuncPresetEncoderPos[i].func == pEnum)
		{
			return &aFuncPresetEncoderPos[i];
		}
	}
	// error!
	DM_SetErrorDebugMsg("FuncO_FindFPresetObject(): no FPreset obj found");
	return 0;
}


/*
 *
 *	@brief Get currently set function output preset
 *
 *	@param None
 *	@retval pointer to Func_Preset_Encoder_Pos_t struct
 *
 */
Func_Preset_Encoder_Pos_t * FuncO_GetSignalFPresetObject()
{
	return pSignalFuncPresetEncoderPos;
}

/*
 *
 *	@brief Get currently set function output preset
 *
 *	@param None
 *	@retval pointer to Func_Preset_Encoder_Pos_t struct
 *
 */
Func_Preset_Encoder_Pos_t * FuncO_GetSyncFPresetObject()
{
	return pSyncFuncPresetEncoderPos;
}


/*
 *
 *	@brief	Get range value for rotary encoder
 *
 *	@param None
 *	@retval uint8_t
 *
 */
uint8_t FuncO_GetFuncPresetEncoderRange()
{
	return FuncPresetEncoderRange;
}



