/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "usart.h"
#include "gpio.h"
#include "log.h"
#include "hxd019.h"
#include "flash.h"
#include "tim.h"
#include "ir_decode.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

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
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void EnterSTOP0Mode(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  Button_Id_t button_id = BUTTON_MAX;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* System interrupt init*/

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  Log_Init();
  Log_Printf("batteryless remote start\n");
  MX_TIM3_Init();
  MX_TIM14_Init();
  MX_TIM16_Init();
  MX_ADC1_Init();
  LL_GPIO_WriteOutputPort(GPIOA, LL_GPIO_PIN_2);

  LL_mDelay(500000);
  Log_Printf("enter stop mode\n");
  EnterSTOP0Mode();
  Log_Printf("wake up from stop mode\n");

  /* USER CODE BEGIN 2 */
  // if(Get_Run_Mode() == IR_OUTPUT_MODE)
  // {
  //   Log_Printf("IR OUTPUT MODE\n");
  //   while(1)
  //   {
  //     button_id = Ir_Get_Button();
  //     if(button_id != BUTTON_MAX)
  //     {
  //       Log_Printf("button id:%d\n", button_id);
  //       Log_Printf("output ret:%d\n", Ir_Output(button_id));
  //     }
  //   }
  // }
  // else
  // {
  //   Log_Printf("IR LEARN MODE\n");
  //   while(1)
  //   {
  //     button_id = Ir_Get_Button();
  //     if(button_id != BUTTON_MAX)
  //     {
  //       Log_Printf("button id:%d\n", button_id);
  //       ir_decode_init();
  //       LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
  //       LL_TIM_EnableIT_CC1(TIM3);
  //       LL_TIM_EnableCounter(TIM3);
  //       Log_Printf("learn ret:%d\n", Ir_Learn(button_id, 10));
  //     }
  //   }
  // }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    // LL_mDelay(500000);
    // if(ir_get_state() == IR_READY)
    // {
    //   Log_Printf("total len:%d\n", ir_decode.data_len - 1);
    //   for(uint8_t i = 1;i < ir_decode.data_len; ++i)
    //   {
    //     Log_Printf("%d ", ir_decode.ir_data[i]);
    //   }
    //   Log_Printf("\n");
    //   ir_decode_init();
    //   LL_TIM_EnableIT_CC1(TIM3);
    // }
    //LL_mDelay(100000);
    //Log_Printf("button:%d\n", Ir_Get_Button());
    //LL_mDelay(10000);
    //Log_Printf("adc data: %d\n", LL_ADC_REG_ReadConversionData12(ADC1));
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  LL_RCC_SetHSIDiv(LL_RCC_HSI_DIV_8);
  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the HSI */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

  LL_Init1msTick(2000000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(2000000);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
}

/* USER CODE BEGIN 4 */
void EnterSTOP0Mode(void)
{
  /** Request to enter "Stop 0" mode
    * Following procedure describe in STM32G0xx Reference Manual
    * See PWR part, section Low-power modes, "Stop 0" mode
    */
  /* Set Stop 0 mode when CPU enters deepsleep */
  LL_PWR_SetPowerMode(LL_PWR_MODE_STOP1);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  LL_LPM_EnableDeepSleep();

  /* Request Wait For Interrupt */
  __WFI();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
