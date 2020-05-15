/*
 * FuncMenu.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include <FuncMenus.h>
#include "DisplayManager.h"


void FuncMenu_DrawMainMenu();
void FuncMenu_DrawSignalMenu();
void FuncMenu_DrawSyncMenu();

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FuncMenu_DrawMenu(eFuncMenu_Status pMenu)
{
	switch(pMenu)
	{
		case ENABLE_FUNC_MAIN_MENU:
			FuncMenu_DrawMainMenu();
			break;
		case ENABLE_FUNC_SIGNAL_MENU:
			FuncMenu_DrawSignalMenu();
			break;
		case ENABLE_FUNC_SYNC_MENU:
			FuncMenu_DrawSyncMenu();
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
void FuncMenu_DrawMainMenu()
{
	ILI9341_Draw_Text("FUNCTION MAIN MENU", 	10, 10, WHITE, 3, BLACK);
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
void FuncMenu_DrawSignalMenu()
{
	ILI9341_Draw_Text("SELECT SIGNAL FUNCTION", 	10, 10, WHITE, 3, BLACK);

	//FunctionProfile_t *func_profileTmp = FuncO_GetSignalFPresetObject();
	FunctionProfile_t *func_profileTmp = SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile;
	if(func_profileTmp)
	{
		switch(func_profileTmp->func)
		{
			case SINE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SAW", 		10, 90, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- UNIT", 	10, 150, BLACK, 2, WHITE);
				break;
			case SQUARE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- SAW", 		10, 90, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- UNIT", 	10, 150, BLACK, 2, WHITE);
				break;
			case SAW_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SAW", 		10, 90, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- UNIT", 	10, 150, BLACK, 2, WHITE);
				break;
			case REV_SAW_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SAW", 		10, 90, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- UNIT", 	10, 150, BLACK, 2, WHITE);
				break;
			case TRIANGLE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SAW", 		10, 90, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- UNIT", 	10, 150, BLACK, 2, WHITE);
				break;
			case IMPULSE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SAW", 		10, 90, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- UNIT", 	10, 150, WHITE, 2, BLACK);
				break;

		}
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
void FuncMenu_DrawSyncMenu()
{
	ILI9341_Draw_Text("SELECT SYNC FUNCTION", 	10, 10, WHITE, 3, BLACK);
	//FunctionProfile_t *func_profileTmp = FuncO_GetSyncFPresetObject();
	FunctionProfile_t *func_profileTmp = SM_GetOutputChannel(SYNC_CHANNEL)->func_profile;
	if(func_profileTmp)
	{
		switch(func_profileTmp->func)
		{
			case SINE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SAW", 		10, 90, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- UNIT", 	10, 150, BLACK, 2, WHITE);
				break;
			case SQUARE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- SAW", 		10, 90, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- UNIT", 	10, 150, BLACK, 2, WHITE);
				break;
			case SAW_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SAW", 		10, 90, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- UNIT", 	10, 150, BLACK, 2, WHITE);
				break;
			case REV_SAW_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SAW", 		10, 90, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- UNIT", 	10, 150, BLACK, 2, WHITE);
				break;
			case TRIANGLE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SAW", 		10, 90, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- UNIT", 	10, 150, BLACK, 2, WHITE);
				break;
			case IMPULSE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SQUARE", 	10, 70, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- SAW", 		10, 90, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- UNIT", 	10, 150, WHITE, 2, BLACK);
				break;

		}
	}

}
