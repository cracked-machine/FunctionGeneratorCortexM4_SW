/*
 * ILI9341_TextManager.h
 *
 *  Created on: 6 May 2020
 *      Author: chris
 */

#ifndef ILI9341_TEXTMANAGER_H_
#define ILI9341_TEXTMANAGER_H_

#include <stdint.h>

#define MAX_REG_INDEX 4
#define MAX_TEXT_LENGTH 32



typedef struct
{
	char text[MAX_TEXT_LENGTH];
	int16_t x;
	int16_t y;
	int8_t size;
} StringRegister;

StringRegister STRINGREG[MAX_REG_INDEX];

void TM_DeRegisterString(uint8_t pIndex);
int TM_RegisterString(char* pText, int16_t pX, int16_t pY, int16_t pSize);
int TM_FindStringRegister(char* pSearch);

#endif /* ILI9341_TEXTMANAGER_H_ */
