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
#include <math.h>


// the displayed freq menu
eFreqMenu_Status eNextFreqMenuStatus = 	DISABLE_FREQ_MENU;

// the current setting of TIM_CR1_DIR in SWEEP_TIMER
eFreqSweepModes active_sweep_mode = SWEEP_MODE_UP;

// current function of rotary encoder knob
eEncoderSweepFunctions theCurrentEncoderSweepFunction = ENCODER_SWEEP_SPEED_FUNCTION;


//#define RATE_COEF	32	// how much the encoder increments/decrements per pulse
//#define RATE_DELTA	1.1	// how much we increment/decrement by


/*
 * 	Function prototypes
 */
eFreqMenu_Status FreqMenu_getStatus();
eFreqSweepModes FMSH_GetSweepMode();


eFreqSweepModes FMSH_GetSweepMode()
{
	return active_sweep_mode;
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
	#ifdef EVENT_MENU_DEBUG
		printf("FreqSweepMenuEntryHandler captured\n");
	#endif

	DM_RefreshScreen();

	if( sweep_upper_bounds_longest_output_arr != OUTPUT_TIMER->ARR)
		sweep_upper_bounds_longest_output_arr  = OUTPUT_TIMER->ARR;

	if( sweep_upper_bounds_longest_output_arr == MIN_OUTPUT_ARR)
	{
		FS_SetSweepModeDown();
	}

	FS_SetEncoderControlMode(ENCODER_SWEEP_SPEED_FUNCTION);
	FS_SetSweepTimerAutoReloadForEncoderControl(ENCODER_SWEEP_SPEED_FUNCTION);
	calculated_sweep_in_hertz = FS_GetCalculatedSweepFrequencyInHertz();

	// reset sweep start value
	SWEEP_TIMER->CNT = 0;

	// set default mode to sweep speed control
	FreqSweepMenuInputHandler(evSweepSpeedBtn);

	// sweep start speed
	SWEEP_TIMER->ARR = MIN_SWEEP_ARR;
	SWEEP_TIMER->PSC = 0;



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
	#ifdef EVENT_MENU_DEBUG
		printf("FreqAdjustMenuInputHandler Event captured\n");
	#endif



	switch(pEvent)
	{
		case evSweepEnableBtn:

			#ifdef EVENT_MENU_DEBUG
				printf("evSweepEnable captured\n");
			#endif

			// toggle enable/disable
			SWEEP_TIMER->DIER 	^= TIM_DIER_UIE;
			SWEEP_TIMER->CR1	^= TIM_CR1_CEN;
			break;

		case evSweepModeBtn:

			#ifdef EVENT_MENU_DEBUG
				printf("evSweepMode captured\n");
			#endif

			// flip between 0:Upcounter and 1:Downcounter
			active_sweep_mode ^= 1U;

			switch(active_sweep_mode)
			{
				case SWEEP_MODE_DOWN:
					FS_SetSweepModeDown();
					break;

				case SWEEP_MODE_UP:
					FS_SetSweepModeUp();
					break;

				case SWEEP_MODE_BIDIR:	// not used
					//SWEEP_TIMER->CR1 |= (TIM_CR1_CMS_0);
					break;
			}
			// switch(active_sweep_mode)
			// TODO
			FS_SetEncoderControlMode(theCurrentEncoderSweepFunction);

			break;

		// rotary encoder is turned
		case evEncoderSweep:

			#ifdef EVENT_MENU_DEBUG
				printf("evEncoderSweep captured\n");
			#endif

			switch(theCurrentEncoderSweepFunction)
			{
				case ENCODER_SWEEP_SPEED_FUNCTION:

					FS_SetSweepTimerAutoReloadForEncoderControl(ENCODER_SWEEP_SPEED_FUNCTION);

					calculated_sweep_in_hertz = FS_GetCalculatedSweepFrequencyInHertz();

					break;

				case ENCODER_SWEEP_LIMIT_FUNCTION:

					switch(active_sweep_mode)
					{
						case SWEEP_MODE_UP:

							// 100KHz is the max sweep upper limit
							if(ENCODER_TIMER->CNT < MIN_OUTPUT_ARR)
							{
								ENCODER_TIMER->CNT = MIN_OUTPUT_ARR;
								//
							}
							// the current "sweep lower" setting is the min sweep upper limit
							else if (ENCODER_TIMER->CNT > sweep_upper_bounds_longest_output_arr)
							{
								ENCODER_TIMER->CNT = sweep_upper_bounds_longest_output_arr;
							}
							// otherwise change the sweep upper limit
							else
							{
								sweep_lower_bounds_shortest_output_arr = ENCODER_TIMER->CNT;
							}
							break;

						case SWEEP_MODE_DOWN:
							// encoder limit
							if(ENCODER_TIMER->CNT >= MAX_OUTPUT_ARR)
							{
								ENCODER_TIMER->CNT = MAX_OUTPUT_ARR;
							}
							else if (ENCODER_TIMER->CNT < sweep_lower_bounds_shortest_output_arr)
							{
								ENCODER_TIMER->CNT = sweep_lower_bounds_shortest_output_arr;
							}
							else
							{
								sweep_upper_bounds_longest_output_arr = ENCODER_TIMER->CNT;
							}

							//						ENCODER_TIMER->ARR = sweep_lower_bounds_shortest_output_arr;

//							if(ENCODER_TIMER->CNT > sweep_lower_bounds_shortest_output_arr)
//

							break;

						default:
							break;

					}
					// switch(active_sweep_mode)

					break;

			}
			// switch(theCurrentEncoderSweepFunction)

			break;

		// set sweep speed button
		case evSweepSpeedBtn:
			FS_SetEncoderControlMode(ENCODER_SWEEP_SPEED_FUNCTION);

			break;

		// set sweep limit button
		case evSweepLimitBtn:
			FS_SetEncoderControlMode(ENCODER_SWEEP_LIMIT_FUNCTION);
/*			switch(active_sweep_mode)
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
			*/
			// switch(active_sweep_mode)

			break;

		default:
			break;
	}
	// switch(pEvent)


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
	#ifdef EVENT_MENU_DEBUG
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
	#ifdef EVENT_MENU_DEBUG
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
	#ifdef EVENT_MENU_DEBUG
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
	#ifdef EVENT_MENU_DEBUG
		printf("FreqMainMenuExitHandler Event captured\n");
	#endif


	// disable the menu
	eNextFreqMenuStatus = DISABLE_FREQ_MENU;

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

	#ifdef EVENT_MENU_DEBUG
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
	#ifdef EVENT_MENU_DEBUG
		printf("FreqPresetMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();
	FreqO_ResetLastEncoderValue();

	eNextFreqMenuStatus = ENABLE_FREQ_PRESET_MENU;

	FreqProfile_t *pFreqPresetTmp =  FreqO_GetFPresetObject();
	if(pFreqPresetTmp)
	{
		// set rotary encoder limit to full scale and set centre starting position
		ENCODER_TIMER->CNT = 32768;
		ENCODER_TIMER->ARR = 65535;
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
	#ifdef EVENT_MENU_DEBUG
		printf("FreqPresetMenuInputHandler Event captured\n");
	#endif

	FreqO_MapEncoderPositionCoarse(SM_GetEncoderValue(ENCODER_NORMAL));

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
	#ifdef EVENT_MENU_DEBUG
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
	#ifdef EVENT_MENU_DEBUG
		printf("FreqAdjustMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextFreqMenuStatus = ENABLE_FREQ_ADJUST_MENU;

	// set rotary encoder limit to full scale and set OUTPUT_TIMER "TOP" starting position
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
	#ifdef EVENT_MENU_DEBUG
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
	#ifdef EVENT_MENU_DEBUG
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
eFreqMenu_Status FreqMenu_getStatus()
{
	return eNextFreqMenuStatus;
}
