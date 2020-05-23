/*
 * GainMenuStateHandler.h
 *
 *	Defines Gain menu and its sub menus: GainSignal and GainAux
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
	ENABLE_GAIN_Aux_MENU,

} eGainMenu_Status;


eGainMenu_Status GainMenu_getStatus();

eSystemState GainMainMenuEntryHandler();
eSystemState GainMainMenuInputHandler();
eSystemState GainMainMenuExitHandler();
eSystemState GainSignalMenuEntryHandler();
eSystemState GainSignalMenuInputHandler();
eSystemState GainSignalMenuExitHandler();
eSystemState GainAuxMenuEntryHandler();
eSystemState GainAuxMenuInputHandler();
eSystemState GainAuxMenuExitHandler();

#endif /* SRC_EVENTMANAGER_GAINMENUSTATEHANDLER_H_ */
