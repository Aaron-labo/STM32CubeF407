/*
 * app_main.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Francis
 */

#include "app_main.h"

#include "gpio.h"

#include "key.h"
#include "led.h"

void app_main_init() {

}

void app_main() {
	key = KeyScan(1);
	switch (key) {
	case KEY0_PRES:
		LED0_Tog();
		break;
	case KEY1_PRES:
		LED1_Tog();
		break;
	case KEY2_PRES:
		LED0_Tog();
		LED1_Tog();
		break;
	case KY_UP_PRES:
		LED0_On();
		LED1_On();
		break;
	case NO_PRES:
		LED0_Off();
		LED1_Off();
	}
}
