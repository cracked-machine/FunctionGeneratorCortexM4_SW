/*
 * BiasMenu.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#include "BiasMenus.h"
#include "DisplayManager.h"





/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void BiasMenu_DrawMenu(eSystemState pMenu)
{
	switch(pMenu)
	{
		case Bias_Menu_State:
			BiasMenu_DrawMainMenu();
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
void BiasMenu_DrawMainMenu()
{
	ILI9341_Draw_Text("OUT->BIAS", 	10, 10, BREADTRAIL_FGCOLOUR, 2, BREADTRAIL_BGCOLOUR);

	DM_DisplayFormattedOutput();

	ILI9341_Draw_Text("POS", 15,   210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("NEG", 97,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("GND",  190, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);

}
