/*
 * FuncMenu.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_DISPLAYMANAGER_FUNCMENUS_H_
#define SRC_DISPLAYMANAGER_FUNCMENUS_H_

#include "FuncMenuStateHandler.h"

void FuncMenu_DrawMenu(eFuncMenu_Status pMenu);

void FuncMenu_DrawMainMenu();
void FuncMenu_DrawSignalMenu();
void FuncMenu_DrawSyncMenu();

#endif /* SRC_DISPLAYMANAGER_FUNCMENUS_H_ */
