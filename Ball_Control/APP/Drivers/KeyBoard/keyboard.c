/*
 * keyboard.c
 *
 *  Created on: Jul 15, 2021
 *      Author: Francis
 */

#include "keyboard.h"

uint8_t keyboard_scan(void) {
	uint8_t i, keynum = 0;
	static uint8_t lastnum = 0;
	if (Row1_INPUT_Read == GPIO_PIN_RESET) {			//当有按键按下
		HAL_Delay(20);
		if (Row1_INPUT_Read == GPIO_PIN_RESET) { //消抖
			for (i = 1; i <= 4; i++) {
				if (i == 1)
					Column1_OUT_High;		//逐个拉低每列的IO
				else if (i == 2)
					Column2_OUT_High;
				else if (i == 3)
					Column3_OUT_High;
				else if (i == 4)
					Column4_OUT_High;

				if (Row1_INPUT_Read == GPIO_PIN_SET) //如果检测到行IO电平跟着变化，则判断为该按键按下
					keynum = i;

				if (i == 1)
					Column1_OUT_Low;
				else if (i == 2)
					Column2_OUT_Low;
				else if (i == 3)
					Column3_OUT_Low;	//每次列IO电平操作之后记得复原
				else if (i == 4)
					Column4_OUT_Low;
			}
		}
	} else if (Row2_INPUT_Read == GPIO_PIN_RESET) {
		HAL_Delay(20);
		if (Row2_INPUT_Read == GPIO_PIN_RESET) { //消抖
			for (i = 1; i <= 4; i++) {
				if (i == 1)
					Column1_OUT_High;
				else if (i == 2)
					Column2_OUT_High;
				else if (i == 3)
					Column3_OUT_High;
				else if (i == 4)
					Column4_OUT_High;

				if (Row2_INPUT_Read == GPIO_PIN_SET)
					keynum = i + 4;

				if (i == 1)
					Column1_OUT_Low;
				else if (i == 2)
					Column2_OUT_Low;
				else if (i == 3)
					Column3_OUT_Low;
				else if (i == 4)
					Column4_OUT_Low;

			}
		}
	} else if (Row3_INPUT_Read == GPIO_PIN_RESET) {
		HAL_Delay(20);
		if (Row3_INPUT_Read == GPIO_PIN_RESET) { //消抖
			for (i = 1; i <= 4; i++) {
				if (i == 1)
					Column1_OUT_High;
				else if (i == 2)
					Column2_OUT_High;
				else if (i == 3)
					Column3_OUT_High;
				else if (i == 4)
					Column4_OUT_High;

				if (Row3_INPUT_Read == GPIO_PIN_SET)
					keynum = i + 8;

				if (i == 1)
					Column1_OUT_Low;
				else if (i == 2)
					Column2_OUT_Low;
				else if (i == 3)
					Column3_OUT_Low;
				else if (i == 4)
					Column4_OUT_Low;

			}
		}
	} else if (Row4_INPUT_Read == GPIO_PIN_RESET) {
		HAL_Delay(20);
		if (Row4_INPUT_Read == GPIO_PIN_RESET) { //消抖
			for (i = 1; i <= 4; i++) {
				if (i == 1)
					Column1_OUT_High;
				else if (i == 2)
					Column2_OUT_High;
				else if (i == 3)
					Column3_OUT_High;
				else if (i == 4)
					Column4_OUT_High;

				if (Row4_INPUT_Read == GPIO_PIN_SET)
					keynum = i + 12;

				if (i == 1)
					Column1_OUT_Low;
				else if (i == 2)
					Column2_OUT_Low;
				else if (i == 3)
					Column3_OUT_Low;
				else if (i == 4)
					Column4_OUT_Low;

			}
		}
	} else if (Row1_INPUT_Read == GPIO_PIN_SET
			&& Row2_INPUT_Read == GPIO_PIN_RESET
			&& Row3_INPUT_Read == GPIO_PIN_RESET
			&& Row4_INPUT_Read == GPIO_PIN_RESET) {
		return NOPRES;
	}

	if(lastnum == keynum)
	{
		return NOPRES;
	}
	lastnum = keynum;

	ShowMode(keynum, 0xff);

	return keynum;
}

void keyOperat(void) {
	static uint8_t keynum = 0, lastnum = 0;
	keynum = keyboard_scan();
	if (lastnum == keynum) {
		return;
	}
	switch (keynum) {
	case ONE:
		printf("按键被按下。\r\n------------1\r\n");
		break;
	case TWO:
		printf("按键被按下。\r\n------------2\r\n");
		break;
	case THREE:
		printf("按键被按下。\r\n------------3\r\n");
		break;
	case FOUR:
		printf("按键被按下。\r\n------------4\r\n");
		break;
	case FIVE:
		printf("按键被按下。\r\n------------5\r\n");
		break;
	case SIX:
		printf("按键被按下。\r\n------------6\r\n");
		break;
	case SEVEN:
		printf("按键被按下。\r\n------------7\r\n");
		break;
	case EIGHT:
		printf("按键被按下。\r\n------------8\r\n");
		break;
	case NINE:
		printf("按键被按下。\r\n------------9\r\n");
		break;
	case ZERO:
		printf("按键被按下。\r\n------------0\r\n");
		break;
	case STABLE:
		printf("按键被按下。\r\n------------稳定\r\n");
		break;
	case MOVE:
		printf("按键被按下。\r\n------------移动\r\n");
		break;
	case ROUND:
		printf("按键被按下。\r\n------------绕圈\r\n");
		break;
	case CANCEL:
		printf("按键被按下。\r\n------------取消\r\n");
		break;
	case DETER:
		printf("按键被按下。\r\n------------确定\r\n");
		break;
	case RESET:
		printf("按键被按下。\r\n------------重置\r\n");
		break;

	default:
		break;
	}
	lastnum = keynum;
}


