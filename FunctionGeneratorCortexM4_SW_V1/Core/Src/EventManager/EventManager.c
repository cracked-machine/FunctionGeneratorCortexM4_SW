/*
 * EventManager.c
 *
 *  Created on: May 8, 2020
 *      Author: chris
 */


#include "EventManager.h"
#include "DisplayManager.h"

#include "dac.h"
#include "tim.h"

#include <stdio.h>

#include "pysine.h"
#include "pysquare.h"
#include "pyunitimpulse.h"
#include "pysaw.h"
#include "pysaw_rev.h"
#include "pytriangle.h"

// public function prototypes
void EM_SetNewEvent(eSystemEvent pEvent);
eOutput_mode EM_GetOutputMode();

// private function prototypes
void _ClearEvent();
eSystemState _FuncMenuHandler();
eSystemState _FuncSetHandler();
eSystemState _FreqMenuHandler();
eSystemState _AmplMenuHandler();
eSystemState _BiasMenuHandler();
eSystemState _AdjustConfirmedHandler();
eSystemState _ExitFuncMenuHandler();

// state machine
eSystemState eNextState = Idle_State;
eSystemEvent eNewEvent = evIdle;

// function output mode
eOutput_mode eNewOutMode = Sine_Out_Mode;

// rotary encoder value
uint32_t newRotEncoderValue = 0;
uint32_t oldRotEncoderValue = 0;

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
			if(eNewEvent == evAmplMenu)
			{
				eNextState = _AmplMenuHandler();
			}
			if(eNewEvent == evBiasMenu)
			{
				eNextState = _BiasMenuHandler();
			}
			if(eNewEvent == evAdjustConfirmed)
			{
				eNextState = _AdjustConfirmedHandler();
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
	TIM1->ARR = 20;

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

	switch(TIM1->CNT)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			eNewOutMode = Sine_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, sine_data_table, SINE_DATA_SIZE, DAC_ALIGN_12B_R);
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			eNewOutMode = Square_Out_Mode;

			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, square_data_table, SQUARE_DATA_SIZE, DAC_ALIGN_12B_R);

			break;
		case 8:
		case 9:
		case 10:
		case 11:
			eNewOutMode = Saw_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, saw_data_table, SAW_DATA_SIZE, DAC_ALIGN_12B_R);
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			eNewOutMode = RevSaw_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, saw_rev_data_table, SAW_REV_DATA_SIZE, DAC_ALIGN_12B_R);
			break;
		case 16:
		case 17:
		case 18:
		case 19:
			eNewOutMode = Triangle_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, triangle_data_table, TRIANGLE_DATA_SIZE, DAC_ALIGN_12B_R);
			break;
		case 20:
		case 21:
		case 22:
		case 23:
			eNewOutMode = Impulse_Out_Mode;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, unitimpulse_data_table, UNITIMPULSE_DATA_SIZE, DAC_ALIGN_12B_R);
			break;
	}
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
	TIM1->ARR = 1024;

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
 *	Business logic for FreqAdjust events
 *
 */
eSystemState _FreqMenuHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("FreqMenu Event captured\n");
#endif

	return Idle_State;
}

/*
 *
 *	Business logic for AmplitudeAdjust events
 *
 */
eSystemState _AmplMenuHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("AmplitudeMenu Event captured\n");
#endif

	return Idle_State;
}

/*
 *
 *	Business logic for BiasAdjust events
 *
 */
eSystemState _BiasMenuHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("BiasMenu Event captured\n");
#endif

	return Idle_State;
}

/*
 *
 *	Business logic for AdjustConfirmed events
 *
 */
eSystemState _AdjustConfirmedHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("AdjustConfirmed Event captured\n");
#endif

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
eOutput_mode EM_GetOutputMode()
{
	return eNewOutMode;
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

/*
 *
 *
 *
 */
void EM_SetEncoderValue(uint32_t pValue)
{
	newRotEncoderValue = pValue;


}
