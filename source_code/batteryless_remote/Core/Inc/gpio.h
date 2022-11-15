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

#define IR_BUTTON1_PORT GPIOB
#define IR_BUTTON1_PIN  LL_GPIO_PIN_7
#define IR_BUTTON2_PORT GPIOB
#define IR_BUTTON2_PIN  LL_GPIO_PIN_9
#define IR_BUTTON3_PORT GPIOC
#define IR_BUTTON3_PIN  LL_GPIO_PIN_15
#define IR_BUTTON4_PORT GPIOA
#define IR_BUTTON4_PIN  LL_GPIO_PIN_0
#define IR_BUTTON5_PORT GPIOA
#define IR_BUTTON5_PIN  LL_GPIO_PIN_4
#define IR_BUTTON6_PORT GPIOA
#define IR_BUTTON6_PIN  LL_GPIO_PIN_5
#define IR_BUTTON7_PORT GPIOA
#define IR_BUTTON7_PIN  LL_GPIO_PIN_8
#define IR_BUTTON8_PORT GPIOA
#define IR_BUTTON8_PIN  LL_GPIO_PIN_11
#define IR_BUTTON9_PORT GPIOA
#define IR_BUTTON9_PIN  LL_GPIO_PIN_12
#define IR_BUTTON10_PORT GPIOA
#define IR_BUTTON10_PIN  LL_GPIO_PIN_13
#define IR_BUTTON11_PORT GPIOA
#define IR_BUTTON11_PIN  LL_GPIO_PIN_14
#define IR_BUTTON12_PORT GPIOB
#define IR_BUTTON12_PIN  LL_GPIO_PIN_6

typedef enum {
  IR_OUTPUT_MODE = 0,
  IR_LEARN_MODE,
}Run_Mode_t;

typedef enum {
  BUTTON_1 = 0,
  BUTTON_2,
  BUTTON_3,
  BUTTON_4,
  BUTTON_5,
  BUTTON_6,
  BUTTON_7,
  BUTTON_8,
  BUTTON_9,
  BUTTON_10,
  BUTTON_11,
  BUTTON_12,
  BUTTON_MAX
}Button_Id_t;

typedef struct {
  uint32_t port;
  uint32_t pin;
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
