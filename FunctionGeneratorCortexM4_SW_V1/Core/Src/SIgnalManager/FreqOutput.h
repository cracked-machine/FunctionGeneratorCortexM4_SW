/*
 * FreqOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FREQOUTPUT_H_
#define SRC_SIGNALMANAGER_FREQOUTPUT_H_

#include <stdint.h>

#define FREQ_ENCODER_MAG 1						// adjustment speed
#define FREQ_ENCODER_MAX 384/FREQ_ENCODER_MAG

void FreqO_ModifyOutput();
uint32_t FreqO_GetOutputFreq();

#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_H_ */