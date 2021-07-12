/*
 * app_main.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Francis
 */

#include "app_main.h"

#include "main.h"
#include "tim.h"
#include "gpio.h"

#include "led.h"

void app_main_init() {

}

void app_main() {
	LED0_On();
	HAL_Delay(500);
	LED1_On();
	HAL_Delay(500);
	LED0_Off();
	HAL_Delay(500);
	LED1_Off();
	HAL_Delay(500);
}
