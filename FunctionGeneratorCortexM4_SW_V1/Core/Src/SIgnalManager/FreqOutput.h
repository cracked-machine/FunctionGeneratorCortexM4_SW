/*
 * FreqOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FREQOUTPUT_H_
#define SRC_SIGNALMANAGER_FREQOUTPUT_H_

#include <stdint.h>

typedef enum
{
	FPRESET_1HZ 	= 1U,
	FPRESET_10HZ	= 10U,
	FPRESET_50HZ	= 50U,
	FPRESET_100HZ	= 100U,
	FPRESET_250HZ	= 250U,
	FPRESET_500HZ	= 500U,
	FPRESET_750HZ	= 750U,
	FPRESET_1KHZ	= 1000U,
	FPRESET_5KHZ	= 5000U,
	FPRESET_10KHZ	= 10000U,
	FPRESET_25KHZ	= 25000U,
	FPRESET_50KHZ	= 50000U,
	FPRESET_75KHZ	= 75000U,
	FPRESET_100KHZ	= 100000U

} eFreq_Preset;

#define FREQ_ENCODER_HIFREQ_MAG 1						// adjustment speed
#define FREQ_ENCODER_MIDFREQ_MAG 5						// adjustment speed
#define FREQ_ENCODER_LOFREQ_MAG 10						// adjustment speed
#define FREQ_ENCODER_MAX 65535

void FreqO_ModifyOutput();
uint32_t FreqO_GetOutputFreq();

void FreqO_ApplyPreset(eFreq_Preset pPreset);
void FreqO_ApplyPreset_Fast(eFreq_Preset pPreset);

eFreq_Preset FreqO_GetFPreset();
void FreqO_AdjustFreq();

#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_H_ */
