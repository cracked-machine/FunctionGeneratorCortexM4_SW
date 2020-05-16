/*
 * FreqMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#include "FreqMenuStateHandler.h"

#include "DisplayManager.h"
#include "SignalManager.h"
#include <stdio.h>

eFreqMenu_Status eNextFreqMenuStatus = 	DISABLE_FREQ_MENU;

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
	return Idle_State;
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


	// disable the menu
	eNextFreqMenuStatus = DISABLE_FREQ_MENU;

	// back to main freq menu
	eNewEvent = evGreenBtn;
	return Idle_State;
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
	ENCODER_TIMER->CNT = TIM8->ARR;
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


	// disable the menu
	eNextFreqMenuStatus = DISABLE_FREQ_MENU;

	// back to main freq menu
	eNewEvent = evGreenBtn;
	return Idle_State;
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

	eNextFreqMenuStatus = ENABLE_FREQ_SWEEP_MENU;

	// set the rotary encoder limits to 0-? for this menu
	ENCODER_TIMER->CNT = 0;
	ENCODER_TIMER->ARR = 56;

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


	// disable the menu
	eNextFreqMenuStatus = DISABLE_FREQ_MENU;

	// back to main freq menu
	eNewEvent = evGreenBtn;
	return Idle_State;
}

