/*
 * EventManager.c
 *
 *  Created on: May 8, 2020
 *      Author: chris
 */


#include "EventManager.h"
#include "DisplayManager.h"

#include "SignalManager.h"
//#include "funcgen.h"

#include "dac.h"
#include "tim.h"

#include <stdio.h>



// public function prototypes
void EM_SetNewEvent(eSystemEvent pEvent);



// private function prototypes
eSystemState _FuncMenuEntryHandler();
eSystemState _FuncMenuInputHandler();
eSystemState _FuncMenuExitHandler();

eSystemState _GainMenuEntryHandler();
eSystemState _GainMenuInputHandler();
eSystemState _GainMenuExitHandler();

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



// state machine
eSystemState eNextState = Idle_State;
eSystemEvent eNewEvent = evIdle;




/*
 *
 * 	Main state machine for event process
 *
 */
void EM_ProcessEvent()
{

	switch(eNextState)
	{
		case Idle_State:

			if(eNewEvent == evBlueBtn)
			{
				eNextState = _FuncMenuEntryHandler();
			}
			if(eNewEvent == evGreenBtn)
			{
				eNextState = _FreqMainMenuEntryHandler();
			}
			if(eNewEvent == evYellowBtn)
			{
				eNextState = _GainMenuEntryHandler();
			}
			if(eNewEvent == evRedBtn)
			{
				eNextState = _BiasMenuEntryHandler();
			}

			break;

		case Func_Menu_State:

			if(eNewEvent == evEncoderSet)
			{
				eNextState = _FuncMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _FuncMenuExitHandler();
			}
			break;

		case Gain_Menu_State:

			if(eNewEvent == evEncoderSet)
			{
				eNextState = _GainMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _GainMenuExitHandler();
			}
			break;

		case Freq_Main_Menu_State:

			if(eNewEvent == evEncoderSet)
			{
//				eNextState = _FreqMainMenuSetHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _FreqMainMenuExitHandler();
			}
			if(eNewEvent == evBlueBtn)
			{
//				FreqO_ApplyPreset(FPRESET_1HZ);
				eNextState = _FreqPresetMenuEntryHandler();
			}
			if(eNewEvent == evGreenBtn)
			{
//				FreqO_ApplyPreset(FPRESET_100HZ);
				eNextState = _FreqAdjustMenuEntryHandler();
			}
			if(eNewEvent == evYellowBtn)
			{
//				FreqO_ApplyPreset(FPRESET_1KHZ);
				eNextState = _FreqSweepMenuEntryHandler();
			}
			if(eNewEvent == evRedBtn)
			{
				// No menu action
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
			if(eNewEvent == evEncoderSet)
			{
//				eNextState = _FreqMainMenuSetHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _FreqSweepMenuExitHandler();
			}
			break;

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
//////		PRIVATE EVENTHANDLER FUNCTIONS		///////
///////////////////////////////////////////////////////

/*
 *
 *	Business logic for evFunctionMenu events
 *
 */
eSystemState _FuncMenuEntryHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("FunctionMenu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowFuncSelectMenu(ENABLE_FUNCMENU);

	// set the rotary encoder limits to 0-20 for this menu
	ENCODER_TIMER->CNT = 20;
	ENCODER_TIMER->ARR = 20;

	return Func_Menu_State;
}

/*
 *
 *	Business logic for evFunctionSet events
 *
 */
eSystemState _FuncMenuInputHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("FunctionAdjust Event captured\n");
#endif


	FuncO_ModifyOutput();
	eNewEvent = evBlueBtn;
	return Func_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _FuncMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitFuncMenu Event captured\n");
#endif

	// disable the menu

	DM_ShowFuncSelectMenu(DISABLE_FUNCMENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	_RefreshDisplay();

	eNewEvent = evIdle;
	return Idle_State;
}


/*
 *
 *	Business logic for AmplitudeAdjust events
 *
 */
eSystemState _GainMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainMenu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowGainSelectMenu(ENABLE_GAINMENU);

	// set the rotary encoder limits to 0-32 for this menu
	ENCODER_TIMER->CNT = GO_GetOutputGain();
	ENCODER_TIMER->ARR = 32;

	return Gain_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _GainMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainSet Event captured\n");
#endif

	GO_SetOutputToEncoder(SM_GetEncoderValue(ENCODER_REVERSE));

	eNewEvent = evYellowBtn;
	return Gain_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _GainMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitGainMenu Event captured\n");
#endif


	// disable the menu
	DM_ShowGainSelectMenu(DISABLE_GAINMENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	_RefreshDisplay();

	eNewEvent = evIdle;
	return Idle_State;
}

/*
 *
 *	Business logic for BiasMenu events
 *
 */
eSystemState _BiasMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("BiasMenu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowBiasSelectMenu(ENABLE_BIASMENU);

	// set the rotary encoder limits to 0-20 for this menu


	ENCODER_TIMER->ARR = BIAS_MAX;
	ENCODER_TIMER->CNT = BIAS_CENTER;

	return Bias_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _BiasMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("BiasSet Event captured\n");
#endif

	BO_ModifyOutput();

	eNewEvent = evRedBtn;
	return Bias_Menu_State;
}

/*
 *
 *
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

	ENCODER_TIMER->ARR = 1024;

	_RefreshDisplay();

	eNewEvent = evIdle;
	return Idle_State;
}

/*
 *
 *	event handler for main freq menu
 *
 */
eSystemState _FreqMainMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqMenu Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowFreqMenu(ENABLE_FREQ_MAIN_MENU);

	// set the rotary encoder limits to 0-? for this menu
//	ENCODER_TIMER->CNT = 0;
//	ENCODER_TIMER->ARR = 56;

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Main_Menu_State;
}


/*
 *
 *
 *
 */
eSystemState _FreqMainMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqSet Event captured\n");
#endif

	//FreqO_ModifyOutput();

	//eNewEvent = evGreenBtn;
	return Freq_Main_Menu_State;
}

/*
 *
 *
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
 *	event handler for main freq menu
 *
 */
eSystemState _FreqPresetMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Freq Preset Menu Entry Event captured\n");
#endif

	_RefreshDisplay();

	DM_ShowFreqMenu(ENABLE_FREQ_PRESET_MENU);

	// Always set the default preset to 100Hz
	ENCODER_TIMER->CNT = 44;
	FreqO_ApplyPreset(FPRESET_100HZ);
	ENCODER_TIMER->ARR = 56;

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Preset_Menu_State;
}


/*
 *
 *
 *
 */
eSystemState _FreqPresetMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqSet Event captured\n");
#endif

	FreqO_ModifyOutput();

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Preset_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _FreqPresetMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Menu Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

	// reset the encoder range

	//ENCODER_TIMER->ARR = 1024;

	// back to main freq menu
	eNewEvent = evGreenBtn;
	return Idle_State;
}

/*
 *
 *	event handler for main freq menu
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
 *
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
 *
 *
 */
eSystemState _FreqAdjustMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Adjust Menu Exit Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

	// reset the encoder range

	//ENCODER_TIMER->ARR = 1024;

	// back to main freq menu
	eNewEvent = evGreenBtn;
	return Idle_State;
}

/*
 *
 *	event handler for main freq menu
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
 *
 *
 */
eSystemState _FreqSweepMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Sweep Menu Exit Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	// back to main freq menu
	eNewEvent = evGreenBtn;
	return Idle_State;
}


/*
 *
 * 	Set by NVIC interrupt handlers
 *
 */
void EM_SetNewEvent(eSystemEvent pEvent)
{
	eNewEvent = pEvent;
}


/*
 *
 *
 *
 */
eSystemState EM_GetSystemState()
{
	return eNextState;
}



void _RefreshDisplay()
{
	// don't let the DisplayManager interrupt the LCD refresh
	HAL_TIM_Base_Stop_IT(&htim15);
	{
		DM_RefreshBackgroundLayout();
	}
	HAL_TIM_Base_Start_IT(&htim15);
}




