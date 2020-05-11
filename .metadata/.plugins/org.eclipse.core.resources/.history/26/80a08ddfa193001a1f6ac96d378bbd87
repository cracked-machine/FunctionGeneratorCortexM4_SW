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
	FPRESET_1HZ = 0U,
	FPRESET_10HZ,
	FPRESET_50HZ,
	FPRESET_100HZ,
	FPRESET_250HZ,
	FPRESET_500HZ,
	FPRESET_750HZ,
	FPRESET_1KHZ,
	FPRESET_5KHZ,
	FPRESET_10KHZ,
	FPRESET_25KHZ,
	FPRESET_50KHZ,
	FPRESET_75KHZ,
	FPRESET_100KHZ

} eFreq_Preset;

#define FREQ_ENCODER_HIFREQ_MAG 1						// adjustment speed
#define FREQ_ENCODER_MIDFREQ_MAG 5						// adjustment speed
#define FREQ_ENCODER_LOFREQ_MAG 10						// adjustment speed
#define FREQ_ENCODER_MAX 65535

void FreqO_ModifyOutput();
uint32_t FreqO_GetOutputFreq();
void FreqO_ApplyPreset(eFreq_Preset pPreset);
eFreq_Preset FreqO_GetFPreset();

#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_H_ */
