/*
 * FuncMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include "FuncMenuStateHandler.h"

#include "DisplayManager.h"
#include "SignalManager.h"

#include <stdio.h>

eFuncMenu_Status eNextFuncMenuStatus = 	DISABLE_FUNC_MENU;

eFuncMenu_Status FuncMenu_getStatus()
{
	return eNextFuncMenuStatus;
}

/*
 *
 *	@brief	_FuncMenuEntryHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncMainMenuEntryHandler(void)
{
#ifdef SWV_DEBUG_ENABLED
	printf("FuncMainMenuEntryHandler Event captured\n");
#endif

	DM_RefreshScreen();



	eNextFuncMenuStatus = 	ENABLE_FUNC_MAIN_MENU;

/*	FunctionProfile_t *func_profileTmp =  FuncO_GetSignalFPresetObject();
	if(func_profileTmp)
	{
		ENCODER_TIMER->CNT = func_profileTmp->epos;
		ENCODER_TIMER->ARR = FuncO_GetFuncPresetEncoderRange();
	}
	else
	{
		DM_SetErrorDebugMsg("_FuncMenuEntryHandler: func_profileTmp null pointer");
	}
*/
	eNewEvent = evIdle;
	return Func_Main_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuInputHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncMainMenuInputHandler(void)
{
#ifdef SWV_DEBUG_ENABLED
	printf("FuncMainMenuInputHandler Event captured\n");
#endif


//	FuncO_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_REVERSE));

	eNewEvent = evBlueBtn;
	return Func_Main_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuExitHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncMainMenuExitHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("FuncMainMenuExitHandler Event captured\n");
#endif

	// disable the menu

	eNextFuncMenuStatus = 	DISABLE_FUNC_MENU;

	// reset the encoder range

//	ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

#ifdef SWV_DEBUG_ENABLED
	  printf("returning to Idle State\n");
#endif

	eNewEvent = evIdle;
	return Toplevel_Output_Menu_State;
}


/*
 *
 *	@brief	_FuncMenuEntryHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncSignalMenuEntryHandler(void)
{
#ifdef SWV_DEBUG_ENABLED
	printf("FuncSignalMenuEntryHandler Event captured\n");
#endif

	DM_RefreshScreen();
	FuncO_ResetLastEncoderValue();

	eNextFuncMenuStatus = 	ENABLE_FUNC_SIGNAL_MENU;

	//FunctionProfile_t *func_profileTmp =  FuncO_GetSignalFPresetObject();
	FunctionProfile_t *func_profileTmp = SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile;
	if(func_profileTmp)
	{
		ENCODER_TIMER->CNT = func_profileTmp->epos;
		ENCODER_TIMER->ARR = FuncO_GetFuncPresetEncoderRange();
	}
	else
	{
		DM_SetErrorDebugMsg("_FuncMenuEntryHandler: func_profileTmp null pointer");
	}

	eNewEvent = evIdle;
	return Func_Signal_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuInputHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncSignalMenuInputHandler(void)
{
#ifdef SWV_DEBUG_ENABLED
	printf("FuncSignalMenuInputHandler Event captured\n");
#endif


	FuncO_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_REVERSE));
	eNewEvent = evBlueBtn;
	return Func_Signal_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuExitHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncSignalMenuExitHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("FuncSignalMenuExitHandler Event captured\n");
#endif

	// disable the menu

	eNextFuncMenuStatus = 	ENABLE_FUNC_MAIN_MENU;

	// reset the encoder range

//	ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Func_Main_Menu_State;
}


/*
 *
 *	@brief	_FuncMenuEntryHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncSyncMenuEntryHandler(void)
{
#ifdef SWV_DEBUG_ENABLED
	printf("FuncSyncMenuEntryHandler Event captured\n");
#endif

	DM_RefreshScreen();
	FuncO_ResetLastEncoderValue();

	eNextFuncMenuStatus = 	ENABLE_FUNC_SYNC_MENU;

	//FunctionProfile_t *func_profileTmp =  FuncO_GetSyncFPresetObject();
	FunctionProfile_t *func_profileTmp = SM_GetOutputChannel(SYNC_CHANNEL)->func_profile;
	if(func_profileTmp)
	{
		ENCODER_TIMER->CNT = func_profileTmp->epos;
		ENCODER_TIMER->ARR = FuncO_GetFuncPresetEncoderRange();
	}
	else
	{
		DM_SetErrorDebugMsg("_FuncMenuEntryHandler: func_profileTmp null pointer");
	}

	eNewEvent = evIdle;
	return Func_Sync_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuInputHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncSyncMenuInputHandler(void)
{
#ifdef SWV_DEBUG_ENABLED
	printf("FuncSyncMenuInputHandler Event captured\n");
#endif


	FuncO_MapEncoderPositionToSyncOutput(SM_GetEncoderValue(ENCODER_REVERSE));
	eNewEvent = evBlueBtn;
	return Func_Sync_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuExitHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncSyncMenuExitHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("FuncSyncMenuExitHandler Event captured\n");
#endif

	// disable the menu

	eNextFuncMenuStatus = 	ENABLE_FUNC_MAIN_MENU;

	// reset the encoder range

	//ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Func_Main_Menu_State;
}
