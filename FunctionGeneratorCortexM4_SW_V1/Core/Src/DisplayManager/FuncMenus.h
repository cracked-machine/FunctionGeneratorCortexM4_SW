/*
 * FuncMenu.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_DISPLAYMANAGER_FUNCMENUS_H_
#define SRC_DISPLAYMANAGER_FUNCMENUS_H_

#include "FuncMenuStateHandler.h"
#include "DisplayManager.h"

void FuncMenu_DrawMenu(eSystemState pMenu);

void FuncMenu_DrawMainMenu();
void FuncMenu_DrawOutputMenu(eOutputChannel_t pOutChan);

#endif /* SRC_DISPLAYMANAGER_FUNCMENUS_H_ */
