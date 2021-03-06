/*
 * FreqSweep.c
 *
 *  Created on: May 23, 2020
 *      Author: chris
 */


#include "FreqSweep.h"

#include <math.h>

#include "SignalManager.h"


// these store shortest/longest ARR values that the sweep function will set to the OUTPUT_TIMER->ARR.
float sweep_lower_bounds_shortest_output_arr = MIN_OUTPUT_ARR;		// higher freq
float sweep_upper_bounds_longest_output_arr = MAX_OUTPUT_ARR;		// lower freq

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FS_SetSweepModeDown()
{
	// "Center-aligned" mode sets direction register to readonly,
	// so disable "Center-aligned" mode first
	SWEEP_TIMER->CR1 &= ~((TIM_CR1_CMS_0) | (TIM_CR1_CMS_1));

	// 0: Counter used as upcounter
	SWEEP_TIMER->CR1 |= (TIM_CR1_DIR);

	sweep_lower_bounds_shortest_output_arr  = OUTPUT_TIMER->ARR;
	sweep_upper_bounds_longest_output_arr  = MAX_OUTPUT_ARR;
	ENCODER_TIMER->CNT = MAX_OUTPUT_ARR;

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FS_SetSweepModeUp()
{

	// "Center-aligned" mode sets direction register to readonly,
	// so disable "Center-aligned" mode first
	SWEEP_TIMER->CR1 &= ~((TIM_CR1_CMS_0) | (TIM_CR1_CMS_1));

	// 1: Counter used as downcounter
	SWEEP_TIMER->CR1 &= ~(TIM_CR1_DIR);

	sweep_upper_bounds_longest_output_arr  = OUTPUT_TIMER->ARR;
	sweep_lower_bounds_shortest_output_arr  = MIN_OUTPUT_ARR;


}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FS_SetEncoderControlMode(eEncoderSweepFunctions pFunction)
{
	if(pFunction)
	{
		//	ENCODER_SWEEP_LIMIT_FUNCTION
		theCurrentEncoderSweepFunction = pFunction;
		ENCODER_TIMER->CNT = MIN_OUTPUT_ARR;
		ENCODER_TIMER->ARR = MAX_OUTPUT_ARR;

		switch(active_sweep_mode)
		{

			case SWEEP_MODE_UP:


				// if encoder position is above the lower bounds set it below it
					if(ENCODER_TIMER->CNT > sweep_upper_bounds_longest_output_arr)
						 ENCODER_TIMER->CNT = OUTPUT_TIMER->ARR;


				break;

			case SWEEP_MODE_DOWN:
					// if encoder position is below the lower bounds set it above it
					if(ENCODER_TIMER->CNT < sweep_lower_bounds_shortest_output_arr)
						ENCODER_TIMER->CNT = OUTPUT_TIMER->ARR;
				break;
			default:
				break;
		}
		// switch(active_sweep_mode)
	}
	else
	{
		// ENCODER_SWEEP_SPEED_FUNCTION
		theCurrentEncoderSweepFunction = pFunction;
		// encoder start value
		ENCODER_TIMER->CNT = 1;
		// encoder limit for default (set speed)
		ENCODER_TIMER->ARR = 1600;
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
void FS_SetSweepTimerAutoReloadForEncoderControl(eEncoderSweepFunctions pFunction)
{
	uint32_t next_sweep_tim_arr;

	if(pFunction)
	{

	}
	else
	{
		// get logarithmic curve to speed up turns at low end
		next_sweep_tim_arr = MIN_SWEEP_ARR + (pow(ENCODER_TIMER->CNT, 3));

		if(next_sweep_tim_arr < 0xFFFFFFFF)
		{
			SWEEP_TIMER->ARR = next_sweep_tim_arr;

		}
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
float FS_GetCalculatedSweepFrequencyInHertz()
{
	if(SWEEP_TIMER->PSC == 0)
	{
		return (float)SM_MCLK / ((float)1 * (float)SWEEP_TIMER->ARR);
	}
	else
	{
		return (float)SM_MCLK / ((float)SWEEP_TIMER->PSC * (float)SWEEP_TIMER->ARR);
	}

}
