/*
 * uln2003.h
 *
 *  Created on: Jul 31, 2021
 *      Author: Francis
 */

#ifndef DRIVERS_ULN2003_ULN2003_H_
#define DRIVERS_ULN2003_ULN2003_H_
#include "main.h"

//IN4: PC3  d
//IN3: PC2  c
//IN2: PC1  b
//IN1: PC0  a

#define MOTOR_A_Pin GPIO_PIN_0
#define MOTOR_B_Pin GPIO_PIN_1
#define MOTOR_C_Pin GPIO_PIN_2
#define MOTOR_D_Pin GPIO_PIN_3
#define MOTOR_GPIO_Port GPIOC

//电机8节拍控制
void MotorControl(unsigned char InputData);

/*
	功能：转1/64圈
	步距角5.625 360/5.625=64 减速比1/64
	故64*64个脉冲转一圈
	n 圈数
	direction 方向 1正转 非1反转
	delay delay时长 >= 2
*/
void MotorCircle(int Rotation_Angle, int direction, int delay);

#endif /* DRIVERS_ULN2003_ULN2003_H_ */
