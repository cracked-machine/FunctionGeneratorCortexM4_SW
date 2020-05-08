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

#include "ILI9341_TextManager.h"

 extern uint16_t BURST_MAX_SIZE;

#define BTN_WIDTH 				(ILI9341_SCREEN_WIDTH)/4
#define BTN_HEIGHT				50
#define BTN_Y_POS 				(ILI9341_SCREEN_HEIGHT)-40
#define BORDER_SIZE				10
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
void DM_Init()
{
	  ILI9341_Init();
	  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
	  ILI9341_Fill_Screen(WHITE);
	  ILI9341_Draw_Text("Initialising", 10, 10, BLACK, 1, WHITE);
}

/*
 *
 *
 *
 */
void DM_RegisterStrings()
{
	int res = 0;
	res = TM_RegisterString("ONE", 100, 200, 2);
	res = TM_RegisterString("TWO", 110, 210, 3);
	res = TM_RegisterString("THREE", 170, 210, 3);
	res = TM_RegisterString("FOUR", 250, 210, 3);
	if(res < 0)
	{
		ILI9341_Draw_Text("Exceeded String Buffer Bounds!", 10, 20, BLACK, 1, WHITE);
	}
}

/*
 *
 *
 *
 */
void DM_UpdateDisplay()
{
	int res;
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
	/*
	int res;
	if( (res = TM_FindStringRegister("ONE")) >= 0 )
	{
		ILI9341_Draw_Text(STRINGREG[res].text, STRINGREG[res].x, STRINGREG[res].y, BLACK, STRINGREG[res].size, DARKCYAN);
	}

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[0],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													DARKCYAN,
													BORDER_SIZE,
													BLACK);

	if( (res = TM_FindStringRegister("TWO")) >= 0 )
	{
		ILI9341_Draw_Text(STRINGREG[res].text, STRINGREG[res].x, STRINGREG[res].y, BLACK, STRINGREG[res].size, DARKGREEN);
	}

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[1],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													DARKGREEN,
													BORDER_SIZE,
													BLACK);
	if( (res = TM_FindStringRegister("THREE")) >= 0 )
	{
		ILI9341_Draw_Text(STRINGREG[res].text, STRINGREG[res].x, STRINGREG[res].y, BLACK, STRINGREG[res].size, YELLOW);
	}
	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[2],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													YELLOW,
													BORDER_SIZE,
													BLACK);
	if( (res = TM_FindStringRegister("FOUR")) >= 0 )
	{
		ILI9341_Draw_Text(STRINGREG[res].text, STRINGREG[res].x, STRINGREG[res].y, BLACK, STRINGREG[res].size, RED);
	}
	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[3],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													RED,
													BORDER_SIZE,
													BLACK);
*/
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
