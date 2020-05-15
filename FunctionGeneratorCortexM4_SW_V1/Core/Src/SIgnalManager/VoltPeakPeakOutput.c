/*
 * VoltPeakPeakOutput.c
 *
 *  Created on: 14 May 2020
 *      Author: chris
 */

#include "VoltPeakPeakOutput.h"
#include "DisplayManager.h"
#include "SignalManager.h"

#include "dac.h"

#define VPP_OFFSET 0
#define VPP_OFFSET50 VPP_OFFSET+50
#define VPP_OFFSET60 VPP_OFFSET+60
#define VPP_OFFSET70 VPP_OFFSET+70
#define VPP_OFFSET80 VPP_OFFSET+80
#define VPP_OFFSET90 VPP_OFFSET+90
#define VPP_OFFSET100 VPP_OFFSET+100


//uint8_t last_gain_preset = 1;

/*
 *	Array of objects for Function Presets and their encoder positions for func preset menu
 */
VppEncoderPreset_t aVppEncoderPresets[MAX_VPP_PRESETS] =
{

		{	VPP01	,	0.1	,	1	,	"+	40.0	 dBmV"	,	0.037	,	VPP_OFFSET+5	,	392	},
		{	VPP02	,	0.2	,	1	,	"+	46.0	 dBmV"	,	0.074	,	VPP_OFFSET+5	,	388	},
		{	VPP03	,	0.3	,	1	,	"+	49.5	 dBmV"	,	0.111	,	VPP_OFFSET+3	,	384	},
		{	VPP04	,	0.4	,	1	,	"+	52.0	 dBmV"	,	0.148	,	VPP_OFFSET+2	,	380	},
		{	VPP05	,	0.5	,	1	,	"+	54.0	 dBmV"	,	0.185	,	VPP_OFFSET+2	,	376	},
		{	VPP06	,	0.6	,	1	,	"+	55.6	 dBmV"	,	0.222	,	VPP_OFFSET	,	372	},
		{	VPP07	,	0.7	,	1	,	"+	56.9	 dBmV"	,	0.259	,	VPP_OFFSET	,	368	},
		{	VPP08	,	0.8	,	1	,	"+	58.1	 dBmV"	,	0.296	,	VPP_OFFSET	,	364	},
		{	VPP09	,	0.9	,	1	,	"+	59.1	 dBmV"	,	0.333	,	VPP_OFFSET	,	360	},
		{	VPP10	,	1.0	,	1	,	"+	60.0	 dBmV"	,	0.370	,	VPP_OFFSET	,	356	},
		{	VPP11	,	1.1	,	1	,	"+	60.8	 dBmV"	,	0.407	,	VPP_OFFSET	,	352	},
		{	VPP12	,	1.2	,	1	,	"+	61.6	 dBmV"	,	0.444	,	VPP_OFFSET	,	348	},
		{	VPP13	,	1.3	,	1	,	"+	62.3	 dBmV"	,	0.481	,	VPP_OFFSET	,	344	},
		{	VPP14	,	1.4	,	1	,	"+	62.9	 dBmV"	,	0.519	,	VPP_OFFSET	,	340	},
		{	VPP15	,	1.5	,	1	,	"+	63.5	 dBmV"	,	0.556	,	VPP_OFFSET	,	336	},
		{	VPP16	,	1.6	,	1	,	"+	64.1	 dBmV"	,	0.593	,	VPP_OFFSET	,	332	},
		{	VPP17	,	1.7	,	1	,	"+	64.6	 dBmV"	,	0.630	,	VPP_OFFSET	,	328	},
		{	VPP18	,	1.8	,	1	,	"+	65.1	 dBmV"	,	0.667	,	VPP_OFFSET	,	324	},
		{	VPP19	,	1.9	,	1	,	"+	65.6	 dBmV"	,	0.704	,	VPP_OFFSET	,	320	},
		{	VPP20	,	2.0	,	1	,	"+	66.0	 dBmV"	,	0.741	,	VPP_OFFSET	,	316	},
		{	VPP21	,	2.1	,	1	,	"+	66.4	 dBmV"	,	0.778	,	VPP_OFFSET	,	312	},
		{	VPP22	,	2.2	,	1	,	"+	66.8	 dBmV"	,	0.815	,	VPP_OFFSET	,	308	},
		{	VPP23	,	2.3	,	1	,	"+	67.2	 dBmV"	,	0.852	,	VPP_OFFSET	,	304	},
		{	VPP24	,	2.4	,	1	,	"+	67.6	 dBmV"	,	0.889	,	VPP_OFFSET	,	300	},
		{	VPP25	,	2.5	,	1	,	"+	68.0	 dBmV"	,	0.926	,	VPP_OFFSET	,	296	},
		{	VPP26	,	2.6	,	1	,	"+	68.3	 dBmV"	,	0.963	,	VPP_OFFSET	,	292	},
		{	VPP27	,	2.7	,	1	,	"+	68.6	 dBmV"	,	1.000	,	VPP_OFFSET	,	288	},
		{	VPP28	,	2.8	,	2	,	"+	68.9	 dBmV"	,	0.519	,	VPP_OFFSET	,	284	},
		{	VPP29	,	2.9	,	2	,	"+	69.2	 dBmV"	,	0.537	,	VPP_OFFSET	,	280	},
		{	VPP30	,	3.0	,	2	,	"+	69.5	 dBmV"	,	0.556	,	VPP_OFFSET	,	276	},
		{	VPP31	,	3.1	,	2	,	"+	69.8	 dBmV"	,	0.574	,	VPP_OFFSET	,	272	},
		{	VPP32	,	3.2	,	2	,	"+	70.1	 dBmV"	,	0.593	,	VPP_OFFSET	,	268	},
		{	VPP33	,	3.3	,	2	,	"+	70.4	 dBmV"	,	0.611	,	VPP_OFFSET	,	264	},
		{	VPP34	,	3.4	,	2	,	"+	70.6	 dBmV"	,	0.630	,	VPP_OFFSET	,	260	},
		{	VPP35	,	3.5	,	2	,	"+	70.9	 dBmV"	,	0.648	,	VPP_OFFSET	,	256	},
		{	VPP36	,	3.6	,	2	,	"+	71.1	 dBmV"	,	0.667	,	VPP_OFFSET	,	252	},
		{	VPP37	,	3.7	,	2	,	"+	71.4	 dBmV"	,	0.685	,	VPP_OFFSET	,	248	},
		{	VPP38	,	3.8	,	2	,	"+	71.6	 dBmV"	,	0.704	,	VPP_OFFSET	,	244	},
		{	VPP39	,	3.9	,	2	,	"+	71.8	 dBmV"	,	0.722	,	VPP_OFFSET	,	240	},
		{	VPP40	,	4.0	,	2	,	"+	72.0	 dBmV"	,	0.741	,	VPP_OFFSET	,	236	},
		{	VPP41	,	4.1	,	2	,	"+	72.3	 dBmV"	,	0.759	,	VPP_OFFSET	,	232	},
		{	VPP42	,	4.2	,	2	,	"+	72.5	 dBmV"	,	0.778	,	VPP_OFFSET	,	228	},
		{	VPP43	,	4.3	,	2	,	"+	72.7	 dBmV"	,	0.796	,	VPP_OFFSET	,	224	},
		{	VPP44	,	4.4	,	2	,	"+	72.9	 dBmV"	,	0.815	,	VPP_OFFSET	,	220	},
		{	VPP45	,	4.5	,	2	,	"+	73.1	 dBmV"	,	0.833	,	VPP_OFFSET	,	216	},
		{	VPP46	,	4.6	,	2	,	"+	73.3	 dBmV"	,	0.852	,	VPP_OFFSET	,	212	},
		{	VPP47	,	4.7	,	2	,	"+	73.4	 dBmV"	,	0.870	,	VPP_OFFSET	,	208	},
		{	VPP48	,	4.8	,	2	,	"+	73.6	 dBmV"	,	0.889	,	VPP_OFFSET	,	204	},
		{	VPP49	,	4.9	,	2	,	"+	73.8	 dBmV"	,	0.907	,	VPP_OFFSET	,	200	},
		{	VPP50	,	5.0	,	2	,	"+	74.0	 dBmV"	,	0.926	,	VPP_OFFSET	,	196	},
		{	VPP51	,	5.1	,	2	,	"+	74.2	 dBmV"	,	0.944	,	VPP_OFFSET	,	192	},
		{	VPP52	,	5.2	,	2	,	"+	74.3	 dBmV"	,	0.963	,	VPP_OFFSET	,	188	},
		{	VPP53	,	5.3	,	2	,	"+	74.5	 dBmV"	,	0.981	,	VPP_OFFSET	,	184	},
		{	VPP54	,	5.4	,	2	,	"+	74.6	 dBmV"	,	1.000	,	VPP_OFFSET	,	180	},
		{	VPP55	,	5.5	,	3	,	"+	74.8	 dBmV"	,	0.679	,	VPP_OFFSET	,	176	},
		{	VPP56	,	5.6	,	3	,	"+	75.0	 dBmV"	,	0.691	,	VPP_OFFSET	,	172	},
		{	VPP57	,	5.7	,	3	,	"+	75.1	 dBmV"	,	0.704	,	VPP_OFFSET	,	168	},
		{	VPP58	,	5.8	,	3	,	"+	75.3	 dBmV"	,	0.716	,	VPP_OFFSET	,	164	},
		{	VPP59	,	5.9	,	3	,	"+	75.4	 dBmV"	,	0.728	,	VPP_OFFSET	,	160	},
		{	VPP60	,	6.0	,	3	,	"+	75.6	 dBmV"	,	0.741	,	VPP_OFFSET	,	156	},
		{	VPP61	,	6.1	,	3	,	"+	75.7	 dBmV"	,	0.753	,	VPP_OFFSET	,	152	},
		{	VPP62	,	6.2	,	3	,	"+	75.8	 dBmV"	,	0.765	,	VPP_OFFSET	,	148	},
		{	VPP63	,	6.3	,	3	,	"+	76.0	 dBmV"	,	0.778	,	VPP_OFFSET	,	144	},
		{	VPP64	,	6.4	,	3	,	"+	76.1	 dBmV"	,	0.790	,	VPP_OFFSET	,	140	},
		{	VPP65	,	6.5	,	3	,	"+	76.3	 dBmV"	,	0.802	,	VPP_OFFSET	,	136	},
		{	VPP66	,	6.6	,	3	,	"+	76.4	 dBmV"	,	0.815	,	VPP_OFFSET	,	132	},
		{	VPP67	,	6.7	,	3	,	"+	76.5	 dBmV"	,	0.827	,	VPP_OFFSET	,	128	},
		{	VPP68	,	6.8	,	3	,	"+	76.7	 dBmV"	,	0.840	,	VPP_OFFSET	,	124	},
		{	VPP69	,	6.9	,	3	,	"+	76.8	 dBmV"	,	0.852	,	VPP_OFFSET	,	120	},
		{	VPP70	,	7.0	,	3	,	"+	76.9	 dBmV"	,	0.864	,	VPP_OFFSET	,	116	},
		{	VPP71	,	7.1	,	3	,	"+	77.0	 dBmV"	,	0.877	,	VPP_OFFSET	,	112	},
		{	VPP72	,	7.2	,	3	,	"+	77.1	 dBmV"	,	0.889	,	VPP_OFFSET	,	108	},
		{	VPP73	,	7.3	,	3	,	"+	77.3	 dBmV"	,	0.901	,	VPP_OFFSET	,	104	},
		{	VPP74	,	7.4	,	3	,	"+	77.4	 dBmV"	,	0.914	,	VPP_OFFSET	,	100	},
		{	VPP75	,	7.5	,	3	,	"+	77.5	 dBmV"	,	0.926	,	VPP_OFFSET	,	96	},
		{	VPP76	,	7.6	,	3	,	"+	77.6	 dBmV"	,	0.938	,	VPP_OFFSET	,	92	},
		{	VPP77	,	7.7	,	3	,	"+	77.7	 dBmV"	,	0.951	,	VPP_OFFSET	,	88	},
		{	VPP78	,	7.8	,	3	,	"+	77.8	 dBmV"	,	0.963	,	VPP_OFFSET	,	84	},
		{	VPP79	,	7.9	,	3	,	"+	78.0	 dBmV"	,	0.975	,	VPP_OFFSET	,	80	},
		{	VPP80	,	8.0	,	3	,	"+	78.1	 dBmV"	,	0.988	,	VPP_OFFSET	,	76	},
		{	VPP81	,	8.1	,	6	,	"+	78.2	 dBmV"	,	0.500	,	VPP_OFFSET50	,	72	},
		{	VPP82	,	8.2	,	6	,	"+	78.3	 dBmV"	,	0.506	,	VPP_OFFSET50	,	68	},
		{	VPP83	,	8.3	,	6	,	"+	78.4	 dBmV"	,	0.512	,	VPP_OFFSET50	,	64	},
		{	VPP84	,	8.4	,	6	,	"+	78.5	 dBmV"	,	0.519	,	VPP_OFFSET50	,	60	},
		{	VPP85	,	8.5	,	6	,	"+	78.6	 dBmV"	,	0.525	,	VPP_OFFSET50	,	56	},
		{	VPP86	,	8.6	,	6	,	"+	78.7	 dBmV"	,	0.531	,	VPP_OFFSET60	,	52	},
		{	VPP87	,	8.7	,	6	,	"+	78.8	 dBmV"	,	0.537	,	VPP_OFFSET60	,	48	},
		{	VPP88	,	8.8	,	6	,	"+	78.9	 dBmV"	,	0.543	,	VPP_OFFSET60	,	44	},
		{	VPP89	,	8.9	,	6	,	"+	79.0	 dBmV"	,	0.549	,	VPP_OFFSET70	,	40	},
		{	VPP90	,	9.0	,	6	,	"+	79.1	 dBmV"	,	0.556	,	VPP_OFFSET70	,	36	}

};


VppEncoderPreset_t* pVppEncoderPreset = &aVppEncoderPresets[eDefaultVppPreset];


/*
 * 		Function prototypes
 */
void _ProcessDataTable(float _neg_gain_coeff, float vpp_offset, uint16_t _encoder_value);
void VPP_ApplyPreset_Fast(eVppPreset_t pPresetEnum);

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void VPP_ApplyPreset_Fast(eVppPreset_t pPresetEnum)
{
    pVppEncoderPreset = &aVppEncoderPresets[pPresetEnum];
    //GO_ApplyPreset_Fast((ONE_GAIN));

 /*   // if gain_preset is changed, lower the amplitude before changing it
    if(last_gain_preset != pVppEncoderPreset->gain_preset)
    	_ProcessDataTable(0.3, pVppEncoderPreset->vpp_offset , pVppEncoderPreset->epos);
*/
    // change the gain preset and remember this preset id
    GO_ApplyPreset_Fast(pVppEncoderPreset->gain_preset);
  //  last_gain_preset = pVppEncoderPreset->gain_preset;

    // set the new amplitude for real
    _ProcessDataTable(pVppEncoderPreset->neg_gain_coeff, pVppEncoderPreset->vpp_offset , pVppEncoderPreset->epos);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessDataTable(float _neg_gain_coeff, float vpp_offset, uint16_t _encoder_value)
{
	for(int i = 0; i < SINE_DATA_SIZE; i++)
	{
		tmpDataTable[i] = pOriginalDataTable[i];
	}

	float pos_offset_coeff = 1;
	if(_encoder_value)
		pos_offset_coeff = (_encoder_value/4);

	for(int i = 0; i < SINE_DATA_SIZE; i++)
	{

		tmpDataTable[i] = tmpDataTable[i] * (_neg_gain_coeff);
		tmpDataTable[i] = tmpDataTable[i] + (vpp_offset * pos_offset_coeff);
	}
	//HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
	for(int i = 0; i < SINE_DATA_SIZE; i++)
	{
		aModdedDataTable[i] = tmpDataTable[i];
	}
	//HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)aModdedDataTable, SINE_DATA_SIZE,  DAC_ALIGN_12B_R);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void VPP_ModifyOutput(uint16_t pEncoderValue)
{
	switch(pEncoderValue)
	{
		case 0	:
		case 1	:
		case 2	:
			VPP_ApplyPreset_Fast( VPP01 );
			break;
		case 3	:
		case 4	:
		case 5	:
		case 6	:
			VPP_ApplyPreset_Fast( VPP02	);
			break;
		case 7	:
		case 8	:
		case 9	:
		case 10	:
			VPP_ApplyPreset_Fast( VPP03	);
			break;
		case 11	:
		case 12	:
		case 13	:
		case 14	:
			VPP_ApplyPreset_Fast( VPP04	);
			break;
		case 15	:
		case 16	:
		case 17	:
		case 18	:
			VPP_ApplyPreset_Fast( VPP05	);
			break;
		case 19	:
		case 20	:
		case 21	:
		case 22	:
			VPP_ApplyPreset_Fast( VPP06	);
			break;
		case 23	:
		case 24	:
		case 25	:
		case 26	:
			VPP_ApplyPreset_Fast( VPP07	);
			break;
		case 27	:
		case 28	:
		case 29	:
		case 30	:
			VPP_ApplyPreset_Fast( VPP08	);
			break;
		case 31	:
		case 32	:
		case 33	:
		case 34	:
			VPP_ApplyPreset_Fast( VPP09	);
			break;
		case 35	:
		case 36	:
		case 37	:
		case 38	:
			VPP_ApplyPreset_Fast( VPP10	);
			break;
		case 39	:
		case 40	:
		case 41	:
		case 42	:
			VPP_ApplyPreset_Fast( VPP11	);
			break;
		case 43	:
		case 44	:
		case 45	:
		case 46	:
			VPP_ApplyPreset_Fast( VPP12	);
			break;
		case 47	:
		case 48	:
		case 49	:
		case 50	:
			VPP_ApplyPreset_Fast( VPP13	);
			break;
		case 51	:
		case 52	:
		case 53	:
		case 54	:
			VPP_ApplyPreset_Fast( VPP14	);
			break;
		case 55	:
		case 56	:
		case 57	:
		case 58	:
			VPP_ApplyPreset_Fast( VPP15	);
			break;
		case 59	:
		case 60	:
		case 61	:
		case 62	:
			VPP_ApplyPreset_Fast( VPP16	);
			break;
		case 63	:
		case 64	:
		case 65	:
		case 66	:
			VPP_ApplyPreset_Fast( VPP17	);
			break;
		case 67	:
		case 68	:
		case 69	:
		case 70	:
			VPP_ApplyPreset_Fast( VPP18	);
			break;
		case 71	:
		case 72	:
		case 73	:
		case 74	:
			VPP_ApplyPreset_Fast( VPP19	);
			break;
		case 75	:
		case 76	:
		case 77	:
		case 78	:
			VPP_ApplyPreset_Fast( VPP20	);
			break;
		case 79	:
		case 80	:
		case 81	:
		case 82	:
			VPP_ApplyPreset_Fast( VPP21	);
			break;
		case 83	:
		case 84	:
		case 85	:
		case 86	:
			VPP_ApplyPreset_Fast( VPP22	);
			break;
		case 87	:
		case 88	:
		case 89	:
		case 90	:
			VPP_ApplyPreset_Fast( VPP23	);
			break;
		case 91	:
		case 92	:
		case 93	:
		case 94	:
			VPP_ApplyPreset_Fast( VPP24	);
			break;
		case 95	:
		case 96	:
		case 97	:
		case 98	:
			VPP_ApplyPreset_Fast( VPP25	);
			break;
		case 99		:
		case 100	:
		case 101	:
		case 102	:
			VPP_ApplyPreset_Fast( VPP26	);
			break;
		case 103	:
		case 104	:
		case 105	:
		case 106	:
			VPP_ApplyPreset_Fast( VPP27	);
			break;
		case 107	:
		case 108	:
		case 109	:
		case 110	:
			VPP_ApplyPreset_Fast( VPP28	);
			break;
		case 111	:
		case 112	:
		case 113	:
		case 114	:
			VPP_ApplyPreset_Fast( VPP29	);
			break;
		case 115	:
		case 116	:
		case 117	:
		case 118	:
			VPP_ApplyPreset_Fast( VPP30	);
			break;
		case 119	:
		case 120	:
		case 121	:
		case 122	:
			VPP_ApplyPreset_Fast( VPP31	);
			break;
		case 123	:
		case 124	:
		case 125	:
		case 126	:
			VPP_ApplyPreset_Fast( VPP32	);
			break;
		case 127	:
		case 128	:
		case 129	:
		case 130	:
			VPP_ApplyPreset_Fast( VPP33	);
			break;
		case 131	:
		case 132	:
		case 133	:
		case 134	:
			VPP_ApplyPreset_Fast( VPP34	);
			break;
		case 135	:
		case 136	:
		case 137	:
		case 138	:
			VPP_ApplyPreset_Fast( VPP35	);
			break;
		case 139	:
		case 140	:
		case 141	:
		case 142	:
			VPP_ApplyPreset_Fast( VPP36	);
			break;
		case 143	:
		case 144	:
		case 145	:
		case 146	:
			VPP_ApplyPreset_Fast( VPP37	);
			break;
		case 147	:
		case 148	:
		case 149	:
		case 150	:
			VPP_ApplyPreset_Fast( VPP38	);
			break;
		case 151	:
		case 152	:
		case 153	:
		case 154	:
			VPP_ApplyPreset_Fast( VPP39	);
			break;
		case 155	:
		case 156	:
		case 157	:
		case 158	:
			VPP_ApplyPreset_Fast( VPP40	);
			break;
		case 159	:
		case 160	:
		case 161	:
		case 162	:
			VPP_ApplyPreset_Fast( VPP41	);
			break;
		case 163	:
		case 164	:
		case 165	:
		case 166	:
			VPP_ApplyPreset_Fast( VPP42	);
			break;
		case 167	:
		case 168	:
		case 169	:
		case 170	:
			VPP_ApplyPreset_Fast( VPP43	);
			break;
		case 171	:
		case 172	:
		case 173	:
		case 174	:
			VPP_ApplyPreset_Fast( VPP44	);
			break;
		case 175	:
		case 176	:
		case 177	:
		case 178	:
			VPP_ApplyPreset_Fast( VPP45	);
			break;
		case 179	:
		case 180	:
		case 181	:
		case 182	:
			VPP_ApplyPreset_Fast( VPP46	);
			break;
		case 183	:
		case 184	:
		case 185	:
		case 186	:
			VPP_ApplyPreset_Fast( VPP47	);
			break;
		case 187	:
		case 188	:
		case 189	:
		case 190	:
			VPP_ApplyPreset_Fast( VPP48	);
			break;
		case 191	:
		case 192	:
		case 193	:
		case 194	:
			VPP_ApplyPreset_Fast( VPP49	);
			break;
		case 195	:
		case 196	:
		case 197	:
		case 198	:
			VPP_ApplyPreset_Fast( VPP50	);
			break;
		case 199	:
		case 200	:
		case 201	:
		case 202	:
			VPP_ApplyPreset_Fast( VPP51	);
			break;
		case 203	:
		case 204	:
		case 205	:
		case 206	:
			VPP_ApplyPreset_Fast( VPP52	);
			break;
		case 207	:
		case 208	:
		case 209	:
		case 210	:
			VPP_ApplyPreset_Fast( VPP53	);
			break;
		case 211	:
		case 212	:
		case 213	:
		case 214	:
			VPP_ApplyPreset_Fast( VPP54	);
			break;
		case 215	:
		case 216	:
		case 217	:
		case 218	:
			VPP_ApplyPreset_Fast( VPP55	);
			break;
		case 219	:
		case 220	:
		case 221	:
		case 222	:
			VPP_ApplyPreset_Fast( VPP56	);
			break;
		case 223	:
		case 224	:
		case 225	:
		case 226	:
			VPP_ApplyPreset_Fast( VPP57	);
			break;
		case 227	:
		case 228	:
		case 229	:
		case 230	:
			VPP_ApplyPreset_Fast( VPP58	);
			break;
		case 231	:
		case 232	:
		case 233	:
		case 234	:
			VPP_ApplyPreset_Fast( VPP59	);
			break;
		case 235	:
		case 236	:
		case 237	:
		case 238	:
			VPP_ApplyPreset_Fast( VPP60	);
			break;
		case 239	:
		case 240	:
		case 241	:
		case 242	:
			VPP_ApplyPreset_Fast( VPP61	);
			break;
		case 243	:
		case 244	:
		case 245	:
		case 246	:
			VPP_ApplyPreset_Fast( VPP62	);
			break;
		case 247	:
		case 248	:
		case 249	:
		case 250	:
			VPP_ApplyPreset_Fast( VPP63	);
			break;
		case 251	:
		case 252	:
		case 253	:
		case 254	:
			VPP_ApplyPreset_Fast( VPP64	);
			break;
		case 255	:
		case 256	:
		case 257	:
		case 258	:
			VPP_ApplyPreset_Fast( VPP65	);
			break;
		case 259	:
		case 260	:
		case 261	:
		case 262	:
			VPP_ApplyPreset_Fast( VPP66	);
			break;
		case 263	:
		case 264	:
		case 265	:
		case 266	:
			VPP_ApplyPreset_Fast( VPP67	);
			break;
		case 267	:
		case 268	:
		case 269	:
		case 270	:
			VPP_ApplyPreset_Fast( VPP68	);
			break;
		case 271	:
		case 272	:
		case 273	:
		case 274	:
			VPP_ApplyPreset_Fast( VPP69	);
			break;
		case 275	:
		case 276	:
		case 277	:
		case 278	:
			VPP_ApplyPreset_Fast( VPP70	);
			break;
		case 279	:
		case 280	:
		case 281	:
		case 282	:
			VPP_ApplyPreset_Fast( VPP71	);
			break;
		case 283	:
		case 284	:
		case 285	:
		case 286	:
			VPP_ApplyPreset_Fast( VPP72	);
			break;
		case 287	:
		case 288	:
		case 289	:
		case 290	:
			VPP_ApplyPreset_Fast( VPP73	);
			break;
		case 291	:
		case 292	:
		case 293	:
		case 294	:
			VPP_ApplyPreset_Fast( VPP74	);
			break;
		case 295	:
		case 296	:
		case 297	:
		case 298	:
			VPP_ApplyPreset_Fast( VPP75	);
			break;
		case 299	:
		case 300	:
		case 301	:
		case 302	:
			VPP_ApplyPreset_Fast( VPP76	);
			break;
		case 303	:
		case 304	:
		case 305	:
		case 306	:
			VPP_ApplyPreset_Fast( VPP77	);
			break;
		case 307	:
		case 308	:
		case 309	:
		case 310	:
			VPP_ApplyPreset_Fast( VPP78	);
			break;
		case 311	:
		case 312	:
		case 313	:
		case 314	:
			VPP_ApplyPreset_Fast( VPP79	);
			break;
		case 315	:
		case 316	:
		case 317	:
		case 318	:
			VPP_ApplyPreset_Fast( VPP80	);
			break;
		case 319	:
		case 320	:
		case 321	:
		case 322	:
			VPP_ApplyPreset_Fast( VPP81	);
			break;
		case 323	:
		case 324	:
		case 325	:
		case 326	:
			VPP_ApplyPreset_Fast( VPP82	);
			break;
		case 327	:
		case 328	:
		case 329	:
		case 330	:
			VPP_ApplyPreset_Fast( VPP83	);
			break;
		case 331	:
		case 332	:
		case 333	:
		case 334	:
			VPP_ApplyPreset_Fast( VPP84	);
			break;
		case 335	:
		case 336	:
		case 337	:
		case 338	:
			VPP_ApplyPreset_Fast( VPP85	);
			break;
		case 339	:
		case 340	:
		case 341	:
		case 342	:
			VPP_ApplyPreset_Fast( VPP86	);
			break;
		case 343	:
		case 344	:
		case 345	:
		case 346	:
			VPP_ApplyPreset_Fast( VPP87	);
			break;
		case 347	:
		case 348	:
		case 349	:
		case 350	:
			VPP_ApplyPreset_Fast( VPP88	);
			break;
		case 351	:
		case 352	:
		case 353	:
		case 354	:
			VPP_ApplyPreset_Fast( VPP89	);
			break;
		case 355	:
		case 356	:
		case 357	:
		case 358	:
			VPP_ApplyPreset_Fast( VPP90	);
			break;
/*		case 359	:
		case 360	:
		case 361	:
		case 362	:
			VPP_ApplyPreset_Fast( VPP91	);
			break;
		case 363	:
		case 364	:
		case 365	:
		case 366	:
			VPP_ApplyPreset_Fast( VPP92	);
			break;
		case 367	:
		case 368	:
		case 369	:
		case 370	:
			VPP_ApplyPreset_Fast( VPP93	);
			break;
		case 371	:
		case 372	:
		case 373	:
		case 374	:
			VPP_ApplyPreset_Fast( VPP94	);
			break;
		case 375	:
		case 376	:
		case 377	:
		case 378	:
			VPP_ApplyPreset_Fast( VPP95	);
			break;
		case 379	:
		case 380	:
		case 381	:
		case 382	:
			VPP_ApplyPreset_Fast( VPP96	);
			break;
		case 383	:
		case 384	:
		case 385	:
		case 386	:
			VPP_ApplyPreset_Fast( VPP97	);
			break;
		case 387	:
		case 388	:
		case 389	:
		case 390	:
			VPP_ApplyPreset_Fast( VPP98	);
			break;
*/
		default:
			break;
	}
}



/*
 *
 *	@brief Get VPP preset pointer
 *
 *	@param None
 *	@retval pointer to VppEncoderPreset_t struct
 *
 */
VppEncoderPreset_t * VPP_GetVppPresetObject()
{
	return pVppEncoderPreset;
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

 *	@retval pointer to VppEncoderPreset_t struct
 *
 */
VppEncoderPreset_t * VPP_FindVppPresetObject(eVppPreset_t pEnum)
{
	for(int i = 0; i < MAX_VPP_PRESETS; i++ )
	{
		if(aVppEncoderPresets[i].Vpp_literal == pEnum)
		{
			return &aVppEncoderPresets[i];
		}
	}
	// error!
	DM_SetErrorDebugMsg("VPP_FindVppPresetObject(): VppEncoderPreset_t obj not found");
	return 0;
}




