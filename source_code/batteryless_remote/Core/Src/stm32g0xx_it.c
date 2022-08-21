/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "stm32g0xx_it.h"
#include "ir_decode.h"
#include "log.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM3 global interrupt.
  */
static uint32_t Trig_Edge = LL_TIM_IC_POLARITY_FALLING;
static uint16_t l_max_time = 0;
static uint16_t h_max_time = 0;
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
  LL_TIM_ClearFlag_CC1(TIM3);
  if(ir_decode.data_len < IR_DATA_MAX_LEN)
    ir_decode.ir_data[ir_decode.data_len] = LL_TIM_IC_GetCaptureCH1(TIM3);
  if(Trig_Edge == LL_TIM_IC_POLARITY_FALLING)
  {
    Trig_Edge = LL_TIM_IC_POLARITY_RISING;
    LL_TIM_IC_SetPolarity(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
      if(ir_decode.data_len > 0)
        h_max_time = (h_max_time > ir_decode.ir_data[ir_decode.data_len] ? \
          h_max_time : ir_decode.ir_data[ir_decode.data_len]);
      if(h_max_time > l_max_time * 2){
        LL_TIM_DisableIT_CC1(TIM3);
        l_max_time = 0;
        h_max_time = 0;
        ir_set_state(IR_READY);
        return ;
      }
  }
  else
  {
    Trig_Edge = LL_TIM_IC_POLARITY_FALLING;
    LL_TIM_IC_SetPolarity(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_FALLING);
      if(ir_decode.data_len > 0)
        l_max_time = (l_max_time > ir_decode.ir_data[ir_decode.data_len] ? \
          l_max_time : ir_decode.ir_data[ir_decode.data_len]);
  }
  if(ir_decode.data_len < IR_DATA_MAX_LEN)
    ir_decode.data_len++;
  LL_TIM_SetCounter(TIM3, 0);
  LL_TIM_ClearFlag_CC1(TIM3);
  /* USER CODE END TIM3_IRQn 0 */
  /* USER CODE BEGIN TIM3_IRQn 1 */
  if(LL_TIM_IsActiveFlag_CC1OVR(TIM3))
  {
    LL_TIM_ClearFlag_CC1OVR(TIM3);
    LL_TIM_DisableIT_CC1(TIM3);
    l_max_time = 0;
    h_max_time = 0;
    ir_set_state(IR_READY);
    return ;
  }
  /* USER CODE END TIM3_IRQn 1 */
}

/* USER CODE BEGIN 1 */
/**
  * @brief This function handles TIM16 global interrupt.
  */
void TIM16_IRQHandler(void)
{
  static uint16_t cnt = 1;
  /* USER CODE BEGIN TIM16_IRQn 0 */
  LL_TIM_ClearFlag_UPDATE(TIM16);
  if(cnt < ir_decode.data_len){
    LL_TIM_SetAutoReload(TIM16, ir_decode.ir_data[cnt]);
    if(cnt % 2){
      LL_TIM_EnableCounter(TIM14);
    } else {
      LL_TIM_DisableCounter(TIM14);
    }
    cnt++;
  } else {
    cnt = 1;
    LL_TIM_DisableCounter(TIM16);
    LL_TIM_DisableIT_UPDATE(TIM16);
    LL_TIM_DisableCounter(TIM14);
  }
  /* USER CODE END TIM16_IRQn 0 */
  /* USER CODE BEGIN TIM16_IRQn 1 */

  /* USER CODE END TIM16_IRQn 1 */
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
