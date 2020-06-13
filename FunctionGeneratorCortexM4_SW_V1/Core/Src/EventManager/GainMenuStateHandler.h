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

eSystemState GainMainMenuEntryHandler();
eSystemState GainMainMenuInputHandler();
eSystemState GainMainMenuExitHandler();
eSystemState GainSignalMenuEntryHandler();
eSystemState GainSignalMenuInputHandler(eSystemEvent pEvent);
eSystemState GainSignalMenuExitHandler();
eSystemState GainAuxMenuEntryHandler();
eSystemState GainAuxMenuInputHandler();
eSystemState GainAuxMenuExitHandler();

#endif /* SRC_EVENTMANAGER_GAINMENUSTATEHANDLER_H_ */
