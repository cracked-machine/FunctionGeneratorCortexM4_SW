/*
 * DacChannel.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_DACCHANNEL_H_
#define SRC_SIGNALMANAGER_DACCHANNEL_H_


#include "FunctionOutput.h"
#include "dac.h"

typedef enum
{
	SIGNAL_OUT_DAC = 0U,
	SYNC_OUT_DAC

} eOutputDac_t;

typedef enum
{
	STM_DAC_CH1 = DAC_CHANNEL_1,
	STM_DAC_CH2 = DAC_CHANNEL_2
} eOutputDacChannel_t;

typedef struct
{
	eOutputDac_t theDac;
	eOutputDacChannel_t channel;
	eOutput_mode function;
	uint32_t *pProcessedDataTable;

} DacDevice_t;

DacDevice_t *pSignalOutputDac;
DacDevice_t *pSyncOutputDac;


void DAC_InitDevices();

#endif /* SRC_SIGNALMANAGER_DACCHANNEL_H_ */
