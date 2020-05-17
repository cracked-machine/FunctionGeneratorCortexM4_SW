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

uint32_t last_enc_value = 0;

// public function protochannels
void EM_SetNewEvent(eSystemEvent pEvent);





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


			#ifdef SWV_DEBUG_ENABLED
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

			#ifdef SWV_DEBUG_ENABLED
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

			#ifdef SWV_DEBUG_ENABLED
			  printf("Toplevel_Input_Menu_State\n");
			#endif

			if(eNewEvent == evEncoderPush)
			{
				eNextState = ToplevelInputMenuExitHandler();
			}
			if(eNewEvent == evBlueBtn)
			{
				//eNextState = ToplevelOutputMenuEntryHandler();
			}
			if(eNewEvent == evGreenBtn)
			{
				//eNextState = ToplevelInputMenuEntryHandler();
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


// FUNC MENUS

		case Func_Main_Menu_State:

			#ifdef SWV_DEBUG_ENABLED
				  printf("Func_Main_Menu_State\n");
			#endif

			if(eNewEvent == evEncoderSet)
			{
				// No menu action
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = FuncMainMenuExitHandler();
				ToplevelMenu_setStatus(ENABLE_TOPLEVEL_OUTPUT_MENU);
			}
			if(eNewEvent == evBlueBtn)
			{
				eNextState = FuncSignalMenuEntryHandler();
			}
			if(eNewEvent == evGreenBtn)
			{
				eNextState = FuncSyncMenuEntryHandler();
			}

			break;

		case Func_Signal_Menu_State:

			#ifdef SWV_DEBUG_ENABLED
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

		case Func_Sync_Menu_State:

			#ifdef SWV_DEBUG_ENABLED
				  printf("Func_Sync_Menu_State\n");
			#endif

			if(eNewEvent == evEncoderSet)
			{
				eNextState = FuncSyncMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = FuncSyncMenuExitHandler();
			}

			break;

// GAIN MENUS

		case Gain_Main_Menu_State:

			#ifdef SWV_DEBUG_ENABLED
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
				eNextState = GainSyncMenuEntryHandler();
			}

			break;

		case Gain_Signal_Menu_State:

			#ifdef SWV_DEBUG_ENABLED
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

		case Gain_Sync_Menu_State:

			#ifdef SWV_DEBUG_ENABLED
				  printf("Gain_Sync_Menu_State\n");
			#endif

			if(eNewEvent == evEncoderSet)
			{
				eNextState = GainSyncMenuInputHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = GainSyncMenuExitHandler();
			}

			break;

// FREQ MENUS

		case Freq_Main_Menu_State:

			#ifdef SWV_DEBUG_ENABLED
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

			break;

		case Freq_Preset_Menu_State:

			#ifdef SWV_DEBUG_ENABLED
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

			#ifdef SWV_DEBUG_ENABLED
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

		case Freq_Sweep_Menu_State:

			#ifdef SWV_DEBUG_ENABLED
				  printf("Freq_Sweep_Menu_State\n");
			#endif

			if(eNewEvent == evBlueBtn)
			{
				// enable
				eNextState = FreqSweepMenuInputHandler(evSweepEnable);

			}
			if(eNewEvent == evGreenBtn)
			{
				// center-aligned mode
				eNextState = FreqSweepMenuInputHandler(evSweepMode);

			}
			if(eNewEvent == evYellowBtn)
			{
				// direction
				//eNextState = FreqSweepMenuInputHandler();

			}
			if(eNewEvent == evRedBtn)
			{
				// no event action
			}
			if(eNewEvent == evEncoderSet)
			{
				eNextState = FreqSweepMenuInputHandler(evSweepSpeed);

			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = FreqSweepMenuExitHandler();
			}

			break;

// BIAS MENUS

		case Bias_Menu_State:

			#ifdef SWV_DEBUG_ENABLED
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






