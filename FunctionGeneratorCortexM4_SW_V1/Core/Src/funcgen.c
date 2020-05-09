/*
 * funcgen.c
 *
 *  Created on: Mar 13, 2020
 *      Author: chris
 */

#include "funcgen.h"
#include "gpio.h"
#include "dac.h"


uint16_t dcbias = 0;
int dcbias_dir = 1;
int dcinverted = 0;

void update_dc_bias_sweep()
{
	  // sweep up=1, sweep down=0
	  //(dcbias_dir) ? (dcbias++) : (dcbias--);

	  // invert the bias signal at zero crossing
	  if(TIM1->CNT < 512) {
		  HAL_GPIO_WritePin(DCBIAS_INVERT_GPIO_Port, DCBIAS_INVERT_Pin, GPIO_PIN_SET);
	  }
	  if(TIM1->CNT > 512) {
	  	  HAL_GPIO_WritePin(DCBIAS_INVERT_GPIO_Port, DCBIAS_INVERT_Pin, GPIO_PIN_RESET);
	  }

	  // change sweep direction if dac limits are reached
	  //if(dcbias < 1) 	{ dcbias_dir = 1; }
	  //if(dcbias > 4095) { dcbias_dir = 0; }



	  //HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_2, DAC_ALIGN_12B_R, dcbias);
}


