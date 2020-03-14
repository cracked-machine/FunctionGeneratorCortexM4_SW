/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_pwr.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define TRIGGER_DATA_SIZE 1
extern uint32_t trigger_input[TRIGGER_DATA_SIZE];

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_TEST_Pin GPIO_PIN_14
#define LED_TEST_GPIO_Port GPIOC
#define ENC_SW_Pin GPIO_PIN_2
#define ENC_SW_GPIO_Port GPIOC
#define ENC_SW_EXTI_IRQn EXTI2_IRQn
#define TRIGMODE_Pin GPIO_PIN_3
#define TRIGMODE_GPIO_Port GPIOC
#define DCBIAS_INVERT_Pin GPIO_PIN_3
#define DCBIAS_INVERT_GPIO_Port GPIOA
#define SG2_Pin GPIO_PIN_4
#define SG2_GPIO_Port GPIOC
#define SG1_Pin GPIO_PIN_5
#define SG1_GPIO_Port GPIOC
#define SG0_Pin GPIO_PIN_0
#define SG0_GPIO_Port GPIOB
#define DC_Pin GPIO_PIN_6
#define DC_GPIO_Port GPIOB
#define CS_Pin GPIO_PIN_7
#define CS_GPIO_Port GPIOB
#define RST_Pin GPIO_PIN_9
#define RST_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
