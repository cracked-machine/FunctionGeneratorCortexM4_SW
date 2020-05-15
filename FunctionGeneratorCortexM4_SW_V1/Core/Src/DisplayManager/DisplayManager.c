/*
 * DisplayManager.c
 *
 *  Created on: 3 May 2020
 *      Author: chris
 */

#include "DisplayManager.h"
#include "FreqMenus.h"
#include "GainMenus.h"
#include "FuncMenus.h"
#include "BiasMenus.h"

#include "EventManager.h"


#include <stdint.h>
#include <stdio.h>

#include "rng.h"
#include <string.h>
#include <stdlib.h>



 extern uint16_t BURST_MAX_SIZE;

 char ErrorDebugMsg[45] = "";


#define BTN_WIDTH 				(ILI9341_SCREEN_WIDTH)/4
#define BTN_HEIGHT				50
#define BTN_Y_POS 				(ILI9341_SCREEN_HEIGHT)-40
#define BORDER_SIZE				2
#define BTN_TXT_X_POS 			(ILI9341_SCREEN_WIDTH)/8
#define BTN_TXT_Y_POS 			(ILI9341_SCREEN_HEIGHT)-25

uint16_t btn_x_pos[4] = { 0, (BTN_WIDTH)+1, (BTN_WIDTH*2)+2, (BTN_WIDTH*3)+2 };


// public function protochannels
void DM_RefreshScreen();
int DM_AddDigitPadding(uint16_t num, char *buffer, uint16_t buflen);

// private function protochannels

void _DrawBiasSelectMenu();


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void DM_Init()
{
	  ILI9341_Init();
	  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
	  ILI9341_Fill_Screen(WHITE);

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void DM_PostInit()
{

	  ILI9341_Draw_Text("Initialising", 10, 10, BLACK, 1, WHITE);
	  HAL_Delay(500);

	  DM_RefreshScreen();
	  printf("Init Completed\n");
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _DisplayFormattedOutput()
{
	char out_hertz[13] = "";
	uint8_t out_hertz_x = 70;
	uint8_t out_hertz_y = 40;

	char out_vpp[16] = "";
	uint8_t out_vpp_x = 70;
	uint8_t out_vpp_y = 70;

	char out_decibels[11] = "";
	uint8_t out_decibels_x = 70;
	uint8_t out_decibels_y = 100;


	float volts_per_thou = 0.00075;
	char out_dcvolts[10] = "";
	uint8_t out_dcvolts_x = 70;
	uint8_t out_dcvolts_y = 130;

	// display output in hertz
	snprintf(out_hertz, sizeof(out_hertz), "%4.2f Hz", SM_GetOutputInHertz());
	ILI9341_Draw_Text(out_hertz, out_hertz_x, out_hertz_y, BLACK, 3, WHITE);

	// display output in volts peak-to-peak and decibels
	AmplitudeProfile_t* pTmpVppPreset = SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile;

	if(pTmpVppPreset)
	{
		snprintf(out_vpp, sizeof(out_vpp), "%2.2f Vpp", pTmpVppPreset->Vpp_target);
		snprintf(out_decibels, sizeof(out_decibels), "%s", pTmpVppPreset->gain_decibels);
	}
	ILI9341_Draw_Text(out_vpp, out_vpp_x, out_vpp_y, BLACK, 3, WHITE);
	ILI9341_Draw_Text(out_decibels, out_decibels_x, out_decibels_y, BLACK, 3, WHITE);



	// display output bias in +/- Volts
	float dc_volts;
	(BO_GetOutputBias() == 0) ? (dc_volts = 0) : (dc_volts = volts_per_thou * (float)BO_GetOutputBias());

	snprintf(out_dcvolts, sizeof(out_dcvolts), "%1.4f v", dc_volts);
	if(BO_GetBiasPolarity())
	{
		char symbol[2] = "+\0";
		ILI9341_Draw_Text(strcat(symbol, out_dcvolts), out_dcvolts_x, out_dcvolts_y, BLACK, 3, WHITE);
	}
	else
	{
		char symbol[2] = "-\0";
		ILI9341_Draw_Text(strcat(symbol, out_dcvolts), out_dcvolts_x, out_dcvolts_y, BLACK, 3, WHITE);
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
void DM_UpdateDisplay()
{

	// Function menus
	if(FuncMenu_getStatus())		//  != DISABLE_FUNC_MENU
	{
		switch(FuncMenu_getStatus())
		{
			case ENABLE_FUNC_MAIN_MENU:

				_DisplayFormattedOutput();
				FuncMenu_DrawMenu(ENABLE_FUNC_MAIN_MENU);

				break;

			case ENABLE_FUNC_SIGNAL_MENU:

				// _DisplayFormattedOutput();
				FuncMenu_DrawMenu(ENABLE_FUNC_SIGNAL_MENU);

				break;

			case ENABLE_FUNC_SYNC_MENU:

				//_DisplayFormattedOutput();
				FuncMenu_DrawMenu(ENABLE_FUNC_SYNC_MENU);

				break;

			default:
				break;
		}

	}
	// Gain menus
	else if(GainMenu_getStatus())		//  != DISABLE_GAIN_MENU
	{

		switch(GainMenu_getStatus())
		{
			case ENABLE_GAIN_MAIN_MENU:

				_DisplayFormattedOutput();
				GainMenu_DrawMenu(ENABLE_GAIN_MAIN_MENU);

				break;

			case ENABLE_GAIN_SIGNAL_MENU:

				_DisplayFormattedOutput();
				GainMenu_DrawMenu(ENABLE_GAIN_SIGNAL_MENU);

				break;

			case ENABLE_GAIN_SYNC_MENU:

				_DisplayFormattedOutput();
				GainMenu_DrawMenu(ENABLE_GAIN_SYNC_MENU);

				break;

			default:
				break;
		}

	}

	// Frequency menus
	else if(FreqMenu_getStatus())		//  != DISABLE_FREQ_MENU
	{

		ILI9341_Draw_Text("FREQUENCY MENU", 	30, 10, WHITE, 3, BLACK);

		switch(FreqMenu_getStatus())
		{
			case ENABLE_FREQ_MAIN_MENU:

				_DisplayFormattedOutput();
				FreqMenu_DrawMenu(ENABLE_FREQ_MAIN_MENU);

				break;

			case ENABLE_FREQ_PRESET_MENU:

				FreqMenu_DrawMenu(ENABLE_FREQ_PRESET_MENU);
				break;

			case ENABLE_FREQ_ADJUST_MENU:

				_DisplayFormattedOutput();
				FreqMenu_DrawMenu(ENABLE_FREQ_ADJUST_MENU);

				break;

			case ENABLE_FREQ_SWEEP_MENU:

				FreqMenu_DrawMenu(ENABLE_FREQ_SWEEP_MENU);
				break;

			default:
				break;
		}

	}

	// Bias menu
	else if(BiasMenu_getStatus())		//  != DISABLE_BIAS_MENU
	{

		_DisplayFormattedOutput();
		BiasMenu_DrawMenu(ENABLE_BIAS_MENU);
	}
	else
	{
		// Main screen
		ILI9341_Draw_Text("SIGNAL GENERATOR", 	10, 10, WHITE, 3, BLACK);
		_DisplayFormattedOutput();

		ILI9341_Draw_Text("FUNC", 10, 210, BLACK, 2, DARKCYAN);
		ILI9341_Draw_Text("FREQ", 100, 210, BLACK, 2, DARKGREEN);
		ILI9341_Draw_Text("GAIN", 175, 210, BLACK, 2, YELLOW);
		ILI9341_Draw_Text("BIAS", 260, 210, BLACK, 2, RED);
	}

#ifdef ENCODER_DEBUG
	char encoder_value[5] = "";
	//snprintf(tim1tmp, sizeof(tim1tmp), "%lu", ENCODER_TIMER->CNT);
	if(DM_AddDigitPadding(ENCODER_TIMER->CNT, encoder_value, sizeof(encoder_value)) == 0)
		ILI9341_Draw_Text(encoder_value, 280, 190, BLACK, 1, RED);
#endif //ENCODER_DEBUG

	if(*ErrorDebugMsg)
		ILI9341_Draw_Text(ErrorDebugMsg, 10, 190, BLACK, 1, RED);

}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
int DM_DigitCount(int num)
{
	if(num < 10)
		return 1;
	if(num < 100)
		return 2;
	if(num < 1000)
		return 3;
	if(num < 10000)
		return 4;
	if(num < 100000)
		return 5;
	else
		return 0;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void DM_RefreshScreen()
{
	// pause display interrupts
	HAL_TIM_Base_Stop_IT(&htim15);


	//ILI9341_Fill_Screen(WHITE);
	ILI9341_FillScreenGradient();

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[0],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													DARKCYAN,
													BORDER_SIZE,
													BLACK);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[1],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													DARKGREEN,
													BORDER_SIZE,
													BLACK);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[2],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													YELLOW,
													BORDER_SIZE,
													BLACK);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[3],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													RED,
													BORDER_SIZE,
													BLACK);
	// resume diaplay interrupts
	HAL_TIM_Base_Start_IT(&htim15);
}







/*
 *
 *	@brief adds num to buffer with empty char padding
 *
 *	used so that smaller number can erase previously
 *	larger number when displayed on TFT
 *
 *	buflen should be +1 to account for terminating null zero
 *
 *	@param num
 *	@param buffer
 *	@param buflen
 *
 *	@retval 0 when OK
 *			1 if buflen is invalid size
 *			2 unknown error
 *
 */
int DM_AddDigitPadding(uint16_t num, char *buffer, uint16_t buflen)
{
	if((buflen < 1) || (buflen > 6))
	{
		DM_SetErrorDebugMsg("DM_AddDigitPadding: invalid input string size");
		return 1;
	}

	//char* tmpbuf = malloc(sizeof(buffer) * buflen);

	uint16_t tmpcnt = num;
	switch(DM_DigitCount(tmpcnt))
	{

		case 0:
			snprintf(buffer,buflen, "     ");
			return 0;
		case 1:
			snprintf(buffer, buflen, "%u    ", tmpcnt);
			return 0;
		case 2:
			snprintf(buffer, buflen, "%u   ", tmpcnt);
			return 0;
		case 3:
			snprintf(buffer, buflen, "%u  ", tmpcnt);
			return 0;
		case 4:
			snprintf(buffer, buflen, "%u ", tmpcnt);
			return 0;
		case 5:
			snprintf(buffer, buflen, "%u", tmpcnt);
			return 0;

	}
	DM_SetErrorDebugMsg("DM_AddDigitPadding: unknown error");
	return 2;


}



/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void DM_TestScreen()
{



	/*
	for(int f=0; f<50;f++)
		ILI9341_Draw_Pixel(f, 50, RED);

	ILI9341_Draw_Text("- SINE", 	10, 30, WHITE, 2, BLACK);
	*/
}

void DM_SetErrorDebugMsg(char* msg)
{
	snprintf(ErrorDebugMsg, sizeof(ErrorDebugMsg), "%s", msg);
}
