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
 * 	Used by DM_ShowFreqMenu()
 */
typedef enum
{
	DISABLE_FREQ_MENU = 0x00U,
	ENABLE_FREQ_MAIN_MENU,
	ENABLE_FREQ_PRESET_MENU,
	ENABLE_FREQ_ADJUST_MENU,
	ENABLE_FREQ_SWEEP_MENU

} eFreqMenu_Status;



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
eSystemState FreqSweepMenuInputHandler();
eSystemState FreqSweepMenuExitHandler();


#endif /* SRC_EVENTMANAGER_FREQMENUSTATEHANDLER_H_ */
