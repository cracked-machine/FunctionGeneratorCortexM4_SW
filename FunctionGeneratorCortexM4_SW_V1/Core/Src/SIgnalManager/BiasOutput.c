/*
 * BiasOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#include "BiasOutput.h"

#include "gpio.h"
#include "dac.h"

#include "SignalManager.h"


/*
 *
 *
 *
 */
void BO_ModifyOutput()
{
	// apply negative dc bias
	if(SM_GetEncoderValue(ENCODER_REVERSE) < 400) {

		HAL_DAC_SetValue(	&hdac1,
							DAC1_CHANNEL_2,
							DAC_ALIGN_12B_R,
							(BIAS_CENTER - SM_GetEncoderValue(ENCODER_REVERSE)) * BIAS_MAG);

		HAL_GPIO_WritePin(	DCBIAS_INVERT_GPIO_Port,
							DCBIAS_INVERT_Pin,
							GPIO_PIN_SET);
	}
	// apply positive dc bias
	if(SM_GetEncoderValue(ENCODER_REVERSE) >= 400) {

		HAL_DAC_SetValue(	&hdac1,
							DAC1_CHANNEL_2,
							DAC_ALIGN_12B_R,
							(SM_GetEncoderValue(ENCODER_REVERSE) - BIAS_CENTER) * BIAS_MAG);

		HAL_GPIO_WritePin(	DCBIAS_INVERT_GPIO_Port,
							DCBIAS_INVERT_Pin,
							GPIO_PIN_RESET);
	}
}

/*
 *
 *
 *
 */
uint32_t BO_GetOutputBias()
{
	return HAL_DAC_GetValue(&hdac1, DAC1_CHANNEL_2);
}




