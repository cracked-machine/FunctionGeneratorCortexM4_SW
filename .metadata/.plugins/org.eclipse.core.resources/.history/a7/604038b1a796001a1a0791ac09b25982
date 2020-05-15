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
 *  Used by DM_ShowFuncMenu()
 */
typedef enum
{
	DISABLE_FUNCMENU = 0x00U,
	ENABLE_FUNC_MAIN_MENU,
	ENABLE_FUNC_SIGNAL_MENU,
	ENABLE_FUNC_SYNC_MENU,

} eFuncMenu_Status;

eSystemState FuncMainMenuEntryHandler();
eSystemState FuncMainMenuInputHandler();
eSystemState FuncMainMenuExitHandler();
eSystemState FuncSignalMenuEntryHandler();
eSystemState FuncSignalMenuInputHandler();
eSystemState FuncSignalMenuExitHandler();
eSystemState FuncSyncMenuEntryHandler();
eSystemState FuncSyncMenuInputHandler();
eSystemState FuncSyncMenuExitHandler();

#endif /* SRC_EVENTMANAGER_FUNCMENUSTATEHANDLER_H_ */
