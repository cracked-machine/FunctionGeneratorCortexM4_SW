/*
 * InputTrigger.h
 *
 *  Created on: 3 Jun 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_INPUTTRIGGER_H_
#define SRC_SIGNALMANAGER_INPUTTRIGGER_H_

// Enumerations

typedef enum
{
	DISABLE_TRIGGER_INPUT 	= 	0U,
	ENABLE_TRIGGER_INPUT	= 	1U,
} eTriggerInput;

typedef enum
{
	//INPUT_TRIGGER_DISABLED = 0U,
	INPUT_TRIGGER_TIM,
	INPUT_TRIGGER_COMP,
	INPUT_TRIGGER_ADC
} eTriggerInputMode;


// Public functions

void 				IT_CycleInputTriggerMode();
void 				IT_ArbitrateInputTrigger();

eTriggerInput 		IT_GetTriggerStatus();
void 				IT_SetTriggerStatus(eTriggerInput newTriggerStatus);
eTriggerInputMode 	IT_GetActiveTriggerMode();
void 				IT_SetActiveTriggerMode(eTriggerInputMode newTriggerMode);

#endif /* SRC_SIGNALMANAGER_INPUTTRIGGER_H_ */
