/*
 * GainMenus.h
 *
 *	Declares draw functions for Gain menu and its sub menus: GainSignal and GainAux
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_DISPLAYMANAGER_GAINMENUS_H_
#define SRC_DISPLAYMANAGER_GAINMENUS_H_

#include "GainMenuStateHandler.h"

void GainMenu_DrawMenu(eSystemState pMenu);

void GainMenu_DrawMainMenu();
void GainMenu_DrawSignalMenu();
void GainMenu_DrawAuxMenu();

#endif /* SRC_DISPLAYMANAGER_GAINMENUS_H_ */
