/*
 * OutputMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#include "DisplayManager.h"
//#include "SignalManager.h"
#include <stdio.h>
#include <ToplevelMenuStateHandler.h>



eToplevelMenu_Status eNextToplevelMenuStatus = 	ENABLE_TOPLEVEL_MAIN_MENU;



eToplevelMenu_Status ToplevelMenu_getStatus()
{
	return eNextToplevelMenuStatus;
}

void ToplevelMenu_setStatus(eToplevelMenu_Status pStatus)
{
	eNextToplevelMenuStatus = pStatus;
}

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
	#ifdef SWV_DEBUG_ENABLED
		printf("ToplevelMainMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextToplevelMenuStatus = ENABLE_TOPLEVEL_MAIN_MENU;

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
	#ifdef SWV_DEBUG_ENABLED
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
	#ifdef SWV_DEBUG_ENABLED
		printf("ToplevelMainMenuExitHandler Event captured\n");
	#endif


	// disable the menu
	eNextToplevelMenuStatus = DISABLE_TOPLEVEL_MENU;

	// reset the encoder range

	DM_RefreshScreen();

	#ifdef SWV_DEBUG_ENABLED
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
	#ifdef SWV_DEBUG_ENABLED
		printf("ToplevelOutputMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextToplevelMenuStatus = ENABLE_TOPLEVEL_OUTPUT_MENU;




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
	#ifdef SWV_DEBUG_ENABLED
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
	#ifdef SWV_DEBUG_ENABLED
		printf("ToplevelOutputMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	// disable the menu
	eNextToplevelMenuStatus = ENABLE_TOPLEVEL_MAIN_MENU;

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
	#ifdef SWV_DEBUG_ENABLED
		printf("ToplevelInputMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextToplevelMenuStatus = ENABLE_TOPLEVEL_INPUT_MENU;




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
eSystemState ToplevelInputMenuInputHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("ToplevelInputMenuInputHandler Event captured\n");
	#endif


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
eSystemState ToplevelInputMenuExitHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("ToplevelInputMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	// disable the menu
	eNextToplevelMenuStatus = ENABLE_TOPLEVEL_MAIN_MENU;

	// back to main freq menu
	eNewEvent = evIdle;
	return Idle_State;
}