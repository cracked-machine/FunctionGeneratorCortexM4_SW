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

eGainMenu_Status eNextGainMenuStatus = 	DISABLE_GAIN_MENU;

eGainMenu_Status GainMenu_getStatus()
{
	return eNextGainMenuStatus;
}

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

	eNextGainMenuStatus = ENABLE_GAIN_MAIN_MENU;

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

	//GO_ModifyOutput(SMGetEncoderValue(ENCODER_REVERSE));
	//VPP_MapEncoderPositionToSignalOutput(SMGetEncoderValue(ENCODER_REVERSE));

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

	eNextGainMenuStatus = DISABLE_GAIN_MENU;

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

	eNextGainMenuStatus = ENABLE_GAIN_SIGNAL_MENU;

	AmplitudeProfile_t* pTmpVppPreset = SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile;

	if(pTmpVppPreset)
	{
		//ENCODER_TIMER->CNT = pTmpVppPreset->epos;
		//ENCODER_TIMER->ARR = MAX_VPP_ENCODER_RANGE;
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
eSystemState GainSignalMenuInputHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("GainSignalMenuInputHandler Event captured\n");
	#endif

	FunctionProfile_t *tmpFuncProfile = SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile;
	if(tmpFuncProfile)
	{
		if(tmpFuncProfile->func == PWM_FUNC_MODE)
		{
			GO_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_REVERSE));

		}
		else
		{
			VPP_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_FORWARD));
		}
	}
	//GO_ModifyOutput(SMGetEncoderValue(ENCODER_REVERSE));
	//

	eNewEvent = evYellowBtn;
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

	eNextGainMenuStatus = ENABLE_GAIN_MAIN_MENU;

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

	eNextGainMenuStatus = ENABLE_GAIN_Aux_MENU;

	AmplitudeProfile_t* pTmpVppPreset = SM_GetOutputChannel(AUX_CHANNEL)->amp_profile;

	if(pTmpVppPreset)
	{
		ENCODER_TIMER->CNT = pTmpVppPreset->epos;
		ENCODER_TIMER->ARR = MAX_VPP_ENCODER_RANGE;
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

	//GO_ModifyOutput(SMGetEncoderValue(ENCODER_REVERSE));
	VPP_MapEncoderPositionToAuxOutput(SM_GetEncoderValue(ENCODER_REVERSE));

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

	eNextGainMenuStatus = ENABLE_GAIN_MAIN_MENU;

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Gain_Main_Menu_State;
}

