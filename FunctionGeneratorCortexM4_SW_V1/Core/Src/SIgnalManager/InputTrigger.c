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
		OUTPUT_TIMER->SMCR &= ~(TIM_SMCR_ECE);
		// disable timer enable "Filtered timer input 1" (tim_ti1fp1)
		OUTPUT_TIMER->SMCR &= ~(TIM_TS_TI1FP1);
		// disable timer reset trigger mode
		OUTPUT_TIMER->SMCR &= ~(TIM_SMCR_SMS_2);
		// set status to disabled

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

				// ALT FUNC PIN INIT
				GPIOA->MODER &= ~(GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1);	// reset
				GPIOA->MODER |= (GPIO_MODER_MODE0_1);	// set port mode to AF
				GPIOA->AFR[0] &= ~((1 << 0x04) | (1 << 0x03) | (1 << 0x02) | (1 << 0x01));	// reset
				GPIOA->AFR[0] |= GPIO_AF1_TIM2;	// set alt pin function to TIM2 CH1

				// TIMER SLAVE MODE INIT
				OUTPUT_TIMER->SMCR |= (TIM_SMCR_ECE);		// enable timer external clock source
				OUTPUT_TIMER->SMCR |= (TIM_TS_TI1FP1);		// enable timer "Filtered timer input 1" (tim_ti1fp1)
				OUTPUT_TIMER->SMCR |= (TIM_SMCR_SMS_2);		// enable timer reset trigger mode

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

				// pause timer to reAux both outputs
				OUTPUT_TIMER->CR1 &= ~(TIM_CR1_CEN);
				//HAL_TIM_Base_Stop(&htim2);

				// restart the DAC with the new data
				HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, trigger_input, TRIGGER_DATA_SIZE, DAC_ALIGN_12B_R);

				// resume timer to reAux both outputs
				//HAL_TIM_Base_Start(&htim2);
				OUTPUT_TIMER->CR1 |= (TIM_CR1_CEN);

				//TODO enable ADC trigger input

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
