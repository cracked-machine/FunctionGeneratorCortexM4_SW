/*
 * GainMenus.c
 *
 *	Defines draw functions for Gain menu and its sub menus: GainSignal and GainAux
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
 *	@param 	Gain_Main_Menu_State,
			Gain_Signal_Menu_State,
			Gain_Aux_Menu_State,
 *	@retval None
 *
 */
void GainMenu_DrawMenu(eSystemState pMenu)
{
	switch(pMenu)
	{
		case Gain_Main_Menu_State:
			GainMenu_DrawMainMenu();
			break;
		case Gain_Signal_Menu_State:
			GainMenu_DrawSignalMenu();
			break;
		case Gain_Aux_Menu_State:
			GainMenu_DrawAuxMenu();
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

	ILI9341_Draw_Text("OUT->GAIN", 	10, 10, BREADTRAIL_FGCOLOUR, 2, BREADTRAIL_BGCOLOUR);

	DM_DisplayFormattedOutput();

	// coloured menu btn labels
	ILI9341_Draw_Text("SIGNAL", 5, 	 210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);

	eOutput_mode aux_output_func = SM_GetOutputChannel(AUX_CHANNEL)->func_profile->func;
	if(aux_output_func == PWM_FUNC_MODE)
	{
		ILI9341_Draw_Text("    ",	100,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
	}
	else
	{
		ILI9341_Draw_Text("AUX",	100,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
	}

	ILI9341_Draw_Text("    ", 	175, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("    ", 	260, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);
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
	ILI9341_Draw_Text("OUT->GAIN->SIG", 10, 10, BREADTRAIL_FGCOLOUR, 2, BREADTRAIL_BGCOLOUR);

	DM_DisplayFormattedOutput();

	ILI9341_Draw_Text("1.8V", 15,   210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("3.3V", 97,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("5V",  190, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("9V", 265, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void GainMenu_DrawAuxMenu()
{
	ILI9341_Draw_Text("OUT->GAIN->Aux", 10, 10, BREADTRAIL_FGCOLOUR, 2, BREADTRAIL_BGCOLOUR);

	DM_DisplayFormattedOutput();
}
