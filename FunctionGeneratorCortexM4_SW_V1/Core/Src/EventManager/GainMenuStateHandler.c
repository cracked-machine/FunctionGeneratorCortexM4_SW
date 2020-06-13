/*
 * GainMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include "GainMenuStateHandler.h"
#include "DisplayManager.h"
#include "SignalManager.h"
#include <stdio.h>

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainMainMenuEntryHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("GainMainMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Gain_Main_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainMainMenuInputHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("GainMainMenuInputHandler Event captured\n");
	#endif

	eNewEvent = evYellowBtn;
	return Gain_Main_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainMainMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("GainMainMenuExitHandler Event captured\n");
	#endif

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
eSystemState GainSignalMenuEntryHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("GainSignalMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();
	GO_ResetLastEncoderValue();
	VPP_ResetLastEncoderValue();

	AmplitudeProfile_t* pTmpVppPreset = SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile;

	if(pTmpVppPreset)
	{
		// set to full range and mid starting position
		ENCODER_TIMER->CNT = 32768;
		ENCODER_TIMER->ARR = 65535;
	}
	else
	{
		DM_SetErrorDebugMsg("GainMainMenuEntryHandler: pVppPresetTmp null pointer");
	}

	eNewEvent = evIdle;
	return Gain_Signal_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainSignalMenuInputHandler(eSystemEvent pEvent)
{
	#ifdef EVENT_MENU_DEBUG
		printf("GainSignalMenuInputHandler Event captured\n");
	#endif


	FunctionProfile_t *tmpFuncProfile = SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile;

	switch(pEvent)
	{
		case evEncoderSet:

			if(tmpFuncProfile)
			{
				if(tmpFuncProfile->func == PWM_FUNC_MODE)
				{
					GO_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_INVERSE));

				}
				else
				{
					VPP_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_NORMAL));
				}
			}
			break;

		case evBlueBtn:
			VPP_ApplyProfileToSignal(VPP18);
			break;

		case evGreenBtn:
			VPP_ApplyProfileToSignal(VPP33);
			break;

		case evYellowBtn:
			VPP_ApplyProfileToSignal(VPP50);
			break;

		case evRedBtn:
			VPP_ApplyProfileToSignal(VPP90);
			break;

		default:
			break;
	}

	eNewEvent = evIdle;
	return Gain_Signal_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainSignalMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("GainSignalMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Gain_Main_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainAuxMenuEntryHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("GainAuxMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();
	VPP_ResetLastEncoderValue();

	AmplitudeProfile_t* pTmpVppPreset = SM_GetOutputChannel(AUX_CHANNEL)->amp_profile;

	if(pTmpVppPreset)
	{
		// set to full range and mid starting position
		ENCODER_TIMER->CNT = 32768;
		ENCODER_TIMER->ARR = 65535;
	}
	else
	{
		DM_SetErrorDebugMsg("GainMainMenuEntryHandler: pVppPresetTmp null pointer");
	}

	eNewEvent = evIdle;
	return Gain_Aux_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainAuxMenuInputHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("GainAuxMenuInputHandler Event captured\n");
	#endif

	VPP_MapEncoderPositionToAuxOutput(SM_GetEncoderValue(ENCODER_NORMAL));

	eNewEvent = evYellowBtn;
	return Gain_Aux_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainAuxMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("GainAuxMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Gain_Main_Menu_State;
}

