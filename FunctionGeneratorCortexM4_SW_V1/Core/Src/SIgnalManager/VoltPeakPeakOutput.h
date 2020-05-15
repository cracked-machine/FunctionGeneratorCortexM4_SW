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

uint32_t tmpDataTable[SINE_DATA_SIZE];

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

} eVppPreset_t;


/*
 *	object for Vpp Preset and its encoder position for Vpp preset menu
 */
typedef struct
{
	eVppPreset_t Vpp_literal;
	float Vpp_target;
	uint8_t gain_preset;
	char* gain_decibels;
	float neg_gain_coeff;
	float vpp_offset;
	uint16_t epos;

} VppEncoderPreset_t;

typedef enum
{
	SIGNAL_OUTPUT_PRESET = 0U,
	SYNC_OUTPUT_PRESET
} eVppActivePresetSelect_t;


/*
 * 		Array of Vpp presets
 */
VppEncoderPreset_t aVppEncoderPresets[MAX_VPP_PRESETS];

/*
 * 		Pointer to active Vpp preset
 */
VppEncoderPreset_t* pSignalVppEncoderPreset;

/*
 * 		Pointer to active "sync output" Vpp preset
 */
VppEncoderPreset_t* pSyncVppEncoderPreset;


/*
 * 		Function declarations
 */

void VPP_ModifySignalOutput(uint16_t pEncoderValue);
void VPP_ApplyPresetToSignal(eVppPreset_t pPresetEnum);
//void VPP_ProcessDataTable(float _neg_gain_coeff, uint16_t _encoder_value);

VppEncoderPreset_t * VPP_FindVppPresetObject(eVppPreset_t pEnum);
VppEncoderPreset_t * VPP_GetVppPresetObject(eVppActivePresetSelect_t eVppActivePresetSelect);





#endif /* SRC_SIGNALMANAGER_VOLTPEAKPEAKOUTPUT_H_ */
