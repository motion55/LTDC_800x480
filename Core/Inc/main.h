/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "ov7670/ov7670.h"

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
#define DISP_Pin GPIO_PIN_8
#define DISP_GPIO_Port GPIOI
#define TP_RST_Pin GPIO_PIN_6
#define TP_RST_GPIO_Port GPIOF
#define TP_SCL_Pin GPIO_PIN_7
#define TP_SCL_GPIO_Port GPIOF
#define TP_SDA_Pin GPIO_PIN_8
#define TP_SDA_GPIO_Port GPIOF
#define LED3_Pin GPIO_PIN_4
#define LED3_GPIO_Port GPIOH
#define TP_SCLD12_Pin GPIO_PIN_12
#define TP_SCLD12_GPIO_Port GPIOD
#define TP_SDAD13_Pin GPIO_PIN_13
#define TP_SDAD13_GPIO_Port GPIOD
#define TP_INT_Pin GPIO_PIN_7
#define TP_INT_GPIO_Port GPIOD
#define TP_INT_EXTI_IRQn EXTI9_5_IRQn
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_7
#define LED2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define	CAMERA_RESET_GPIO_Port	DISP_GPIO_Port
#define	CAMERA_RESET_Pin		DISP_Pin

#define	debug_huart	huart1
#define	debug_data	uart1_data

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
