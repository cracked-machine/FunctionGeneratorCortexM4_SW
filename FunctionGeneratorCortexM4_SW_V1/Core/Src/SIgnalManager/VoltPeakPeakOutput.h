/*
 * VppOutput.h
 *
 *  Created on: 14 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_VOLTPEAKPEAKOUTPUT_H_
#define SRC_SIGNALMANAGER_VOLTPEAKPEAKOUTPUT_H_

#include <stdint.h>

#include "pysine.h"

#define MAX_VPP_PRESETS 98
#define MAX_VPP_ENCODER_RANGE 398



typedef enum
{
	VPP01 = 0U,
	VPP02, 	VPP03, 	VPP04, 	VPP05,	VPP06,	VPP07,	VPP08,	VPP09,	VPP10,	VPP11,	VPP12,	VPP13,	VPP14,	VPP15,
	VPP16,	VPP17,	VPP18,	VPP19,	VPP20,	VPP21,	VPP22,	VPP23,	VPP24,	VPP25,	VPP26,	VPP27,	VPP28,	VPP29,
	VPP30,	VPP31,	VPP32,	VPP33,	VPP34,	VPP35,	VPP36,	VPP37,	VPP38,	VPP39,	VPP40,	VPP41,	VPP42,	VPP43,
	VPP44,	VPP45,	VPP46,	VPP47,	VPP48,	VPP49,	VPP50,	VPP51,	VPP52,	VPP53,	VPP54,	VPP55,	VPP56,	VPP57,
	VPP58,	VPP59,	VPP60,	VPP61,	VPP62,	VPP63,	VPP64,	VPP65,	VPP66,	VPP67,	VPP68,	VPP69,	VPP70,	VPP71,
	VPP72,	VPP73,	VPP74,	VPP75,	VPP76,	VPP77,	VPP78,	VPP79,	VPP80,	VPP81,  VPP82,	VPP83,	VPP84,	VPP85,
	VPP86,	VPP87,	VPP88,	VPP89,	VPP90,	VPP91,	VPP92,	VPP93,	VPP94,	VPP95,	VPP96,	VPP97,	VPP98,

} eAmpSettings_t;


/*
 *	object for Vpp Preset and its encoder position for amp profile menu
 */
typedef struct
{
	eAmpSettings_t amp_setting;
	float amp_value;
	uint8_t gain_preset;
	float gain_decibels;
	float neg_gain_coeff;
	float amp_offset;
	uint16_t epos;

} AmplitudeProfile_t;

/*
 * 		Array of  amp profile
 */
AmplitudeProfile_t theAmpProfiles[MAX_VPP_PRESETS];

#define LUT_VPP 2.7		// Used to calculate AmplitudeProfile_t.neg_gain_coeff. This must be less than MCU VDD = 3.3

/*
 * 		Function declarations
 */

void VPP_MapEncoderPositionToSignalOutput(uint16_t pEncoderValue);
void VPP_ApplyProfileToSignal(eAmpSettings_t pPresetEnum);

void VPP_MapEncoderPositionToAuxOutput(uint16_t pEncoderValue);
void VPP_ApplyProfileToAux(eAmpSettings_t pPresetEnum);

void VPP_ResetLastEncoderValue();

AmplitudeProfile_t * VPP_FindVppPresetObject(eAmpSettings_t pEnum);


#endif /* SRC_SIGNALMANAGER_VOLTPEAKPEAKOUTPUT_H_ */
