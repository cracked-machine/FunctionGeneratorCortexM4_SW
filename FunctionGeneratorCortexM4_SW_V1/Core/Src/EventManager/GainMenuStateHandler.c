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
#ifdef EM_SWV_DEBUG
	printf("GainMenu Event captured\n");
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
#ifdef EM_SWV_DEBUG
	printf("GainSet Event captured\n");
#endif

	//GO_ModifyOutput(SMGetEncoderValue(ENCODER_REVERSE));
	//VPP_ModifySignalOutput(SMGetEncoderValue(ENCODER_REVERSE));

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
#ifdef EM_SWV_DEBUG
	printf("ExitGainMenu Event captured\n");
#endif

	eNextGainMenuStatus = DISABLE_GAIN_MENU;

	DM_RefreshScreen();

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
eSystemState GainSignalMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainMenu Event captured\n");
#endif

	DM_RefreshScreen();

	eNextGainMenuStatus = ENABLE_GAIN_SIGNAL_MENU;

	VppEncoderPreset_t *pVppPresetTmp =  VPP_GetVppPresetObject(SIGNAL_OUTPUT_PRESET);
	if(pVppPresetTmp)
	{
		ENCODER_TIMER->CNT = pVppPresetTmp->epos;
		ENCODER_TIMER->ARR = MAX_VPP_ENCODER_RANGE;
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
#ifdef EM_SWV_DEBUG
	printf("GainSet Event captured\n");
#endif

	//GO_ModifyOutput(SMGetEncoderValue(ENCODER_REVERSE));
	VPP_ModifySignalOutput(SM_GetEncoderValue(ENCODER_REVERSE));

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
#ifdef EM_SWV_DEBUG
	printf("ExitGainMenu Event captured\n");
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
eSystemState GainSyncMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainMenu Event captured\n");
#endif

	DM_RefreshScreen();

	eNextGainMenuStatus = ENABLE_GAIN_SYNC_MENU;

	VppEncoderPreset_t *pVppPresetTmp =  VPP_GetVppPresetObject(SYNC_OUTPUT_PRESET);
	if(pVppPresetTmp)
	{
		ENCODER_TIMER->CNT = pVppPresetTmp->epos;
		ENCODER_TIMER->ARR = MAX_VPP_ENCODER_RANGE;
	}
	else
	{
		DM_SetErrorDebugMsg("GainMainMenuEntryHandler: pVppPresetTmp null pointer");
	}

	eNewEvent = evIdle;
	return Gain_Sync_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainSyncMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainSet Event captured\n");
#endif

	//GO_ModifyOutput(SMGetEncoderValue(ENCODER_REVERSE));
	VPP_ModifySyncOutput(SM_GetEncoderValue(ENCODER_REVERSE));

	eNewEvent = evYellowBtn;
	return Gain_Sync_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainSyncMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitGainMenu Event captured\n");
#endif

	eNextGainMenuStatus = ENABLE_GAIN_MAIN_MENU;

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Gain_Main_Menu_State;
}

