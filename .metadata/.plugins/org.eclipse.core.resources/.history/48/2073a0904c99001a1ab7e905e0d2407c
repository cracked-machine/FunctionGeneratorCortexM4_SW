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
void BiasMenu_DrawMenu(eBiasMenu_Status pMenu)
{
	switch(pMenu)
	{
		case ENABLE_BIAS_MENU:
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
	ILI9341_Draw_Text("OUT->BIAS", 	10, 10, WHITE, 2, BLACK);

	DM_DisplayFormattedOutput();

}
