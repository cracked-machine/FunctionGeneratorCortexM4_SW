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
 *	Array of objects for Function Presets, their encoder positions for func preset menu and LUT data for the function
 */
Func_Preset_Encoder_Pos_t aFuncPresetEncoderPos[MAX_NUM_FUNC_PRESETS] =
{
	{ SINE_FUNC_MODE,		20, sine_data_table_3600 		},
	{ SQUARE_FUNC_MODE,		16, square_data_table_3600 		},
	{ SAW_FUNC_MODE,		12, saw_data_table_3600 		},
	{ REV_SAW_FUNC_MODE,	8, 	saw_rev_data_table_3600 	},
	{ TRIANGLE_FUNC_MODE, 	4, 	triangle_data_table_3600 	},
	{ IMPULSE_FUNC_MODE, 	0, 	unitimpulse_data_table_3600 }

};


// pointer to eDefaultFuncPreset used by Signal output
Func_Preset_Encoder_Pos_t *pSignalFuncPresetEncoderPos = &aFuncPresetEncoderPos[eDefaultFuncPreset];

// pointer to eDefaultFuncPreset used by Signal output
Func_Preset_Encoder_Pos_t *pSyncFuncPresetEncoderPos = &aFuncPresetEncoderPos[eDefaultFuncPreset];


uint8_t FuncPresetEncoderRange = 20;

/*
 *
 *	@brief	multiplex encoder input -> preset function
 *
 *	@param pEncoderValue rotary encoder value
 *	@retval None
 *
 */
void FuncO_ModifySignalOutput(uint16_t pEncoderValue)
{


	switch(pEncoderValue)
	{
		case 0: case 1: case 2:
			FuncO_ApplyPresetToSignal(SINE_FUNC_MODE);
			break;

		case 3: case 4: case 5: case 6:
			FuncO_ApplyPresetToSignal(SQUARE_FUNC_MODE);
			break;

		case 7: case 8: case 9: case 10:
			FuncO_ApplyPresetToSignal(SAW_FUNC_MODE);
			break;

		case 11: case 12: case 13: case 14:
			FuncO_ApplyPresetToSignal(REV_SAW_FUNC_MODE);
			break;

		case 15: case 16: case 17: case 18:
			FuncO_ApplyPresetToSignal(TRIANGLE_FUNC_MODE);
			break;

		case 19: case 20: case 21: case 22: case 23:
			FuncO_ApplyPresetToSignal(IMPULSE_FUNC_MODE);
			break;

	}
}

/*
 *
 *	@brief multiplex encoder input -> preset function
 *
 *	@param pEncoderValue rotary encoder value
 *	@retval None
 *
 */
void FuncO_ModifySyncOutput(uint16_t pEncoderValue)
{


	switch(pEncoderValue)
	{
		case 0: case 1: case 2:
			FuncO_ApplyPresetToSync(SINE_FUNC_MODE);
			break;

		case 3: case 4: case 5: case 6:
			FuncO_ApplyPresetToSync(SQUARE_FUNC_MODE);
			break;

		case 7: case 8: case 9: case 10:
			FuncO_ApplyPresetToSync(SAW_FUNC_MODE);
			break;

		case 11: case 12: case 13: case 14:
			FuncO_ApplyPresetToSync(REV_SAW_FUNC_MODE);
			break;

		case 15: case 16: case 17: case 18:
			FuncO_ApplyPresetToSync(TRIANGLE_FUNC_MODE);
			break;

		case 19: case 20: case 21: case 22: case 23:
			FuncO_ApplyPresetToSync(IMPULSE_FUNC_MODE);
			break;

	}
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
void FuncO_ApplyPresetToSignal(eOutput_mode pPresetEnum)
{
	// get pointer to the LUT data.  This will be the restore point for the dsp
	pOriginalSignalDataTable = aFuncPresetEncoderPos[pPresetEnum].lookup_table_data;

	// set PGA gain preset and dsp amplitude adjustment
	VPP_ApplyPresetToSignal(VPP_GetVppPresetObject(SIGNAL_OUTPUT_PRESET)->Vpp_literal);

	// set the requested function output
	pSignalFuncPresetEncoderPos = &aFuncPresetEncoderPos[pPresetEnum];

	// restart the DAC with the new data
	HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
	HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)aProcessedSignalDataTable, SINE_DATA_SIZE, DAC_ALIGN_12B_R);

}

/*
 *
 *	@brief	Modify the function and gain of the aux Sync output (DAC2/CH1)
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
void FuncO_ApplyPresetToSync(eOutput_mode pPresetEnum)
{
	// get pointer to the LUT data.  This will be the restore point for the dsp
	pOriginalSyncDataTable = aFuncPresetEncoderPos[pPresetEnum].lookup_table_data;

	// set PGA gain preset and dsp amplitude adjustment
	VPP_ApplyPresetToSync(VPP_GetVppPresetObject(SYNC_OUTPUT_PRESET)->Vpp_literal);

	// set the requested function output
	pSyncFuncPresetEncoderPos = &aFuncPresetEncoderPos[pPresetEnum];

	// restart the DAC with the new data
	HAL_DAC_Stop_DMA(&hdac2, DAC1_CHANNEL_1);
	HAL_DAC_Start_DMA(&hdac2, DAC1_CHANNEL_1, (uint32_t*)aProcessedSyncDataTable, SINE_DATA_SIZE, DAC_ALIGN_12B_R);

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



