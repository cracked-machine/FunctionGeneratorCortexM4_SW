/*
 * EventManager.c
 *
 *  Created on: May 8, 2020
 *      Author: chris
 */


#include "EventManager.h"
#include "DisplayManager.h"
#include "SignalManager.h"



//#include "pysine.h"

#include "dac.h"
#include "tim.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

uint32_t last_enc_value = 0;

// public function protochannels
void _ProcessIdleStateEvents();

void _ProcessTopLevelOutputMenuStateEvents();
void _ProcessTopLevelInputMenuStateEvents();

void _ProcessFreqSweepMenuStateEvents();
void _ProcessFreqAdjustMenuState();
void _ProcessFreqPrescalerMenuStateEvents();
void _ProcessFreqPresetMenuStateEvents();
void _ProcessFreqMainMenuStateEvents();

void _ProcessGainAuxMenuStateEvents();
void _ProcessGainSignalMenuStateEvents();
void _ProcessGainMainMenuStateEvents();

void _ProcessFuncMainMenuStateEvents();
void _ProcessFuncSignalMenuStateEvents();
void _ProcessFuncAuxMenuStateEvents();

void _ProcessBiasMainMenuEvents();

void EM_SetNewEvent(eSystemEvent pEvent);



//uint8_t duty_adjust_mode = 0;

void EM_RefreshDisplay();

//uint32_t tmpDataTable[SINE_DATA_SIZE];

// state machine
eSystemState eNextState = Idle_State;
eSystemEvent eNewEvent = evIdle;





uint8_t mode = 0;

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

			_ProcessIdleStateEvents();
			break;

		case Toplevel_Output_Menu_State:

			_ProcessTopLevelOutputMenuStateEvents();
			break;

		case Toplevel_Input_Menu_State:

			_ProcessTopLevelInputMenuStateEvents();
			break;


// FUNC MENUS

		case Func_Main_Menu_State:

			_ProcessFuncMainMenuStateEvents();
			break;

		case Func_Signal_Menu_State:

			_ProcessFuncSignalMenuStateEvents();
			break;

		case Func_Aux_Menu_State:

			_ProcessFuncAuxMenuStateEvents();
			break;

// GAIN MENUS

		case Gain_Main_Menu_State:

			_ProcessGainMainMenuStateEvents();
			break;

		case Gain_Signal_Menu_State:

			_ProcessGainSignalMenuStateEvents();
			break;

		case Gain_Aux_Menu_State:

			_ProcessGainAuxMenuStateEvents();
			break;

// FREQ MENUS

		case Freq_Main_Menu_State:

			_ProcessFreqMainMenuStateEvents();
			break;

		case Freq_Preset_Menu_State:

			_ProcessFreqPresetMenuStateEvents();
			break;

		case Freq_Adjust_Menu_State:

			_ProcessFreqAdjustMenuState();
			break;

		case Freq_Prescaler_Menu_State:

			_ProcessFreqPrescalerMenuStateEvents();
			break;


		case Freq_Sweep_Menu_State:

			_ProcessFreqSweepMenuStateEvents();
			break;

// BIAS MENUS

		case Bias_Menu_State:

			_ProcessBiasMainMenuEvents();
			break;

		default:
			break;
	}

}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessIdleStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
	  printf("Idle_State\n");
	#endif

	if(eNewEvent == evBlueBtn)
	{
		eNextState = ToplevelOutputMenuEntryHandler();
	}
	if(eNewEvent == evGreenBtn)
	{
		eNextState = ToplevelInputMenuEntryHandler();
	}
	if(eNewEvent == evYellowBtn)
	{
		// no menu action
	}
	if(eNewEvent == evRedBtn)
	{
		// no menu action
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessTopLevelOutputMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
	  printf("Toplevel_Output_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderPush)
	{
		eNextState = ToplevelOutputMenuExitHandler();
	}
	if(eNewEvent == evBlueBtn)
	{
		//ToplevelMenu_setStatus(DISABLE_TOPLEVEL_MENU);
		eNextState = FuncMainMenuEntryHandler();
	}
	if(eNewEvent == evGreenBtn)
	{
		//ToplevelMenu_setStatus(DISABLE_TOPLEVEL_MENU);
		eNextState = FreqMainMenuEntryHandler();
	}
	if(eNewEvent == evYellowBtn)
	{
		//ToplevelMenu_setStatus(DISABLE_TOPLEVEL_MENU);
		eNextState = GainMainMenuEntryHandler();
	}
	if(eNewEvent == evRedBtn)
	{
		//ToplevelMenu_setStatus(DISABLE_TOPLEVEL_MENU);
		eNextState = BiasMenuEntryHandler();
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessTopLevelInputMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
	  printf("Toplevel_Input_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderPush)
	{
		eNextState = ToplevelInputMenuExitHandler();
	}
	if(eNewEvent == evBlueBtn)
	{
		eNextState = ToplevelInputMenuInputHandler(eNewEvent);
	}
	if(eNewEvent == evGreenBtn)
	{

		eNextState = ToplevelInputMenuInputHandler(eNewEvent);
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessFuncMainMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Func_Main_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderSet)
	{
		// No menu action
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = FuncMainMenuExitHandler();

	}
	if(eNewEvent == evBlueBtn)
	{
		eNextState = FuncSignalMenuEntryHandler();
	}
	if(eNewEvent == evGreenBtn)
	{
		eNextState = FuncAuxMenuEntryHandler();
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessFuncSignalMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Func_Signal_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderSet)
	{
		eNextState = FuncSignalMenuInputHandler();
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = FuncSignalMenuExitHandler();
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessFuncAuxMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Func_Aux_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderSet)
	{
		eNextState = FuncAuxMenuInputHandler();
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = FuncAuxMenuExitHandler();
	}
	if(eNewEvent == evYellowBtn)
	{
		eNextState = FuncAuxToggleDutyMode();
	}

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessGainMainMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Gain_Main_Menu_State\n");
	#endif
	if(eNewEvent == evEncoderSet)
	{
		// No menu action
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = GainMainMenuExitHandler();
		//ToplevelMenu_setStatus(ENABLE_TOPLEVEL_OUTPUT_MENU);
	}
	if(eNewEvent == evBlueBtn)
	{
		eNextState = GainSignalMenuEntryHandler();
	}
	if(eNewEvent == evGreenBtn)
	{
		eOutput_mode aux_output_func = SM_GetOutputChannel(AUX_CHANNEL)->func_profile->func;
		if(aux_output_func != PWM_FUNC_MODE)
			eNextState = GainAuxMenuEntryHandler();
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessGainSignalMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Gain_Signal_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderSet)
	{
		eNextState = GainSignalMenuInputHandler(evEncoderSet);
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = GainSignalMenuExitHandler();
	}
	if(eNewEvent == evBlueBtn)
	{
		eNextState = GainSignalMenuInputHandler(evBlueBtn);
	}
	if(eNewEvent == evGreenBtn)
	{
		eNextState = GainSignalMenuInputHandler(evGreenBtn);
	}
	if(eNewEvent == evYellowBtn)
	{
		eNextState = GainSignalMenuInputHandler(evYellowBtn);
	}
	if(eNewEvent == evRedBtn)
	{
		eNextState = GainSignalMenuInputHandler(evRedBtn);
	}

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessGainAuxMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Gain_Aux_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderSet)
	{
		eNextState = GainAuxMenuInputHandler();
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = GainAuxMenuExitHandler();
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessFreqMainMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Freq_Main_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderPush)
	{
		eNextState = FreqMainMenuExitHandler();
		//ToplevelMenu_setStatus(ENABLE_TOPLEVEL_OUTPUT_MENU);
	}
	if(eNewEvent == evBlueBtn)
	{
		eNextState = FreqPresetMenuEntryHandler();
	}
	if(eNewEvent == evGreenBtn)
	{
		eNextState = FreqAdjustMenuEntryHandler();
	}
	if(eNewEvent == evYellowBtn)
	{
		eNextState = FreqSweepMenuEntryHandler();
	}
	if(eNewEvent == evRedBtn)
	{
		eNextState = FreqPrescalerMenuEntryHandler();
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessFreqPresetMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Freq_Preset_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderSet)
	{
		eNextState = FreqPresetMenuInputHandler();
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = FreqPresetMenuExitHandler();
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessFreqAdjustMenuState()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Freq_Adjust_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderSet)
	{
		eNextState = FreqAdjustMenuInputHandler();
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = FreqAdjustMenuExitHandler();
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessFreqPrescalerMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Freq_Prescaler_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderSet)
	{
		eNextState = FreqPrescalerMenuInputHandler();
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = FreqPrescalerMenuExitHandler();
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessFreqSweepMenuStateEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Freq_Sweep_Menu_State\n");
	#endif

	if(eNewEvent == evBlueBtn)
	{
		// enable
		eNextState = FreqSweepMenuInputHandler(evSweepEnableBtn);
	}
	if(eNewEvent == evGreenBtn)
	{
		// direction
		eNextState = FreqSweepMenuInputHandler(evSweepModeBtn);
	}
	if(eNewEvent == evYellowBtn)
	{
		// set sweep speed
		eNextState = FreqSweepMenuInputHandler(evSweepSpeedBtn);
	}
	if(eNewEvent == evRedBtn)
	{
		// set lower/upper sweep limit
		eNextState = FreqSweepMenuInputHandler(evSweepLimitBtn);
	}
	if(eNewEvent == evEncoderSet)
	{
		eNextState = FreqSweepMenuInputHandler(evEncoderSweep);
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = FreqSweepMenuExitHandler();
	}

}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessBiasMainMenuEvents()
{
	#ifdef EVENT_MENU_DEBUG
		  printf("Bias_Menu_State\n");
	#endif

	if(eNewEvent == evEncoderSet)
	{
		eNextState = BiasMenuInputHandler(evEncoderSet);
	}
	if(eNewEvent == evEncoderPush)
	{
		eNextState = BiasMenuExitHandler();
		//ToplevelMenu_setStatus(ENABLE_TOPLEVEL_OUTPUT_MENU);
	}
	if(eNewEvent == evBlueBtn)
	{
		// enable
		eNextState = BiasMenuInputHandler(evBlueBtn);
	}
	if(eNewEvent == evGreenBtn)
	{
		// direction
		eNextState = BiasMenuInputHandler(evGreenBtn);
	}
	if(eNewEvent == evYellowBtn)
	{
		// set sweep speed
		eNextState = BiasMenuInputHandler(evYellowBtn);
	}
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






