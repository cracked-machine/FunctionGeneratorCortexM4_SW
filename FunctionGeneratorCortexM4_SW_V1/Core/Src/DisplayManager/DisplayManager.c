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


#define BUTTON_WIDTH (ILI9341_SCREEN_WIDTH)/4
//#define BUTTON_Y_POSITION ILI9341_SCREEN_HEIGHT-50

#define BORDER_SIZE 10

//uint16_t button_x_positions[4] = { BORDER_SIZE-1, (BUTTON_WIDTH)+1, (BUTTON_WIDTH*2)+1, (BUTTON_WIDTH*3)+1 };
#define BUTTON_Y_POSITION 50
uint16_t button_x_positions[1] = { (BUTTON_WIDTH) };


void dm_update_display()
{


	// BLUE BUTTON GFX
/*	ILI9341_Draw_Filled_Rectangle_Coord(	button_x_positions[0] + (BORDER_SIZE),
											BUTTON_Y_POSITION + (BORDER_SIZE),
											(button_x_positions[0] + BUTTON_WIDTH) - (BORDER_SIZE),
											BUTTON_Y_POSITION*2 - (BORDER_SIZE),
											DARKCYAN);

*/

	ILI9341_Draw_Bordered_Hollow_Rectangle_Coord(	10,
													50,
													90,
													50,
													BLACK,
													20);


	ILI9341_Draw_Rectangle(100, 100, 100, 100, RED);
/*
		// BLUE BUTTON GFX
		ILI9341_Draw_Filled_Rectangle_Coord(	button_x_positions[0] + (BORDER_SIZE),
												BUTTON_Y_POSITION + (BORDER_SIZE),
												(button_x_positions[0] + BUTTON_WIDTH) - (BORDER_SIZE),
												ILI9341_SCREEN_HEIGHT - (BORDER_SIZE),
												DARKCYAN);

		ILI9341_Draw_Bordered_Hollow_Rectangle_Coord(	button_x_positions[0],
														BUTTON_Y_POSITION,
														button_x_positions[0] + BUTTON_WIDTH,
														ILI9341_SCREEN_HEIGHT,
														BLACK,
														BORDER_SIZE);

		// GREEN BUTTON GFX
		ILI9341_Draw_Filled_Rectangle_Coord(	button_x_positions[1] + (BORDER_SIZE),
												BUTTON_Y_POSITION + (BORDER_SIZE),
												(button_x_positions[1] + BUTTON_WIDTH) - (BORDER_SIZE),
												ILI9341_SCREEN_HEIGHT - (BORDER_SIZE),
												DARKGREEN);

		ILI9341_Draw_Bordered_Hollow_Rectangle_Coord(	button_x_positions[1],
														BUTTON_Y_POSITION,
														button_x_positions[1] + BUTTON_WIDTH,
														ILI9341_SCREEN_HEIGHT,
														BLACK,
														BORDER_SIZE);

		// YELLOW BUTTON GFX
		ILI9341_Draw_Filled_Rectangle_Coord(	button_x_positions[2] + (BORDER_SIZE),
												BUTTON_Y_POSITION + (BORDER_SIZE),
												(button_x_positions[2] + BUTTON_WIDTH) - (BORDER_SIZE),
												ILI9341_SCREEN_HEIGHT - (BORDER_SIZE),
												YELLOW);

		ILI9341_Draw_Bordered_Hollow_Rectangle_Coord(	button_x_positions[2],
														BUTTON_Y_POSITION,
														button_x_positions[2] + BUTTON_WIDTH,
														ILI9341_SCREEN_HEIGHT,
														BLACK,
														BORDER_SIZE);

		// RED BUTTON GFX
		ILI9341_Draw_Filled_Rectangle_Coord(	button_x_positions[3] + (BORDER_SIZE),
												BUTTON_Y_POSITION + (BORDER_SIZE),
												(button_x_positions[3] + BUTTON_WIDTH) - (BORDER_SIZE),
												ILI9341_SCREEN_HEIGHT,
												RED);

		ILI9341_Draw_Bordered_Hollow_Rectangle_Coord(	button_x_positions[3],
														BUTTON_Y_POSITION,
														button_x_positions[3] + BUTTON_WIDTH,
														ILI9341_SCREEN_HEIGHT,
														BLACK,
														BORDER_SIZE);
*/

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
