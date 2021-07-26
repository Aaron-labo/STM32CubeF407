/*
 * led.h
 *
 *  Created on: Apr 3, 2021
 *      Author: Francis
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "gpio.h"

#define LED0_Pin GPIO_PIN_9
#define LED0_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOF

//LED宏定义
#define LED0_On() HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET)
#define LED0_Off() HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET)
#define LED1_On() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
#define LED1_Off() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define LED0_Tog() HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin)
#define LED1_Tog() HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)
#define LED0 HAL_GPIO_ReadPin(LED0_GPIO_Port, LED0_Pin)
#define LED1 HAL_GPIO_ReadPin(LED1_GPIO_Port, LED1_Pin)

#endif /* INC_LED_H_ */
