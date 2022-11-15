/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
static Button_List button_list[] = DEFAULT_KEY_MAP;
#define BUTTON_MAX (sizeof(button_list)/sizeof(button_list[0]))
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
*/
void MX_GPIO_Init(void)
{

  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);

  /* USER LED */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  LL_GPIO_WriteOutputPort(GPIOA, LL_GPIO_PIN_2);

  /* Mode detect */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Init Key */
  for(uint8_t i = 0;i < BUTTON_MAX; ++i) {
    LL_GPIO_SetPinPull(button_list[i].port, button_list[i].pin, LL_GPIO_PULL_DOWN);
    LL_GPIO_SetPinMode(button_list[i].port, button_list[i].pin, LL_GPIO_MODE_INPUT);

    LL_EXTI_SetEXTISource(button_list[i].exti_port, button_list[i].exti_cfg_line);
    EXTI_InitStruct.Line_0_31 |= button_list[i].exti_line;
  }

  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  NVIC_SetPriority(EXTI0_1_IRQn, 0);
  NVIC_SetPriority(EXTI2_3_IRQn, 0);
  NVIC_SetPriority(EXTI4_15_IRQn, 0);

}

/* USER CODE BEGIN 2 */
Run_Mode_t Get_Run_Mode(void)
{
  return LL_GPIO_IsInputPinSet(IR_RUN_MODE_PORT, IR_RUN_MODE_PIN);
}

uint8_t Ir_Get_Button(void)
{
  uint8_t i;
  for(i = 0;i < BUTTON_MAX; ++i)
  {
    if(LL_GPIO_IsInputPinSet(button_list[i].port, button_list[i].pin))
      return i;
  }

  return 0xff; // no button detected
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
