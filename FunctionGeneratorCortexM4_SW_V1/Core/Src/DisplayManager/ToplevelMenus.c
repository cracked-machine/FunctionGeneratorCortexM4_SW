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

#include "comp.h"

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
	#ifdef EVENT_MENU_DEBUG
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

	ILI9341_Draw_Text("FUNC", 15,  210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("FREQ", 98,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
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
	ILI9341_Draw_Text("TRIGGER:", 	10, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
	if(isTriggerInputEnabled)
	{
		ILI9341_Draw_Text("ON", 	150, 50,  HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);
		ILI9341_Draw_Text("OFF", 	200, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
	}
	else
	{
		ILI9341_Draw_Text("ON", 	150, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
		ILI9341_Draw_Text("OFF", 	200, 50,  HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);
	}


	ILI9341_Draw_Text("MODE:", 	10, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
	if(activeInputerTriggerMode == INPUT_TRIGGER_TIM)
	{
		ILI9341_Draw_Text("TIM", 	150, 70,  HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);
		ILI9341_Draw_Text("COMP", 	200, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
		ILI9341_Draw_Text("ADC", 	270, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

		ILI9341_Draw_Text("     ", 150, 100,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
	}
	else if(activeInputerTriggerMode == INPUT_TRIGGER_COMP)
	{
		ILI9341_Draw_Text("TIM", 	150, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
		ILI9341_Draw_Text("COMP", 	200, 70,  HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);
		ILI9341_Draw_Text("ADC", 	270, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

		char comp_text[20] = "";
		snprintf(comp_text, sizeof(comp_text), "%lu V", HAL_COMP_GetOutputLevel(&hcomp1));

		ILI9341_Draw_Text(comp_text, 150, 100,  HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);
	}
	else if(activeInputerTriggerMode == INPUT_TRIGGER_ADC)
	{
		ILI9341_Draw_Text("TIM", 	150, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
		ILI9341_Draw_Text("COMP", 	200, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
		ILI9341_Draw_Text("ADC", 	270, 70,  HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);

		ILI9341_Draw_Text("     ", 150, 100,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
	}


	ILI9341_Draw_Text("ON/", 	20, 	204, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("OFF ",	20, 	222, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);

	ILI9341_Draw_Text("SET", 	104,	204, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("MODE",	97, 	222, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);

/*	ILI9341_Draw_Text("SET", 	183,	204, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("SPEED",	173, 	222, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);

	ILI9341_Draw_Text("SET", 	263, 	204, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("LIMIT", 	252, 	222, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);
*/
}
