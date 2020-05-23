/**
  ******************************************************************************
  * @file    stm32g4xx_hal_dma_ex.c
  * @author  MCD Application Team
  * @brief   DMA Extension HAL module driver
  *         This file provides firmware functions to manage the following
  *         functionalities of the DMA Extension peripheral:
  *           + Extended features functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
  The DMA Extension HAL driver can be used as follows:

   (+) Configure the DMA_MUX Auxhronization Block using HAL_DMAEx_ConfigMuxAux function.
   (+) Configure the DMA_MUX Request Generator Block using HAL_DMAEx_ConfigMuxRequestGenerator function.
       Functions HAL_DMAEx_EnableMuxRequestGenerator and HAL_DMAEx_DisableMuxRequestGenerator can then be used
       to respectively enable/disable the request generator.

   (+) To handle the DMAMUX Interrupts, the function  HAL_DMAEx_MUX_IRQHandler should be called from
       the DMAMUX IRQ handler i.e DMAMUX1_OVR_IRQHandler.
       As only one interrupt line is available for all DMAMUX channels and request generators , HAL_DMAEx_MUX_IRQHandler should be
       called with, as parameter, the appropriate DMA handle as many as used DMAs in the user project
      (exception done if a given DMA is not using the DMAMUX Aux block neither a request generator)

  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @defgroup DMAEx DMAEx
  * @brief DMA Extended HAL module driver
  * @{
  */

#ifdef HAL_DMA_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private Constants ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup DMAEx_Exported_Functions DMAEx Exported Functions
  * @{
  */

/** @defgroup DMAEx_Exported_Functions_Group1 DMAEx Extended features functions
  *  @brief   Extended features functions
  *
@verbatim
 ===============================================================================
                #####  Extended features functions  #####
 ===============================================================================
    [..]  This section provides functions allowing to:

    (+) Configure the DMAMUX Auxhronization Block using HAL_DMAEx_ConfigMuxAux function.
    (+) Configure the DMAMUX Request Generator Block using HAL_DMAEx_ConfigMuxRequestGenerator function.
       Functions HAL_DMAEx_EnableMuxRequestGenerator and HAL_DMAEx_DisableMuxRequestGenerator can then be used
       to respectively enable/disable the request generator.

@endverbatim
  * @{
  */


/**
  * @brief  Configure the DMAMUX Auxhronization parameters for a given DMA channel (instance).
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA channel.
  * @param  pAuxConfig : pointer to HAL_DMA_MuxAuxConfigTypeDef : contains the DMAMUX Auxhronization parameters
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMAEx_ConfigMuxAux(DMA_HandleTypeDef *hdma, HAL_DMA_MuxAuxConfigTypeDef *pAuxConfig)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));

  assert_param(IS_DMAMUX_Aux_SIGNAL_ID(pAuxConfig->AuxSignalID));

  assert_param(IS_DMAMUX_Aux_POLARITY(pAuxConfig-> AuxPolarity));
  assert_param(IS_DMAMUX_Aux_STATE(pAuxConfig->AuxEnable));
  assert_param(IS_DMAMUX_Aux_EVENT(pAuxConfig->EventEnable));
  assert_param(IS_DMAMUX_Aux_REQUEST_NUMBER(pAuxConfig->RequestNumber));

  /*Check if the DMA state is ready */
  if (hdma->State == HAL_DMA_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hdma);

    /* Set the new Auxhronization parameters (and keep the request ID filled during the Init)*/
    MODIFY_REG(hdma->DMAmuxChannel->CCR, \
               (~DMAMUX_CxCR_DMAREQ_ID), \
               ((pAuxConfig->AuxSignalID) << DMAMUX_CxCR_Aux_ID_Pos) | ((pAuxConfig->RequestNumber - 1U) << DMAMUX_CxCR_NBREQ_Pos) | \
               pAuxConfig->AuxPolarity | ((uint32_t)pAuxConfig->AuxEnable << DMAMUX_CxCR_SE_Pos) | \
               ((uint32_t)pAuxConfig->EventEnable << DMAMUX_CxCR_EGE_Pos));

    /* Process UnLocked */
    __HAL_UNLOCK(hdma);

    return HAL_OK;
  }
  else
  {
    /*DMA State not Ready*/
    return HAL_ERROR;
  }
}

/**
  * @brief  Configure the DMAMUX request generator block used by the given DMA channel (instance).
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA channel.
  * @param  pRequestGeneratorConfig : pointer to HAL_DMA_MuxRequestGeneratorConfigTypeDef :
  *         contains the request generator parameters.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMAEx_ConfigMuxRequestGenerator(DMA_HandleTypeDef *hdma,
                                                      HAL_DMA_MuxRequestGeneratorConfigTypeDef *pRequestGeneratorConfig)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));

  assert_param(IS_DMAMUX_REQUEST_GEN_SIGNAL_ID(pRequestGeneratorConfig->SignalID));

  assert_param(IS_DMAMUX_REQUEST_GEN_POLARITY(pRequestGeneratorConfig->Polarity));
  assert_param(IS_DMAMUX_REQUEST_GEN_REQUEST_NUMBER(pRequestGeneratorConfig->RequestNumber));

  /* check if the DMA state is ready
     and DMA is using a DMAMUX request generator block
  */
  if ((hdma->State == HAL_DMA_STATE_READY) && (hdma->DMAmuxRequestGen != 0U))
  {
    /* Process Locked */
    __HAL_LOCK(hdma);

    /* Set the request generator new parameters */
    hdma->DMAmuxRequestGen->RGCR = pRequestGeneratorConfig->SignalID | \
                                   ((pRequestGeneratorConfig->RequestNumber - 1U) << (POSITION_VAL(DMAMUX_RGxCR_GNBREQ) & 0x1FU)) | \
                                   pRequestGeneratorConfig->Polarity;
    /* Process UnLocked */
    __HAL_UNLOCK(hdma);

    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Enable the DMAMUX request generator block used by the given DMA channel (instance).
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA channel.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMAEx_EnableMuxRequestGenerator(DMA_HandleTypeDef *hdma)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));

  /* check if the DMA state is ready
     and DMA is using a DMAMUX request generator block
  */
  if ((hdma->State != HAL_DMA_STATE_RESET) && (hdma->DMAmuxRequestGen != 0))
  {

    /* Enable the request generator*/
    hdma->DMAmuxRequestGen->RGCR |= DMAMUX_RGxCR_GE;

    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Disable the DMAMUX request generator block used by the given DMA channel (instance).
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA channel.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMAEx_DisableMuxRequestGenerator(DMA_HandleTypeDef *hdma)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));

  /* check if the DMA state is ready
     and DMA is using a DMAMUX request generator block
  */
  if ((hdma->State != HAL_DMA_STATE_RESET) && (hdma->DMAmuxRequestGen != 0))
  {

    /* Disable the request generator*/
    hdma->DMAmuxRequestGen->RGCR &= ~DMAMUX_RGxCR_GE;

    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Handles DMAMUX interrupt request.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA channel.
  * @retval None
  */
void HAL_DMAEx_MUX_IRQHandler(DMA_HandleTypeDef *hdma)
{
  /* Check for DMAMUX Auxhronization overrun */
  if ((hdma->DMAmuxChannelStatus->CSR & hdma->DMAmuxChannelStatusMask) != 0U)
  {
    /* Disable the Auxhro overrun interrupt */
    hdma->DMAmuxChannel->CCR &= ~DMAMUX_CxCR_SOIE;

    /* Clear the DMAMUX Auxhro overrun flag */
    hdma->DMAmuxChannelStatus->CFR = hdma->DMAmuxChannelStatusMask;

    /* Update error code */
    hdma->ErrorCode |= HAL_DMA_ERROR_Aux;

    if (hdma->XferErrorCallback != NULL)
    {
      /* Transfer error callback */
      hdma->XferErrorCallback(hdma);
    }
  }

  if (hdma->DMAmuxRequestGen != 0)
  {
    /* if using a DMAMUX request generator block Check for DMAMUX request generator overrun */
    if ((hdma->DMAmuxRequestGenStatus->RGSR & hdma->DMAmuxRequestGenStatusMask) != 0U)
    {
      /* Disable the request gen overrun interrupt */
      hdma->DMAmuxRequestGen->RGCR &= ~DMAMUX_RGxCR_OIE;

      /* Clear the DMAMUX request generator overrun flag */
      hdma->DMAmuxRequestGenStatus->RGCFR = hdma->DMAmuxRequestGenStatusMask;

      /* Update error code */
      hdma->ErrorCode |= HAL_DMA_ERROR_REQGEN;

      if (hdma->XferErrorCallback != NULL)
      {
        /* Transfer error callback */
        hdma->XferErrorCallback(hdma);
      }
    }
  }
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_DMA_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
