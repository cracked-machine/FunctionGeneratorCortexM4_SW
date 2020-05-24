/*
 * FuncMenu.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include <FuncMenus.h>



void FuncMenu_DrawMainMenu();
void FuncMenu_DrawOutputMenu(eOutputChannel_t pOutChan);

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
			FuncMenu_DrawOutputMenu(SIGNAL_CHANNEL);
			break;
		case ENABLE_FUNC_Aux_MENU:
			FuncMenu_DrawOutputMenu(AUX_CHANNEL);
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
	ILI9341_Draw_Text("OUT->FUNC", 	10, 10, BREADTRAIL_FGCOLOUR, 2, BREADTRAIL_BGCOLOUR);

	DM_DisplayFormattedOutput();

 	// coloured menu btn labels
	ILI9341_Draw_Text("SIGNAL", 5,   210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
	ILI9341_Draw_Text("Aux", 	97,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
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
void FuncMenu_DrawOutputMenu(eOutputChannel_t pOutChan)
{
	if(pOutChan)
		ILI9341_Draw_Text("OUT->FUNC->AUX", 	10, 10, BREADTRAIL_FGCOLOUR, 2, BREADTRAIL_BGCOLOUR);
	else
		ILI9341_Draw_Text("OUT->FUNC->SIG", 	10, 10, BREADTRAIL_FGCOLOUR, 2, BREADTRAIL_BGCOLOUR);

	//FunctionProfile_t *func_profileTmp = FuncO_GetSignalFPresetObject();
	FunctionProfile_t *func_profileTmp = SM_GetOutputChannel(pOutChan)->func_profile;
	if(func_profileTmp)
	{
		switch(func_profileTmp->func)
		{
			case SINE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50,  HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SQUARE", 	10, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SAW", 		10, 90,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- UNIT", 	10, 150, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

				if(pOutChan)
					ILI9341_Draw_Text("- PWM", 		10, 170, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

				// coloured menu btn labels
				ILI9341_Draw_Text("    ", 5,   210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	97,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	175, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	260, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);
				break;
			case SQUARE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SQUARE", 	10, 70,  HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SAW", 		10, 90,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- UNIT", 	10, 150, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

				if(pOutChan)
					ILI9341_Draw_Text("- PWM", 		10, 170, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

				// coloured menu btn labels
				ILI9341_Draw_Text("    ", 5,   210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	97,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	175, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	260, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);
				break;
			case SAW_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SQUARE", 	10, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SAW", 		10, 90,  HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- UNIT", 	10, 150, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				if(pOutChan)
					ILI9341_Draw_Text("- PWM", 		10, 170, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
			 	// coloured menu btn labels
				ILI9341_Draw_Text("    ", 5,   210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	97,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	175, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	260, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);
				break;
			case REV_SAW_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SQUARE", 	10, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SAW", 		10, 90,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- UNIT", 	10, 150, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

				if(pOutChan)
					ILI9341_Draw_Text("- PWM", 		10, 170, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

				// coloured menu btn labels
				ILI9341_Draw_Text("    ", 5,   210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	97,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	175, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	260, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);
				break;
			case TRIANGLE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SQUARE", 	10, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SAW", 		10, 90,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- UNIT", 	10, 150, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

				if(pOutChan)
					ILI9341_Draw_Text("- PWM", 		10, 170, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

				// coloured menu btn labels
				ILI9341_Draw_Text("    ", 5,   210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	97,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	175, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	260, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);

				ILI9341_Draw_Text("               ", 	150, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				break;
			case IMPULSE_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SQUARE", 	10, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SAW", 		10, 90,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- UNIT", 	10, 150, HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);

				if(pOutChan)
					ILI9341_Draw_Text("- PWM", 		10, 170, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

				// coloured menu btn labels
				ILI9341_Draw_Text("    ", 5,   210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	97,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	175, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	260, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);

				ILI9341_Draw_Text("               ", 	150, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				break;
			case PWM_FUNC_MODE:
				ILI9341_Draw_Text("- SINE", 	10, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SQUARE", 	10, 70,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- SAW", 		10, 90,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- REV SAW", 	10, 110, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- TRIANGLE",	10, 130, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("- UNIT", 	10, 150, NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);

				if(pOutChan)
					ILI9341_Draw_Text("- PWM", 		10, 170, HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);

				// coloured menu btn labels
				ILI9341_Draw_Text("    ", 5,   210, BTN1_TEXT_FGCOLOUR, 2, BTN1_TEXT_BGCOLOUR);
				ILI9341_Draw_Text("    ", 	97,  210, BTN2_TEXT_FGCOLOUR, 2, BTN2_TEXT_BGCOLOUR);

				if(pOutChan)
				{
					ILI9341_Draw_Text("DUTY", 	175, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
					char duty[10] = "";
					snprintf(duty, sizeof(duty), "%0.2f%%", ((float)PWM_AUX_OUT_TIM->CCR1 / (float)PWM_AUX_OUT_TIM->ARR) * 100);
					ILI9341_Draw_Text(duty, 	220, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
					if(SM_IsFuncPwmDutyMode())
					{
						ILI9341_Draw_Text("DUTY:", 	150, 50,  HIGHLIGHT_TEXT_FGCOLOUR, 2, HIGHLIGHT_TEXT_BGCOLOUR);

					}
					else
					{
						ILI9341_Draw_Text("DUTY:", 	150, 50,  NORMAL_TEXT_FGCOLOUR, 2, NORMAL_TEXT_BGCOLOUR);
					}
				}
				else
				{
					ILI9341_Draw_Text("    ", 	175, 210, BTN3_TEXT_FGCOLOUR, 2, BTN3_TEXT_BGCOLOUR);
				}

				ILI9341_Draw_Text("    ", 	260, 210, BTN4_TEXT_FGCOLOUR, 2, BTN4_TEXT_BGCOLOUR);

				break;
				//
		}
	}
}
