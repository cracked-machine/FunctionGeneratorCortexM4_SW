/*
 * GainMenus.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_DISPLAYMANAGER_GAINMENUS_H_
#define SRC_DISPLAYMANAGER_GAINMENUS_H_

#include "GainMenuStateHandler.h"

void GainMenu_DrawMenu(eGainMenu_Status pMenu);

void GainMenu_DrawMainMenu();
void GainMenu_DrawSignalMenu();
void GainMenu_DrawSyncMenu();

#endif /* SRC_DISPLAYMANAGER_GAINMENUS_H_ */
