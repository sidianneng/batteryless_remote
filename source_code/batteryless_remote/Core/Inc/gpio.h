/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define IR_RUN_MODE_PORT GPIOA
#define IR_RUN_MODE_PIN LL_GPIO_PIN_3

#define DEFAULT_KEY_MAP { \
  {GPIOB, LL_GPIO_PIN_7,  LL_EXTI_CONFIG_PORTB, LL_EXTI_CONFIG_LINE7, LL_EXTI_LINE_7}, \
  {GPIOB, LL_GPIO_PIN_9,  LL_EXTI_CONFIG_PORTB, LL_EXTI_CONFIG_LINE9, LL_EXTI_LINE_9}, \
  {GPIOC, LL_GPIO_PIN_15, LL_EXTI_CONFIG_PORTC, LL_EXTI_CONFIG_LINE15, LL_EXTI_LINE_15}, \
  {GPIOA, LL_GPIO_PIN_0,  LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE0, LL_EXTI_LINE_0}, \
  {GPIOA, LL_GPIO_PIN_4,  LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE4, LL_EXTI_LINE_4}, \
  {GPIOA, LL_GPIO_PIN_5,  LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE5, LL_EXTI_LINE_5}, \
  {GPIOA, LL_GPIO_PIN_8,  LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE8, LL_EXTI_LINE_8}, \
  {GPIOA, LL_GPIO_PIN_11, LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE11, LL_EXTI_LINE_11}, \
  {GPIOA, LL_GPIO_PIN_12, LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE12, LL_EXTI_LINE_12}, \
  {GPIOA, LL_GPIO_PIN_13, LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE13, LL_EXTI_LINE_13}, \
  {GPIOA, LL_GPIO_PIN_14, LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE14, LL_EXTI_LINE_14}, \
  {GPIOB, LL_GPIO_PIN_6,  LL_EXTI_CONFIG_PORTB, LL_EXTI_CONFIG_LINE6, LL_EXTI_LINE_6}, \
}

typedef enum {
  IR_OUTPUT_MODE = 0,
  IR_LEARN_MODE,
}Run_Mode_t;

typedef struct {
  uint32_t port;
  uint32_t pin;
  uint32_t exti_port;
  uint32_t exti_cfg_line;
  uint32_t exti_line;
}Button_List;

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
Run_Mode_t Get_Run_Mode(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
