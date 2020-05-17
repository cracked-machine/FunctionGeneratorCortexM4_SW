/*
 * FreqMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#include "FreqMenuStateHandler.h"

#include "DisplayManager.h"
//#include "SignalManager.h"
#include <stdio.h>


float sweep_lower_arr_bounds = MIN_OUTPUT_ARR;		// higher freq
float sweep_upper_arr_bounds = MAX_OUTPUT_ARR;		// lower freq

eFreqMenu_Status eNextFreqMenuStatus = 	DISABLE_FREQ_MENU;
eFreqSweepModes active_sweep_mode = SWEEP_MODE_UP;
eEncoderSweepFunctions theCurrentEncoderSweepFunction = ENCODER_SWEEP_SPEED_FUNCTION;


#define RATE_COEF	32	// how much the encoder increments/decrements per pulse
#define RATE_DELTA	1.1	// how much we increment/decrement by

/*
 * 	Function prototypes
 */
void _setSweepModeUp();
void _setSweepModeDown();

eFreqMenu_Status FreqMenu_getStatus()
{
	return eNextFreqMenuStatus;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqMainMenuEntryHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqMainMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextFreqMenuStatus = ENABLE_FREQ_MAIN_MENU;

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Main_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqMainMenuInputHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqMainMenuInputHandler Event captured\n");
	#endif


	return Freq_Main_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqMainMenuExitHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqMainMenuExitHandler Event captured\n");
	#endif


	// disable the menu
	eNextFreqMenuStatus = DISABLE_FREQ_MENU;

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

	#ifdef SWV_DEBUG_ENABLED
		  printf("returning to Idle State\n");
	#endif

	eNewEvent = evIdle;
	return Toplevel_Output_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqPresetMenuEntryHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqPresetMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextFreqMenuStatus = ENABLE_FREQ_PRESET_MENU;

	FreqProfile_t *pFreqPresetTmp =  FreqO_GetFPresetObject();
	if(pFreqPresetTmp)
	{
		ENCODER_TIMER->CNT = pFreqPresetTmp->epos;
		ENCODER_TIMER->ARR = FreqO_GetFreqPresetEncoderRange();
	}
	else
	{
		DM_SetErrorDebugMsg("_FreqPresetMenuEntryHandler: pFreqPresetTmp null pointer");
	}


	// stay in this state
	eNewEvent = evIdle;
	return Freq_Preset_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqPresetMenuInputHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqPresetMenuInputHandler Event captured\n");
	#endif

	FreqO_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Preset_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqPresetMenuExitHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqPresetMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	// disable the menu
	eNextFreqMenuStatus = ENABLE_FREQ_MAIN_MENU;

	// back to main freq menu
	eNewEvent = evIdle;
	return Freq_Main_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqAdjustMenuEntryHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqAdjustMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextFreqMenuStatus = ENABLE_FREQ_ADJUST_MENU;

	// set the rotary encoder limits to 0-? for this menu
	ENCODER_TIMER->CNT = OUTPUT_TIMER->ARR;
	ENCODER_TIMER->ARR = 65535;

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Adjust_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqAdjustMenuInputHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqAdjustMenuInputHandler Event captured\n");
	#endif

	FreqO_AdjustFreq();

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Adjust_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqAdjustMenuExitHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqAdjustMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	// disable the menu
	eNextFreqMenuStatus = ENABLE_FREQ_MAIN_MENU;

	// back to main freq menu
	eNewEvent = evIdle;
	return Freq_Main_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqSweepMenuEntryHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqSweepMenuEntryHandler captured\n");
	#endif

	DM_RefreshScreen();

	if( sweep_upper_arr_bounds != OUTPUT_TIMER->ARR)
		sweep_upper_arr_bounds  = OUTPUT_TIMER->ARR;

	if( sweep_upper_arr_bounds == MIN_OUTPUT_ARR)
	{
		_setSweepModeDown();
	}

	// encoder start value
	ENCODER_TIMER->CNT = 1;
	// encoder limit
	ENCODER_TIMER->ARR = 65535;

	// reset sweep start value
	SWEEP_TIMER->CNT = 0;

	// sweep start speed
	SWEEP_TIMER->ARR = MIN_SWEEP_ARR;
	SWEEP_TIMER->PSC = 0;

	// do stuff
	FreqSweepMenuInputHandler(evSweepSpeed);

	// get ready to load menu
	eNextFreqMenuStatus = ENABLE_FREQ_SWEEP_MENU;


	// stay in this state
	eNewEvent = evIdle;
	return Freq_Sweep_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqSweepMenuInputHandler(eSystemEvent pEvent)
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqAdjustMenuInputHandler Event captured\n");
	#endif



	switch(pEvent)
	{
		case evSweepEnable:

			#ifdef SWV_DEBUG_ENABLED
				printf("evSweepEnable captured\n");
			#endif

			// toggle enable/disable
			SWEEP_TIMER->DIER 	^= TIM_DIER_UIE;
			SWEEP_TIMER->CR1	^= TIM_CR1_CEN;
			break;

		case evSweepMode:

			#ifdef SWV_DEBUG_ENABLED
				printf("evSweepMode captured\n");
			#endif

			// flip between 0:Upcounter and 1:Downcounter
			active_sweep_mode ^= 1U;

			switch(active_sweep_mode)
			{
				case SWEEP_MODE_DOWN:

					_setSweepModeDown();


					break;

				case SWEEP_MODE_UP:

					_setSweepModeUp();

					break;

				case SWEEP_MODE_BIDIR:
					// not used
					//SWEEP_TIMER->CR1 |= (TIM_CR1_CMS_0);
					break;
			}
			// toggle bi-directional (center-alligned)

			break;

		case evSweepSpeed:

			#ifdef SWV_DEBUG_ENABLED
				printf("evSweepSpeed captured\n");
			#endif

			switch(theCurrentEncoderSweepFunction)
			{
				case ENCODER_SWEEP_SPEED_FUNCTION:

					SWEEP_TIMER->ARR = MIN_SWEEP_ARR + ((ENCODER_TIMER->CNT*ENCODER_TIMER->CNT*ENCODER_TIMER->CNT));


					if(SWEEP_TIMER->PSC == 0)
					{
						calculated_sweep_in_hertz = (float)SM_MCLK / ((float)1 * (float)SWEEP_TIMER->ARR);
					}
					else
					{
						calculated_sweep_in_hertz = (float)SM_MCLK / ((float)SWEEP_TIMER->PSC * (float)SWEEP_TIMER->ARR);
					}

					break;

				case ENCODER_SWEEP_LIMIT_FUNCTION:
						switch(active_sweep_mode)
						{

							case SWEEP_MODE_UP:
									if(ENCODER_TIMER->CNT < sweep_upper_arr_bounds)
										sweep_lower_arr_bounds = ENCODER_TIMER->CNT;


								break;

							case SWEEP_MODE_DOWN:
									if(ENCODER_TIMER->CNT > sweep_lower_arr_bounds)
										sweep_upper_arr_bounds = ENCODER_TIMER->CNT;
								break;
							default:
								break;
						}
					break;

			}



			break;

		case evSweepSpeedBtn:
			theCurrentEncoderSweepFunction = ENCODER_SWEEP_SPEED_FUNCTION;
			ENCODER_TIMER->CNT = 1;
			break;

		case evSweepLimitBtn:
			theCurrentEncoderSweepFunction = ENCODER_SWEEP_LIMIT_FUNCTION;

			switch(active_sweep_mode)
			{

				case SWEEP_MODE_UP:
					// if encoder position is above the lower bounds set it below it
						if(ENCODER_TIMER->CNT > sweep_upper_arr_bounds)
							 ENCODER_TIMER->CNT = OUTPUT_TIMER->ARR;


					break;

				case SWEEP_MODE_DOWN:
						// if encoder position is below the lower bounds set it above it
						if(ENCODER_TIMER->CNT < sweep_lower_arr_bounds)
							ENCODER_TIMER->CNT = OUTPUT_TIMER->ARR;
					break;
				default:
					break;
			}

			break;

		default:
			// don't care about other eSystemEvent
			break;
	}

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Sweep_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqSweepMenuExitHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqSweepMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	// disable sweep timer and interrupts
	SWEEP_TIMER->DIER 	&= ~(TIM_DIER_UIE);
	SWEEP_TIMER->CR1 	&= ~(TIM_CR1_CEN);



	// disable the menu
	eNextFreqMenuStatus = ENABLE_FREQ_MAIN_MENU;

	// back to main freq menu
	eNewEvent = evIdle;
	return Freq_Main_Menu_State;
}

void _setSweepModeDown()
{
	// "Center-aligned" mode sets direction register to readonly,
	// so disable "Center-aligned" mode first
	SWEEP_TIMER->CR1 &= ~((TIM_CR1_CMS_0) | (TIM_CR1_CMS_1));

	// 0: Counter used as upcounter
	SWEEP_TIMER->CR1 |= (TIM_CR1_DIR);

	sweep_lower_arr_bounds  = OUTPUT_TIMER->ARR;
	sweep_upper_arr_bounds  = MAX_OUTPUT_ARR;
}

void _setSweepModeUp()
{

	// "Center-aligned" mode sets direction register to readonly,
	// so disable "Center-aligned" mode first
	SWEEP_TIMER->CR1 &= ~((TIM_CR1_CMS_0) | (TIM_CR1_CMS_1));

	// 1: Counter used as downcounter
	SWEEP_TIMER->CR1 &= ~(TIM_CR1_DIR);

	sweep_upper_arr_bounds  = OUTPUT_TIMER->ARR;
	sweep_lower_arr_bounds  = MIN_OUTPUT_ARR;

}
