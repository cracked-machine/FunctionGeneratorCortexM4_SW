//	MIT License
//
//	Copyright (c) 2017 Matej Artnak
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, ExPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.
//
//
//
//-----------------------------------
//	ILI9341 GFx library for STM32
//-----------------------------------
//
//	Very simple GFx library built upon ILI9342_STM32_Driver library.
//	Adds basic shapes, image and font drawing capabilities to ILI9341
//
//	Library is written for STM32 HAL library and supports STM32CUBEMx. To use the library with Cube software
//	you need to tick the box that generates peripheral initialization code in their own respective .c and .h file
//
//
//-----------------------------------
//	How to use this library
//-----------------------------------
//
//	-If using MCUs other than STM32F7 you will have to change the #include "stm32g4xx_hal.h" in the ILI9341_GFx.h to your respective .h file
//
//	If using "ILI9341_STM32_Driver" then all other prequisites to use the library have allready been met
//	Simply include the library and it is ready to be used
//
//-----------------------------------


#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "5x5_font.h"
#include "spi.h"
#include <assert.h>
#include <math.h>

#include "fade_log_seq.h"
#include "fade_lin_seq.h"

 extern uint16_t BURST_MAX_SIZE;

 /*
  *
  *	@brief Draws an arrow pointing at the x,y centre point
  *
  *	TODO not completed
  *
  *						ARROW_DOWN
  *
  *							|
  *							|
  *					       \ /
  *						\		/
  *	ARROW_RIGHT		-----		-----	ARROW_LEFT
  *						/		\
  *					       / \
  *					        |
  *					        |
  *
  *	 	      			ARROW UP
  *
  *	@param None
  *	@retval None
  *
  */
 void ILI9341_Draw_Arrow(eILI9341_ArrowDirections_t dir, uint16_t x, uint16_t y, uint16_t len, uint16_t fcolour)
 {
	 uint8_t tip_width = 6;

	 switch(dir)
	 {
	 	 case ARROW_UP:
	 		ILI9341_Draw_Vertical_Line(x, y, len, fcolour);
	 		ILI9341_Draw_Horizontal_Line(x - (tip_width/2), y, tip_width, fcolour);
	 		break;

	 	 case ARROW_RIGHT:
	 		ILI9341_Draw_Horizontal_Line(x-len, y, len, fcolour);
	 		ILI9341_Draw_Vertical_Line(x, y - (tip_width/2), tip_width, fcolour);
	 		break;

	 	 case ARROW_DOWN:
	 		ILI9341_Draw_Vertical_Line(x, y-len, len, fcolour);
	 		ILI9341_Draw_Horizontal_Line(x - (tip_width/2), y, tip_width, fcolour);
	 		break;

	 	 case ARROW_LEFT:
	 		ILI9341_Draw_Horizontal_Line(x, y, len, fcolour);
	 		ILI9341_Draw_Vertical_Line(x, y - (tip_width/2), tip_width, fcolour);
	 		break;

	 }

 }

 /*
  *
  *	@brief Draw hollow circle at X,Y location with specified radius and colour. X and Y represent circles center
  *
  *	@param None
  *	@retval None
  *
  */

void ILI9341_Draw_Hollow_Circle(uint16_t x, uint16_t y, uint16_t Radius, uint16_t Colour)
{
	int tx = Radius-1;
    int ty = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (Radius << 1);

    while (tx >= ty)
    {
        ILI9341_Draw_Pixel(x + tx, y + ty, Colour);
        ILI9341_Draw_Pixel(x + ty, y + tx, Colour);
        ILI9341_Draw_Pixel(x - ty, y + tx, Colour);
        ILI9341_Draw_Pixel(x - tx, y + ty, Colour);
        ILI9341_Draw_Pixel(x - tx, y - ty, Colour);
        ILI9341_Draw_Pixel(x - ty, y - tx, Colour);
        ILI9341_Draw_Pixel(x + ty, y - tx, Colour);
        ILI9341_Draw_Pixel(x + tx, y - ty, Colour);

        if (err <= 0)
        {
        	ty++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
        	tx--;
            dx += 2;
            err += (-Radius << 1) + dx;
        }
    }
}

/*
 *
 *	@brief	Draw filled circle at X,Y location with specified radius and colour. X and Y represent circles center
 *
 *	@param None
 *	@retval None
 *
 */
void ILI9341_Draw_Filled_Circle(uint16_t x, uint16_t y, uint16_t r, uint16_t Colour)
{
	
	int tx = r;
    int ty = 0;
    int xChange = 1 - (r << 1);
    int yChange = 0;
    int radiusError = 0;

    while (tx >= ty)
    {
        for (int i = x - tx; i <= x + tx; i++)
        {
            ILI9341_Draw_Pixel(i, y + y,Colour);
            ILI9341_Draw_Pixel(i, y - ty,Colour);
        }
        for (int i = x - ty; i <= x + ty; i++)
        {
            ILI9341_Draw_Pixel(i, y + tx,Colour);
            ILI9341_Draw_Pixel(i, y - tx,Colour);
        }

        ty++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
        	tx--;
            radiusError += xChange;
            xChange += 2;
        }
    }
		//Really slow implementation, will require future overhaul
		//TODO:	https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles	
}


/*
 *
 *
 *
 *
 *
 */
void ILI9341_Draw_Hollow_Rectangle_Coord(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t colour)
{

	
	// Horizontal lines
	ILI9341_Draw_Horizontal_Line(	x,
									y,
									w,
									colour);

	ILI9341_Draw_Horizontal_Line(	x,
									y + h,
									w,
									colour);
	

	// Vertical lines
	ILI9341_Draw_Vertical_Line(		x,
									y,
									h,
									colour);

	ILI9341_Draw_Vertical_Line(		x + w,
									y,
									h,
									colour);

	
}

/*
 *
 *
 *
 *
 *
 *
 */
void ILI9341_Draw_Bordered_Filled_Rectangle_Coord(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t inner_colour, uint8_t border_weight, uint8_t border_colour)
{

	// Draw inwards (and shorter) for each level of border weight
	for(uint8_t b = 0; ; b++)
	{


		if(b > border_weight)
		{

			// stop before the inner space reaches zero! (hard fault)
			if( ((y + b) == ((y + h) - b)) || ((x + b) == ((x + w) - b)) )
			{
				// add final line?
				goto finish;
			}
			else
			{
				ILI9341_Draw_Rectangle(x + b, y + b, (w - (2*b)) + 1, (h - (2*b)) + 1, inner_colour, AREA_CHUNK);
				goto finish;
			}
		}

		// Horizontal lines
		ILI9341_Draw_Horizontal_Line(	x + b,
										y + b,
										w - (2*b),
										border_colour);

		ILI9341_Draw_Horizontal_Line(	x + b,
										(y + h) - b,
										w - (b),
										border_colour);


		// Vertical lines
		ILI9341_Draw_Vertical_Line(		x + b,
										y + b,
										h - (2*b),
										border_colour);

		ILI9341_Draw_Vertical_Line(		(x + w) - b,
										y + b,
										h - (2*b),
										border_colour);

	}

	finish:
	// done
	return;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void ILI9341_Draw_Bordered_Hollow_Rectangle_Coord(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t border_weight, uint8_t border_colour)
{

	// Draw inwards (and shorter) for each level of border weight
	for(uint8_t b = 0; b < border_weight; b++)
	{



		// Horizontal lines
		ILI9341_Draw_Horizontal_Line(	x + b,
										y + b,
										w - (2*b),
										border_colour);

		ILI9341_Draw_Horizontal_Line(	x + b,
										(y + h) - b,
										w - (b),
										border_colour);


		// Vertical lines
		ILI9341_Draw_Vertical_Line(		x + b,
										y + b,
										h - (2*b),
										border_colour);

		ILI9341_Draw_Vertical_Line(		(x + w) - b,
										y + b,
										h - (2*b),
										border_colour);

	}


}

/*
 *
 *	@brief	Draws a character (fonts imported from fonts.h) at x,Y location with specified font colour, size and Background colour
 *			See fonts.h implementation of font on what is required for changing to a different font when switching fonts libraries
 *
 *	@param None
 *	@retval None
 *
 */

void ILI9341_Draw_Char(char character, uint16_t x, uint16_t y, uint16_t colour, uint16_t size, uint16_t bgcolour)
{
	uint8_t 	function_char;
    uint8_t 	i,j;
		



	function_char = character;
		
    if (function_char < ' ')
    {
        character = 0;
    }
    else
    {
    	function_char -= 32;
	}
   	
	char temp[CHAR_WIDTH];

	for(uint8_t k = 0; k<CHAR_WIDTH; k++)
	{
		temp[k] = font[function_char][k];
	}
		
    // Draw pixels
	//ILI9341_Draw_Rectangle(x, Y, CHAR_WIDTH*size, CHAR_HEIGHT*size, bgcolour);
    for (j=0; j<CHAR_WIDTH; j++)
    {
        for (i=0; i<CHAR_HEIGHT; i++)
        {
            if (temp[j] & (1<<i))
            {
            	if(size == 1)
				{
            		ILI9341_Draw_Pixel(x+j, y+i, colour);
				}
				else
				{
					ILI9341_Draw_Rectangle(x+(j*size), y+(i*size), size, size, colour, TEXT_CHUNK);
				}
            }
            else
            {
               	if(size == 1)
				{
					ILI9341_Draw_Pixel(x+j, y+i, bgcolour);
				}
				else
				{
					ILI9341_Draw_Rectangle(x+(j*size), y+(i*size), size, size, bgcolour, TEXT_CHUNK);
				}
            }
        }
    }
}

/*
 *
 *	@brief	Draws an array of characters (fonts imported from fonts.h) at x,Y location with specified font colour, size and Background colour
 *			See fonts.h implementation of font on what is required for changing to a different font when switching fonts libraries
 *
 *	@param None
 *	@retval None
 *
 */
void ILI9341_Draw_Text(const char* Text, uint16_t x, uint16_t y, uint16_t colour, uint16_t size, uint16_t bgcolour)
{
    /*if(size & 1)
    {
    	size = ((size >> 1) * 2);
    }*/

    while (*Text) {
        ILI9341_Draw_Char(*Text++, x, y, colour, size, bgcolour);
        x += CHAR_WIDTH*size;
    }


}

/*
 *
 *	@brief	Draws a full screen picture from flash. Image converted from RGB .jpeg/other to C array using online converter
 *			USING CONVERTER: http://www.digole.com/tools/PicturetoC_Hex_converter.php
 *			65K colour (2Bytes / Pixel)
 *
 *	@param None
 *	@retval None
 *
 */
void ILI9341_Draw_Image(const char* Image_Array, uint8_t Orientation)
{
	if(Orientation == SCREEN_HORIZONTAL_1)
	{
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
		ILI9341_Set_Frame(0, 0, ILI9341_SCREEN_WIDTH, ILI9341_SCREEN_HEIGHT);
			
		GPIOC->ODR |= DC_Pin;
		GPIOC->ODR &= ~(DC_Pin);
		
		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{			
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];		
				}						
				HAL_SPI_Transmit(&hspi3, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		GPIOC->ODR |= CS_Pin;
	}
	else if(Orientation == SCREEN_HORIZONTAL_2)
	{
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Set_Frame(0,0,ILI9341_SCREEN_WIDTH,ILI9341_SCREEN_HEIGHT);
			
		GPIOC->ODR |= DC_Pin;
		GPIOC->ODR &= ~(CS_Pin);
		
		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{			
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];		
				}						
				HAL_SPI_Transmit(&hspi3, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		GPIOC->ODR |= CS_Pin;
	}
	else if(Orientation == SCREEN_VERTICAL_2)
	{
		ILI9341_Set_Rotation(SCREEN_VERTICAL_2);
		ILI9341_Set_Frame(0,0,ILI9341_SCREEN_HEIGHT,ILI9341_SCREEN_WIDTH);
			
		GPIOC->ODR |= DC_Pin;
		GPIOC->ODR &= ~(CS_Pin);
		
		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{			
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];		
				}						
				HAL_SPI_Transmit(&hspi3, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		GPIOC->ODR |= CS_Pin;
	}
	else if(Orientation == SCREEN_VERTICAL_1)
	{
		ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
		ILI9341_Set_Frame(0,0,ILI9341_SCREEN_HEIGHT,ILI9341_SCREEN_WIDTH);
			
		GPIOC->ODR |= DC_Pin;
		GPIOC->ODR &= ~(CS_Pin);
		
		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{			
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];		
				}						
				HAL_SPI_Transmit(&hspi3, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		GPIOC->ODR |= CS_Pin;
	}
}

/*
 *
 *	@brief	Draws a full screen picture from flash. Image converted from RGB .jpeg/other to C array using online converter
 *			USING CONVERTER: http://www.digole.com/tools/PicturetoC_Hex_converter.php
 *			65K colour (2Bytes / Pixel)
 *
 *	@param None
 *	@retval None
 *
 */
void ILI9341_Draw_ImageF(const float* Image_Array, uint8_t Orientation)
{
	if(Orientation == SCREEN_HORIZONTAL_1)
	{
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
		ILI9341_Set_Frame(0,0,ILI9341_SCREEN_WIDTH,ILI9341_SCREEN_HEIGHT);

		GPIOC->ODR |= DC_Pin;
		GPIOC->ODR &= ~(CS_Pin);

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= (unsigned char)Image_Array[counter+k] * 100;
				}
				HAL_SPI_Transmit(&hspi3, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		GPIOC->ODR |= CS_Pin;
	}
	else if(Orientation == SCREEN_HORIZONTAL_2)
	{
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Set_Frame(0,0,ILI9341_SCREEN_WIDTH,ILI9341_SCREEN_HEIGHT);

		GPIOC->ODR |= DC_Pin;
		GPIOC->ODR &= ~(CS_Pin);

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];
				}
				HAL_SPI_Transmit(&hspi3, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		GPIOC->ODR |= CS_Pin;
	}
	else if(Orientation == SCREEN_VERTICAL_2)
	{
		ILI9341_Set_Rotation(SCREEN_VERTICAL_2);
		ILI9341_Set_Frame(0,0,ILI9341_SCREEN_HEIGHT,ILI9341_SCREEN_WIDTH);

		GPIOC->ODR |= DC_Pin;
		GPIOC->ODR &= ~(CS_Pin);

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];
				}
				HAL_SPI_Transmit(&hspi3, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		GPIOC->ODR |= CS_Pin;
	}
	else if(Orientation == SCREEN_VERTICAL_1)
	{
		ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
		ILI9341_Set_Frame(0,0,ILI9341_SCREEN_HEIGHT,ILI9341_SCREEN_WIDTH);

		GPIOC->ODR |= DC_Pin;
		GPIOC->ODR &= ~(CS_Pin);

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];
				}
				HAL_SPI_Transmit(&hspi3, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		GPIOC->ODR |= CS_Pin;
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
void ILI9341_FillScreenGradient()
{
	uint16_t x = 0;
	//ILI9341_Fill_Screen(WHITE);
	//ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
	//ILI9341_Draw_Text("Colour gradient", 10, 10, BLACK, 1, WHITE);
	//ILI9341_Draw_Text("Grayscale", 10, 20, BLACK, 1, WHITE);



	for(uint16_t i = 0; i <= (320); i++)
	{
/*		uint16_t Red = 0;
		uint16_t Green = 0;
		uint16_t Blue = 0;

		Red = i/(10);
		Red <<= 11;
		Green = i/(5);
		Green <<= 5;
		Blue = i/(10);



		uint16_t RGB_color = Red + Green + Blue;
		ILI9341_Draw_Rectangle(i, x, 1, 240, RGB_color, AREA_CHUNK);
*/

	ILI9341_Draw_Rectangle(i, x, 1, 240, (uint16_t)fade_log_seq_data_table[i], AREA_CHUNK);

	}
}

