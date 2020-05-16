/*
 * GainMenuStateHandler.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_GAINMENUSTATEHANDLER_H_
#define SRC_EVENTMANAGER_GAINMENUSTATEHANDLER_H_

#include "EventManager.h"

/*
 * 	Sub menus should have their ExitHandlers set eXXXXMenu_Status to ENABLE_xxxx_MAIN_MENU
 */
typedef enum
{
	DISABLE_GAIN_MENU = 0x00U,
	ENABLE_GAIN_MAIN_MENU,
	ENABLE_GAIN_SIGNAL_MENU,
	ENABLE_GAIN_SYNC_MENU,

} eGainMenu_Status;


eGainMenu_Status GainMenu_getStatus();

eSystemState GainMainMenuEntryHandler();
eSystemState GainMainMenuInputHandler();
eSystemState GainMainMenuExitHandler();
eSystemState GainSignalMenuEntryHandler();
eSystemState GainSignalMenuInputHandler();
eSystemState GainSignalMenuExitHandler();
eSystemState GainSyncMenuEntryHandler();
eSystemState GainSyncMenuInputHandler();
eSystemState GainSyncMenuExitHandler();

#endif /* SRC_EVENTMANAGER_GAINMENUSTATEHANDLER_H_ */
