/*
 * DisplayManager.h
 *
 *  Created on: 3 May 2020
 *      Author: chris
 */

#ifndef INC_DISPLAYMANAGER_DISPLAYMANAGER_H_
#define INC_DISPLAYMANAGER_DISPLAYMANAGER_H_

#define ENCODER_DEBUG

#include <stdint.h>

/*
typedef enum
{
	Func_Adjust_mode,				// edit output function
	Freq_Adjust_mode,				// edit output frequency
	Ampl_Adjust_mode,				// edit output amplitude
	Bias_Adjust_mode				// edit output DC bias

} eDisplay_Mode;
*/

typedef enum
{
	DISABLE_FUNCMENU = 0x00U,
	ENABLE_FUNCMENU

} eFuncMenu_Status;

typedef enum
{
	DISABLE_GAINMENU = 0x00U,
	ENABLE_GAINMENU

} eGainMenu_Status;

typedef enum
{
	DISABLE_BIASMENU = 0x00U,
	ENABLE_BIASMENU

} eBiasMenu_Status;

typedef enum
{
	DISABLE_FREQ_MENU = 0x00U,
	ENABLE_FREQ_MAIN_MENU,
	ENABLE_FREQ_PRESET_MENU,
	ENABLE_FREQ_ADJUST_MENU,
	ENABLE_FREQ_SWEEP_MENU

} eFreqMenu_Status;

void DM_Init();
void DM_PostInit();
void DM_UpdateDisplay();

void DM_RefreshBackgroundLayout();
int DM_AddDigitPadding(uint16_t num, char *buffer, uint16_t buflen);

//void DM_SetDisplayMode(eDisplay_Mode pMode);
void DM_ShowFuncSelectMenu(eFuncMenu_Status pValue);
void DM_ShowGainSelectMenu(eGainMenu_Status pValue);


void DM_ShowFreqMenu(eFreqMenu_Status pValue);



void DM_ShowBiasSelectMenu(eBiasMenu_Status pValue);

// unused
int DM_DigitCount(int num);
void DM_TestScreen();
void DM_RegisterStrings();

#endif /* INC_DISPLAYMANAGER_DISPLAYMANAGER_H_ */
