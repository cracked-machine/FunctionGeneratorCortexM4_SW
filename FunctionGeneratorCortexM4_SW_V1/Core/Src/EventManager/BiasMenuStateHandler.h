/*
 * BiasMenuStateHandler.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_BIASMENUSTATEHANDLER_H_
#define SRC_EVENTMANAGER_BIASMENUSTATEHANDLER_H_

#include "EventManager.h"



/*
 * 	Used by DM_ShowBiasMenu()
 */
typedef enum
{
	DISABLE_BIAS_MENU = 0x00U,
	ENABLE_BIAS_MENU

} eBiasMenu_Status;


eBiasMenu_Status BiasMenu_getStatus();
eSystemState BiasMenuEntryHandler();
eSystemState BiasMenuInputHandler();
eSystemState BiasMenuExitHandler();

#endif /* SRC_EVENTMANAGER_BIASMENUSTATEHANDLER_H_ */
