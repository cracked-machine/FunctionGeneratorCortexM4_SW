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
eSystemState _FuncMenuHandler();
eSystemState _FuncSetHandler();
eSystemState _ExitFuncMenuHandler();

eSystemState _GainMenuHandler();
eSystemState _GainSetHandler();
eSystemState _ExitGainMenuHandler();

eSystemState _FreqMenuHandler();
eSystemState _FreqSetHandler();
eSystemState _ExitFreqMenuHandler();

eSystemState _BiasMenuHandler();
eSystemState _BiasSetHandler();
eSystemState _ExitBiasMenuHandler();

eSystemState _AdjustConfirmedHandler();



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
			if(eNewEvent == evFuncMenu)
			{
				eNextState = _FuncMenuHandler();
			}
			if(eNewEvent == evFreqMenu)
			{
				eNextState = _FreqMenuHandler();
			}
			if(eNewEvent == evGainMenu)
			{
				eNextState = _GainMenuHandler();
			}
			if(eNewEvent == evBiasMenu)
			{
				eNextState = _BiasMenuHandler();
			}

			break;

		case Func_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _FuncSetHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _ExitFuncMenuHandler();
			}
			break;

		case Gain_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _GainSetHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _ExitGainMenuHandler();
			}
			break;

		case Freq_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _FreqSetHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _ExitFreqMenuHandler();
			}
			break;

		case Bias_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _BiasSetHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _ExitBiasMenuHandler();
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
eSystemState _FuncMenuHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("FunctionMenu Event captured\n");
#endif

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
eSystemState _FuncSetHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("FunctionAdjust Event captured\n");
#endif

	FuncO_ModifyOutput();
	eNewEvent = evFuncMenu;
	return Func_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _ExitFuncMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitFuncMenu Event captured\n");
#endif

	// disable the menu
	DM_ShowFuncSelectMenu(DISABLE_FUNCMENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	// don't let the DisplayManager interrupt the LCD refresh
	HAL_TIM_Base_Stop_IT(&htim15);
	{
		DM_RefreshBackgroundLayout();
	}
	HAL_TIM_Base_Start_IT(&htim15);

	eNewEvent = evIdle;
	return Idle_State;
}


/*
 *
 *	Business logic for AmplitudeAdjust events
 *
 */
eSystemState _GainMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainMenu Event captured\n");
#endif
	DM_ShowGainSelectMenu(ENABLE_GAINMENU);

	// set the rotary encoder limits to 0-20 for this menu
	ENCODER_TIMER->CNT = 7;
	ENCODER_TIMER->ARR = 32;

	return Gain_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _GainSetHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainSet Event captured\n");
#endif

	GO_ModifyOutput();

	eNewEvent = evGainMenu;
	return Gain_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _ExitGainMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitGainMenu Event captured\n");
#endif


	// disable the menu
	DM_ShowGainSelectMenu(DISABLE_GAINMENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	// don't let the DisplayManager interrupt the LCD refresh
	HAL_TIM_Base_Stop_IT(&htim15);
	{
		DM_RefreshBackgroundLayout();
	}
	HAL_TIM_Base_Start_IT(&htim15);

	eNewEvent = evIdle;
	return Idle_State;
}

/*
 *
 *	Business logic for BiasMenu events
 *
 */
eSystemState _BiasMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("BiasMenu Event captured\n");
#endif
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
eSystemState _BiasSetHandler()
{
#ifdef EM_SWV_DEBUG
	printf("BiasSet Event captured\n");
#endif

	BO_ModifyOutput();

	eNewEvent = evBiasMenu;
	return Bias_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _ExitBiasMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitBiasMenu Event captured\n");
#endif


	// disable the menu
	DM_ShowBiasSelectMenu(DISABLE_BIASMENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	// don't let the DisplayManager interrupt the LCD refresh
	HAL_TIM_Base_Stop_IT(&htim15);
	{
		DM_RefreshBackgroundLayout();
	}
	HAL_TIM_Base_Start_IT(&htim15);

	eNewEvent = evIdle;
	return Idle_State;
}

/*
 *
 *	Business logic for FREQ MENU events
 *
 */
eSystemState _FreqMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqMenu Event captured\n");
#endif
	DM_ShowFreqSelectMenu(ENABLE_FREQMENU);

	// set the rotary encoder limits to 0-20 for this menu
	ENCODER_TIMER->CNT = TIM8->ARR;
	ENCODER_TIMER->ARR = FREQ_ENCODER_MAX;

	return Freq_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _FreqSetHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqSet Event captured\n");
#endif

	FreqO_ModifyOutput();

	eNewEvent = evFreqMenu;
	return Freq_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _ExitFreqMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitFreqMenu Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqSelectMenu(DISABLE_FREQMENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	// don't let the DisplayManager interrupt the LCD refresh
	HAL_TIM_Base_Stop_IT(&htim15);
	{
		DM_RefreshBackgroundLayout();
	}
	HAL_TIM_Base_Start_IT(&htim15);

	eNewEvent = evIdle;
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








