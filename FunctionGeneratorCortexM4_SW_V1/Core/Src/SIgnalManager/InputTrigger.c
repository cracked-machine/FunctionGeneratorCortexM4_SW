/*
 * InputTrigger.c
 *
 *  Created on: 3 Jun 2020
 *      Author: chris
 */

#include "InputTrigger.h"

#include "SignalManager.h"

#include "comp.h"
#include "dac.h"
#include "adc.h"

float _GetNearestFreqToVolts(float volts);
uint16_t _GetNearestPeriodToVolts(float volts);

eTriggerInputMode 	activeInputerTriggerMode = INPUT_TIMER_TIM;
eTriggerInput 		isTriggerInputEnabled = DISABLE_TRIGGER;

#define				VOLT_ADC_RESOLUTION		0.000805861
#define 			MAX_ADCSTEPS_MEASURE_STORE 	16
uint32_t 			adcsteps_measure_store[MAX_ADCSTEPS_MEASURE_STORE] = {};
float 				avg_adcsteps_measure;
float				avg_volt_measure;

#define 			MAX_FREQ_COUNT_STORE	8
uint32_t 			freq_count_store[MAX_FREQ_COUNT_STORE];
uint32_t 			avg_freq_count_period;
float 				avg_freq_count_hertz;


VoltsPerOctave_t theVoltsPerOctaveTable[MAX_VOLTS_PER_OCTAVE_INDEX] =
{
		{	"C0"	,	0.08	,	16.35	,	42813	},
		{	"C#0"	,	0.17	,	17.32	,	40416	},
		{	"D0"	,	0.25	,	18.35	,	38147	},
		{	"D#0"	,	0.33	,	19.45	,	35990	},
		{	"E0"	,	0.42	,	20.60	,	33981	},
		{	"F0"	,	0.50	,	21.83	,	32066	},
		{	"F#0"	,	0.58	,	23.12	,	30277	},
		{	"G0"	,	0.67	,	24.50	,	28571	},
		{	"G#0"	,	0.75	,	25.96	,	26965	},
		{	"A0"	,	0.83	,	27.50	,	25455	},
		{	"A#0"	,	0.92	,	29.14	,	24022	},
		{	"B0"	,	1.00	,	30.87	,	22676	},
		{	"C1"	,	1.08	,	32.70	,	21407	},
		{	"C#1"	,	1.17	,	34.65	,	20202	},
		{	"D1"	,	1.25	,	36.71	,	19068	},
		{	"D#1"	,	1.33	,	38.89	,	17999	},
		{	"E1"	,	1.42	,	41.20	,	16990	},
		{	"F1"	,	1.50	,	43.65	,	16037	},
		{	"F#1"	,	1.58	,	46.25	,	15135	},
		{	"G1"	,	1.67	,	49.00	,	14286	},
		{	"G#1"	,	1.75	,	51.91	,	13485	},
		{	"A1"	,	1.83	,	55.00	,	12727	},
		{	"A#1"	,	1.92	,	58.27	,	12013	},
		{	"B1"	,	2.00	,	61.74	,	11338	},
		{	"C2"	,	2.08	,	65.41	,	10702	},
		{	"C#2"	,	2.17	,	69.30	,	10101	},
		{	"D2"	,	2.25	,	73.42	,	9534	},
		{	"D#2"	,	2.33	,	77.78	,	9000	},
		{	"E2"	,	2.42	,	82.41	,	8494	},
		{	"F2"	,	2.50	,	87.31	,	8017	},
		{	"F#2"	,	2.58	,	92.50	,	7568	},
		{	"G2"	,	2.67	,	98.00	,	7143	},
		{	"G#2"	,	2.75	,	103.83	,	6742	},
		{	"A2"	,	2.83	,	110.00	,	6364	},
		{	"A#2"	,	2.92	,	116.54	,	6007	},
		{	"B2"	,	3.00	,	123.47	,	5669	},
		{	"C3"	,	3.08	,	130.81	,	5351	},
		{	"C#3"	,	3.17	,	138.59	,	5051	},
		{	"D3"	,	3.25	,	146.83	,	4767	},
		{	"D#3"	,	3.33	,	155.56	,	4500	},
};

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void IT_ArbitrateInputTrigger()
{
	if(IT_GetTriggerStatus())
	{
		// disable timer external clock source
/*		OUTPUT_TIMER->SMCR &= ~(TIM_SMCR_ECE);
		// disable timer enable "Filtered timer input 1" (tim_ti1fp1)
		OUTPUT_TIMER->SMCR &= ~(TIM_TS_TI1FP1);
		// disable timer reset trigger mode
		OUTPUT_TIMER->SMCR &= ~(TIM_SMCR_SMS_2);
		// set status to disabled
*/

		// disable freq count timer
		HAL_TIM_IC_Stop_DMA(&htim2, TIM_CHANNEL_1);

		// disable the comparator
		HAL_COMP_Stop(&hcomp1);

		// stop the ADC
		HAL_ADC_Stop_DMA(&hadc1);

		GPIOA->AFR[0] &= ~(GPIO_AF1_TIM2);
		GPIOA->AFR[0] &= ~(GPIO_AF8_COMP1);


		IT_SetTriggerStatus(DISABLE_TRIGGER);

		FuncO_ApplyProfileToSignal(eDefaultFuncPreset);



	}
	// enable the trigger input
	else
	{
		// select the pin to use for trigger input
		switch(IT_GetActiveTriggerMode())
		{
			case INPUT_TIMER_TIM:

				// TS5A3357 -> PA0
				HAL_GPIO_WritePin(TRIGMUX1_GPIO_Port, TRIGMUX1_Pin, GPIO_PIN_SET);		// TS5A3357 Pin6
				HAL_GPIO_WritePin(TRIGMUX2_GPIO_Port, TRIGMUX2_Pin, GPIO_PIN_RESET); 	// TS5A3357 Pin5

				HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, freq_count_store, MAX_FREQ_COUNT_STORE);

				// Init PA0 with TIM2 CH1 alt-function (AF) -
				GPIOA->MODER &= ~(GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1);	// reset mode registers
				GPIOA->MODER |= (GPIO_MODER_MODE0_1);	// set port mode to AF
				GPIOA->AFR[0] &= ~((1 << 0x04) | (1 << 0x03) | (1 << 0x02) | (1 << 0x01));	// reset AF registers - See Table 13 "Alternate Functions" in STM32G474 datasheet
				GPIOA->AFR[0] |= GPIO_AF1_TIM2;		// set AF to TIM2_CH1

				break;
			case INPUT_TIMER_COMP:
				// TS5A3357 -> PA1
				HAL_GPIO_WritePin(TRIGMUX1_GPIO_Port, TRIGMUX1_Pin, GPIO_PIN_RESET);	// TS5A3357 Pin6
				HAL_GPIO_WritePin(TRIGMUX2_GPIO_Port, TRIGMUX2_Pin, GPIO_PIN_SET); 		// TS5A3357 Pin5

/*
				//HAL_COMP_Start(&hcomp1);
				COMP1->CSR |= COMP_CSR_EN;
				// set alt pin function to COMP1 OUT
				GPIOA->AFR[0] &= ~((1 << 0x04) | (1 << 0x03) | (1 << 0x02) | (1 << 0x01));	// reset
				GPIOA->AFR[0] |= (GPIO_AF8_COMP1);

				// enable timer external clock source
				//OUTPUT_TIMER->SMCR |= (TIM_SMCR_ECE);
				// enable timer "Filtered timer input 1" (tim_ti1fp1)
				//OUTPUT_TIMER->SMCR |= (TIM_TS_TI1FP1);
				// enable timer reset trigger mode
				//OUTPUT_TIMER->SMCR |= (TIM_SMCR_SMS_2);


				// pause timer to reAux both outputs
				OUTPUT_TIMER->CR1 &= ~(TIM_CR1_CEN);
				//HAL_TIM_Base_Stop(&htim2);

				// restart the DAC with the new data
				HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, comp1_output_value, 1, DAC_ALIGN_12B_R);

				// resume timer to reAux both outputs
				//HAL_TIM_Base_Start(&htim2);
				OUTPUT_TIMER->CR1 |= (TIM_CR1_CEN);
*/

				break;
			case INPUT_TIMER_ADC:
				// TS5A3357 -> PA2

				HAL_GPIO_WritePin(TRIGMUX1_GPIO_Port, TRIGMUX1_Pin, GPIO_PIN_SET);		// TS5A3357 Pin6
				HAL_GPIO_WritePin(TRIGMUX2_GPIO_Port, TRIGMUX2_Pin, GPIO_PIN_SET);		// TS5A3357 Pin5

				HAL_ADC_Start_DMA(&hadc1, adcsteps_measure_store, MAX_ADCSTEPS_MEASURE_STORE);

				// pause timer to reAux both outputs
				OUTPUT_TIMER->CR1 &= ~(TIM_CR1_CEN);
				//HAL_TIM_Base_Stop(&htim2);

				// restart the DAC with the new data
				HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, adcsteps_measure_store, MAX_ADCSTEPS_MEASURE_STORE, DAC_ALIGN_12B_R);

				// resume timer to reAux both outputs
				//HAL_TIM_Base_Start(&htim2);
				OUTPUT_TIMER->CR1 |= (TIM_CR1_CEN);

				//TODO enable ADC trigger input

				FuncO_ApplyProfileToSignal(eDefaultFuncPreset);
				break;

			default:
				break;

		}
		// set status to enabled
		IT_SetTriggerStatus(ENABLE_TRIGGER);
	}

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void IT_CycleInputTriggerMode()
{
	// change the trigger input mode
	switch(IT_GetActiveTriggerMode())
	{
		case INPUT_TIMER_TIM:
			IT_SetActiveTriggerMode(INPUT_TIMER_COMP);
			break;
		case INPUT_TIMER_COMP:
			IT_SetActiveTriggerMode(INPUT_TIMER_ADC);
			break;
		case INPUT_TIMER_ADC:
			IT_SetActiveTriggerMode(INPUT_TIMER_TIM);
			break;

		default:
			break;
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
	if(HAL_COMP_GetOutputLevel(&hcomp1))
	{
		comp1_output_value[0] = 4095;
	}
	else
	{
		comp1_output_value[0] = 0;
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	// mean average the DMA data set
	avg_adcsteps_measure = 0;
	for(int x = 0; x < MAX_ADCSTEPS_MEASURE_STORE; x++)
	{
		avg_adcsteps_measure += adcsteps_measure_store[x];
	}
	avg_adcsteps_measure = avg_adcsteps_measure / MAX_ADCSTEPS_MEASURE_STORE;

	// convert ADC steps into voltage
	avg_volt_measure = avg_adcsteps_measure * VOLT_ADC_RESOLUTION;

	// find nearest freq in ref table
	uint16_t new_output_period = _GetNearestPeriodToVolts(avg_volt_measure);
	if(new_output_period > 0)
	{
		// set the output timer to new period
		OUTPUT_TIMER->ARR = new_output_period;
		OUTPUT_TIMER->PSC = 1;
	}

}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

	// mean average the DMA data set
	avg_freq_count_period = 0;
	for(int x = 0; x < MAX_FREQ_COUNT_STORE; x++)
	{
		avg_freq_count_period += freq_count_store[x];
	}
	avg_freq_count_period /= MAX_FREQ_COUNT_STORE;

	// convert period to hertz
	avg_freq_count_hertz = (float)SM_MCLK / ((float)INPUT_TIMER->PSC * (float)avg_freq_count_period);

	// sync the output timer (DAC) with the input timer
	OUTPUT_TIMER->ARR = avg_freq_count_period;

	// auto toggle "LF" mode
	if(avg_freq_count_hertz < 50)
	{
		INPUT_TIMER->PSC = 8000;
		OUTPUT_TIMER->PSC = 48;
	}
	else
	{
		INPUT_TIMER->PSC = 128;
		OUTPUT_TIMER->PSC = 0;
	}

	//printf("ARR %lu = %4.2fHz\n",avg_freq_count_period, avg_freq_count_hertz);

}

float _GetNearestFreqToVolts(float volts)
{
	float error_margin = 0.05;
	for(int x = 0; x < MAX_VOLTS_PER_OCTAVE_INDEX; x++)
	{
		if((volts - theVoltsPerOctaveTable[x].volts) < error_margin)
		{
			return theVoltsPerOctaveTable[x].hertz;
		}

	}
	return 0.0f;
}

uint16_t _GetNearestPeriodToVolts(float volts)
{
	float error_margin = 0.05;
	for(int x = 0; x < MAX_VOLTS_PER_OCTAVE_INDEX; x++)
	{
		if((volts - theVoltsPerOctaveTable[x].volts) < error_margin)
		{
			return theVoltsPerOctaveTable[x].period;
		}

	}
	return 0.0f;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
float IT_GetAverageFreqCountPeriod()
{
	return avg_freq_count_period;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
float IT_GetAverageFreqCountHertz()
{
	return avg_freq_count_hertz;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eTriggerInputMode IT_GetActiveTriggerMode()
{
	return activeInputerTriggerMode;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void IT_SetActiveTriggerMode(eTriggerInputMode newTriggerMode)
{
	activeInputerTriggerMode = newTriggerMode;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eTriggerInput IT_GetTriggerStatus()
{
	return isTriggerInputEnabled;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void IT_SetTriggerStatus(eTriggerInput newTriggerStatus)
{
	isTriggerInputEnabled = newTriggerStatus;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
float IT_GetAvgAdcVoltage()
{
	return avg_volt_measure;
}

