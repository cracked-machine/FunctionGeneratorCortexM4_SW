/*
 * BiasOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_BIASOUTPUT_H_
#define SRC_SIGNALMANAGER_BIASOUTPUT_H_

#include <stdint.h>



// dc bias constants
#define BIAS_MAG 10						// adjustment speed
#define BIAS_MAX 8092/BIAS_MAG			// The encoder max value: top=max pos bias, 0=max neg bias
#define BIAS_CENTER	4096/BIAS_MAG		// the encoder center value: zero crossing point

void BO_ModifyOutput();
uint32_t BO_GetOutputBias();

#endif /* SRC_SIGNALMANAGER_BIASOUTPUT_H_ */