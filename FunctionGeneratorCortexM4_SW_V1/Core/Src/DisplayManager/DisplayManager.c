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


#define BUTTON_WIDTH 				(ILI9341_SCREEN_WIDTH)/4
#define BUTTON_Y_POSITION 			(ILI9341_SCREEN_HEIGHT)-50
#define BORDER_size 				10
#define BUTTON_TEXT_X_POS 			(ILI9341_SCREEN_WIDTH)/8
#define BUTTON_TEXT_Y_POS 			(ILI9341_SCREEN_HEIGHT)-25

uint16_t button_x_positions[4] = { 0, (BUTTON_WIDTH)+1, (BUTTON_WIDTH*2)+1, (BUTTON_WIDTH*3)+1 };
//#define BUTTON_Y_POSITION 50
//uint16_t button_x_positions[1] = { (BUTTON_WIDTH) };

uint8_t size_test = 1;

void dm_update_display()
{

	ILI9341_Draw_Text("TEST", 10, 2, BLACK, 3, DARKCYAN);

	ILI9341_Draw_Text("TEST", 200, 200, BLACK, 3, DARKCYAN);



	//ILI9341_Draw_Filled_Circle(50, 50, 50, BLUE);
	ILI9341_Draw_Text("TEST", 10, 200, BLACK, 3, DARKCYAN);


	size_test++;
	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	button_x_positions[0],
													BUTTON_Y_POSITION,
													BUTTON_WIDTH,
													50,
													DARKCYAN,
													3,
													BLACK);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	button_x_positions[1],
													BUTTON_Y_POSITION,
													BUTTON_WIDTH,
													50,
													DARKGREEN,
													3,
													BLACK);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	button_x_positions[2],
													BUTTON_Y_POSITION,
													BUTTON_WIDTH,
													50,
													YELLOW,
													3,
													BLACK);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	button_x_positions[3],
													BUTTON_Y_POSITION,
													BUTTON_WIDTH,
													50,
													RED,
													3,
													BLACK);



	//dm_test_screen();
}

void dm_test_screen()
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
