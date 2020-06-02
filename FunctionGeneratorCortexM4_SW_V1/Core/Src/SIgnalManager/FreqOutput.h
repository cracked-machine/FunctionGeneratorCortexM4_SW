/*
 * FreqOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FREQOUTPUT_H_
#define SRC_SIGNALMANAGER_FREQOUTPUT_H_

#include <stdint.h>


/*
 *	Frequency Profile value enumerations
 */
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

} eFreqSettings_t;

#define MAX_NUM_FREQ_PRESETS 14

/*
 *	Frequency Profile structure
 */
typedef struct
{
	uint8_t 		index;			// index is needed, "eFreqSettings_t" literals are mapped to value

	eFreqSettings_t hertz;

	uint32_t		psc;			// MCU timer prescaler. Default 0. Set higher for freq < 20Hz.

	uint32_t		arr;			// MCU timer auto-reload (top). Set by FreqO_InitFreqProfiles()

	float			error;			// coefficient for error correction, set to 1.0 if not required
									// 0 < error < 1	- correction for under freq (increase)
									// 1 < error		- correction for over freq (decrease)
} FreqProfile_t;

// array of frequency profiles, one for each eFreqSettings_t enum
FreqProfile_t theFreqProfiles[MAX_NUM_FREQ_PRESETS];

// the active frequency profile!
FreqProfile_t *freq_profile;

uint8_t FreqPresetEncoderRange;

/*
 *  Function definitions
 */

void 			FreqO_InitFreqProfiles();

void 			FreqO_MapEncoderPositionCoarse(uint16_t pEncValue);
void 			FreqO_MapEncoderPositionFine(uint16_t pEncValue);

void 			FreqO_ApplyProfile(eFreqSettings_t pPresetEnum);
void 			FreqO_AdjustFreq();


uint32_t 		FreqO_GetOutputFreq();
void 			FreqO_ResetLastEncoderValue();

FreqProfile_t * FreqO_FindFPresetObject(eFreqSettings_t pEnum);
FreqProfile_t * FreqO_GetFPresetObject();
uint8_t 		FreqO_GetPresetEncoderPos();
uint8_t 		FreqO_GetFreqPresetEncoderRange();
FreqProfile_t* 	FreqO_GetProfileByIndex(uint32_t pIndex);


#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_H_ */
