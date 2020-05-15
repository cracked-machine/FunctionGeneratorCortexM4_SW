/*
 * DisplayManager.h
 *
 *  Created on: 3 May 2020
 *      Author: chris
 */

#ifndef INC_DISPLAYMANAGER_DISPLAYMANAGER_H_
#define INC_DISPLAYMANAGER_DISPLAYMANAGER_H_

#define ENCODER_DEBUG

#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

#include "SignalManager.h"
#include "EventManager.h"
#include "GainMenuStateHandler.h"
#include "FuncMenuStateHandler.h"
#include "FreqMenuStateHandler.h"
#include "BiasMenuStateHandler.h"

#include <stdint.h>




void DM_Init();
void DM_PostInit();
void DM_UpdateDisplay();

void DM_RefreshScreen();

void DM_ShowFuncMenu(eFuncMenu_Status pValue);
void DM_ShowGainMenu(eGainMenu_Status pValue);
void DM_ShowFreqMenu(eFreqMenu_Status pValue);
void DM_ShowBiasMenu(eBiasMenu_Status pValue);

void DM_SetErrorDebugMsg(char* msg);
int DM_AddDigitPadding(uint16_t num, char *buffer, uint16_t buflen);


// unused
int DM_DigitCount(int num);
void DM_TestScreen();
void DM_RegisterStrings();

#endif /* INC_DISPLAYMANAGER_DISPLAYMANAGER_H_ */
