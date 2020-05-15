/*
 * DacDevice.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include "DacChannel.h"
#include <stdio.h>


void DAC_InitDevices()
{
	// init DacDevice_t for signal output
	pSignalOutputDac->theDac = SIGNAL_OUT_DAC;
	pSignalOutputDac->channel = STM_DAC_CH1;
	pSignalOutputDac->function = SINE_FUNC_MODE;

	for(int i = 0; i < SINE_DATA_SIZE; i++)
		pSignalOutputDac->pProcessedDataTable[i] = sine_data_table_3600[i];

	for(int i = 0; i < SINE_DATA_SIZE; i++)
		printf("%lu\n", pSignalOutputDac->pProcessedDataTable[i]);

	// init DacDevice_t for sync output
	pSyncOutputDac->theDac = SYNC_OUT_DAC;
	pSyncOutputDac->channel = STM_DAC_CH1;
	pSyncOutputDac->function = SAW_FUNC_MODE;

	for(int i = 0; i < SINE_DATA_SIZE; i++)
		pSyncOutputDac->pProcessedDataTable[i] = saw_data_table_3600[i];

}
