/*
 * keyboard.h
 *
 *  Created on: Jul 15, 2021
 *      Author: Francis
 */

#ifndef DRIVERS_KEYBOARD_KEYBOARD_H_
#define DRIVERS_KEYBOARD_KEYBOARD_H_

#include "app_main.h"
#include "gpio.h"

/*********列输出IO操作宏定义*********/
#define Column1_OUT_Low  HAL_GPIO_WritePin(Column1_GPIO_Port, Column1_Pin, GPIO_PIN_RESET)
#define Column2_OUT_Low  HAL_GPIO_WritePin(Column2_GPIO_Port, Column2_Pin, GPIO_PIN_RESET)
#define Column3_OUT_Low  HAL_GPIO_WritePin(Column3_GPIO_Port, Column3_Pin, GPIO_PIN_RESET)
#define Column4_OUT_Low  HAL_GPIO_WritePin(Column4_GPIO_Port, Column4_Pin, GPIO_PIN_RESET)

#define Column1_OUT_High  HAL_GPIO_WritePin(Column1_GPIO_Port, Column1_Pin, GPIO_PIN_SET)
#define Column2_OUT_High  HAL_GPIO_WritePin(Column2_GPIO_Port, Column2_Pin, GPIO_PIN_SET)
#define Column3_OUT_High  HAL_GPIO_WritePin(Column3_GPIO_Port, Column3_Pin, GPIO_PIN_SET)
#define Column4_OUT_High  HAL_GPIO_WritePin(Column4_GPIO_Port, Column4_Pin, GPIO_PIN_SET)

/*********行输入IO操作宏定义*********/
#define Row1_INPUT_Read  HAL_GPIO_ReadPin(Row1_GPIO_Port, Row1_Pin)
#define Row2_INPUT_Read  HAL_GPIO_ReadPin(Row2_GPIO_Port, Row2_Pin)
#define Row3_INPUT_Read  HAL_GPIO_ReadPin(Row3_GPIO_Port, Row3_Pin)
#define Row4_INPUT_Read  HAL_GPIO_ReadPin(Row4_GPIO_Port, Row4_Pin)

/*********按键宏定义*************/
#define ONE		1					//	1		2		3		上
#define TWO 	2					//	4		5		6		下
#define THREE	3					//	7		8		9		左
#define FOUR	5					//	确定		0		重置		右
#define FIVE	6
#define SIX		7
#define SEVEN	9
#define EIGHT	10
#define NINE	11
#define ZERO	14

#define UP		4
#define DOWN	8
#define LEFT	12
#define RIGHT	16

#define DETER	13
#define RESET	15

#define NOPRES	0

uint8_t keyboard_scan(void);
void keyOperat(void);

#endif /* DRIVERS_KEYBOARD_KEYBOARD_H_ */
