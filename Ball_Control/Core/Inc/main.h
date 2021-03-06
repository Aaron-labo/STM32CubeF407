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
#define OLED_CS_Pin GPIO_PIN_4
#define OLED_CS_GPIO_Port GPIOE
#define BEEP_Pin GPIO_PIN_8
#define BEEP_GPIO_Port GPIOF
#define KY_UP_Pin GPIO_PIN_0
#define KY_UP_GPIO_Port GPIOA
#define KY_UP_EXTI_IRQn EXTI0_IRQn
#define Row4_Pin GPIO_PIN_2
#define Row4_GPIO_Port GPIOG
#define Row3_Pin GPIO_PIN_3
#define Row3_GPIO_Port GPIOG
#define Row2_Pin GPIO_PIN_4
#define Row2_GPIO_Port GPIOG
#define Row1_Pin GPIO_PIN_5
#define Row1_GPIO_Port GPIOG
#define Column1_Pin GPIO_PIN_6
#define Column1_GPIO_Port GPIOG
#define Column2_Pin GPIO_PIN_7
#define Column2_GPIO_Port GPIOG
#define Column3_Pin GPIO_PIN_8
#define Column3_GPIO_Port GPIOG
#define Column4_Pin GPIO_PIN_9
#define Column4_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
