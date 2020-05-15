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

///////////////////////////////////////////////////////
//////    "FUNCTION" EVENTHANDLER FUNCTIONS		///////
///////////////////////////////////////////////////////


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
#ifdef EM_SWV_DEBUG
	printf("FunctionMenu Event captured\n");
#endif

	DM_RefreshScreen();

	DM_ShowFuncMenu(ENABLE_FUNC_MAIN_MENU);

/*	Func_Preset_Encoder_Pos_t *pFuncPresetTmp =  FuncO_GetFPresetObject();
	if(pFuncPresetTmp)
	{
		ENCODER_TIMER->CNT = pFuncPresetTmp->epos;
		ENCODER_TIMER->ARR = FuncO_GetFuncPresetEncoderRange();
	}
	else
	{
		DM_SetErrorDebugMsg("_FuncMenuEntryHandler: pFuncPresetTmp null pointer");
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
#ifdef EM_SWV_DEBUG
	printf("FunctionAdjust Event captured\n");
#endif


//	FuncO_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));

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
#ifdef EM_SWV_DEBUG
	printf("ExitFuncMenu Event captured\n");
#endif

	// disable the menu

	DM_ShowFuncMenu(DISABLE_FUNCMENU);

	// reset the encoder range

//	ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Idle_State;
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
#ifdef EM_SWV_DEBUG
	printf("FunctionMenu Event captured\n");
#endif

	DM_RefreshScreen();

	DM_ShowFuncMenu(ENABLE_FUNC_SIGNAL_MENU);

	Func_Preset_Encoder_Pos_t *pFuncPresetTmp =  FuncO_GetFPresetObject();
	if(pFuncPresetTmp)
	{
		ENCODER_TIMER->CNT = pFuncPresetTmp->epos;
		ENCODER_TIMER->ARR = FuncO_GetFuncPresetEncoderRange();
	}
	else
	{
		DM_SetErrorDebugMsg("_FuncMenuEntryHandler: pFuncPresetTmp null pointer");
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
#ifdef EM_SWV_DEBUG
	printf("FunctionAdjust Event captured\n");
#endif


	FuncO_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));
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
#ifdef EM_SWV_DEBUG
	printf("ExitFuncMenu Event captured\n");
#endif

	// disable the menu

	DM_ShowFuncMenu(ENABLE_FUNC_MAIN_MENU);

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
#ifdef EM_SWV_DEBUG
	printf("FunctionMenu Event captured\n");
#endif

	DM_RefreshScreen();

	DM_ShowFuncMenu(ENABLE_FUNC_SYNC_MENU);

	Func_Preset_Encoder_Pos_t *pFuncPresetTmp =  FuncO_GetFPresetObject();
	if(pFuncPresetTmp)
	{
		ENCODER_TIMER->CNT = pFuncPresetTmp->epos;
		ENCODER_TIMER->ARR = FuncO_GetFuncPresetEncoderRange();
	}
	else
	{
		DM_SetErrorDebugMsg("_FuncMenuEntryHandler: pFuncPresetTmp null pointer");
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
#ifdef EM_SWV_DEBUG
	printf("FunctionAdjust Event captured\n");
#endif


	FuncO_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));
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
#ifdef EM_SWV_DEBUG
	printf("ExitFuncMenu Event captured\n");
#endif

	// disable the menu

	DM_ShowFuncMenu(ENABLE_FUNC_MAIN_MENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Func_Main_Menu_State;
}
