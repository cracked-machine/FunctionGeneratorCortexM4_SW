/*
 * GainMenus.c
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
	ILI9341_Draw_Text("GAIN MAIN MENU", 	10, 10, WHITE, 3, BLACK);
 	// coloured menu btn labels
	ILI9341_Draw_Text("SIGNAL", 10, 210, BLACK, 2, DARKCYAN);
	ILI9341_Draw_Text("SYNC", 100, 210, BLACK, 2, DARKGREEN);
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
	ILI9341_Draw_Text("SELECT SIGNAL GAIN", 10, 10, WHITE, 3, BLACK);
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
	ILI9341_Draw_Text("SELECT SYNC GAIN", 10, 10, WHITE, 3, BLACK);
}
