/**
  ******************************************************************************
  * @file    stm32g4xx_hal_dma_ex.h
  * @author  MCD Application Team
  * @brief   Header file of DMA HAL extension module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32G4xx_HAL_DMA_EX_H
#define __STM32G4xx_HAL_DMA_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @addtogroup DMAEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup DMAEx_Exported_Types DMAEx Exported Types
  * @{
  */

/**
  * @brief  HAL DMA Auxhro definition
  */


/**
  * @brief  HAL DMAMUX Auxhronization configuration structure definition
  */
typedef struct
{
  uint32_t AuxSignalID;  /*!< Specifies the Auxhronization signal gating the DMA request in periodic mode.
                              This parameter can be a value of @ref DMAEx_DMAMUX_AuxSignalID_selection */

  uint32_t AuxPolarity;  /*!< Specifies the polarity of the signal on which the DMA request is Auxhronized.
                              This parameter can be a value of @ref DMAEx_DMAMUX_AuxPolarity_selection */

  FunctionalState AuxEnable;  /*!< Specifies if the Auxhronization shall be enabled or disabled
                                    This parameter can take the value ENABLE or DISABLE*/


  FunctionalState EventEnable;    /*!< Specifies if an event shall be generated once the RequestNumber is reached.
                                       This parameter can take the value ENABLE or DISABLE */

  uint32_t RequestNumber; /*!< Specifies the number of DMA request that will be authorized after a Aux event
                               This parameter must be a number between Min_Data = 1 and Max_Data = 32 */


} HAL_DMA_MuxAuxConfigTypeDef;


/**
  * @brief  HAL DMAMUX request generator parameters structure definition
  */
typedef struct
{
  uint32_t SignalID;      /*!< Specifies the ID of the signal used for DMAMUX request generator
                              This parameter can be a value of @ref DMAEx_DMAMUX_SignalGeneratorID_selection */

  uint32_t Polarity;       /*!< Specifies the polarity of the signal on which the request is generated.
                             This parameter can be a value of @ref DMAEx_DMAMUX_RequestGeneneratorPolarity_selection */

  uint32_t RequestNumber;  /*!< Specifies the number of DMA request that will be generated after a signal event
                                This parameter must be a number between Min_Data = 1 and Max_Data = 32 */

} HAL_DMA_MuxRequestGeneratorConfigTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DMAEx_Exported_Constants DMAEx Exported Constants
  * @{
  */

/** @defgroup DMAEx_DMAMUX_AuxSignalID_selection DMAMUX AuxSignalID selection
  * @{
  */
#define HAL_DMAMUX1_Aux_EXTI0                      0U     /*!<  Auxhronization Signal is EXTI0  IT   */
#define HAL_DMAMUX1_Aux_EXTI1                      1U     /*!<  Auxhronization Signal is EXTI1  IT   */
#define HAL_DMAMUX1_Aux_EXTI2                      2U     /*!<  Auxhronization Signal is EXTI2  IT   */
#define HAL_DMAMUX1_Aux_EXTI3                      3U     /*!<  Auxhronization Signal is EXTI3  IT   */
#define HAL_DMAMUX1_Aux_EXTI4                      4U     /*!<  Auxhronization Signal is EXTI4  IT   */
#define HAL_DMAMUX1_Aux_EXTI5                      5U     /*!<  Auxhronization Signal is EXTI5  IT   */
#define HAL_DMAMUX1_Aux_EXTI6                      6U     /*!<  Auxhronization Signal is EXTI6  IT   */
#define HAL_DMAMUX1_Aux_EXTI7                      7U     /*!<  Auxhronization Signal is EXTI7  IT   */
#define HAL_DMAMUX1_Aux_EXTI8                      8U     /*!<  Auxhronization Signal is EXTI8  IT   */
#define HAL_DMAMUX1_Aux_EXTI9                      9U     /*!<  Auxhronization Signal is EXTI9  IT   */
#define HAL_DMAMUX1_Aux_EXTI10                    10U     /*!<  Auxhronization Signal is EXTI10 IT   */
#define HAL_DMAMUX1_Aux_EXTI11                    11U     /*!<  Auxhronization Signal is EXTI11 IT   */
#define HAL_DMAMUX1_Aux_EXTI12                    12U     /*!<  Auxhronization Signal is EXTI12 IT   */
#define HAL_DMAMUX1_Aux_EXTI13                    13U     /*!<  Auxhronization Signal is EXTI13 IT   */
#define HAL_DMAMUX1_Aux_EXTI14                    14U     /*!<  Auxhronization Signal is EXTI14 IT   */
#define HAL_DMAMUX1_Aux_EXTI15                    15U     /*!<  Auxhronization Signal is EXTI15 IT   */
#define HAL_DMAMUX1_Aux_DMAMUX1_CH0_EVT           16U     /*!<  Auxhronization Signal is DMAMUX1 Channel0 Event  */
#define HAL_DMAMUX1_Aux_DMAMUX1_CH1_EVT           17U     /*!<  Auxhronization Signal is DMAMUX1 Channel1 Event  */
#define HAL_DMAMUX1_Aux_DMAMUX1_CH2_EVT           18U     /*!<  Auxhronization Signal is DMAMUX1 Channel2 Event  */
#define HAL_DMAMUX1_Aux_DMAMUX1_CH3_EVT           19U     /*!<  Auxhronization Signal is DMAMUX1 Channel3 Event  */
#define HAL_DMAMUX1_Aux_LPTIM1_OUT                20U     /*!<  Auxhronization Signal is LPTIM1 OUT */

/**
  * @}
  */

/** @defgroup DMAEx_DMAMUX_AuxPolarity_selection DMAMUX AuxPolarity selection
  * @{
  */
#define HAL_DMAMUX_Aux_NO_EVENT                               0U    /*!< block Auxhronization events        */
#define HAL_DMAMUX_Aux_RISING     ((uint32_t)DMAMUX_CxCR_SPOL_0)    /*!< Auxhronize with rising edge events */
#define HAL_DMAMUX_Aux_FALLING    ((uint32_t)DMAMUX_CxCR_SPOL_1)    /*!< Auxhronize with falling edge events */
#define HAL_DMAMUX_Aux_RISING_FALLING ((uint32_t)DMAMUX_CxCR_SPOL)  /*!< Auxhronize with rising and falling edge events */

/**
  * @}
  */

/** @defgroup DMAEx_DMAMUX_SignalGeneratorID_selection DMAMUX SignalGeneratorID selection
  * @{
  */
#define HAL_DMAMUX1_REQ_GEN_EXTI0                0U        /*!< Request generator Signal is EXTI0 IT    */
#define HAL_DMAMUX1_REQ_GEN_EXTI1                1U        /*!< Request generator Signal is EXTI1 IT    */
#define HAL_DMAMUX1_REQ_GEN_EXTI2                2U        /*!< Request generator Signal is EXTI2 IT    */
#define HAL_DMAMUX1_REQ_GEN_EXTI3                3U        /*!< Request generator Signal is EXTI3 IT    */
#define HAL_DMAMUX1_REQ_GEN_EXTI4                4U        /*!< Request generator Signal is EXTI4 IT    */
#define HAL_DMAMUX1_REQ_GEN_EXTI5                5U        /*!< Request generator Signal is EXTI5 IT    */
#define HAL_DMAMUX1_REQ_GEN_EXTI6                6U        /*!< Request generator Signal is EXTI6 IT    */
#define HAL_DMAMUX1_REQ_GEN_EXTI7                7U        /*!< Request generator Signal is EXTI7 IT    */
#define HAL_DMAMUX1_REQ_GEN_EXTI8                8U        /*!< Request generator Signal is EXTI8 IT    */
#define HAL_DMAMUX1_REQ_GEN_EXTI9                9U        /*!< Request generator Signal is EXTI9 IT    */
#define HAL_DMAMUX1_REQ_GEN_EXTI10              10U        /*!< Request generator Signal is EXTI10 IT   */
#define HAL_DMAMUX1_REQ_GEN_EXTI11              11U        /*!< Request generator Signal is EXTI11 IT   */
#define HAL_DMAMUX1_REQ_GEN_EXTI12              12U        /*!< Request generator Signal is EXTI12 IT   */
#define HAL_DMAMUX1_REQ_GEN_EXTI13              13U        /*!< Request generator Signal is EXTI13 IT   */
#define HAL_DMAMUX1_REQ_GEN_EXTI14              14U        /*!< Request generator Signal is EXTI14 IT   */
#define HAL_DMAMUX1_REQ_GEN_EXTI15              15U        /*!< Request generator Signal is EXTI15 IT   */
#define HAL_DMAMUX1_REQ_GEN_DMAMUX1_CH0_EVT     16U        /*!< Request generator Signal is DMAMUX1 Channel0 Event */
#define HAL_DMAMUX1_REQ_GEN_DMAMUX1_CH1_EVT     17U        /*!< Request generator Signal is DMAMUX1 Channel1 Event */
#define HAL_DMAMUX1_REQ_GEN_DMAMUX1_CH2_EVT     18U        /*!< Request generator Signal is DMAMUX1 Channel2 Event */
#define HAL_DMAMUX1_REQ_GEN_DMAMUX1_CH3_EVT     19U        /*!< Request generator Signal is DMAMUX1 Channel3 Event */
#define HAL_DMAMUX1_REQ_GEN_LPTIM1_OUT          20U        /*!< Request generator Signal is LPTIM1 OUT  */

/**
  * @}
  */

/** @defgroup DMAEx_DMAMUX_RequestGeneneratorPolarity_selection DMAMUX RequestGeneneratorPolarity selection
  * @{
  */
#define HAL_DMAMUX_REQ_GEN_NO_EVENT         0x00000000U           /*!< block request generator events        */
#define HAL_DMAMUX_REQ_GEN_RISING           DMAMUX_RGxCR_GPOL_0   /*!< generate request on rising edge events */
#define HAL_DMAMUX_REQ_GEN_FALLING          DMAMUX_RGxCR_GPOL_1   /*!< generate request on falling edge events */
#define HAL_DMAMUX_REQ_GEN_RISING_FALLING   DMAMUX_RGxCR_GPOL     /*!< generate request on rising and falling edge events */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DMAEx_Exported_Functions
  * @{
  */

/* IO operation functions *****************************************************/
/** @addtogroup DMAEx_Exported_Functions_Group1
  * @{
  */

/* ------------------------- REQUEST -----------------------------------------*/
HAL_StatusTypeDef HAL_DMAEx_ConfigMuxRequestGenerator(DMA_HandleTypeDef *hdma,
                                                      HAL_DMA_MuxRequestGeneratorConfigTypeDef *pRequestGeneratorConfig);
HAL_StatusTypeDef HAL_DMAEx_EnableMuxRequestGenerator(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMAEx_DisableMuxRequestGenerator(DMA_HandleTypeDef *hdma);
/* -------------------------------------------------------------------------- */

/* ------------------------- AuxHRO -----------------------------------------*/
HAL_StatusTypeDef HAL_DMAEx_ConfigMuxAux(DMA_HandleTypeDef *hdma, HAL_DMA_MuxAuxConfigTypeDef *pAuxConfig);
/* -------------------------------------------------------------------------- */

void HAL_DMAEx_MUX_IRQHandler(DMA_HandleTypeDef *hdma);

/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DMAEx_Private_Macros DMAEx Private Macros
  * @brief    DMAEx private macros
  * @{
  */

#define IS_DMAMUX_Aux_SIGNAL_ID(SIGNAL_ID) ((SIGNAL_ID) <= HAL_DMAMUX1_Aux_LPTIM1_OUT)

#define IS_DMAMUX_Aux_REQUEST_NUMBER(REQUEST_NUMBER) (((REQUEST_NUMBER) > 0U) && ((REQUEST_NUMBER) <= 32U))

#define IS_DMAMUX_Aux_POLARITY(POLARITY) (((POLARITY) == HAL_DMAMUX_Aux_NO_EVENT)    || \
                                           ((POLARITY) == HAL_DMAMUX_Aux_RISING)   || \
                                           ((POLARITY) == HAL_DMAMUX_Aux_FALLING)  || \
                                           ((POLARITY) == HAL_DMAMUX_Aux_RISING_FALLING))

#define IS_DMAMUX_Aux_STATE(Aux) (((Aux) == DISABLE)   || ((Aux) == ENABLE))

#define IS_DMAMUX_Aux_EVENT(EVENT) (((EVENT) == DISABLE)   || \
                                     ((EVENT) == ENABLE))

#define IS_DMAMUX_REQUEST_GEN_SIGNAL_ID(SIGNAL_ID) ((SIGNAL_ID) <= HAL_DMAMUX1_REQ_GEN_LPTIM1_OUT)

#define IS_DMAMUX_REQUEST_GEN_REQUEST_NUMBER(REQUEST_NUMBER) (((REQUEST_NUMBER) > 0U) && ((REQUEST_NUMBER) <= 32U))

#define IS_DMAMUX_REQUEST_GEN_POLARITY(POLARITY) (((POLARITY) == HAL_DMAMUX_REQ_GEN_NO_EVENT)   || \
                                                  ((POLARITY) == HAL_DMAMUX_REQ_GEN_RISING)  || \
                                                  ((POLARITY) == HAL_DMAMUX_REQ_GEN_FALLING) || \
                                                  ((POLARITY) == HAL_DMAMUX_REQ_GEN_RISING_FALLING))

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32G4xx_HAL_DMA_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
