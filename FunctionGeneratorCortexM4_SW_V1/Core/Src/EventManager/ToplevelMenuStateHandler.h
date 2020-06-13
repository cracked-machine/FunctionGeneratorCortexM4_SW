/*
 * ToplevelMenuStateHandler.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_TOPLEVELMENUSTATEHANDLER_H_
#define SRC_EVENTMANAGER_TOPLEVELMENUSTATEHANDLER_H_

#include "EventManager.h"


eSystemState ToplevelMainMenuEntryHandler();
eSystemState ToplevelMainMenuInputHandler();
eSystemState ToplevelMainMenuExitHandler();

eSystemState ToplevelOutputMenuEntryHandler();
eSystemState ToplevelOutputMenuInputHandler();
eSystemState ToplevelOutputMenuExitHandler();

eSystemState ToplevelInputMenuEntryHandler();
eSystemState ToplevelInputMenuInputHandler(eSystemEvent pEvent);
eSystemState ToplevelInputMenuExitHandler();



#endif /* SRC_EVENTMANAGER_TOPLEVELMENUSTATEHANDLER_H_ */
