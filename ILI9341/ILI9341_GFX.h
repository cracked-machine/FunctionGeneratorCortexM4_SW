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
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
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
//	ILI9341 GFX library for STM32
//-----------------------------------
//
//	Very simple GFX library built upon ILI9342_STM32_Driver library.
//	Adds basic shapes, image and font drawing capabilities to ILI9341
//
//	Library is written for STM32 HAL library and supports STM32CUBEMX. To use the library with Cube software
//	you need to tick the box that generates peripheral initialization code in their own respective .c and .h file
//
//
//-----------------------------------
//	How to use this library
//-----------------------------------
//
//	-If using MCUs other than STM32F7 you will have to change the #include "stm32g4xx_hal.h" in the ILI9341_GFX.h to your respective .h file
//
//	If using "ILI9341_STM32_Driver" then all other prequisites to use the library have allready been met
//	Simply include the library and it is ready to be used
//
//-----------------------------------

#ifndef ILI9341_GFX_H
#define ILI9341_GFX_H

#include "stm32g4xx_hal.h"
#include "STMBasicGui.h"

typedef enum
{
	ARROW_DOWN = 0U,
	ARROW_LEFT,
	ARROW_UP,
	ARROW_RIGHT
} eILI9341_ArrowDirections_t;


#define HORIZONTAL_IMAGE	0
#define VERTICAL_IMAGE		1


void ILI9341_Draw_Wave(uint16_t x, uint16_t y, uint8_t weight, uint16_t colour, uint8_t scale, uint32_t* data_table, uint16_t data_table_size);

void ILI9341_Draw_Arrow(eILI9341_ArrowDirections_t dir, uint16_t x, uint16_t y, uint16_t len, uint16_t fcolour);

void ILI9341_Draw_Hollow_Circle(uint16_t x, uint16_t Y, uint16_t Radius, uint16_t colour);
void ILI9341_Draw_Filled_Circle(uint16_t x, uint16_t Y, uint16_t Radius, uint16_t colour);

void ILI9341_Draw_Hollow_Rectangle_Coord(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t colour);
void ILI9341_Draw_Bordered_Filled_Rectangle_Coord(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t inner_colour, uint8_t border_weight, uint16_t border_colour);
void ILI9341_Draw_Bordered_Hollow_Rectangle_Coord(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t border_weight, uint8_t border_colour);
void ILI9341_Draw_Char(char character, uint16_t x, uint16_t y, uint16_t colour, uint16_t size, uint16_t bgcolour);
void ILI9341_Draw_Text(const char* Text, uint16_t x, uint16_t y, uint16_t colour, uint16_t size, uint16_t bgcolour);
void ILI9341_FillScreenGradient();
//void ILI9341_Draw_Filled_Rectangle_size_Text(uint16_t x, uint16_t Y0, uint16_t size_X, uint16_t size_Y, uint16_t colour);

//USING CONVERTER: http://www.digole.com/tools/PicturetoC_Hex_converter.php
//65K colour (2Bytes / Pixel)
void ILI9341_Draw_Image(const char* Image_Array, uint8_t Orientation);
void ILI9341_Draw_ImageF(const float* Image_Array, uint8_t Orientation);

#endif
