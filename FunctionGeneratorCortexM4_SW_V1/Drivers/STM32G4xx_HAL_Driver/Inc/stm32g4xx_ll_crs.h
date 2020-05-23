/**
  ******************************************************************************
  * @file    stm32g4xx_ll_crs.h
  * @author  MCD Application Team
  * @brief   Header file of CRS LL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
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
#ifndef __STM32G4xx_LL_CRS_H
#define __STM32G4xx_LL_CRS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx.h"

/** @addtogroup STM32G4xx_LL_Driver
  * @{
  */

#if defined(CRS)

/** @defgroup CRS_LL CRS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup CRS_LL_Exported_Constants CRS Exported Constants
  * @{
  */

/** @defgroup CRS_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_CRS_ReadReg function
  * @{
  */
#define LL_CRS_ISR_AuxOKF                 CRS_ISR_AuxOKF
#define LL_CRS_ISR_AuxWARNF               CRS_ISR_AuxWARNF
#define LL_CRS_ISR_ERRF                    CRS_ISR_ERRF
#define LL_CRS_ISR_EAuxF                  CRS_ISR_EAuxF
#define LL_CRS_ISR_AuxERR                 CRS_ISR_AuxERR
#define LL_CRS_ISR_AuxMISS                CRS_ISR_AuxMISS
#define LL_CRS_ISR_TRIMOVF                 CRS_ISR_TRIMOVF
/**
  * @}
  */

/** @defgroup CRS_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_CRS_ReadReg and  LL_CRS_WriteReg functions
  * @{
  */
#define LL_CRS_CR_AuxOKIE                 CRS_CR_AuxOKIE
#define LL_CRS_CR_AuxWARNIE               CRS_CR_AuxWARNIE
#define LL_CRS_CR_ERRIE                    CRS_CR_ERRIE
#define LL_CRS_CR_EAuxIE                  CRS_CR_EAuxIE
/**
  * @}
  */

/** @defgroup CRS_LL_EC_Aux_DIV Auxhronization Signal Divider
  * @{
  */
#define LL_CRS_Aux_DIV_1                  ((uint32_t)0x00U)                         /*!< Auxhro Signal not divided (default) */
#define LL_CRS_Aux_DIV_2                  CRS_CFGR_AuxDIV_0                        /*!< Auxhro Signal divided by 2 */
#define LL_CRS_Aux_DIV_4                  CRS_CFGR_AuxDIV_1                        /*!< Auxhro Signal divided by 4 */
#define LL_CRS_Aux_DIV_8                  (CRS_CFGR_AuxDIV_1 | CRS_CFGR_AuxDIV_0) /*!< Auxhro Signal divided by 8 */
#define LL_CRS_Aux_DIV_16                 CRS_CFGR_AuxDIV_2                        /*!< Auxhro Signal divided by 16 */
#define LL_CRS_Aux_DIV_32                 (CRS_CFGR_AuxDIV_2 | CRS_CFGR_AuxDIV_0) /*!< Auxhro Signal divided by 32 */
#define LL_CRS_Aux_DIV_64                 (CRS_CFGR_AuxDIV_2 | CRS_CFGR_AuxDIV_1) /*!< Auxhro Signal divided by 64 */
#define LL_CRS_Aux_DIV_128                CRS_CFGR_AuxDIV                          /*!< Auxhro Signal divided by 128 */
/**
  * @}
  */

/** @defgroup CRS_LL_EC_Aux_SOURCE Auxhronization Signal Source
  * @{
  */
#define LL_CRS_Aux_SOURCE_GPIO            ((uint32_t)0x00U)       /*!< Auxhro Signal soucre GPIO */
#define LL_CRS_Aux_SOURCE_LSE             CRS_CFGR_AuxSRC_0      /*!< Auxhro Signal source LSE */
#define LL_CRS_Aux_SOURCE_USB             CRS_CFGR_AuxSRC_1      /*!< Auxhro Signal source USB SOF (default)*/
/**
  * @}
  */

/** @defgroup CRS_LL_EC_Aux_POLARITY Auxhronization Signal Polarity
  * @{
  */
#define LL_CRS_Aux_POLARITY_RISING        ((uint32_t)0x00U)     /*!< Auxhro Active on rising edge (default) */
#define LL_CRS_Aux_POLARITY_FALLING       CRS_CFGR_AuxPOL      /*!< Auxhro Active on falling edge */
/**
  * @}
  */

/** @defgroup CRS_LL_EC_FREQERRORDIR Frequency Error Direction
  * @{
  */
#define LL_CRS_FREQ_ERROR_DIR_UP             ((uint32_t)0x00U)         /*!< Upcounting direction, the actual frequency is above the target */
#define LL_CRS_FREQ_ERROR_DIR_DOWN           ((uint32_t)CRS_ISR_FEDIR) /*!< Downcounting direction, the actual frequency is below the target */
/**
  * @}
  */

/** @defgroup CRS_LL_EC_DEFAULTVALUES Default Values
  * @{
  */
/**
  * @brief Reset value of the RELOAD field
  * @note The reset value of the RELOAD field corresponds to a target frequency of 48 MHz
  *       and a Auxhronization signal frequency of 1 kHz (SOF signal from USB)
  */
#define LL_CRS_RELOADVALUE_DEFAULT         ((uint32_t)0xBB7FU)

/**
  * @brief Reset value of Frequency error limit.
  */
#define LL_CRS_ERRORLIMIT_DEFAULT          ((uint32_t)0x22U)

/**
  * @brief Reset value of the HSI48 Calibration field
  * @note The default value is 64, which corresponds to the middle of the trimming interval.
  *       The trimming step is specified in the product datasheet.
  *       A higher TRIM value corresponds to a higher output frequency
  */
#define LL_CRS_HSI48CALIBRATION_DEFAULT    ((uint32_t)0x40U)
/**
  * @}
  */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup CRS_LL_Exported_Macros CRS Exported Macros
  * @{
  */

/** @defgroup CRS_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in CRS register
  * @param  __INSTANCE__ CRS Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_CRS_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in CRS register
  * @param  __INSTANCE__ CRS Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_CRS_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/** @defgroup CRS_LL_EM_Exported_Macros_Calculate_Reload Exported_Macros_Calculate_Reload
  * @{
  */

/**
  * @brief  Macro to calculate reload value to be set in CRS register according to target and Aux frequencies
  * @note   The RELOAD value should be selected according to the ratio between
  *         the target frequency and the frequency of the Auxhronization source after
  *         prescaling. It is then decreased by one in order to reach the expected
  *         Auxhronization on the zero value. The formula is the following:
  *              RELOAD = (fTARGET / fAux) -1
  * @param  __FTARGET__ Target frequency (value in Hz)
  * @param  __FAux__ Auxhronization signal frequency (value in Hz)
  * @retval Reload value (in Hz)
  */
#define __LL_CRS_CALC_CALCULATE_RELOADVALUE(__FTARGET__, __FAux__) (((__FTARGET__) / (__FAux__)) - 1U)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup CRS_LL_Exported_Functions CRS Exported Functions
  * @{
  */

/** @defgroup CRS_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable Frequency error counter
  * @note When this bit is set, the CRS_CFGR register is write-protected and cannot be modified
  * @rmtoll CR           CEN           LL_CRS_EnableFreqErrorCounter
  * @retval None
  */
__STATIC_INLINE void LL_CRS_EnableFreqErrorCounter(void)
{
  SET_BIT(CRS->CR, CRS_CR_CEN);
}

/**
  * @brief  Disable Frequency error counter
  * @rmtoll CR           CEN           LL_CRS_DisableFreqErrorCounter
  * @retval None
  */
__STATIC_INLINE void LL_CRS_DisableFreqErrorCounter(void)
{
  CLEAR_BIT(CRS->CR, CRS_CR_CEN);
}

/**
  * @brief  Check if Frequency error counter is enabled or not
  * @rmtoll CR           CEN           LL_CRS_IsEnabledFreqErrorCounter
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsEnabledFreqErrorCounter(void)
{
  return ((READ_BIT(CRS->CR, CRS_CR_CEN) == (CRS_CR_CEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Automatic trimming counter
  * @rmtoll CR           AUTOTRIMEN    LL_CRS_EnableAutoTrimming
  * @retval None
  */
__STATIC_INLINE void LL_CRS_EnableAutoTrimming(void)
{
  SET_BIT(CRS->CR, CRS_CR_AUTOTRIMEN);
}

/**
  * @brief  Disable Automatic trimming counter
  * @rmtoll CR           AUTOTRIMEN    LL_CRS_DisableAutoTrimming
  * @retval None
  */
__STATIC_INLINE void LL_CRS_DisableAutoTrimming(void)
{
  CLEAR_BIT(CRS->CR, CRS_CR_AUTOTRIMEN);
}

/**
  * @brief  Check if Automatic trimming is enabled or not
  * @rmtoll CR           AUTOTRIMEN    LL_CRS_IsEnabledAutoTrimming
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsEnabledAutoTrimming(void)
{
  return ((READ_BIT(CRS->CR, CRS_CR_AUTOTRIMEN) == (CRS_CR_AUTOTRIMEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set HSI48 oscillator smooth trimming
  * @note   When the AUTOTRIMEN bit is set, this field is controlled by hardware and is read-only
  * @rmtoll CR           TRIM          LL_CRS_SetHSI48SmoothTrimming
  * @param  Value a number between Min_Data = 0 and Max_Data = 63
  * @note   Default value can be set thanks to @ref LL_CRS_HSI48CALIBRATION_DEFAULT
  * @retval None
  */
__STATIC_INLINE void LL_CRS_SetHSI48SmoothTrimming(uint32_t Value)
{
  MODIFY_REG(CRS->CR, CRS_CR_TRIM, Value << CRS_CR_TRIM_Pos);
}

/**
  * @brief  Get HSI48 oscillator smooth trimming
  * @rmtoll CR           TRIM          LL_CRS_GetHSI48SmoothTrimming
  * @retval a number between Min_Data = 0 and Max_Data = 63
  */
__STATIC_INLINE uint32_t LL_CRS_GetHSI48SmoothTrimming(void)
{
  return (uint32_t)(READ_BIT(CRS->CR, CRS_CR_TRIM) >> CRS_CR_TRIM_Pos);
}

/**
  * @brief  Set counter reload value
  * @rmtoll CFGR         RELOAD        LL_CRS_SetReloadCounter
  * @param  Value a number between Min_Data = 0 and Max_Data = 0xFFFF
  * @note   Default value can be set thanks to @ref LL_CRS_RELOADVALUE_DEFAULT
  *         Otherwise it can be calculated in using macro @ref __LL_CRS_CALC_CALCULATE_RELOADVALUE (_FTARGET_, _FAux_)
  * @retval None
  */
__STATIC_INLINE void LL_CRS_SetReloadCounter(uint32_t Value)
{
  MODIFY_REG(CRS->CFGR, CRS_CFGR_RELOAD, Value);
}

/**
  * @brief  Get counter reload value
  * @rmtoll CFGR         RELOAD        LL_CRS_GetReloadCounter
  * @retval a number between Min_Data = 0 and Max_Data = 0xFFFF
  */
__STATIC_INLINE uint32_t LL_CRS_GetReloadCounter(void)
{
  return (uint32_t)(READ_BIT(CRS->CFGR, CRS_CFGR_RELOAD));
}

/**
  * @brief  Set frequency error limit
  * @rmtoll CFGR         FELIM         LL_CRS_SetFreqErrorLimit
  * @param  Value a number between Min_Data = 0 and Max_Data = 255
  * @note   Default value can be set thanks to @ref LL_CRS_ERRORLIMIT_DEFAULT
  * @retval None
  */
__STATIC_INLINE void LL_CRS_SetFreqErrorLimit(uint32_t Value)
{
  MODIFY_REG(CRS->CFGR, CRS_CFGR_FELIM, Value << CRS_CFGR_FELIM_Pos);
}

/**
  * @brief  Get frequency error limit
  * @rmtoll CFGR         FELIM         LL_CRS_GetFreqErrorLimit
  * @retval A number between Min_Data = 0 and Max_Data = 255
  */
__STATIC_INLINE uint32_t LL_CRS_GetFreqErrorLimit(void)
{
  return (uint32_t)(READ_BIT(CRS->CFGR, CRS_CFGR_FELIM) >> CRS_CFGR_FELIM_Pos);
}

/**
  * @brief  Set division factor for Aux signal
  * @rmtoll CFGR         AuxDIV       LL_CRS_SetAuxDivider
  * @param  Divider This parameter can be one of the following values:
  *         @arg @ref LL_CRS_Aux_DIV_1
  *         @arg @ref LL_CRS_Aux_DIV_2
  *         @arg @ref LL_CRS_Aux_DIV_4
  *         @arg @ref LL_CRS_Aux_DIV_8
  *         @arg @ref LL_CRS_Aux_DIV_16
  *         @arg @ref LL_CRS_Aux_DIV_32
  *         @arg @ref LL_CRS_Aux_DIV_64
  *         @arg @ref LL_CRS_Aux_DIV_128
  * @retval None
  */
__STATIC_INLINE void LL_CRS_SetAuxDivider(uint32_t Divider)
{
  MODIFY_REG(CRS->CFGR, CRS_CFGR_AuxDIV, Divider);
}

/**
  * @brief  Get division factor for Aux signal
  * @rmtoll CFGR         AuxDIV       LL_CRS_GetAuxDivider
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CRS_Aux_DIV_1
  *         @arg @ref LL_CRS_Aux_DIV_2
  *         @arg @ref LL_CRS_Aux_DIV_4
  *         @arg @ref LL_CRS_Aux_DIV_8
  *         @arg @ref LL_CRS_Aux_DIV_16
  *         @arg @ref LL_CRS_Aux_DIV_32
  *         @arg @ref LL_CRS_Aux_DIV_64
  *         @arg @ref LL_CRS_Aux_DIV_128
  */
__STATIC_INLINE uint32_t LL_CRS_GetAuxDivider(void)
{
  return (uint32_t)(READ_BIT(CRS->CFGR, CRS_CFGR_AuxDIV));
}

/**
  * @brief  Set Aux signal source
  * @rmtoll CFGR         AuxSRC       LL_CRS_SetAuxSignalSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_CRS_Aux_SOURCE_GPIO
  *         @arg @ref LL_CRS_Aux_SOURCE_LSE
  *         @arg @ref LL_CRS_Aux_SOURCE_USB
  * @retval None
  */
__STATIC_INLINE void LL_CRS_SetAuxSignalSource(uint32_t Source)
{
  MODIFY_REG(CRS->CFGR, CRS_CFGR_AuxSRC, Source);
}

/**
  * @brief  Get Aux signal source
  * @rmtoll CFGR         AuxSRC       LL_CRS_GetAuxSignalSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CRS_Aux_SOURCE_GPIO
  *         @arg @ref LL_CRS_Aux_SOURCE_LSE
  *         @arg @ref LL_CRS_Aux_SOURCE_USB
  */
__STATIC_INLINE uint32_t LL_CRS_GetAuxSignalSource(void)
{
  return (uint32_t)(READ_BIT(CRS->CFGR, CRS_CFGR_AuxSRC));
}

/**
  * @brief  Set input polarity for the Aux signal source
  * @rmtoll CFGR         AuxPOL       LL_CRS_SetAuxPolarity
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref LL_CRS_Aux_POLARITY_RISING
  *         @arg @ref LL_CRS_Aux_POLARITY_FALLING
  * @retval None
  */
__STATIC_INLINE void LL_CRS_SetAuxPolarity(uint32_t Polarity)
{
  MODIFY_REG(CRS->CFGR, CRS_CFGR_AuxPOL, Polarity);
}

/**
  * @brief  Get input polarity for the Aux signal source
  * @rmtoll CFGR         AuxPOL       LL_CRS_GetAuxPolarity
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CRS_Aux_POLARITY_RISING
  *         @arg @ref LL_CRS_Aux_POLARITY_FALLING
  */
__STATIC_INLINE uint32_t LL_CRS_GetAuxPolarity(void)
{
  return (uint32_t)(READ_BIT(CRS->CFGR, CRS_CFGR_AuxPOL));
}

/**
  * @brief  Configure CRS for the Auxhronization
  * @rmtoll CR           TRIM          LL_CRS_ConfigAuxhronization\n
  *         CFGR         RELOAD        LL_CRS_ConfigAuxhronization\n
  *         CFGR         FELIM         LL_CRS_ConfigAuxhronization\n
  *         CFGR         AuxDIV       LL_CRS_ConfigAuxhronization\n
  *         CFGR         AuxSRC       LL_CRS_ConfigAuxhronization\n
  *         CFGR         AuxPOL       LL_CRS_ConfigAuxhronization
  * @param  HSI48CalibrationValue a number between Min_Data = 0 and Max_Data = 63
  * @param  ErrorLimitValue a number between Min_Data = 0 and Max_Data = 0xFFFF
  * @param  ReloadValue a number between Min_Data = 0 and Max_Data = 255
  * @param  Settings This parameter can be a combination of the following values:
  *         @arg @ref LL_CRS_Aux_DIV_1 or @ref LL_CRS_Aux_DIV_2 or @ref LL_CRS_Aux_DIV_4 or @ref LL_CRS_Aux_DIV_8
  *              or @ref LL_CRS_Aux_DIV_16 or @ref LL_CRS_Aux_DIV_32 or @ref LL_CRS_Aux_DIV_64 or @ref LL_CRS_Aux_DIV_128
  *         @arg @ref LL_CRS_Aux_SOURCE_GPIO or @ref LL_CRS_Aux_SOURCE_LSE or @ref LL_CRS_Aux_SOURCE_USB
  *         @arg @ref LL_CRS_Aux_POLARITY_RISING or @ref LL_CRS_Aux_POLARITY_FALLING
  * @retval None
  */
__STATIC_INLINE void LL_CRS_ConfigAuxhronization(uint32_t HSI48CalibrationValue, uint32_t ErrorLimitValue,
                                                  uint32_t ReloadValue, uint32_t Settings)
{
  MODIFY_REG(CRS->CR, CRS_CR_TRIM, HSI48CalibrationValue);
  MODIFY_REG(CRS->CFGR,
             CRS_CFGR_RELOAD | CRS_CFGR_FELIM | CRS_CFGR_AuxDIV | CRS_CFGR_AuxSRC | CRS_CFGR_AuxPOL,
             ReloadValue | (ErrorLimitValue << CRS_CFGR_FELIM_Pos) | Settings);
}

/**
  * @}
  */

/** @defgroup CRS_LL_EF_CRS_Management CRS_Management
  * @{
  */

/**
  * @brief  Generate software Aux event
  * @rmtoll CR           SWAux        LL_CRS_GenerateEvent_SWAux
  * @retval None
  */
__STATIC_INLINE void LL_CRS_GenerateEvent_SWAux(void)
{
  SET_BIT(CRS->CR, CRS_CR_SWAux);
}

/**
  * @brief  Get the frequency error direction latched in the time of the last
  * Aux event
  * @rmtoll ISR          FEDIR         LL_CRS_GetFreqErrorDirection
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CRS_FREQ_ERROR_DIR_UP
  *         @arg @ref LL_CRS_FREQ_ERROR_DIR_DOWN
  */
__STATIC_INLINE uint32_t LL_CRS_GetFreqErrorDirection(void)
{
  return (uint32_t)(READ_BIT(CRS->ISR, CRS_ISR_FEDIR));
}

/**
  * @brief  Get the frequency error counter value latched in the time of the last Aux event
  * @rmtoll ISR          FECAP         LL_CRS_GetFreqErrorCapture
  * @retval A number between Min_Data = 0x0000 and Max_Data = 0xFFFF
  */
__STATIC_INLINE uint32_t LL_CRS_GetFreqErrorCapture(void)
{
  return (uint32_t)(READ_BIT(CRS->ISR, CRS_ISR_FECAP) >> CRS_ISR_FECAP_Pos);
}

/**
  * @}
  */

/** @defgroup CRS_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Check if Aux event OK signal occurred or not
  * @rmtoll ISR          AuxOKF       LL_CRS_IsActiveFlag_AuxOK
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsActiveFlag_AuxOK(void)
{
  return ((READ_BIT(CRS->ISR, CRS_ISR_AuxOKF) == (CRS_ISR_AuxOKF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Aux warning signal occurred or not
  * @rmtoll ISR          AuxWARNF     LL_CRS_IsActiveFlag_AuxWARN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsActiveFlag_AuxWARN(void)
{
  return ((READ_BIT(CRS->ISR, CRS_ISR_AuxWARNF) == (CRS_ISR_AuxWARNF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Auxhronization or trimming error signal occurred or not
  * @rmtoll ISR          ERRF          LL_CRS_IsActiveFlag_ERR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsActiveFlag_ERR(void)
{
  return ((READ_BIT(CRS->ISR, CRS_ISR_ERRF) == (CRS_ISR_ERRF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Expected Aux signal occurred or not
  * @rmtoll ISR          EAuxF        LL_CRS_IsActiveFlag_EAux
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsActiveFlag_EAux(void)
{
  return ((READ_BIT(CRS->ISR, CRS_ISR_EAuxF) == (CRS_ISR_EAuxF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Aux error signal occurred or not
  * @rmtoll ISR          AuxERR       LL_CRS_IsActiveFlag_AuxERR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsActiveFlag_AuxERR(void)
{
  return ((READ_BIT(CRS->ISR, CRS_ISR_AuxERR) == (CRS_ISR_AuxERR)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Aux missed error signal occurred or not
  * @rmtoll ISR          AuxMISS      LL_CRS_IsActiveFlag_AuxMISS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsActiveFlag_AuxMISS(void)
{
  return ((READ_BIT(CRS->ISR, CRS_ISR_AuxMISS) == (CRS_ISR_AuxMISS)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Trimming overflow or underflow occurred or not
  * @rmtoll ISR          TRIMOVF       LL_CRS_IsActiveFlag_TRIMOVF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsActiveFlag_TRIMOVF(void)
{
  return ((READ_BIT(CRS->ISR, CRS_ISR_TRIMOVF) == (CRS_ISR_TRIMOVF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Aux event OK flag
  * @rmtoll ICR          AuxOKC       LL_CRS_ClearFlag_AuxOK
  * @retval None
  */
__STATIC_INLINE void LL_CRS_ClearFlag_AuxOK(void)
{
  WRITE_REG(CRS->ICR, CRS_ICR_AuxOKC);
}

/**
  * @brief  Clear the  Aux warning flag
  * @rmtoll ICR          AuxWARNC     LL_CRS_ClearFlag_AuxWARN
  * @retval None
  */
__STATIC_INLINE void LL_CRS_ClearFlag_AuxWARN(void)
{
  WRITE_REG(CRS->ICR, CRS_ICR_AuxWARNC);
}

/**
  * @brief  Clear TRIMOVF, AuxMISS and AuxERR bits and consequently also
  * the ERR flag
  * @rmtoll ICR          ERRC          LL_CRS_ClearFlag_ERR
  * @retval None
  */
__STATIC_INLINE void LL_CRS_ClearFlag_ERR(void)
{
  WRITE_REG(CRS->ICR, CRS_ICR_ERRC);
}

/**
  * @brief  Clear Expected Aux flag
  * @rmtoll ICR          EAuxC        LL_CRS_ClearFlag_EAux
  * @retval None
  */
__STATIC_INLINE void LL_CRS_ClearFlag_EAux(void)
{
  WRITE_REG(CRS->ICR, CRS_ICR_EAuxC);
}

/**
  * @}
  */

/** @defgroup CRS_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable Aux event OK interrupt
  * @rmtoll CR           AuxOKIE      LL_CRS_EnableIT_AuxOK
  * @retval None
  */
__STATIC_INLINE void LL_CRS_EnableIT_AuxOK(void)
{
  SET_BIT(CRS->CR, CRS_CR_AuxOKIE);
}

/**
  * @brief  Disable Aux event OK interrupt
  * @rmtoll CR           AuxOKIE      LL_CRS_DisableIT_AuxOK
  * @retval None
  */
__STATIC_INLINE void LL_CRS_DisableIT_AuxOK(void)
{
  CLEAR_BIT(CRS->CR, CRS_CR_AuxOKIE);
}

/**
  * @brief  Check if Aux event OK interrupt is enabled or not
  * @rmtoll CR           AuxOKIE      LL_CRS_IsEnabledIT_AuxOK
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsEnabledIT_AuxOK(void)
{
  return ((READ_BIT(CRS->CR, CRS_CR_AuxOKIE) == (CRS_CR_AuxOKIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Aux warning interrupt
  * @rmtoll CR           AuxWARNIE    LL_CRS_EnableIT_AuxWARN
  * @retval None
  */
__STATIC_INLINE void LL_CRS_EnableIT_AuxWARN(void)
{
  SET_BIT(CRS->CR, CRS_CR_AuxWARNIE);
}

/**
  * @brief  Disable Aux warning interrupt
  * @rmtoll CR           AuxWARNIE    LL_CRS_DisableIT_AuxWARN
  * @retval None
  */
__STATIC_INLINE void LL_CRS_DisableIT_AuxWARN(void)
{
  CLEAR_BIT(CRS->CR, CRS_CR_AuxWARNIE);
}

/**
  * @brief  Check if Aux warning interrupt is enabled or not
  * @rmtoll CR           AuxWARNIE    LL_CRS_IsEnabledIT_AuxWARN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsEnabledIT_AuxWARN(void)
{
  return ((READ_BIT(CRS->CR, CRS_CR_AuxWARNIE) == (CRS_CR_AuxWARNIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Auxhronization or trimming error interrupt
  * @rmtoll CR           ERRIE         LL_CRS_EnableIT_ERR
  * @retval None
  */
__STATIC_INLINE void LL_CRS_EnableIT_ERR(void)
{
  SET_BIT(CRS->CR, CRS_CR_ERRIE);
}

/**
  * @brief  Disable Auxhronization or trimming error interrupt
  * @rmtoll CR           ERRIE         LL_CRS_DisableIT_ERR
  * @retval None
  */
__STATIC_INLINE void LL_CRS_DisableIT_ERR(void)
{
  CLEAR_BIT(CRS->CR, CRS_CR_ERRIE);
}

/**
  * @brief  Check if Auxhronization or trimming error interrupt is enabled or not
  * @rmtoll CR           ERRIE         LL_CRS_IsEnabledIT_ERR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsEnabledIT_ERR(void)
{
  return ((READ_BIT(CRS->CR, CRS_CR_ERRIE) == (CRS_CR_ERRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Expected Aux interrupt
  * @rmtoll CR           EAuxIE       LL_CRS_EnableIT_EAux
  * @retval None
  */
__STATIC_INLINE void LL_CRS_EnableIT_EAux(void)
{
  SET_BIT(CRS->CR, CRS_CR_EAuxIE);
}

/**
  * @brief  Disable Expected Aux interrupt
  * @rmtoll CR           EAuxIE       LL_CRS_DisableIT_EAux
  * @retval None
  */
__STATIC_INLINE void LL_CRS_DisableIT_EAux(void)
{
  CLEAR_BIT(CRS->CR, CRS_CR_EAuxIE);
}

/**
  * @brief  Check if Expected Aux interrupt is enabled or not
  * @rmtoll CR           EAuxIE       LL_CRS_IsEnabledIT_EAux
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CRS_IsEnabledIT_EAux(void)
{
  return ((READ_BIT(CRS->CR, CRS_CR_EAuxIE) == (CRS_CR_EAuxIE)) ? 1UL : 0UL);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup CRS_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_CRS_DeInit(void);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(CRS) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32G4xx_LL_CRS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
