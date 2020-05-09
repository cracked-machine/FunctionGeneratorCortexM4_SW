/*
 * EventManager.h
 *
 *  Created on: May 8, 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_EVENTMANAGER_H_
#define SRC_EVENTMANAGER_EVENTMANAGER_H_

#include <stdint.h>

#define EM_SWV_DEBUG

typedef enum
{
	Idle_State = 0x00U,		// main display
	Func_Menu_State,
	Gain_Menu_State,
	Freq_Menu_State,
	Bias_Menu_State

} eSystemState;

typedef enum
{
	evIdle,						// default

	evFuncMenu,					// user presses blue "function" menu button
	evFreqMenu,					// user presses green "freq" menu button
	evGainMenu,					// user presses yellow "Ampl" menu button
	evBiasMenu,					// user presses red "bias" menu button

	evEncoderSet,				// user turns rotary encoder
	evEncoderPush,				// user presses button. return to main screen. All menus closed.

	evAdjustConfirmed			// user presses rotary encoder confirmation button

} eSystemEvent;



void EM_ProcessEvent();
void EM_SetNewEvent(eSystemEvent pEvent);
eSystemState EM_GetSystemState();

#endif /* SRC_EVENTMANAGER_EVENTMANAGER_H_ */