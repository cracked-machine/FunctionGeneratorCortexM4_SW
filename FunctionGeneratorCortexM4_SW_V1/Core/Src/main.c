/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "comp.h"
#include "dac.h"
#include "dma.h"
#include "rng.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "funcgen.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

#include "DisplayManager.h"
#include "EventManager.h"
#include "GainOutput.h"

// python-generated wave lut
#include "pysine.h"
#include "pysquare.h"
#include "pyunitimpulse.h"
#include "pysaw.h"
#include "pysaw_rev.h"
#include "pytriangle.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define DISABLE_ALL_TIMERS  // for debug use only!
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t sin1_max_arr = 64;
uint32_t trigger_input[TRIGGER_DATA_SIZE];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  /* Implement your write code here, this is used by puts and printf for example */
  int i=0;
  for(i=0 ; i<len ; i++)
    ITM_SendChar((*ptr++));
  return len;
}

void HAL_DAC_ErrorCallbackCh1(DAC_HandleTypeDef *hdac)
{
	// do something
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DAC1_Init();
  MX_DAC2_Init();
  MX_ADC1_Init();
  MX_COMP1_Init();
  MX_TIM2_Init();
  MX_TIM17_Init();
  MX_SPI3_Init();
  MX_RNG_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TIM16_Init();
  MX_TIM15_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */

  // main signal function output (external)
  HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, sine_data_table, SINE_DATA_SIZE, DAC_ALIGN_12B_R);
  //TIM8->ARR = sin1_max_arr;

  // DC bias output (internal)
  HAL_DAC_Start(&hdac1, DAC1_CHANNEL_2);

  // auxilliary signal sync output (external)
  //HAL_DAC_Start_DMA(&hdac2, DAC2_CHANNEL_1, sine_data_table, SINE_DATA_SIZE, DAC_ALIGN_12B_R);
  //HAL_DAC_Start_DMA(&hdac2, DAC2_CHANNEL_1, square_data_table, SQUARE_DATA_SIZE, DAC_ALIGN_12B_R);
  //HAL_DAC_Start_DMA(&hdac2, DAC2_CHANNEL_1, unitimpulse_data_table, UNITIMPULSE_DATA_SIZE, DAC_ALIGN_12B_R);
  //HAL_DAC_Start_DMA(&hdac2, DAC2_CHANNEL_1, saw_data_table, SAW_DATA_SIZE, DAC_ALIGN_12B_R);
  //HAL_DAC_Start_DMA(&hdac2, DAC2_CHANNEL_1, saw_rev_data_table, SAW_REV_DATA_SIZE, DAC_ALIGN_12B_R);
  HAL_DAC_Start_DMA(&hdac2, DAC2_CHANNEL_1, triangle_data_table, TRIANGLE_DATA_SIZE, DAC_ALIGN_12B_R);

  //HAL_DAC_Start_DMA(&hdac2, DAC2_CHANNEL_1, trigger_input, TRIGGER_DATA_SIZE, DAC_ALIGN_12B_R);
#ifndef DISABLE_ALL_TIMERS
  // single clock to run all DAC channels. TODO add independent clocks
  HAL_TIM_Base_Start(&htim8);
  TIM8->ARR = 14015;			// 100Hz
  //TIM8->ARR = 65535;
#endif //DISABLE_ALL_TIMERS

  // DC bias inversion
  HAL_GPIO_WritePin(DCBIAS_INVERT_GPIO_Port, DCBIAS_INVERT_Pin, GPIO_PIN_SET);

  // PGA gain
  HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);

#ifndef DISABLE_ALL_TIMERS
  // start test routine (update_dc_bias_sweep())
  //HAL_TIM_Base_Start_IT(&htim17);
#endif	//DISABLE_ALL_TIMERS


// http://www.ti.com/lit/ds/symlink/ts5a3357.pdf
  HAL_GPIO_WritePin(TRIGMUX1_GPIO_Port, TRIGMUX1_Pin, GPIO_PIN_RESET);	// TS5A3357 Pin6
  HAL_GPIO_WritePin(TRIGMUX2_GPIO_Port, TRIGMUX2_Pin, GPIO_PIN_RESET);	// TS5A3357 Pin5
//#define ADC_TRIGGER_MODE
//#define COMP_TRIGGER_MODE
#define TIM_TRIGGER_MODE
#ifdef ADC_TRIGGER_MODE
  // start trigger input capture on in ADC

  // set HW switch to direct ext. trigger input to ADC pin
  HAL_GPIO_WritePin(TRIGMUX1_GPIO_Port, TRIGMUX1_Pin, GPIO_PIN_SET);	// TS5A3357 Pin6
  HAL_GPIO_WritePin(TRIGMUX2_GPIO_Port, TRIGMUX2_Pin, GPIO_PIN_SET);	// TS5A3357 Pin5

  // start writing data to buffer
  HAL_ADC_Start_DMA(&hadc1, trigger_input, TRIGGER_DATA_SIZE);
#endif //ADC_TRIGGER_MODE

#ifdef COMP_TRIGGER_MODE
  // start trigger input capture on in COMP

  // set HW switch to direct ext. trigger input to COMP pin
  HAL_GPIO_WritePin(TRIGMUX1_GPIO_Port, TRIGMUX1_Pin, GPIO_PIN_RESET);	// TS5A3357 Pin6
  HAL_GPIO_WritePin(TRIGMUX2_GPIO_Port, TRIGMUX2_Pin, GPIO_PIN_SET); // TS5A3357 Pin5

  // enable comparator input

#endif //COMP_TRIGGER_MODE

#ifdef TIM_TRIGGER_MODE
  // input capture on in TIM2 slave-mode TF1FP1

  // set HW switch to direct ext. trigger input to TIM pin
  HAL_GPIO_WritePin(TRIGMODE_GPIO_Port, TRIGMODE_Pin, GPIO_PIN_SET);
  //HAL_GPIO_WritePin(TRIGMUX1_GPIO_Port, TRIGMUX1_Pin, GPIO_PIN_SET);	// TS5A3357 Pin6
  //HAL_GPIO_WritePin(TRIGMUX2_GPIO_Port, TRIGMUX2_Pin, GPIO_PIN_RESET); // TS5A3357 Pin5

  // clear slave mode select reg
  TIM2->SMCR &= ~(TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_2);

  // slave mode
  //TIM2->SMCR |= TIM_SMCR_SMS_2;						// SLAVE MODE: RESET
  TIM2->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_2;	// SLAVE MODE: GATED
  //TIM2->SMCR |= TIM_SMCR_SMS_1 | TIM_SMCR_SMS_2;	// SLAVE MODE: TRIGGER

#ifndef DISABLE_ALL_TIMERS
  HAL_TIM_Base_Start_IT(&htim2);
#endif	//DISABLE_ALL_TIMERS

#endif //TIM_TRIGGER_MODE




#ifndef DISABLE_ALL_TIMERS
  // encoder input
  HAL_TIM_Base_Start(&htim1);		// enable encoder timer
  //TIM1->DIER |= TIM_DIER_IDXIE;		// enable index interrupts

#endif	//DISABLE_ALL_TIMERS

  TIM6->PSC = 65535;
  TIM6->ARR = 65535;



  // TFT lib enable
  DM_Init();
  DM_PostInit();


  HAL_TIM_Base_Start_IT(&htim15);

  // debounce timer
  HAL_TIM_Base_Start(&htim5);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


	EM_ProcessEvent();



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 42;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV4;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_8) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks 
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RNG|RCC_PERIPHCLK_ADC12;
  PeriphClkInit.RngClockSelection = RCC_RNGCLKSOURCE_HSI48;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
