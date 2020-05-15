/*
 * DacTimer.c
 *
 *  Created on: 12 May 2020
 *      Author: chris
 */

#include "DacTimerRegistry.h"

/*
 *
 */
DacTimeReg_t DacTimerReg[MAX_DAC_TIMER_SETTINGS] =
{

		{0, 	FPRESET_1HZ, 	0x0016,	0, 1.0},
		{1, 	FPRESET_10HZ, 	0x0003,	0, 1.0},
		{2, 	FPRESET_50HZ,	0x0000,	0, 1.0},
		{3, 	FPRESET_100HZ,	0x0000, 0, 1.0},
		{4, 	FPRESET_250HZ, 	0x0000, 0, 1.0},
		{5, 	FPRESET_500HZ,	0x0000, 0, 1.0},
		{6, 	FPRESET_750HZ,	0x0000, 0, 1.0},
		{7, 	FPRESET_1KHZ,	0x0000, 0, 1.0},
		{8, 	FPRESET_5KHZ,	0x0000, 0, 1.0},
		{9, 	FPRESET_10KHZ,	0x0000, 0, 1.0},
		{10,	FPRESET_25KHZ,  0x0000, 0, 0.99},
		{11,	FPRESET_50KHZ,  0x0000, 0, 0.99},
		{12,	FPRESET_75KHZ,  0x0000, 0, 1.0},
		{13,	FPRESET_100KHZ, 0x0000, 0, 0.95}

};

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void DT_InitRegister()
{
	for(int i = 0; i < MAX_DAC_TIMER_SETTINGS; i++)
	{
		// prevent divide by zero (prescaler)
		if(DacTimerReg[i].psc == 0)
			DacTimerReg[i].arr = ((SM_MCLK / DacTimerReg[i].hertz) / SM_FSAMP) * DacTimerReg[i].error;
		else
			DacTimerReg[i].arr = (((SM_MCLK / DacTimerReg[i].hertz) / DacTimerReg[i].psc) / SM_FSAMP) * DacTimerReg[i].error;
	}
}


/*
 *
 *	@brief Index-based lookup for DAC Timer registry
 *
 *	@param pIndex The index of DacTimerReg array "DacTimeReg_t" struct
 *	@retval pointer to the DacTimeReg_t struct
 */
DacTimeReg_t* DT_GetRegisterByIndex(uint8_t pIndex)
{
	return &DacTimerReg[pIndex];
}

/*
 *
 *	@brief Enum-based Search for DAC Timer registry
 *
 *	@param pEnum Enummeration (eFreqSettings_t) search criteria. Not an index
 *	@retval Pointer to the found DacTimeReg_t struct. Null if no result!
 *
 */
DacTimeReg_t* DT_GetRegisterByEnum(eFreqSettings_t pEnum)
{
	for(int i = 0; i < MAX_DAC_TIMER_SETTINGS; i++)
		if(DacTimerReg[i].hertz == pEnum)
			return &DacTimerReg[i];

	return 0;
}


