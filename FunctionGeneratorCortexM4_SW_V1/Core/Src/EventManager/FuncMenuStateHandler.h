/*
 * FuncMenuStateHandler.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_FUNCMENUSTATEHANDLER_H_
#define SRC_EVENTMANAGER_FUNCMENUSTATEHANDLER_H_

#include "EventManager.h"

/*
 *  Sub menus should have their ExitHandlers set eXXXXMenu_Status to ENABLE_xxxx_MAIN_MENU
 */
typedef enum
{
	DISABLE_FUNC_MENU = 0x00U,
	ENABLE_FUNC_MAIN_MENU,
	ENABLE_FUNC_SIGNAL_MENU,
	ENABLE_FUNC_AUX_MENU,

} eFuncMenu_Status;

eFuncMenu_Status FuncMenu_getStatus();

eSystemState FuncMainMenuEntryHandler();
eSystemState FuncMainMenuInputHandler();
eSystemState FuncMainMenuExitHandler();

eSystemState FuncSignalMenuEntryHandler();
eSystemState FuncSignalMenuInputHandler();
eSystemState FuncSignalToggleDutyMode();
eSystemState FuncSignalMenuExitHandler();

eSystemState FuncAuxMenuEntryHandler();
eSystemState FuncAuxMenuInputHandler();
eSystemState FuncAuxToggleDutyMode();
eSystemState FuncAuxMenuExitHandler();



#endif /* SRC_EVENTMANAGER_FUNCMENUSTATEHANDLER_H_ */
