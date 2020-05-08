/*
 * DisplayManager.c
 *
 *  Created on: 3 May 2020
 *      Author: chris
 */

#include "DisplayManager.h"

#include <stdint.h>
#include <stdio.h>
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "rng.h"
#include <string.h>
#include <stdlib.h>

#include "ILI9341_TextManager.h"

 extern uint16_t BURST_MAX_SIZE;

#define BTN_WIDTH 				(ILI9341_SCREEN_WIDTH)/4
#define BTN_HEIGHT				50
#define BTN_Y_POS 				(ILI9341_SCREEN_HEIGHT)-40
#define BORDER_SIZE				2
#define BTN_TXT_X_POS 			(ILI9341_SCREEN_WIDTH)/8
#define BTN_TXT_Y_POS 			(ILI9341_SCREEN_HEIGHT)-25

uint16_t btn_x_pos[4] = { 0, (BTN_WIDTH)+1, (BTN_WIDTH*2)+2, (BTN_WIDTH*3)+2 };
//#define BUTTON_Y_POSITION 50
//uint16_t button_x_positions[1] = { (BUTTON_WIDTH) };

/*
 *
 *
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
 * Call this only once during init.
 *
 *
 */
void DM_RefreshBackgroundLayout()
{
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
}


/*
 *
 *
 *
 */
void DM_Init()
{
	  ILI9341_Init();
	  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
	  ILI9341_Fill_Screen(WHITE);
	  ILI9341_Draw_Text("Initialising", 10, 10, BLACK, 1, WHITE);
	  DM_RefreshBackgroundLayout();

}


/*
 *
 *
 *
 */
void DM_RegisterStrings()
{
	int res = 0;
	res = TM_RegisterString("ONE", 10, 220, 2);
	res = TM_RegisterString("TWO", 100, 220, 2);
	res = TM_RegisterString("THREE", 175, 220, 2);
	res = TM_RegisterString("FOUR", 260, 220, 2);
	if(res < 0)
	{
		ILI9341_Draw_Text("Exceeded String Buffer Bounds!", 10, 20, BLACK, 1, WHITE);
	}
}

/*
 *
 *	adds num to buffer with empty char padding
 *
 *	used so that smaller number can erase previously
 *	larger number when displayed on TFT
 *
 *	buflen should include terminating null zero
 *
 *	returns 	0 when OK
 *				1 if buflen is invalid size
 *				2 unknown error
 *
 */
int DM_AddDigitPadding(uint16_t num, char *buffer, uint16_t buflen)
{
	if((buflen < 1) || (buflen > 6))
		return 1;

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

	return 2;


}

/*
 *
 *
 *
 */

void DM_UpdateDisplay()
{
/*	int res;
	if( (res = TM_FindStringRegister("ONE")) >= 0 )
	{
		ILI9341_Draw_Text(STRINGREG[res].text, STRINGREG[res].x, STRINGREG[res].y, BLACK, STRINGREG[res].size, RED);
	}

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	50,
													50,
													100,
													100,
													RED,
													BORDER_SIZE,
													BLACK);
													*/
	int res;
//	if( (res = TM_FindStringRegister("ONE")) >= 0 )
//	{

		char tmp[6] = "";
		if(DM_AddDigitPadding(TIM6->CNT, tmp, sizeof(tmp)) == 0)
			ILI9341_Draw_Text(tmp, STRINGREG[0].x, STRINGREG[0].y, BLACK, STRINGREG[0].size, DARKCYAN);
//	}



	if( (res = TM_FindStringRegister("TWO")) >= 0 )
	{
		ILI9341_Draw_Text(STRINGREG[res].text, STRINGREG[res].x, STRINGREG[res].y, BLACK, STRINGREG[res].size, DARKGREEN);
	}


	if( (res = TM_FindStringRegister("THREE")) >= 0 )
	{
		ILI9341_Draw_Text(STRINGREG[res].text, STRINGREG[res].x, STRINGREG[res].y, BLACK, STRINGREG[res].size, YELLOW);
	}

	if( (res = TM_FindStringRegister("FOUR")) >= 0 )
	{
		ILI9341_Draw_Text(STRINGREG[res].text, STRINGREG[res].x, STRINGREG[res].y, BLACK, STRINGREG[res].size, RED);
	}


}

/*
 *
 *
 *
 */
void DM_TestScreen()
{
	  //----------------------------------------------------------FILLED CIRCLES EXAMPLE

	  			uint16_t xr = 0;
	  			uint16_t yr = 0;
	  			uint16_t radiusr = 0;
	  			uint16_t colourr = 0;
	  			xr = LL_RNG_ReadRandData32(RNG);
	  			yr = LL_RNG_ReadRandData32(RNG);
	  			radiusr = LL_RNG_ReadRandData32(RNG);
	  			colourr = LL_RNG_ReadRandData32(RNG);

	  			xr &= 0x01FF;
	  			yr &= 0x01FF;
	  			radiusr &= 0x001F;

	  			ILI9341_Draw_Filled_Circle(xr, yr, radiusr/2, colourr);

	  			char enc_buff[13] = "";
	  			snprintf(enc_buff, sizeof(enc_buff), "%d\n", new_enc_value);
	  			ILI9341_Draw_Text(enc_buff, 10, 20, BLACK, 5, WHITE);

	  			ILI9341_Draw_Text(control_pressed, 10, 60, BLACK, 5, WHITE);
	  		//HAL_Delay(1);
}
