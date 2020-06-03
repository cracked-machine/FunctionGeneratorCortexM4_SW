/*
 * FreqMenuStateHandler.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_FREQMENUSTATEHANDLER_H_
#define SRC_EVENTMANAGER_FREQMENUSTATEHANDLER_H_

#include "EventManager.h"
#include "FreqSweep.h"
/*
 * 	Sub menus should have their ExitHandlers set eXXXXMenu_Status to ENABLE_xxxx_MAIN_MENU
 */
typedef enum
{
	DISABLE_FREQ_MENU = 0x00U,
	ENABLE_FREQ_MAIN_MENU,
	ENABLE_FREQ_PRESET_MENU,
	ENABLE_FREQ_ADJUST_MENU,
	ENABLE_FREQ_SWEEP_MENU,
	ENABLE_FREQ_PRESCALER_MENU

} eFreqMenu_Status;



eFreqSweepModes active_sweep_mode;


float rate_coeff;

// these store shortest/longest ARR values that the sweep function will set to the OUTPUT_TIMER->ARR.
float sweep_lower_bounds_shortest_output_arr;		// higher freq
float sweep_upper_bounds_longest_output_arr;		// lower freq

float calculated_sweep_in_hertz;


eFreqMenu_Status FreqMenu_getStatus();

eSystemState FreqMainMenuEntryHandler();
eSystemState FreqMainMenuInputHandler();
eSystemState FreqMainMenuExitHandler();
eSystemState FreqPresetMenuEntryHandler();
eSystemState FreqPresetMenuInputHandler();
eSystemState FreqPresetMenuExitHandler();
eSystemState FreqAdjustMenuEntryHandler();
eSystemState FreqAdjustMenuInputHandler();
eSystemState FreqAdjustMenuExitHandler();
eSystemState FreqSweepMenuEntryHandler();
eSystemState FreqSweepMenuInputHandler(eSystemEvent pEvent);
eSystemState FreqSweepMenuExitHandler();
eSystemState FreqPrescalerMenuEntryHandler();
eSystemState FreqPrescalerMenuInputHandler();
eSystemState FreqPrescalerMenuExitHandler();
eFreqSweepModes FMSH_GetSweepMode();


#endif /* SRC_EVENTMANAGER_FREQMENUSTATEHANDLER_H_ */
