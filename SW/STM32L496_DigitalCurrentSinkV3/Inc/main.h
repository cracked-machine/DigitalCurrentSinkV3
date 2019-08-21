/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KP5_EXTI0_Pin GPIO_PIN_0
#define KP5_EXTI0_GPIO_Port GPIOB
#define KP5_EXTI0_EXTI_IRQn EXTI0_IRQn
#define KP6_EXTI1_Pin GPIO_PIN_1
#define KP6_EXTI1_GPIO_Port GPIOB
#define KP6_EXTI1_EXTI_IRQn EXTI1_IRQn
#define KP7_EXTI2_Pin GPIO_PIN_2
#define KP7_EXTI2_GPIO_Port GPIOB
#define KP7_EXTI2_EXTI_IRQn EXTI2_IRQn
#define KP1_GPOUT_Pin GPIO_PIN_7
#define KP1_GPOUT_GPIO_Port GPIOE
#define KP2_GPOUT_Pin GPIO_PIN_8
#define KP2_GPOUT_GPIO_Port GPIOE
#define KP3_GPOUT_Pin GPIO_PIN_9
#define KP3_GPOUT_GPIO_Port GPIOE
#define KP4_GPOUT_Pin GPIO_PIN_10
#define KP4_GPOUT_GPIO_Port GPIOE
#define Btn1_EXT10_Pin GPIO_PIN_10
#define Btn1_EXT10_GPIO_Port GPIOD
#define Btn1_EXT10_EXTI_IRQn EXTI15_10_IRQn
#define Btn2_EXT11_Pin GPIO_PIN_11
#define Btn2_EXT11_GPIO_Port GPIOD
#define Btn2_EXT11_EXTI_IRQn EXTI15_10_IRQn
#define Btn3_EXT12_Pin GPIO_PIN_12
#define Btn3_EXT12_GPIO_Port GPIOD
#define Btn3_EXT12_EXTI_IRQn EXTI15_10_IRQn
#define Btn4_EXT13_Pin GPIO_PIN_13
#define Btn4_EXT13_GPIO_Port GPIOD
#define Btn4_EXT13_EXTI_IRQn EXTI15_10_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
