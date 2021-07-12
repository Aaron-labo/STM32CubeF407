/*
 * key.h
 *
 *  Created on: Apr 3, 2021
 *      Author: Francis
 */

#ifndef INC_KEY_H_
#define INC_KEY_H_

#include "gpio.h"

#define KY_UP_Pin GPIO_PIN_0
#define KY_UP_GPIO_Port GPIOA
#define KEY0_Pin GPIO_PIN_2
#define KEY0_GPIO_Port GPIOE
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY2_Pin GPIO_PIN_4
#define KEY2_GPIO_Port GPIOE

//按键宏定义
#define KEY0 HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)
#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)
#define KEY2 HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)
#define KY_UP HAL_GPIO_ReadPin(KY_UP_GPIO_Port, KY_UP_Pin)
enum KEY{
	KEY0_PRES = 1,
	KEY1_PRES,
	KEY2_PRES,
	KY_UP_PRES,
	NO_PRES
};

uint8_t KeyScan(uint8_t mode);

#endif /* INC_KEY_H_ */
