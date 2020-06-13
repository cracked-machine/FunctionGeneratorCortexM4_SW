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

eFreqSweepModes active_sweep_mode;

float rate_coeff;

// these store shortest/longest ARR values that the sweep function will set to the OUTPUT_TIMER->ARR.
float sweep_lower_bounds_shortest_output_arr;		// higher freq
float sweep_upper_bounds_longest_output_arr;		// lower freq

float calculated_sweep_in_hertz;

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
