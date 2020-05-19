/*
 * ToplevelMenus.c
 *
 *	Defines draw functions for TopLevel menu and its sub menus: Output and Input
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include "ToplevelMenus.h"

#include "DisplayManager.h"

#include <stdio.h>

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void ToplevelMenu_DrawMenu(eToplevelMenu_Status pMenu)
{
	switch(pMenu)
	{
		case ENABLE_TOPLEVEL_MAIN_MENU:
			ToplevelMenu_DrawMainMenu();
			break;
		case ENABLE_TOPLEVEL_OUTPUT_MENU:
			ToplevelMenu_DrawOutputMenu();
			break;
		case ENABLE_TOPLEVEL_INPUT_MENU:
			ToplevelMenu_DrawInputMenu();
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
void ToplevelMenu_DrawMainMenu()
{
	// Top Level screen
	#ifdef SWV_DEBUG_ENABLED
		  printf("Drawing Main screen\n");
	#endif

	// Main screen
	//ILI9341_Draw_Text("SIGNAL GENERATOR", 	10, 10, WHITE, 2, BLACK);

	DM_DisplayFormattedOutput();

	ILI9341_Draw_Text("OUTPUT", 6, 210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("INPUT", 93, 210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("    ", 175, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("    ", 260, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);


}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void ToplevelMenu_DrawOutputMenu()
{
	ILI9341_Draw_Text("OUT->", 10, 10, BREADTRAIL_FGCOLOUR, 2, BREADTRAIL_BGCOLOUR);

	DM_DisplayFormattedOutput();

	ILI9341_Draw_Text("FUNC", 13,  210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("FREQ", 99,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("GAIN", 176, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("OFFSET", 245, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void ToplevelMenu_DrawInputMenu()
{
	ILI9341_Draw_Text("IN->", 10, 10, BREADTRAIL_FGCOLOUR, 2, BREADTRAIL_BGCOLOUR);

	DM_DisplayFormattedOutput();
}