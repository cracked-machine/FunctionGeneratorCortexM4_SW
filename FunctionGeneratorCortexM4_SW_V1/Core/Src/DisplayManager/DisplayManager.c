/*
 * DisplayManager.c
 *
 *  Created on: 3 May 2020
 *      Author: chris
 */

#include "DisplayManager.h"

#include "SignalManager.h"
#include "ToplevelMenus.h"
#include "FreqMenus.h"
#include "GainMenus.h"
#include "FuncMenus.h"
#include "BiasMenus.h"

#include "EventManager.h"
//#define ENCODER_DEBUG

#include <stdint.h>
#include <stdio.h>

#include "rng.h"
#include <string.h>
#include <stdlib.h>



 extern uint16_t BURST_MAX_SIZE;

 char ErrorDebugMsg[45] = "";
	uint8_t text_size = 2;

#define BTN_WIDTH 				(ILI9341_SCREEN_WIDTH)/4
#define BTN_HEIGHT				40
#define BORDER_SIZE				2


uint16_t btn_x_pos[4] = { 1, (BTN_WIDTH)+1, (BTN_WIDTH*2)+2, (BTN_WIDTH*3)+2 };


// public function protochannels
void DM_RefreshScreen();
int DM_AddDigitPadding(uint16_t num, char *buffer, uint16_t buflen);
void _DisplayFormattedOutput();
void DM_DisplayInputTriggerData(uint16_t xpos, uint16_t ypos);
void _DisplayOutputSignalHertz(uint16_t xpos, uint16_t ypos);
void _DisplayOutputWaveformIcons(uint16_t main_xpos, uint16_t main_ypos, uint16_t aux_xpos, uint16_t aux_ypos);
void _DisplayOutputSignalOffset(uint16_t xpos, uint16_t ypos);
void _DisplayOutputSignalDecibels(uint16_t xpos, uint16_t ypos);
void _DisplayOutputSignalVpp(uint16_t xpos, uint16_t ypos);
void DM_DrawGenericHertzValue(uint16_t xpos, uint16_t ypos, float output_hertz_value);

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

	ILI9341_Draw_Text("Initialising", 10, 10, NORMAL_TEXT_FGCOLOUR, 1, NORMAL_TEXT_BGCOLOUR);
	HAL_Delay(500);

	DM_RefreshScreen();

	#ifdef EVENT_MENU_DEBUG
		  printf("Init Completed\n");
	#endif


}




/*
 *
 *	@brief Called from TIM1_BRK_TIM15_IRQHandler
 *
 *	@param None
 *	@retval None
 *
 */
void DM_UpdateDisplay()
{

	eSystemState tempState = EM_GetSystemState();
	switch(tempState)
	{
		case Toplevel_Main_Menu_State:
		case Toplevel_Output_Menu_State:
		case Toplevel_Input_Menu_State:
			ToplevelMenu_DrawMenu(tempState);
			break;

		case Func_Main_Menu_State:
		case Func_Signal_Menu_State:
		case Func_Aux_Menu_State:
			FuncMenu_DrawMenu(tempState);
			break;

		case Gain_Main_Menu_State:
		case Gain_Signal_Menu_State:
		case Gain_Aux_Menu_State:
			GainMenu_DrawMenu(tempState);
			break;

		case Freq_Main_Menu_State:
		case Freq_Preset_Menu_State:
		case Freq_Adjust_Menu_State:
		case Freq_Sweep_Menu_State:
		case Freq_Prescaler_Menu_State:
			FreqMenu_DrawMenu(tempState);
			break;

		case Bias_Menu_State:
			BiasMenu_DrawMenu(tempState);
			break;

		default:
			break;

	}

	#ifdef ENCODER_DEBUG
		char tim5_text[50] = "";
		snprintf(tim5_text, sizeof(tim5_text), "OFFSET: %5lu", BO_GetOutputBias());
		ILI9341_Draw_Text(tim5_text, 220, 10, ERR_FGCOLOUR, 1, ERR_BGCOLOUR);

		char encoder_value[50] = "";
		snprintf(encoder_value, sizeof(encoder_value), "ENCODER: %5lu", ENCODER_TIMER->CNT);
		ILI9341_Draw_Text(encoder_value, 220, 20, ERR_FGCOLOUR, 1, ERR_BGCOLOUR);
	#endif //ENCODER_DEBUG



}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void DM_DisplayFormattedOutput()
{

	_DisplayOutputSignalHertz(140, 45);
	_DisplayOutputSignalVpp(175, 70);
	_DisplayOutputSignalDecibels(138, 95);
	_DisplayOutputSignalOffset(161, 120);
	_DisplayOutputWaveformIcons(80, 160, 245, 160);

	DM_DisplayInputTriggerStatus();
	DM_DisplayInputTriggerData(200, 17);

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void DM_DisplayInputTriggerStatus()
{

	uint16_t text_x_pos = 240;
	uint16_t text_y_pos = 1;
	// eTriggerInputMode
	switch(IT_GetActiveTriggerMode())
	{
		case INPUT_TIMER_TIM:
			if(IT_GetTriggerStatus())
				ILI9341_Draw_Text("T:TIM ", text_x_pos, text_y_pos, HIGHLIGHT_TEXT_FGCOLOUR , text_size, HIGHLIGHT_TEXT_BGCOLOUR);
			else
				ILI9341_Draw_Text("T:TIM ", text_x_pos, text_y_pos, HIGHLIGHT_TEXT_BGCOLOUR , text_size, HIGHLIGHT_TEXT_FGCOLOUR);
			break;
		case INPUT_TIMER_COMP:
			if(IT_GetTriggerStatus())
				ILI9341_Draw_Text("T:COMP", text_x_pos, text_y_pos, HIGHLIGHT_TEXT_FGCOLOUR , text_size, HIGHLIGHT_TEXT_BGCOLOUR);
			else
				ILI9341_Draw_Text("T:COMP", text_x_pos, text_y_pos, HIGHLIGHT_TEXT_BGCOLOUR , text_size, HIGHLIGHT_TEXT_FGCOLOUR);
			break;
		case INPUT_TIMER_ADC:
			if(IT_GetTriggerStatus())
				ILI9341_Draw_Text("T:ADC ", text_x_pos, text_y_pos, HIGHLIGHT_TEXT_FGCOLOUR , text_size, HIGHLIGHT_TEXT_BGCOLOUR);
			else
				ILI9341_Draw_Text("T:ADC ", text_x_pos, text_y_pos, HIGHLIGHT_TEXT_BGCOLOUR , text_size, HIGHLIGHT_TEXT_FGCOLOUR);
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
void DM_DisplayInputTriggerData(uint16_t xpos, uint16_t ypos)
{
	if(  IT_GetTriggerStatus() && (IT_GetActiveTriggerMode() == INPUT_TIMER_TIM) )
	{
		char avg_freq_count_hertz[13] = {};

		if(IT_GetAverageFreqCountHertz() < 1000)
		{
			snprintf(avg_freq_count_hertz, sizeof(avg_freq_count_hertz), "%7.1f Hz", IT_GetAverageFreqCountHertz());
		}
		else if(IT_GetAverageFreqCountHertz() < 10000)
		{
			snprintf(avg_freq_count_hertz, sizeof(avg_freq_count_hertz), "%6.1f KHz", IT_GetAverageFreqCountHertz() / 1000);
		}
		else if(IT_GetAverageFreqCountHertz() < 100000)
		{
			snprintf(avg_freq_count_hertz, sizeof(avg_freq_count_hertz), "%6.1f KHz", IT_GetAverageFreqCountHertz()  / 1000);
		}
		else
		{
			snprintf(avg_freq_count_hertz, sizeof(avg_freq_count_hertz), "%6.1f KHz", IT_GetAverageFreqCountHertz()  / 1000);
		}

		ILI9341_Draw_Text(avg_freq_count_hertz, xpos, ypos, NORMAL_TEXT_FGCOLOUR , text_size, NORMAL_TEXT_BGCOLOUR);
	}
	else if(  IT_GetTriggerStatus() && (IT_GetActiveTriggerMode() == INPUT_TIMER_ADC) )
	{
		char adc_volt_string[13] = {};


		snprintf(adc_volt_string, sizeof(adc_volt_string), "%6.1f V", IT_GetAvgAdcVoltage());


		ILI9341_Draw_Text(adc_volt_string, xpos, ypos, NORMAL_TEXT_FGCOLOUR , text_size, NORMAL_TEXT_BGCOLOUR);
	}
	else
	{
		ILI9341_Draw_Text("                   ", xpos, ypos, NORMAL_TEXT_FGCOLOUR , text_size, NORMAL_TEXT_BGCOLOUR);
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
void _DisplayOutputSignalHertz(uint16_t xpos, uint16_t ypos)
{


	// draw row header
	ILI9341_Draw_Text("FREQ   ....", 2, ypos , NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);

	// display output in hertz
	DM_DrawGenericHertzValue(xpos, ypos, SM_GetOutputInHertz());
}

void DM_DrawGenericHertzValue(uint16_t xpos, uint16_t ypos, float output_hertz_value)
{
	char out_hertz[20] = "";
	if(output_hertz_value < 1000)
	{
		snprintf(out_hertz, sizeof(out_hertz), " %7.2f  Hz ", output_hertz_value);
	}
	else if(output_hertz_value < 10000)
	{
		snprintf(out_hertz, sizeof(out_hertz), " %7.2f  KHz ", output_hertz_value /1000);
	}
	else if(output_hertz_value < 100000)
	{
		snprintf(out_hertz, sizeof(out_hertz), " %7.2f  KHz ", output_hertz_value /1000);
	}
	else
	{
		snprintf(out_hertz, sizeof(out_hertz), " %7.2f  KHz ", output_hertz_value /1000);
	}

	ILI9341_Draw_Text(out_hertz, xpos, ypos, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _DisplayOutputSignalVpp(uint16_t xpos, uint16_t ypos)
{
	char out_vpp[18] = "";
	uint8_t out_vpp_x = xpos;
	uint8_t out_vpp_y = ypos;

	// draw row header
	ILI9341_Draw_Text("VPP    ....", 2, out_vpp_y, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);

	AmplitudeProfile_t* pTmpVppPreset = SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile;

	if(pTmpVppPreset)
	{
		snprintf(out_vpp, sizeof(out_vpp), " %2.2f   V ", pTmpVppPreset->amp_value);
	}

	ILI9341_Draw_Text(out_vpp, out_vpp_x, out_vpp_y, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _DisplayOutputSignalDecibels(uint16_t xpos, uint16_t ypos)
{
	char out_decibels[20] = "";
	uint8_t out_decibels_x = xpos;
	uint8_t out_decibels_y = ypos;

	// draw row header
	ILI9341_Draw_Text("GAIN   ....", 2, out_decibels_y, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);

	AmplitudeProfile_t* pTmpVppPreset = SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile;
	if(pTmpVppPreset)
	{
		snprintf(out_decibels, sizeof(out_decibels), " %+7.2f ", pTmpVppPreset->gain_decibels);
	}

	ILI9341_Draw_Text(out_decibels, out_decibels_x, out_decibels_y, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("dBmV", out_decibels_x + 128, out_decibels_y, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _DisplayOutputSignalOffset(uint16_t xpos, uint16_t ypos)
{
	float volts_per_thou = 0.00075;
	char out_dcvolts[12] = "";
	uint8_t out_dcvolts_x = xpos;
	uint8_t out_dcvolts_y = ypos;

	ILI9341_Draw_Text("OFFSET ....", 2, out_dcvolts_y, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);

	// display output bias in +/- Volts
	float dc_volts;
	(BO_GetOutputBias() == 0) ? (dc_volts = 0) : (dc_volts = volts_per_thou * (float)BO_GetOutputBias());

	snprintf(out_dcvolts, sizeof(out_dcvolts), "%05.2f   v ", dc_volts);
	if(BO_GetBiasPolarity())
	{
		char symbol[3] = "+\0";
		ILI9341_Draw_Text(strcat(symbol, out_dcvolts), out_dcvolts_x, out_dcvolts_y, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);
	}
	else
	{
		char symbol[3] = "-\0";
		ILI9341_Draw_Text(strcat(symbol, out_dcvolts), out_dcvolts_x, out_dcvolts_y, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);
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
void _DisplayOutputWaveformIcons(uint16_t main_xpos, uint16_t main_ypos, uint16_t aux_xpos, uint16_t aux_ypos)
{

	ILI9341_Draw_Text(" OUT:", 1, main_ypos+10, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);
	eOutput_mode signal_output_func = SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile->func;
	switch(signal_output_func)
	{
		case SINE_FUNC_MODE:
			ILI9341_Draw_Wave(main_xpos, main_ypos-20, 3, SIGNAL_OUTPUT_ICON, 100, sineicon_data_table_1300, SINEICON_DATA_SIZE);
			break;
		case SQUARE_FUNC_MODE:
			ILI9341_Draw_Wave(main_xpos, main_ypos, 3, SIGNAL_OUTPUT_ICON, 200, squareicon_data_table_3600, SQUAREICON_DATA_SIZE);
			break;
		case SAW_FUNC_MODE:
			ILI9341_Draw_Wave(main_xpos, main_ypos, 3, SIGNAL_OUTPUT_ICON, 200, sawicon_data_table_3600, SAWICON_DATA_SIZE);
			break;
		case REV_SAW_FUNC_MODE:
			ILI9341_Draw_Wave(main_xpos, main_ypos, 3, SIGNAL_OUTPUT_ICON, 200, sawicon_rev_data_table_3600, SAWICON_REV_DATA_SIZE);
			break;
		case TRIANGLE_FUNC_MODE:
			ILI9341_Draw_Wave(main_xpos, main_ypos, 3, SIGNAL_OUTPUT_ICON, 200, triangleicon_data_table_3600, TRIANGLEICON_DATA_SIZE);
			break;
		case IMPULSE_FUNC_MODE:
			ILI9341_Draw_Wave(main_xpos, main_ypos, 3, SIGNAL_OUTPUT_ICON, 200, triangleicon_data_table_3600, TRIANGLEICON_DATA_SIZE);
			break;
		case PWM_FUNC_MODE:
			ILI9341_Draw_Text("PWM", main_xpos, main_ypos+10, SIGNAL_OUTPUT_ICON, text_size, NORMAL_TEXT_BGCOLOUR);
			break;
	}

	ILI9341_Draw_Text("AUX:", 170, aux_ypos+10, NORMAL_TEXT_FGCOLOUR, text_size, NORMAL_TEXT_BGCOLOUR);
	eOutput_mode Aux_output_func = SM_GetOutputChannel(AUX_CHANNEL)->func_profile->func;
	switch(Aux_output_func)
	{
		case SINE_FUNC_MODE:

			ILI9341_Draw_Wave(aux_xpos, aux_ypos-20, 3, Aux_OUTPUT_ICON, 100, sineicon_data_table_1300, SINEICON_DATA_SIZE);
			break;
		case SQUARE_FUNC_MODE:
			ILI9341_Draw_Wave(aux_xpos, aux_ypos, 3, Aux_OUTPUT_ICON, 200, squareicon_data_table_3600, SQUAREICON_DATA_SIZE);
			break;
		case SAW_FUNC_MODE:
			ILI9341_Draw_Wave(aux_xpos, aux_ypos, 3, Aux_OUTPUT_ICON, 200, sawicon_data_table_3600, SAWICON_DATA_SIZE);
			break;
		case REV_SAW_FUNC_MODE:
			ILI9341_Draw_Wave(aux_xpos, aux_ypos, 3, Aux_OUTPUT_ICON, 200, sawicon_rev_data_table_3600, SAWICON_REV_DATA_SIZE);
			break;
		case TRIANGLE_FUNC_MODE:
			ILI9341_Draw_Wave(aux_xpos, aux_ypos, 3, Aux_OUTPUT_ICON, 200, triangleicon_data_table_3600, TRIANGLEICON_DATA_SIZE);
			break;
		case IMPULSE_FUNC_MODE:
			ILI9341_Draw_Wave(aux_xpos, aux_ypos, 3, Aux_OUTPUT_ICON, 200, triangleicon_data_table_3600, TRIANGLEICON_DATA_SIZE);
			break;
		case PWM_FUNC_MODE:
			ILI9341_Draw_Text("PWM", aux_xpos, aux_ypos+10, Aux_OUTPUT_ICON, text_size, NORMAL_TEXT_BGCOLOUR);
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


	ILI9341_Fill_Screen(SCREEN_BGCOLOUR);




	//ILI9341_FillScreenGradient();
/*	for(int q = 0; q < 10; q++)
		ILI9341_Draw_Hollow_Circle(100 + q,  100,  50, RED);
	//ILI9341_Draw_Filled_Circle(100,  50,  50, RED);

	Point Points[]= {{20, 70}, {60, 70}, {60, 100}};
	Point Points2[]= {{80, 70}, {120, 70}, {120, 100}};

	GUI_DrawPolygon(Points, 3, RED);
	GUI_FillPolygon(Points2, 3, BLUE);
	GUI_DrawEllipse(250, 110, 20, 30, GREEN);
	GUI_FillEllipse(250, 110, 20, 30, WHITE);
*/
	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	0,
													ILI9341_SCREEN_HEIGHT - BTN_HEIGHT,
													BTN_WIDTH,
													BTN_HEIGHT,
													BTN1_FILL_COLOUR,
													BTN1_BORDER_WEIGHT,
													BTN1_BORDER_COLOUR);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	BTN_WIDTH,
													ILI9341_SCREEN_HEIGHT - BTN_HEIGHT,
													BTN_WIDTH,
													BTN_HEIGHT,
													BTN2_FILL_COLOUR,
													BTN2_BORDER_WEIGHT,
													BTN2_BORDER_COLOUR);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	BTN_WIDTH*2,
													ILI9341_SCREEN_HEIGHT - BTN_HEIGHT,
													BTN_WIDTH,
													BTN_HEIGHT,
													BTN3_FILL_COLOUR,
													BTN3_BORDER_WEIGHT,
													BTN3_BORDER_COLOUR);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	BTN_WIDTH*3,
													ILI9341_SCREEN_HEIGHT - BTN_HEIGHT,
													BTN_WIDTH,
													BTN_HEIGHT,
													BTN4_FILL_COLOUR,
													BTN4_BORDER_WEIGHT,
													BTN4_BORDER_COLOUR);

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
	ILI9341_Draw_Text(ErrorDebugMsg, 10, 190, ERR_FGCOLOUR, 1, ERR_BGCOLOUR);
}
