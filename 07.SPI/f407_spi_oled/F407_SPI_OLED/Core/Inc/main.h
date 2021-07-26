/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define OLED_Res_Pin GPIO_PIN_2
#define OLED_Res_GPIO_Port GPIOE
#define OLED_DC_Pin GPIO_PIN_3
#define OLED_DC_GPIO_Port GPIOE
#define LED0_Pin GPIO_PIN_9
#define LED0_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOF
#define OLED_CS_Pin GPIO_PIN_13
#define OLED_CS_GPIO_Port GPIOF
#define F_AIN2_Pin GPIO_PIN_2
#define F_AIN2_GPIO_Port GPIOG
#define F_AIN1_Pin GPIO_PIN_3
#define F_AIN1_GPIO_Port GPIOG
#define F_BIN1_Pin GPIO_PIN_4
#define F_BIN1_GPIO_Port GPIOG
#define F_BIN2_Pin GPIO_PIN_5
#define F_BIN2_GPIO_Port GPIOG
#define B_AIN2_Pin GPIO_PIN_6
#define B_AIN2_GPIO_Port GPIOG
#define B_AIN1_Pin GPIO_PIN_7
#define B_AIN1_GPIO_Port GPIOG
#define B_BIN1_Pin GPIO_PIN_8
#define B_BIN1_GPIO_Port GPIOG
#define B_BIN2_Pin GPIO_PIN_7
#define B_BIN2_GPIO_Port GPIOD
#define LED_BOARD_Pin GPIO_PIN_14
#define LED_BOARD_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
