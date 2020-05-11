/*
 * FreqMenus.c
 *
 *  Created on: 11 May 2020
 *      Author: chris
 */

#include "FreqMenus.h"

#include "DisplayManager.h"
#include "SignalManager.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

/*
 *
 *
 *
 */
void FreqMenu_DrawFreqMainMenu()
{
	// main
	ILI9341_Draw_Text("Select an option below", 	10, 120, BLACK, 2, WHITE);

	// buttons
	ILI9341_Draw_Text("PRESET", 5, 210, BLACK, 2, DARKCYAN);
	ILI9341_Draw_Text("ADJUST", 87, 210, BLACK, 2, DARKGREEN);
	ILI9341_Draw_Text("SWEEP", 174, 210, BLACK, 2, YELLOW);
	//ILI9341_Draw_Text("    ", 260, 210, BLACK, 2, RED);
}

/*
 *
 *
 *
 */
void FreqMenu_DrawFreqPresetMenu()
{

	switch(FreqO_GetFPreset())
	{
		case FPRESET_1HZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_10HZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_50HZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_100HZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_250HZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_500HZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_750HZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, WHITE, 2, BLACK);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_1KHZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_5KHZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_10KHZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_25KHZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
			break;
		case FPRESET_50KHZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
		break;
		case FPRESET_75KHZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, BLACK, 2, WHITE);
		break;
		case FPRESET_100KHZ:
			ILI9341_Draw_Text("- 1Hz", 		10, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10Hz", 	10, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50Hz", 	10, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100Hz", 	10, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 250Hz", 	10, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 500Hz",	10, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 750Hz", 	10, 155, BLACK, 2, WHITE);

			ILI9341_Draw_Text("- 1KHz", 	120, 35, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 5KHz", 	120, 55, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 10KHz", 	120, 75, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 25KHz", 	120, 95, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 50KHz", 	120, 115, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 75KHz",	120, 135, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- 100KHz", 	120, 155, WHITE, 2, BLACK);
		break;

	}
}

/*
 *
 *
 *
 */
void FreqMenu_DrawFreqAdjustMenu()
{

	ILI9341_Draw_Text("Output Signal Freq: ", 	10, 120, BLACK, 2, WHITE);

	char freq[6] = "";
	//snprintf(freq, sizeof(freq), "%u", (uint8_t)FreqO_GetOutputFreq());
	if(DM_AddDigitPadding((uint16_t)FreqO_GetOutputFreq(), freq, sizeof(freq)) == 0)
		ILI9341_Draw_Text(freq, 250, 120, WHITE, 2, BLACK);


}

/*
 *
 *
 *
 */
void FreqMenu_DrawFreqSweepMenu()
{

	ILI9341_Draw_Text("TODO: Freq Sweep Menu", 	10, 120, BLACK, 2, WHITE);




}
