/*
 * OutputMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#include "DisplayManager.h"
#include "ToplevelMenuStateHandler.h"

#include "comp.h"
#include "dac.h"
#include "adc.h"

eToplevelMenu_Status eNextToplevelMenuStatus = 	ENABLE_TOPLEVEL_MAIN_MENU;

eToplevelMenu_Status ToplevelMenu_getStatus();
void ToplevelMenu_setStatus(eToplevelMenu_Status pStatus);


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelMainMenuEntryHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelMainMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	ToplevelMenu_setStatus(ENABLE_TOPLEVEL_MAIN_MENU);

	// stay in this state
	eNewEvent = evIdle;
	return Toplevel_Main_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelMainMenuInputHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelMainMenuInputHandler Event captured\n");
	#endif


	return Toplevel_Main_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelMainMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelMainMenuExitHandler Event captured\n");
	#endif

	ToplevelMenu_setStatus(DISABLE_TOPLEVEL_MENU);

	DM_RefreshScreen();

	#ifdef EVENT_MENU_DEBUG
		  printf("returning to Idle State\n");
	#endif

	eNewEvent = evIdle;
	return Idle_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelOutputMenuEntryHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelOutputMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	ToplevelMenu_setStatus(ENABLE_TOPLEVEL_OUTPUT_MENU);




	// stay in this state
	eNewEvent = evIdle;
	return Toplevel_Output_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelOutputMenuInputHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelOutputMenuInputHandler Event captured\n");
	#endif


	// stay in this state
	eNewEvent = evIdle;
	return Toplevel_Output_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelOutputMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelOutputMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	// disable the menu
	ToplevelMenu_setStatus(ENABLE_TOPLEVEL_MAIN_MENU);

	// back to main freq menu
	eNewEvent = evIdle;
	return Idle_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelInputMenuEntryHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelInputMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	ToplevelMenu_setStatus(ENABLE_TOPLEVEL_INPUT_MENU);




	// stay in this state
	eNewEvent = evIdle;
	return Toplevel_Input_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelInputMenuInputHandler(eSystemEvent pEvent)
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelInputMenuInputHandler Event captured\n");
	#endif


		switch(pEvent)
		{

			case evBlueBtn:

				// disable the trigger input
				IT_ArbitrateInputTrigger();

				break;

			case evGreenBtn:

				// cycle to the next mode
				IT_CycleInputTriggerMode();

				// disable and reset the trigger input
				ToplevelInputMenuInputHandler(evBlueBtn);
				// re-enable the trigger input for new mode
				ToplevelInputMenuInputHandler(evBlueBtn);
				break;

			default:
				break;
		}
	// stay in this menu state
	eNewEvent = evIdle;
	return Toplevel_Input_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelInputMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelInputMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	// disable the menu
	ToplevelMenu_setStatus(ENABLE_TOPLEVEL_MAIN_MENU);

	// back to main freq menu
	eNewEvent = evIdle;
	return Idle_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eToplevelMenu_Status ToplevelMenu_getStatus()
{
	return eNextToplevelMenuStatus;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void ToplevelMenu_setStatus(eToplevelMenu_Status pStatus)
{
	eNextToplevelMenuStatus = pStatus;
}


