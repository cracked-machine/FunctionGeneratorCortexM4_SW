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

	//_setFuncMenuStatus(ENABLE_FUNC_MAIN_MENU);

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

	SM_ResetFuncPwmDutyMode();
	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Func_Main_Menu_State;
}


