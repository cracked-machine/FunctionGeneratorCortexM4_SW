/*
 * FunctionOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */


#include "FunctionOutput.h"
#include "EventManager.h"

#include "dac.h"
#include "tim.h"

#include "pysine.h"
#include "pysquare.h"
#include "pyunitimpulse.h"
#include "pysaw.h"
#include "pysaw_rev.h"
#include "pytriangle.h"

#include "SignalManager.h"

eOutput_mode FO_GetOutputMode();
//void FuncO_SetOutputMode(eOutput_mode pNewMode);

// signal output function
eOutput_mode eNewOutMode = Sine_Out_Mode;

void FuncO_ModifyOutput()
{


	switch(SM_GetEncoderValue(ENCODER_REVERSE))
	{
		case 0:
		case 1:
		case 2:

			eNewOutMode = Sine_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, sine_data_table, SINE_DATA_SIZE, DAC_ALIGN_12B_R);
			break;
		case 3:
		case 4:
		case 5:
		case 6:

			eNewOutMode = Square_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, square_data_table, SQUARE_DATA_SIZE, DAC_ALIGN_12B_R);

			break;
		case 7:
		case 8:
		case 9:
		case 10:

			eNewOutMode = Saw_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, saw_data_table, SAW_DATA_SIZE, DAC_ALIGN_12B_R);
			break;
		case 11:
		case 12:
		case 13:
		case 14:

			eNewOutMode = RevSaw_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, saw_rev_data_table, SAW_REV_DATA_SIZE, DAC_ALIGN_12B_R);
			break;
		case 15:
		case 16:
		case 17:
		case 18:

			eNewOutMode = Triangle_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, triangle_data_table, TRIANGLE_DATA_SIZE, DAC_ALIGN_12B_R);
			break;
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:

			eNewOutMode = Impulse_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, unitimpulse_data_table, UNITIMPULSE_DATA_SIZE, DAC_ALIGN_12B_R);
			break;
	}
}

/*
 *
 *
 *
 */
void FuncO_SetOutputMode(eOutput_mode pNewMode)
{
	eNewOutMode = pNewMode;
}


/*
 *
 *
 *
 */
eOutput_mode FuncO_GetOutputMode()
{
	return eNewOutMode;
}

