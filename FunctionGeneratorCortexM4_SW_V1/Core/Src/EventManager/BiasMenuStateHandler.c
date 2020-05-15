/*
 * BiasMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include "BiasMenuStateHandler.h"

#include "DisplayManager.h"
#include "SignalManager.h"
#include <stdio.h>

eBiasMenu_Status eNextBiasMenuStatus =	DISABLE_BIAS_MENU;

eBiasMenu_Status BiasMenu_getStatus()
{
	return eNextBiasMenuStatus;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState BiasMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("BiasMenu Event captured\n");
#endif

	DM_RefreshScreen();

	eNextBiasMenuStatus = ENABLE_BIAS_MENU;

	ENCODER_TIMER->ARR = BIAS_MAX;
	ENCODER_TIMER->CNT = BO_GetDcBiasEncoderValue();

	eNewEvent = evIdle;
	return Bias_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState BiasMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("BiasSet Event captured\n");
#endif

	BO_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));

	eNewEvent = evIdle;
	return Bias_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState BiasMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitBiasMenu Event captured\n");
#endif


	// disable the menu
	eNextBiasMenuStatus = DISABLE_BIAS_MENU;

	// reset the encoder range

	//ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Idle_State;
}
