/*
 * BiasMenuStateHandler.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_BIASMENUSTATEHANDLER_H_
#define SRC_EVENTMANAGER_BIASMENUSTATEHANDLER_H_

#include "EventManager.h"

eSystemState BiasMenuEntryHandler();
eSystemState BiasMenuInputHandler(eSystemEvent pEvent);
eSystemState BiasMenuExitHandler();

#endif /* SRC_EVENTMANAGER_BIASMENUSTATEHANDLER_H_ */
