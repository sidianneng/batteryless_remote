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

typedef enum {
  IR_OUTPUT_MODE = 0,
  IR_LEARN_MODE,
}Run_Mode_t;

typedef enum {
  BUTTON_1,
  BUTTON_2,
  BUTTON_3,
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
