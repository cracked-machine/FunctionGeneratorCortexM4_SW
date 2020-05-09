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

typedef enum
{
	Sine_Out_Mode,
	Square_Out_Mode,
	Saw_Out_Mode,
	RevSaw_Out_Mode,
	Triangle_Out_Mode,
	Impulse_Out_Mode

} eOutput_mode;

typedef enum
{
	Zero_Gain = 0U,
	One_Gain,
	Two_Gain,
	Three_Gain,
	Four_Gain,
	Five_Gain,
	Six_Gain,
	Seven_Gain

} eOutput_gain;


void EM_SetNewEvent(eSystemEvent pEvent);
void EM_ProcessEvent();

eOutput_mode EM_GetOutputMode();
void EM_SetOutputMode(eOutput_mode pNewMode);

eOutput_gain EM_GetOutputGain();
void EM_SetOutputGain(eOutput_gain pNewGain);

uint32_t EM_GetOutputFreq();


uint32_t EM_GetOutputBias();


void EM_SetEncoderValue(uint32_t pValue);
eSystemState EM_GetSystemState();

#endif /* SRC_EVENTMANAGER_EVENTMANAGER_H_ */
