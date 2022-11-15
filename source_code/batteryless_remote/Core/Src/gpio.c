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
static Button_List button_list[] = {
  {IR_BUTTON1_PORT, IR_BUTTON1_PIN},
  {IR_BUTTON2_PORT, IR_BUTTON2_PIN},
  {IR_BUTTON3_PORT, IR_BUTTON3_PIN},
  {IR_BUTTON4_PORT, IR_BUTTON4_PIN},
  {IR_BUTTON5_PORT, IR_BUTTON5_PIN},
  {IR_BUTTON6_PORT, IR_BUTTON6_PIN},
  {IR_BUTTON7_PORT, IR_BUTTON7_PIN},
  {IR_BUTTON8_PORT, IR_BUTTON8_PIN},
  {IR_BUTTON9_PORT, IR_BUTTON9_PIN},
  {IR_BUTTON10_PORT, IR_BUTTON10_PIN},
  {IR_BUTTON11_PORT, IR_BUTTON11_PIN},
  {IR_BUTTON12_PORT, IR_BUTTON12_PIN}
};
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
  }

  /* Init EXTI */
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTB, LL_EXTI_CONFIG_LINE7);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTB, LL_EXTI_CONFIG_LINE9);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTC, LL_EXTI_CONFIG_LINE15);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE0);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE4);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE5);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE8);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE11);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE12);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE13);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE14);
  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTB, LL_EXTI_CONFIG_LINE6);

  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_7 | LL_EXTI_LINE_9 | LL_EXTI_LINE_15 | LL_EXTI_LINE_0 | LL_EXTI_LINE_4 | LL_EXTI_LINE_5 | LL_EXTI_LINE_8 | LL_EXTI_LINE_11 | LL_EXTI_LINE_12 | LL_EXTI_LINE_13 | LL_EXTI_LINE_14 |LL_EXTI_LINE_6;
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

Button_Id_t Ir_Get_Button(void)
{
  uint8_t i;
  for(i = 0;i < BUTTON_MAX; ++i)
  {
    if(LL_GPIO_IsInputPinSet(button_list[i].port, button_list[i].pin))
      return i;
  }

  return i;
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
