/*
 * key.c
 *
 *  Created on: Apr 3, 2021
 *      Author: Francis
 */

#include "key.h"

//按键扫描函数
//mode==1时，按键按下亮，松开灭
//mode==0时，按键按下亮，再次按下灭
uint8_t KeyScan(uint8_t mode)
{
	static uint8_t key_up = 1;
	if(mode == 1){
		key_up = 1;
	}

	if(key_up && (KEY0 == GPIO_PIN_RESET || KEY1 == GPIO_PIN_RESET || KEY2 == GPIO_PIN_RESET || KY_UP == GPIO_PIN_SET)){
		HAL_Delay(10);
		key_up = 0;
		if(KEY0 == GPIO_PIN_RESET){
			return KEY0_PRES;
		}else if(KEY1 == GPIO_PIN_RESET){
			return KEY1_PRES;
		}else if(KEY2 == GPIO_PIN_RESET){
			return KEY2_PRES;
		}else if(KY_UP == GPIO_PIN_SET){
			return KY_UP_PRES;
		}
	}else if(KEY0 == GPIO_PIN_SET && KEY1 == GPIO_PIN_SET && KEY2 == GPIO_PIN_SET && KY_UP == GPIO_PIN_RESET){
		key_up = 1;
		if(mode)
		{
			return NO_PRES;
		}
	}
	return 0;
}
