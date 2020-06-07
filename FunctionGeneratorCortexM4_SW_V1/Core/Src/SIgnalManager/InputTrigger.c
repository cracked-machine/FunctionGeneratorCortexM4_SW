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

eTriggerInputMode activeInputerTriggerMode = INPUT_TRIGGER_TIM;
eTriggerInput isTriggerInputEnabled = DISABLE_TRIGGER_INPUT;

#define TRIGGER_DATA_SIZE 240
uint32_t trigger_input[TRIGGER_DATA_SIZE] = {};

#define 	MAX_FREQ_COUNT_STORE	8
uint32_t 	freq_count_value = 0;
uint8_t 	freq_count_index = 0;
uint32_t 	freq_count_store[MAX_FREQ_COUNT_STORE];


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
//		TIM2->DIER &= ~TIM_DIER_UDE;
//		TIM2->CR1 &= ~TIM_CR1_CEN;

		// disable the comparator
		HAL_COMP_Stop(&hcomp1);

		// stop the ADC
		HAL_ADC_Stop_DMA(&hadc1);

		GPIOA->AFR[0] &= ~(GPIO_AF1_TIM2);
		GPIOA->AFR[0] &= ~(GPIO_AF8_COMP1);


		IT_SetTriggerStatus(DISABLE_TRIGGER_INPUT);

		FuncO_ApplyProfileToSignal(eDefaultFuncPreset);
	}
	// enable the trigger input
	else
	{
		// select the pin to use for trigger input
		switch(IT_GetActiveTriggerMode())
		{
			case INPUT_TRIGGER_TIM:

				// TS5A3357 -> PA0
				HAL_GPIO_WritePin(TRIGMUX1_GPIO_Port, TRIGMUX1_Pin, GPIO_PIN_SET);		// TS5A3357 Pin6
				HAL_GPIO_WritePin(TRIGMUX2_GPIO_Port, TRIGMUX2_Pin, GPIO_PIN_RESET); 	// TS5A3357 Pin5

				// Reciprocal counter timer
				//recip_counter = 0;
				//HAL_TIM_Base_Start_IT(&htim4);

//				TIM2->DIER |= TIM_DIER_UIE;
//				TIM2->CR1 |= TIM_CR1_CEN;

				HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, freq_count_store, MAX_FREQ_COUNT_STORE);
				//HAL_TIM_Base_Start_IT(&htim2);

				// Init PA0 with TIM2 CH1 alt-function (AF) -
/*				GPIOA->MODER &= ~(GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1);	// reset mode registers
				GPIOA->MODER |= (GPIO_MODER_MODE0_1);	// set port mode to AF
				GPIOA->AFR[0] &= ~((1 << 0x04) | (1 << 0x03) | (1 << 0x02) | (1 << 0x01));	// reset AF registers - See Table 13 "Alternate Functions" in STM32G474 datasheet
				//GPIOA->AFR[0] |= GPIO_AF1_TIM2;		// set AF to TIM2_CH1
				GPIOA->AFR[0] |= GPIO_AF14_TIM2;	// set AF to TIM2_ETR

				// TIMER SLAVE MODE INIT
				TIM2->SMCR |= (TIM_SMCR_ECE);		// enable timer external clock source
				//TIM2->CCMR1 |= (TIM_CCMR1_CC1S_1);	// enable channel 1 as direct input
				//TIM2->CCMR1 |= (TIM_CCMR1_IC1PSC_0 | TIM_CCMR1_IC1PSC_1);
				//TIM2->SMCR |= (TIM_TS_TI1FP1);		// enable timer "Filtered timer input 1" (tim_ti1fp1)
				TIM2->SMCR |= TIM_TS_ETRF;
				TIM2->SMCR |= (TIM_SMCR_SMS_2);		// enable timer reset trigger mode

*/

				break;
			case INPUT_TRIGGER_COMP:
				// TS5A3357 -> PA1
				HAL_GPIO_WritePin(TRIGMUX1_GPIO_Port, TRIGMUX1_Pin, GPIO_PIN_RESET);	// TS5A3357 Pin6
				HAL_GPIO_WritePin(TRIGMUX2_GPIO_Port, TRIGMUX2_Pin, GPIO_PIN_SET); 		// TS5A3357 Pin5

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


				break;
			case INPUT_TRIGGER_ADC:
				// TS5A3357 -> PA2
				HAL_GPIO_WritePin(TRIGMUX1_GPIO_Port, TRIGMUX1_Pin, GPIO_PIN_SET);		// TS5A3357 Pin6
				HAL_GPIO_WritePin(TRIGMUX2_GPIO_Port, TRIGMUX2_Pin, GPIO_PIN_SET);		// TS5A3357 Pin5

				HAL_ADC_Start_DMA(&hadc1, trigger_input, TRIGGER_DATA_SIZE);

/*				// pause timer to reAux both outputs
				OUTPUT_TIMER->CR1 &= ~(TIM_CR1_CEN);
				//HAL_TIM_Base_Stop(&htim2);

				// restart the DAC with the new data
				HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, trigger_input, TRIGGER_DATA_SIZE, DAC_ALIGN_12B_R);

				// resume timer to reAux both outputs
				//HAL_TIM_Base_Start(&htim2);
				OUTPUT_TIMER->CR1 |= (TIM_CR1_CEN);

				//TODO enable ADC trigger input
*/
				FuncO_ApplyProfileToSignal(eDefaultFuncPreset);
				break;

			default:
				break;

		}
		// set status to enabled
		IT_SetTriggerStatus(ENABLE_TRIGGER_INPUT);
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
		case INPUT_TRIGGER_TIM:
			IT_SetActiveTriggerMode(INPUT_TRIGGER_COMP);
			break;
		case INPUT_TRIGGER_COMP:
			IT_SetActiveTriggerMode(INPUT_TRIGGER_ADC);
			break;
		case INPUT_TRIGGER_ADC:
			IT_SetActiveTriggerMode(INPUT_TRIGGER_TIM);
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
	if(trigger_input[0] == 0)
		OUTPUT_TIMER->ARR = 1;
	else
		OUTPUT_TIMER->ARR = trigger_input[0];
	printf("%lu\n", trigger_input[0]);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

	uint32_t avg_freq_count = 0;
	for(int x = 0; x < MAX_FREQ_COUNT_STORE; x++)
	{
		avg_freq_count += freq_count_store[x];
	}

	avg_freq_count /= MAX_FREQ_COUNT_STORE;

	printf("ARR %lu = %4.2fHz\n",avg_freq_count, (float)SM_MCLK / ((float)TIM2->PSC * (float)avg_freq_count));

}
/*
void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim)
{
	for(int x = 0; x < MAX_FREQ_COUNT_STORE; x++)
	{
		printf("%lu, ", freq_count_store[x]);
	}
	printf("------------\n");
}
*/
