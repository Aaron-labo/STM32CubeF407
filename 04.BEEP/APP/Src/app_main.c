/*
 * app_main.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Francis
 */

#include "app_main.h"
#include "gpio.h"
#include "beep.h"


void app_main_init() {

}

void app_main() {
	BEEP_On();
	HAL_Delay(1000);
	BEEP_Off();
	HAL_Delay(1000);
}
