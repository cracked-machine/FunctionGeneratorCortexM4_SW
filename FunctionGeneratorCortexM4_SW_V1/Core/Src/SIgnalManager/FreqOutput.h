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
	FPRESET_100HZ,
	FPRESET_1KHZ,
	FPRESET_100KHZ

} eFreq_Preset;

#define FREQ_ENCODER_MAG 1						// adjustment speed
#define FREQ_ENCODER_MAX 384/FREQ_ENCODER_MAG

void FreqO_ModifyOutput();
uint32_t FreqO_GetOutputFreq();
void FreqO_ApplyPreset(eFreq_Preset pPreset);

#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_H_ */
