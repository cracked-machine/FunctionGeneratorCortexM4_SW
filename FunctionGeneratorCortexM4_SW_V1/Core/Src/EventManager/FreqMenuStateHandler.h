/*
 * FreqMenuStateHandler.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_FREQMENUSTATEHANDLER_H_
#define SRC_EVENTMANAGER_FREQMENUSTATEHANDLER_H_

#include "EventManager.h"

/*
 * 	Sub menus should have their ExitHandlers set eXXXXMenu_Status to ENABLE_xxxx_MAIN_MENU
 */
typedef enum
{
	DISABLE_FREQ_MENU = 0x00U,
	ENABLE_FREQ_MAIN_MENU,
	ENABLE_FREQ_PRESET_MENU,
	ENABLE_FREQ_ADJUST_MENU,
	ENABLE_FREQ_SWEEP_MENU

} eFreqMenu_Status;

typedef enum
{
	SWEEP_MODE_UP = 0U,
	SWEEP_MODE_DOWN,
	SWEEP_MODE_BIDIR

} eFreqSweepModes;

eFreqSweepModes active_sweep_mode;

uint16_t min_arr;
uint32_t max_arr;
float rate_coeff;

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


#endif /* SRC_EVENTMANAGER_FREQMENUSTATEHANDLER_H_ */
