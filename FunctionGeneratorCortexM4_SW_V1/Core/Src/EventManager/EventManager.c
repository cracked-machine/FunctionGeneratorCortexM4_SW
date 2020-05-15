/*
 * EventManager.c
 *
 *  Created on: May 8, 2020
 *      Author: chris
 */


#include "EventManager.h"
#include "DisplayManager.h"

#include "SignalManager.h"

#include "pysine.h"

#include "dac.h"
#include "tim.h"

#include <stdio.h>
#include <string.h>

uint32_t last_enc_value = 0;

// public function prototypes
void EM_SetNewEvent(eSystemEvent pEvent);



// private function prototypes
eSystemState _FuncMainMenuEntryHandler();
eSystemState _FuncMainMenuInputHandler();
eSystemState _FuncMainMenuExitHandler();

eSystemState _FuncSignalMenuEntryHandler();
eSystemState _FuncSignalMenuInputHandler();
eSystemState _FuncSignalMenuExitHandler();

eSystemState _FuncSyncMenuEntryHandler();
eSystemState _FuncSyncMenuInputHandler();
eSystemState _FuncSyncMenuExitHandler();

eSystemState _GainMainMenuEntryHandler();
eSystemState _GainMainMenuInputHandler();
eSystemState _GainMainMenuExitHandler();

eSystemState _GainSignalMenuEntryHandler();
eSystemState _GainSignalMenuInputHandler();
eSystemState _GainSignalMenuExitHandler();

eSystemState _GainSyncMenuEntryHandler();
eSystemState _GainSyncMenuInputHandler();
eSystemState _GainSyncMenuExitHandler();

eSystemState _FreqMainMenuEntryHandler();
eSystemState _FreqMainMenuInputHandler();
eSystemState _FreqMainMenuExitHandler();

eSystemState _FreqPresetMenuEntryHandler();
eSystemState _FreqPresetMenuInputHandler();
eSystemState _FreqPresetMenuExitHandler();

eSystemState _FreqAdjustMenuEntryHandler();
eSystemState _FreqAdjustMenuInputHandler();
eSystemState _FreqAdjustMenuExitHandler();

eSystemState _FreqSweepMenuEntryHandler();
eSystemState _FreqSweepMenuInputHandler();
eSystemState _FreqSweepMenuExitHandler();

eSystemState _BiasMenuEntryHandler();
eSystemState _BiasMenuInputHandler();
eSystemState _BiasMenuExitHandler();

void _RefreshDisplay();

uint32_t tmpDataTable[SINE_DATA_SIZE];

// state machine
eSystemState eNextState = Idle_State;
eSystemEvent eNewEvent = evIdle;


uint32_t EM_GetLastEncoderValue()
{
	return last_enc_value;
}
void EM_SetLastEncoderValue(uint32_t _value)
{
	last_enc_value = _value;
}

///////////////////////////////////////////////////////
////// 			   SYSTEM STATEMACHINE			///////
///////////////////////////////////////////////////////

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void EM_ProcessEvent()
{

	switch(eNextState)
	{

// MAIN MENU

		case Idle_State:

//			TIM1->ARR = 12;

			if(eNewEvent == evBlueBtn)
			{
				eNextState = _FuncMainMenuEntryHandler();
			}
			if(eNewEvent == evGreenBtn)
			{
				eNextState = _FreqMainMenuEntryHandler();
			}
			if(eNewEvent == evYellowBtn)
			{
				eNextState = _GainMainMenuEntryHandler();
			}
			if(eNewEvent == evRedBtn)
			{
				eNextState = _BiasMenuEntryHandler();
			}
			break;

// FUNC MENUS

		case Func_Main_Menu_State:

			if(eNewEvent == evEncoderSet)
			{
				// No menu action
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _FuncMainMenuExitHandler();
			}
			if(eNewEvent == evBlueBtn)
			{
				eNextState = _FuncSignalMenuEntryHandler();
			}
			if(eNewEvent == evGreenBtn)
			{
				eNextState = _FuncSyncMenuEntryHandler();
			}

			break;

		case Func_Signal_Menu_State:

			if(eNewEvent == evEncoderSet)
			{
				eNextState = _FuncSignalMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _FuncSignalMenuExitHandler();
			}

			break;

		case Func_Sync_Menu_State:

			if(eNewEvent == evEncoderSet)
			{
				eNextState = _FuncSyncMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _FuncSyncMenuExitHandler();
			}

			break;

// GAIN MENUS

		case Gain_Main_Menu_State:

			if(eNewEvent == evEncoderSet)
			{
				// No menu action
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _GainMainMenuExitHandler();
			}
			if(eNewEvent == evBlueBtn)
			{
				eNextState = _GainSignalMenuEntryHandler();
			}
			if(eNewEvent == evGreenBtn)
			{
				eNextState = _GainSyncMenuEntryHandler();
			}

			break;

		case Gain_Signal_Menu_State:

			if(eNewEvent == evEncoderSet)
			{
				eNextState = _GainSignalMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _GainSignalMenuExitHandler();
			}

			break;

		case Gain_Sync_Menu_State:

			if(eNewEvent == evEncoderSet)
			{
				eNextState = _GainSyncMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _GainSyncMenuExitHandler();
			}

			break;

// FREQ MENUS

		case Freq_Main_Menu_State:

			if(eNewEvent == evEncoderPush)
			{
				eNextState = _FreqMainMenuExitHandler();
			}
			if(eNewEvent == evBlueBtn)
			{
				eNextState = _FreqPresetMenuEntryHandler();
			}
			if(eNewEvent == evGreenBtn)
			{
				eNextState = _FreqAdjustMenuEntryHandler();
			}
			if(eNewEvent == evYellowBtn)
			{
				eNextState = _FreqSweepMenuEntryHandler();
			}

			break;

		case Freq_Preset_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _FreqPresetMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _FreqPresetMenuExitHandler();
			}
			break;

		case Freq_Adjust_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _FreqAdjustMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _FreqAdjustMenuExitHandler();
			}
			break;

		case Freq_Sweep_Menu_State:

			if(eNewEvent == evEncoderPush)
			{
				eNextState = _FreqSweepMenuExitHandler();
			}
			break;

// BIAS MENUS

		case Bias_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _BiasMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _BiasMenuExitHandler();
			}

			break;

		default:
			break;
	}

}

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
eSystemState _FuncMainMenuEntryHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("FunctionMenu Event captured\n");
#endif

	_RefreshDisplay();

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
eSystemState _FuncMainMenuInputHandler(void)
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
eSystemState _FuncMainMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitFuncMenu Event captured\n");
#endif

	// disable the menu

	DM_ShowFuncMenu(DISABLE_FUNCMENU);

	// reset the encoder range

//	ENCODER_TIMER->ARR = 1024;

	_RefreshDisplay();

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
eSystemState _FuncSignalMenuEntryHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("FunctionMenu Event captured\n");
#endif

	_RefreshDisplay();

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
eSystemState _FuncSignalMenuInputHandler(void)
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
eSystemState _FuncSignalMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitFuncMenu Event captured\n");
#endif

	// disable the menu

	DM_ShowFuncMenu(ENABLE_FUNC_MAIN_MENU);

	// reset the encoder range

//	ENCODER_TIMER->ARR = 1024;

	_RefreshDisplay();

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
eSystemState _FuncSyncMenuEntryHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("FunctionMenu Event captured\n");
#endif

	_RefreshDisplay();

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
eSystemState _FuncSyncMenuInputHandler(void)
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
eSystemState _FuncSyncMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitFuncMenu Event captured\n");
#endif

	// disable the menu

	DM_ShowFuncMenu(ENABLE_FUNC_MAIN_MENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	_RefreshDisplay();

	eNewEvent = evIdle;
	return Func_Main_Menu_State;
}


///////////////////////////////////////////////////////
//////    "GAIN" EVENTHANDLER FUNCTIONS		///////
///////////////////////////////////////////////////////

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState _GainMainMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainMenu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowGainMenu(ENABLE_GAIN_MAIN_MENU);

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
eSystemState _GainMainMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainSet Event captured\n");
#endif

	//GO_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));
	//VPP_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));

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
eSystemState _GainMainMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitGainMenu Event captured\n");
#endif

	DM_ShowGainMenu(DISABLE_GAINMENU);

	_RefreshDisplay();

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
eSystemState _GainSignalMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainMenu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowGainMenu(ENABLE_GAIN_SIGNAL_MENU);

	VppEncoderPreset_t *pVppPresetTmp =  VPP_GetVppPresetObject(SIGNAL_OUTPUT_PRESET);
	if(pVppPresetTmp)
	{
		ENCODER_TIMER->CNT = pVppPresetTmp->epos;
		ENCODER_TIMER->ARR = MAX_VPP_ENCODER_RANGE;
	}
	else
	{
		DM_SetErrorDebugMsg("_GainMainMenuEntryHandler: pVppPresetTmp null pointer");
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
eSystemState _GainSignalMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainSet Event captured\n");
#endif

	//GO_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));
	VPP_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));

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
eSystemState _GainSignalMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitGainMenu Event captured\n");
#endif

	DM_ShowGainMenu(ENABLE_GAIN_MAIN_MENU);

	_RefreshDisplay();

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
eSystemState _GainSyncMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainMenu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowGainMenu(ENABLE_GAIN_SYNC_MENU);

/*	VppEncoderPreset_t *pVppPresetTmp =  VPP_GetVppPresetObject(SYNC_OUTPUT_PRESET);
	if(pVppPresetTmp)
	{
		ENCODER_TIMER->CNT = pVppPresetTmp->epos;
		ENCODER_TIMER->ARR = MAX_VPP_ENCODER_RANGE;
	}
	else
	{
		DM_SetErrorDebugMsg("_GainMainMenuEntryHandler: pVppPresetTmp null pointer");
	}
*/
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
eSystemState _GainSyncMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainSet Event captured\n");
#endif

	//GO_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));
//	VPP_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));

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
eSystemState _GainSyncMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitGainMenu Event captured\n");
#endif

	DM_ShowGainMenu(ENABLE_GAIN_MAIN_MENU);

	_RefreshDisplay();

	eNewEvent = evIdle;
	return Gain_Main_Menu_State;
}


///////////////////////////////////////////////////////
//////    "BIAS" EVENTHANDLER FUNCTIONS		///////
///////////////////////////////////////////////////////

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState _BiasMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("BiasMenu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowBiasSelectMenu(ENABLE_BIASMENU);

	ENCODER_TIMER->ARR = BIAS_MAX;
	ENCODER_TIMER->CNT = BO_GetDcBiasEncoderValue();

	eNewEvent = evIdle;
	return Bias_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState _BiasMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("BiasSet Event captured\n");
#endif

	BO_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));

	eNewEvent = evIdle;
	return Bias_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState _BiasMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitBiasMenu Event captured\n");
#endif


	// disable the menu
	DM_ShowBiasSelectMenu(DISABLE_BIASMENU);

	// reset the encoder range

	//ENCODER_TIMER->ARR = 1024;

	_RefreshDisplay();

	eNewEvent = evIdle;
	return Idle_State;
}

///////////////////////////////////////////////////////
//////    "FREQUENCY" EVENTHANDLER FUNCTIONS	///////
///////////////////////////////////////////////////////

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState _FreqMainMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqMenu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowFreqMenu(ENABLE_FREQ_MAIN_MENU);

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
eSystemState _FreqMainMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqSet Event captured\n");
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
eSystemState _FreqMainMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Main Menu Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	_RefreshDisplay();

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
eSystemState _FreqPresetMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Freq Preset Menu Entry Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowFreqMenu(ENABLE_FREQ_PRESET_MENU);

	Freq_Preset_Encoder_Pos_t *pFreqPresetTmp =  FreqO_GetFPresetObject();
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
eSystemState _FreqPresetMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqSet Event captured\n");
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
eSystemState _FreqPresetMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Menu Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

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
eSystemState _FreqAdjustMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Freq Adjust Menu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowFreqMenu(ENABLE_FREQ_ADJUST_MENU);

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
eSystemState _FreqAdjustMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqSet Event captured\n");
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
eSystemState _FreqAdjustMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Adjust Menu Exit Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

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
eSystemState _FreqSweepMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Freq Sweep Menu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowFreqMenu(ENABLE_FREQ_SWEEP_MENU);

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
eSystemState _FreqSweepMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Sweep Menu Exit Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

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
void EM_SetNewEvent(eSystemEvent pEvent)
{
	eNewEvent = pEvent;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState EM_GetSystemState()
{
	return eNextState;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _RefreshDisplay()
{
	// don't let the DisplayManager interrupt the LCD refresh
	HAL_TIM_Base_Stop_IT(&htim15);
	{
		DM_RefreshBackgroundLayout();
	}
	HAL_TIM_Base_Start_IT(&htim15);
}




