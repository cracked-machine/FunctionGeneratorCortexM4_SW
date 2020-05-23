/*
 * VoltPeakPeakOutput.c
 *
 *  Created on: 14 May 2020
 *      Author: chris
 */

#include "VoltPeakPeakOutput.h"
#include "DisplayManager.h"


#include "dac.h"

//#define AMP_OFFSET 20   // gain 4
#define AMP_OFFSET 20   // gain 5
#define AMP_OFFSET50 AMP_OFFSET+50
#define AMP_OFFSET60 AMP_OFFSET+60
#define AMP_OFFSET70 AMP_OFFSET+70
#define AMP_OFFSET80 AMP_OFFSET+80
#define AMP_OFFSET90 AMP_OFFSET+90
#define AMP_OFFSET100 AMP_OFFSET+100


/*
 * 		Array of Vpp presets
 */
AmplitudeProfile_t theAmpProfiles[MAX_VPP_PRESETS] =
{

		{	VPP01	,	0.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	392	},
		{	VPP02	,	0.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	388	},
		{	VPP03	,	0.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	384	},
		{	VPP04	,	0.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	380	},
		{	VPP05	,	0.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	376	},
		{	VPP06	,	0.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	372	},
		{	VPP07	,	0.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	368	},
		{	VPP08	,	0.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	364	},
		{	VPP09	,	0.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	360	},
		{	VPP10	,	1.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	356	},
		{	VPP11	,	1.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	352	},
		{	VPP12	,	1.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	348	},
		{	VPP13	,	1.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	344	},
		{	VPP14	,	1.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	340	},
		{	VPP15	,	1.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	336	},
		{	VPP16	,	1.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	332	},
		{	VPP17	,	1.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	328	},
		{	VPP18	,	1.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	324	},
		{	VPP19	,	1.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	320	},
		{	VPP20	,	2.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	316	},
		{	VPP21	,	2.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	312	},
		{	VPP22	,	2.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	308	},
		{	VPP23	,	2.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	304	},
		{	VPP24	,	2.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	300	},
		{	VPP25	,	2.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	296	},
		{	VPP26	,	2.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	292	},
		{	VPP27	,	2.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	288	},
		{	VPP28	,	2.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	284	},
		{	VPP29	,	2.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	280	},
		{	VPP30	,	3.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	276	},
		{	VPP31	,	3.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	272	},
		{	VPP32	,	3.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	268	},
		{	VPP33	,	3.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	264	},
		{	VPP34	,	3.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	260	},
		{	VPP35	,	3.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	256	},
		{	VPP36	,	3.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	252	},
		{	VPP37	,	3.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	248	},
		{	VPP38	,	3.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	244	},
		{	VPP39	,	3.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	240	},
		{	VPP40	,	4.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	236	},
		{	VPP41	,	4.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	232	},
		{	VPP42	,	4.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	228	},
		{	VPP43	,	4.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	224	},
		{	VPP44	,	4.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	220	},
		{	VPP45	,	4.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	216	},
		{	VPP46	,	4.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	212	},
		{	VPP47	,	4.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	208	},
		{	VPP48	,	4.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	204	},
		{	VPP49	,	4.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	200	},
		{	VPP50	,	5.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	196	},
		{	VPP51	,	5.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	192	},
		{	VPP52	,	5.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	188	},
		{	VPP53	,	5.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	184	},
		{	VPP54	,	5.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	180	},
		{	VPP55	,	5.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	176	},
		{	VPP56	,	5.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	172	},
		{	VPP57	,	5.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	168	},
		{	VPP58	,	5.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	164	},
		{	VPP59	,	5.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	160	},
		{	VPP60	,	6.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	156	},
		{	VPP61	,	6.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	152	},
		{	VPP62	,	6.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	148	},
		{	VPP63	,	6.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	144	},
		{	VPP64	,	6.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	140	},
		{	VPP65	,	6.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	136	},
		{	VPP66	,	6.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	132	},
		{	VPP67	,	6.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	128	},
		{	VPP68	,	6.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	124	},
		{	VPP69	,	6.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	120	},
		{	VPP70	,	7.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	116	},
		{	VPP71	,	7.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	112	},
		{	VPP72	,	7.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	108	},
		{	VPP73	,	7.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	104	},
		{	VPP74	,	7.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	100	},
		{	VPP75	,	7.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	96	},
		{	VPP76	,	7.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	92	},
		{	VPP77	,	7.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	88	},
		{	VPP78	,	7.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	84	},
		{	VPP79	,	7.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	80	},
		{	VPP80	,	8.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	76	},
		{	VPP81	,	8.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	72	},
		{	VPP82	,	8.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	68	},
		{	VPP83	,	8.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	64	},
		{	VPP84	,	8.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	60	},
		{	VPP85	,	8.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	56	},
		{	VPP86	,	8.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	52	},
		{	VPP87	,	8.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	48	},
		{	VPP88	,	8.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	44	},
		{	VPP89	,	8.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	40	},
		{	VPP90	,	9.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	36	},
		{	VPP91	,	9.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	32	},
		{	VPP92	,	9.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	28	},
		{	VPP93	,	9.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	24	},
		{	VPP94	,	9.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	20	},
		{	VPP95	,	9.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	16	},
		{	VPP96	,	9.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	12	},
		{	VPP97	,	9.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	8	},
		{	VPP98	,	9.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	4	}
};


// temp location to hold a copy of the lookup table data that is modified by dsp
uint32_t tmpDataTable[SINE_DATA_SIZE];
uint16_t amp_last_encoder_value = 0;


/*
 * 		Function protochannels
 */
void _ProcessSignalDataTable(float _neg_gain_coeff, float amp_offset, uint16_t _encoder_value);
void VPP_ApplyProfileToSignal(eAmpSettings_t pPresetEnum);

void _ProcessSyncDataTable(float _neg_gain_coeff, float amp_offset, uint16_t _encoder_value);
void VPP_ApplyProfileToSync(eAmpSettings_t pPresetEnum);



/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void VPP_ResetLastEncoderValue()
{
	amp_last_encoder_value = 0;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void VPP_ApplyProfileToSignal(eAmpSettings_t pPresetEnum)
{
	// retrieve the next preset
	AmplitudeProfile_t* pNextEncPreset = &theAmpProfiles[pPresetEnum];

	// Set the new  amp profile to the SignalChannel object
	SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile = pNextEncPreset;

    // set the gain preset
	GO_ApplyPresetToSignal(pNextEncPreset->gain_preset);

    // Apply the next amplitude setting to the SignalChannel object
    _ProcessSignalDataTable(pNextEncPreset->neg_gain_coeff, pNextEncPreset->amp_offset , pNextEncPreset->epos);


}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void VPP_ApplyProfileToSync(eAmpSettings_t pPresetEnum)
{
	// retrieve the next preset
	AmplitudeProfile_t* pNextEncPreset = &theAmpProfiles[pPresetEnum];

	// Set the new VPP Preset to the SyncChannel object
	SM_GetOutputChannel(SYNC_CHANNEL)->amp_profile = pNextEncPreset;

	 // set the gain preset
	//GO_ApplyPresetToSync(pNextEncPreset->gain_preset);

	// Apply the next amplitude setting to the SyncChannel object
	_ProcessSyncDataTable(pNextEncPreset->neg_gain_coeff, pNextEncPreset->amp_offset , pNextEncPreset->epos);



}

/*
 *
 *	@brief	amplitude/offset DSP function for Signal output
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessSignalDataTable(float _neg_gain_coeff, float amp_offset, uint16_t _encoder_value)
{
	sOutputChannel_t * pTmpOutputChannel = SM_GetOutputChannel(SIGNAL_CHANNEL);
	if(pTmpOutputChannel->func_profile->func != PWM_FUNC_MODE)
	{
		// copy refer lookup datat table from SignalChannel object
		for(int i = 0; i < SINE_DATA_SIZE; i++)
		{
			tmpDataTable[i] = pTmpOutputChannel->ref_lut_data[i];
		}

		// calculate positive offset coefficient from encoder position
		float pos_offset_coeff = 1;
		if(_encoder_value)
		{
			pos_offset_coeff = (_encoder_value/4);
		}

		// adjust amplitude and offset of lookup table copy
		for(int i = 0; i < SINE_DATA_SIZE; i++)
		{
			tmpDataTable[i] = tmpDataTable[i] * (_neg_gain_coeff);
			tmpDataTable[i] = tmpDataTable[i] + (AMP_OFFSET * pos_offset_coeff);
		}

		// restore lookup table copy to active lookup table in SignalChannel object
		for(int i = 0; i < SINE_DATA_SIZE; i++)
		{
			SM_GetOutputChannel(SIGNAL_CHANNEL)->dsp_lut_data[i] = tmpDataTable[i];
		}
	}

}

/*
 *
 *	@brief	amplitude/offset DSP function for Sync output
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessSyncDataTable(float _neg_gain_coeff, float amp_offset, uint16_t _encoder_value)
{
	if(SM_GetOutputChannel(SYNC_CHANNEL)->func_profile->func != PWM_FUNC_MODE)
	{
		// copy refer lookup datat table from SyncChannel object
		for(int i = 0; i < SINE_DATA_SIZE; i++)
		{
			tmpDataTable[i] = SM_GetOutputChannel(SYNC_CHANNEL)->ref_lut_data[i];
		}

		// calculate positive offset coefficient from encoder position
		float pos_offset_coeff = 1;
		if(_encoder_value)
		{
			pos_offset_coeff = (_encoder_value/4);
		}

		// adjust amplitude and offset of lookup table copy
		for(int i = 0; i < SINE_DATA_SIZE; i++)
		{

			tmpDataTable[i] = tmpDataTable[i] * (_neg_gain_coeff);
			tmpDataTable[i] = tmpDataTable[i] + (AMP_OFFSET * pos_offset_coeff);
		}
	}


	// restore lookup table copy to active lookup table in SignalChannel object
	for(int i = 0; i < SINE_DATA_SIZE; i++)
	{
		SM_GetOutputChannel(SYNC_CHANNEL)->dsp_lut_data[i] = tmpDataTable[i];
	}
}


/*
 *
 *	@brief Search array of structs for preset
 *
 *	@param Search criteria. Should be one of the following:
 *
 *	VPP01, 	VPP02,	VPP03,	VPP04,	VPP05,	VPP06,	VPP07,	VPP08,	VPP09,	VPP10,	VPP11,	VPP12,	VPP13,	VPP14,	VPP15,
	VPP16,	VPP17,	VPP18,	VPP19,	VPP20,	VPP21,	VPP22,	VPP23,	VPP24,	VPP25,	VPP26,	VPP27,	VPP28,	VPP29,	VPP30,
	VPP31,	VPP32,	VPP33,	VPP34,	VPP35,	VPP36,	VPP37,	VPP38,	VPP39,	VPP40,	VPP41,  VPP42,  VPP43,	VPP44,	VPP45,
	VPP46,	VPP47,	VPP48,	VPP49,	VPP50,	VPP51,	VPP52,	VPP53,	VPP54,	VPP55,	VPP56,	VPP57,	VPP58,	VPP59,	VPP60,
	VPP61,	VPP62,	VPP63,	VPP64,	VPP65,	VPP66,	VPP67,	VPP68,	VPP69,	VPP70,	VPP71,	VPP72,	VPP73,  VPP74,	VPP75,
	VPP76,	VPP77,	VPP78,	VPP79,	VPP80,	VPP81,	VPP82,	VPP83,	VPP84,	VPP85,	VPP86,	VPP87,	VPP88,	VPP89,	VPP90,
	VPP91,	VPP92,	VPP93,	VPP94,	VPP95,	VPP96,	VPP97,	VPP98,

 *	@retval pointer to AmplitudeProfile_t struct
 *
 */
AmplitudeProfile_t * VPP_FindVppPresetObject(eAmpSettings_t pEnum)
{
	for(int i = 0; i < MAX_VPP_PRESETS; i++ )
	{
		if(theAmpProfiles[i].amp_setting == pEnum)
		{
			return &theAmpProfiles[i];
		}
	}
	// error!
	DM_SetErrorDebugMsg("VPP_FindVppPresetObject(): AmplitudeProfile_t obj not found");
	return 0;
}


/*
 *
 *	@brief multiplex encoder input -> preset function
 *
 *
 *	@param Encoder position.
 *
 *	@retval None
 *
 */
void VPP_MapEncoderPositionToSignalOutput(uint16_t pEncoderValue)
{
	eAmpSettings_t tmpAmp = SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile->amp_setting;
	if(pEncoderValue > amp_last_encoder_value)
	{
		tmpAmp++;
		if(tmpAmp > MAX_VPP_PRESETS-1) tmpAmp = VPP98;
		VPP_ApplyProfileToSignal(tmpAmp);
	}
	else if (pEncoderValue < amp_last_encoder_value)
	{
		tmpAmp--;
		if(tmpAmp > MAX_VPP_PRESETS-1) tmpAmp = VPP01;
		VPP_ApplyProfileToSignal(tmpAmp);
	}
	amp_last_encoder_value = pEncoderValue;

}

/*
 *
 *	@brief multiplex encoder input -> preset function
 *
 *	@param Encoder position.
 *
 *	@retval None
 *
 */
void VPP_MapEncoderPositionToSyncOutput(uint16_t pEncoderValue)
{

	eAmpSettings_t tmpAmp = SM_GetOutputChannel(SYNC_CHANNEL)->amp_profile->amp_setting;
	if(pEncoderValue > amp_last_encoder_value)
	{
		tmpAmp++;
		if(tmpAmp > MAX_VPP_PRESETS-1) tmpAmp = VPP98;
		VPP_ApplyProfileToSync(tmpAmp);
	}
	else if (pEncoderValue < amp_last_encoder_value)
	{
		tmpAmp--;
		if(tmpAmp > MAX_VPP_PRESETS-1) tmpAmp = VPP01;
		VPP_ApplyProfileToSync(tmpAmp);
	}
	amp_last_encoder_value = pEncoderValue;

}




