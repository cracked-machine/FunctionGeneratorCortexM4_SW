/*
 * FreqMenus.c
 *
 *  Created on: 11 May 2020
 *      Author: chris
 */


#include "FreqMenus.h"
#include <stdio.h>
#include "DisplayManager.h"

#define SWEEP_TIMER TIM3

void FreqMenu_DrawMainMenu();
void FreqMenu_DrawPresetMenu();
void FreqMenu_DrawSyncMenu();

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FreqMenu_DrawMenu(eFreqMenu_Status pMenu)
{
	switch(pMenu)
	{
		case ENABLE_FREQ_MAIN_MENU:
			FreqMenu_DrawMainMenu();
			break;
		case ENABLE_FREQ_PRESET_MENU:
			FreqMenu_DrawPresetMenu();
			break;
		case ENABLE_FREQ_ADJUST_MENU:
			FreqMenu_DrawAdjustMenu();
			break;
		case ENABLE_FREQ_SWEEP_MENU:
			FreqMenu_DrawSweepMenu();
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
void FreqMenu_DrawMainMenu()
{
	// main
	ILI9341_Draw_Text("FREQUENCY MENU", 	30, 10, WHITE, 3, BLACK);
	ILI9341_Draw_Text("Select an option below", 	30, 165, BLACK, 2, WHITE);

	// buttons
	ILI9341_Draw_Text("PRESET", 5, 210, BLACK, 2, DARKCYAN);
	ILI9341_Draw_Text("ADJUST", 87, 210, BLACK, 2, DARKGREEN);
	ILI9341_Draw_Text("SWEEP", 174, 210, BLACK, 2, YELLOW);
	//ILI9341_Draw_Text("    ", 260, 210, BLACK, 2, RED);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FreqMenu_DrawPresetMenu()
{

	ILI9341_Draw_Text("FREQUENCY PRESET", 	30, 10, WHITE, 3, BLACK);
	uint8_t menu_pos_y1 = 50;
	uint8_t menu_pos_y2 = 70;
	uint8_t menu_pos_y3 = 90;
	uint8_t menu_pos_y4 = 110;
	uint8_t menu_pos_y5 = 130;
	uint8_t menu_pos_y6 = 150;
	uint8_t menu_pos_y7 = 170;
	FreqProfile_t *pFreqPresetTmp =  FreqO_GetFPresetObject();
	if(pFreqPresetTmp)
	{
		switch(pFreqPresetTmp->hertz)
		{
			case FPRESET_1HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_10HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_50HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_100HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_250HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_500HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_750HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, WHITE, 2, BLACK);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_1KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_5KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_10KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_25KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_50KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
			break;
			case FPRESET_75KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
			break;
			case FPRESET_100KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, WHITE, 2, BLACK);
			break;

		}
	}
	else
	{
		ILI9341_Draw_Text("FreqMenus::FreqMenu_DrawFreqPresetMenu() Error", 		10, 180, RED, 1, BLACK);
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
void FreqMenu_DrawAdjustMenu()
{
	ILI9341_Draw_Text("FREQUENCY ADJUST", 	30, 10, WHITE, 3, BLACK);
/*	ILI9341_Draw_Text("Output Signal Freq: ", 	10, 150, BLACK, 1, WHITE);

	char freq[6] = "";
	//snprintf(freq, sizeof(freq), "%u", (uint8_t)FreqO_GetOutputFreq());
	if(DM_AddDigitPadding((uint16_t)FreqO_GetOutputFreq(), freq, sizeof(freq)) == 0)
		ILI9341_Draw_Text(freq, 250, 150, WHITE, 1, BLACK);
*/

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FreqMenu_DrawSweepMenu()
{
	ILI9341_Draw_Text("FREQUENCY SWEEP", 	10, 10, BLACK, 3, WHITE);
	TIM8->ARR = SWEEP_TIMER->CNT;

	// draw enabled status
	char enabled_text[16] = "";
	if((SWEEP_TIMER->CR1 & TIM_CR1_CEN) == TIM_CR1_CEN)
	{
		snprintf(enabled_text, sizeof(enabled_text), "SWEEP  ENABLED");
	}
	else
	{
		snprintf(enabled_text, sizeof(enabled_text), "SWEEP DISABLED");
	}

	ILI9341_Draw_Text(enabled_text, 10, 50, BLACK, 2, WHITE);



	// draw mode (direction) status
	char mode_text[16] = "";

	if((SWEEP_TIMER->CR1 & TIM_CR1_CMS_0) == TIM_CR1_CMS_0)
	{
		// direction not relevant in center-alligned mode (bi-directional)
		snprintf(mode_text, sizeof(mode_text), "DIRECTION: BOTH");
		//snprintf(dir_text, sizeof(dir_text), "DIRECTION:  N/A");
	}
	else
	{
		// center-alligned mode disabled (uni-directional)


		// get direction
		if((SWEEP_TIMER->CR1 & TIM_CR1_DIR) == TIM_CR1_DIR)
			snprintf(mode_text, sizeof(mode_text), "DIRECTION: DOWN");
		else
			snprintf(mode_text, sizeof(mode_text), "DIRECTION:   UP");

	}

	ILI9341_Draw_Text(mode_text, 10, 80, BLACK, 2, WHITE);

	// draw rate status
	char arr_text[20] = "";
	snprintf(arr_text, sizeof(arr_text), "RATE: %1.5f Hertz", calculated_sweep_in_hertz);
	ILI9341_Draw_Text(arr_text, 10, 110, BLACK, 2, WHITE);

	// draw output freq status

	char out_hertz[20] = "";
	snprintf(out_hertz, sizeof(out_hertz), "OUT: %7.2f Hertz", SM_GetOutputInHertz());
	ILI9341_Draw_Text(out_hertz, 10, 140, BLACK, 2, WHITE);



	// draw bottom menu button text
	if((SWEEP_TIMER->CR1 & TIM_CR1_CEN) == TIM_CR1_CEN)
		ILI9341_Draw_Text("PAUSE ", 10, 210, BLACK, 2, DARKCYAN);
	else
		ILI9341_Draw_Text("RESUME", 5, 210, BLACK, 2, DARKCYAN);

	ILI9341_Draw_Text("MODE", 95, 210, BLACK, 2, DARKGREEN);
	ILI9341_Draw_Text("LOWER", 175, 210, BLACK, 2, YELLOW);
	ILI9341_Draw_Text("UPPER", 245, 210, BLACK, 2, RED);

}

