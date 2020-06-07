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
#include <math.h>

eFuncMenu_Status eNextFuncMenuStatus = 	DISABLE_FUNC_MENU;

// prototypes
eFuncMenu_Status FuncMenu_getStatus();
void _setFuncMenuStatus(eFuncMenu_Status newStatus);

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
	#ifdef EVENT_MENU_DEBUG
		printf("FuncMainMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	_setFuncMenuStatus(ENABLE_FUNC_MAIN_MENU);

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
	#ifdef EVENT_MENU_DEBUG
		printf("FuncMainMenuInputHandler Event captured\n");
	#endif

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
	#ifdef EVENT_MENU_DEBUG
		printf("FuncMainMenuExitHandler Event captured\n");
	#endif

	_setFuncMenuStatus(DISABLE_FUNC_MENU);

	// reset the encoder range
	ToplevelMenu_setStatus(ENABLE_TOPLEVEL_OUTPUT_MENU);

	DM_RefreshScreen();

	#ifdef EVENT_MENU_DEBUG
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
	#ifdef EVENT_MENU_DEBUG
		printf("FuncSignalMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();
	FuncO_ResetLastEncoderValue();

	_setFuncMenuStatus(ENABLE_FUNC_SIGNAL_MENU);

	ENCODER_TIMER->CNT = 32768;
	ENCODER_TIMER->ARR = 65535;

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
	#ifdef EVENT_MENU_DEBUG
		printf("FuncSignalMenuInputHandler Event captured\n");
	#endif

	FuncO_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_NORMAL));

	eNewEvent = evIdle;
	return Func_Signal_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FuncSignalToggleDutyMode()
{
	SM_ToggleFuncPwmDutyMode();
	ENCODER_TIMER->ARR = 16384;
	eNewEvent = evIdle;
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
	#ifdef EVENT_MENU_DEBUG
		printf("FuncSignalMenuExitHandler Event captured\n");
	#endif

	// disable the menu
	_setFuncMenuStatus(ENABLE_FUNC_MAIN_MENU);

	DM_RefreshScreen();
	SM_ResetFuncPwmDutyMode();
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
eSystemState FuncAuxMenuEntryHandler(void)
{
	#ifdef EVENT_MENU_DEBUG
		printf("FuncAuxMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();
	FuncO_ResetLastEncoderValue();

	_setFuncMenuStatus(ENABLE_FUNC_AUX_MENU);

	ENCODER_TIMER->CNT = 32768;
	ENCODER_TIMER->ARR = 65535;

	eNewEvent = evIdle;
	return Func_Aux_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuInputHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncAuxMenuInputHandler(void)
{
	#ifdef EVENT_MENU_DEBUG
		printf("FuncAuxMenuInputHandler Event captured\n");
	#endif

	// PWM ADJUST
	if(SM_IsFuncPwmDutyMode())
	{
		uint16_t enc_value = SM_GetEncoderValue(ENCODER_NORMAL);
		PWM_AUX_OUT_TIM->CCR1 = (pow(enc_value, 2));
		//BO_SetPwmSignalOffsetForDuty(BO_GetOutputBias() + SM_GetEncoderValue(ENCODER_NORMAL));

	}
	else
	{
		FuncO_MapEncoderPositionToAuxOutput(SM_GetEncoderValue(ENCODER_NORMAL));
	}

	eNewEvent = evIdle;
	return Func_Aux_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FuncAuxToggleDutyMode()
{
	SM_ToggleFuncPwmDutyMode();
	ENCODER_TIMER->ARR = 16384;
	eNewEvent = evIdle;
	return Func_Aux_Menu_State;
}


/*
 *
 *	@brief	_FuncMenuExitHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncAuxMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("FuncAuxMenuExitHandler Event captured\n");
	#endif

	// disable the menu
	_setFuncMenuStatus(ENABLE_FUNC_MAIN_MENU);

	SM_ResetFuncPwmDutyMode();
	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Func_Main_Menu_State;
}

/*
 *
 *	@brief	FuncMenu_getStatus
 *
 *	@param None
 *	@retval eFuncMenu_Status enum for current menu state
 *
 */
eFuncMenu_Status FuncMenu_getStatus()
{
	return eNextFuncMenuStatus;
}

/*
 *
 *	@brief	_setStatus
 *
 *	@param eFuncMenu_Status enum for next menu state
 *	@retval None
 *
 */
void _setFuncMenuStatus(eFuncMenu_Status newStatus)
{
	eNextFuncMenuStatus = newStatus;
}

