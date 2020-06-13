/*
 * FuncMenuStateHandler.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_FUNCMENUSTATEHANDLER_H_
#define SRC_EVENTMANAGER_FUNCMENUSTATEHANDLER_H_

#include "EventManager.h"

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
