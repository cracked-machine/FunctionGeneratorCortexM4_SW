/*
 * GainMenus.c
 *
 *	Defines draw functions for Gain menu and its sub menus: GainSignal and GainSync
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include "GainMenus.h"

#include "DisplayManager.h"

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void GainMenu_DrawMenu(eGainMenu_Status pMenu)
{
	switch(pMenu)
	{
		case ENABLE_GAIN_MAIN_MENU:
			GainMenu_DrawMainMenu();
			break;
		case ENABLE_GAIN_SIGNAL_MENU:
			GainMenu_DrawSignalMenu();
			break;
		case ENABLE_GAIN_SYNC_MENU:
			GainMenu_DrawSyncMenu();
			break;

		default:
			break;

	}
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void GainMenu_DrawMainMenu()
{

	ILI9341_Draw_Text("OUT->GAIN", 	10, 10, WHITE, 2, BLACK);

	DM_DisplayFormattedOutput();

	// coloured menu btn labels
	ILI9341_Draw_Text("SIGNAL", 5, 210, BLACK, 2, DARKCYAN);
	ILI9341_Draw_Text("SYNC",97, 210, BLACK, 2, DARKGREEN);
	ILI9341_Draw_Text("    ", 175, 210, BLACK, 2, YELLOW);
	ILI9341_Draw_Text("    ", 260, 210, BLACK, 2, RED);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void GainMenu_DrawSignalMenu()
{
	ILI9341_Draw_Text("OUT->GAIN->SIG", 10, 10, WHITE, 2, BLACK);

	DM_DisplayFormattedOutput();
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void GainMenu_DrawSyncMenu()
{
	ILI9341_Draw_Text("OUT->GAIN->SYNC", 10, 10, WHITE, 2, BLACK);

	DM_DisplayFormattedOutput();
}
