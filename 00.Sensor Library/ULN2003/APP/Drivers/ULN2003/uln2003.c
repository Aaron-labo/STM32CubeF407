/*
 * uln2003.c
 *
 *  Created on: Jul 31, 2021
 *      Author: Francis
 */

#include "uln2003.h"

uint8_t forward[8] = { 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09 }; // 正转
uint8_t reverse[8] = { 0x09, 0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01 }; // 反转

//引脚映射
void MotorControl(unsigned char InputData) {
	HAL_GPIO_WritePin(MOTOR_GPIO_Port, MOTOR_A_Pin,
			(GPIO_PinState) InputData & 0x01);
	HAL_GPIO_WritePin(MOTOR_GPIO_Port, MOTOR_B_Pin,
			(GPIO_PinState) InputData & 0x02);
	HAL_GPIO_WritePin(MOTOR_GPIO_Port, MOTOR_C_Pin,
			(GPIO_PinState) InputData & 0x04);
	HAL_GPIO_WritePin(MOTOR_GPIO_Port, MOTOR_D_Pin,
			(GPIO_PinState) InputData & 0x08);
}

/*
 功能：转1/64圈
 步距角5.625 360/5.625=64 减速比1/64
 故64*64个脉冲转一圈
 n 圈数
 direction 方向 1正转 非1反转
 delay delay时长ms >= 2
 */
void MotorCircle(int Rotation_Angle, int direction, int delay) {
	int i, j;
	int Motor_Pulse;
	Motor_Pulse = (int) ((double) (Rotation_Angle / 5.625));

	for (i = 0; i < Motor_Pulse * 8; i++) {
		for (j = 0; j < 8; j++) {
			if (direction == 0) {
				MotorControl(0x00);
				MotorControl(forward[j]);
			} else if(direction == 1) {
				MotorControl(0x00);
				MotorControl(reverse[j]);
			}

			HAL_Delay(delay);
		}
	}
}

