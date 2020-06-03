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
			break;

		case Toplevel_Output_Menu_State:

			#ifdef EVENT_MENU_DEBUG
			  printf("Toplevel_Output_Menu_State\n");
			#endif

			if(eNewEvent == evEncoderPush)
			{
				eNextState = ToplevelOutputMenuExitHandler();
			}
			if(eNewEvent == evBlueBtn)
			{
				ToplevelMenu_setStatus(DISABLE_TOPLEVEL_MENU);
				eNextState = FuncMainMenuEntryHandler();
			}
			if(eNewEvent == evGreenBtn)
			{
				ToplevelMenu_setStatus(DISABLE_TOPLEVEL_MENU);
				eNextState = FreqMainMenuEntryHandler();
			}
			if(eNewEvent == evYellowBtn)
			{
				ToplevelMenu_setStatus(DISABLE_TOPLEVEL_MENU);
				eNextState = GainMainMenuEntryHandler();
			}
			if(eNewEvent == evRedBtn)
			{
				ToplevelMenu_setStatus(DISABLE_TOPLEVEL_MENU);
				eNextState = BiasMenuEntryHandler();
			}
			break;

		case Toplevel_Input_Menu_State:

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
			break;


// FUNC MENUS

		case Func_Main_Menu_State:

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

			break;

		case Func_Signal_Menu_State:

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


			break;

		case Func_Aux_Menu_State:

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

			break;

// GAIN MENUS

		case Gain_Main_Menu_State:

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
				ToplevelMenu_setStatus(ENABLE_TOPLEVEL_OUTPUT_MENU);
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

			break;

		case Gain_Signal_Menu_State:

			#ifdef EVENT_MENU_DEBUG
				  printf("Gain_Signal_Menu_State\n");
			#endif

			if(eNewEvent == evEncoderSet)
			{
				eNextState = GainSignalMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = GainSignalMenuExitHandler();
			}

			break;

		case Gain_Aux_Menu_State:

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

			break;

// FREQ MENUS

		case Freq_Main_Menu_State:

			#ifdef EVENT_MENU_DEBUG
				  printf("Freq_Main_Menu_State\n");
			#endif

			if(eNewEvent == evEncoderPush)
			{
				eNextState = FreqMainMenuExitHandler();
				ToplevelMenu_setStatus(ENABLE_TOPLEVEL_OUTPUT_MENU);
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

			break;

		case Freq_Preset_Menu_State:

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
			break;

		case Freq_Adjust_Menu_State:

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
			break;

		case Freq_Prescaler_Menu_State:

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
			break;


		case Freq_Sweep_Menu_State:

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

			break;

// BIAS MENUS

		case Bias_Menu_State:

			#ifdef EVENT_MENU_DEBUG
				  printf("Bias_Menu_State\n");
			#endif

			if(eNewEvent == evEncoderSet)
			{
				eNextState = BiasMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = BiasMenuExitHandler();
				ToplevelMenu_setStatus(ENABLE_TOPLEVEL_OUTPUT_MENU);
			}

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






