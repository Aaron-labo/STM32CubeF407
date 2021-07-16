/*
 * app_main.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Francis
 */

#include "app_main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"
#include "math.h"
#include "tim.h"

#include "lcd.h"
#include "host_computer.h"
#include "mpu6050.h"
#include "pca9685.h"
#include "PID.h"
#include "keyboard.h"

#define FRAME 50  //设置摄像头帧率为50

//MPU6050_t MPU6050; //MPU6050结构体，用于存放欧拉角的原始值和结果
uint8_t receive_buff[32] = { 0 }; //DMA接收缓存区

uint16_t coordinate_XY[32][2] = { 0 };  //用于保存当前球坐标
uint16_t SetPosi[2];	//用于保存预设坐标,初始值为原点位置

float speed, speedX, speedY; //用于存放当前速度
float distance; //存放当前位置和目标位置距离差

uint8_t i = 0;
PID pid_X, pid_Y;  //PID结构体,分别表示X,Y坐标

uint8_t Mode[6] = { 0 };

//计算小球速度
float ballSpeed(uint16_t *coordinate_XY, uint8_t len) {
	float distanceX, distanceY;
	uint8_t j = 0;
	j = (i - 10) ? (i >= 10) : (i - 10 + len);
	distanceX = *(coordinate_XY + 2 * i + 0) - *(coordinate_XY + 2 * j + 0);
	distanceY = *(coordinate_XY + 2 * i + 1) - *(coordinate_XY + 2 * j + 1);
	distance = sqrtf(distanceX * distanceX + distanceY * distanceY);

	speedX = distanceX * FRAME / 10;
	speedY = distanceY * FRAME / 10;
	speed = distance * FRAME / 10;
	return distance;
}

//确定9个位置坐标
void GetSetPosi(uint16_t *SetPosi, uint8_t number) {
	switch (number) {
	case 1:
		SetPosi[0] = 80;
		SetPosi[1] = 80;
		break;
	case 2:
		SetPosi[0] = 200;
		SetPosi[1] = 80;
		break;
	case 3:
		SetPosi[0] = 320;
		SetPosi[1] = 80;
		break;
	case 4:
		SetPosi[0] = 80;
		SetPosi[1] = 200;
		break;
	case 5:
		SetPosi[0] = 200;
		SetPosi[1] = 200;
		break;
	case 6:
		SetPosi[0] = 320;
		SetPosi[1] = 200;
		break;
	case 7:
		SetPosi[0] = 80;
		SetPosi[1] = 320;
		break;
	case 8:
		SetPosi[0] = 200;
		SetPosi[1] = 320;
		break;
	case 9:
		SetPosi[0] = 320;
		SetPosi[1] = 320;
		break;
	}
}

//LCD显示函数
void ShowString() {
	uint8_t Buffer[32]; //输出文本暂存区
	LCD_ShowString(30, 30, 400, 48, 48, (uint8_t*) "STM32F407");

//	print("\r\nKalmanAngleX:%.2f\r\nKalmanAngleY:%.2f\r\n",
//			MPU6050.KalmanAngleX, MPU6050.KalmanAngleY);
//	//LCD输出平台欧拉角
//	sprintf((char*) Buffer, "KalmanAngleX:%7.2f", MPU6050.KalmanAngleX);
//	LCD_ShowString(30, 100, 400, 32, 32, Buffer);
//	sprintf((char*) Buffer, "KalmanAngleY:%7.2f", MPU6050.KalmanAngleY);
//	LCD_ShowString(30, 150, 400, 32, 32, Buffer);

	//LCD输出设定球坐标
	sprintf((char*) Buffer, "Actual_XY:(%4d, %4d)", SetPosi[0], SetPosi[1]);
	LCD_ShowString(30, 100, 400, 32, 32, Buffer);
	//LCD输出当前球坐标，若球的位置达到要求，则输出黑色文字，否则输出红色文字
	if (distance <= 30) {
		POINT_COLOR = RED;
	} else {
		POINT_COLOR = BLACK;
	}
	sprintf((char*) Buffer, "SET_XY   :(%4d, %4d)", coordinate_XY[i][0],
			coordinate_XY[i][1]);
	LCD_ShowString(30, 150, 400, 32, 32, Buffer);
	POINT_COLOR = BLACK;

	//LCD输出舵机当前角度
	sprintf((char*) Buffer, "Angle_X:%6.2f", pid_X.angle);
	LCD_ShowString(30, 200, 400, 32, 32, Buffer);
	sprintf((char*) Buffer, "Angle_Y:%6.2f", pid_Y.angle);
	LCD_ShowString(30, 250, 400, 32, 32, Buffer);

	LCD_ShowString(30, 300, 400, 32, 32, (uint8_t*) "请选择模式");
}

//模式1：稳定模式
void ModeStable(void) {
	//确定稳定坐标
	GetSetPosi(SetPosi, Mode[1]);
	//将稳定坐标放入PID结构体中
	ChaSetPosi(&pid_X, SetPosi[0]);
	ChaSetPosi(&pid_Y, SetPosi[1]);

	//计算小球速度,同时查看间距
	ballSpeed((uint16_t*) coordinate_XY, 32);
	//分别使用pid算法调整X,Y的坐标
	//其中0通道控制X轴舵机,1通道控制Y轴舵机
	PID_Calc(&pid_X, coordinate_XY[i][0], speedX);
	PID_Calc(&pid_Y, coordinate_XY[i][1], speedY);
	PCA9685_SetServoAngle(0, pid_X.angle);
	PCA9685_SetServoAngle(1, pid_Y.angle);

	//同一使用LCD输出相关信息
	ShowString();
}

//模式2：移动模式
void ModeMove(void) {
	uint8_t count = 0;
	static uint8_t isTim = 0;  //判断是否稳定，是否开始计时，Tim为1即为开始计时
	while (Mode[count] != 0) {
		count++;
	}

	for (uint8_t i = 1; i < count;) {

		//确定目的坐标
		GetSetPosi(SetPosi, Mode[i]);
		ChaSetPosi(&pid_X, SetPosi[0]);
		ChaSetPosi(&pid_Y, SetPosi[1]);

		//计算小球速度,同时查看间距
		ballSpeed((uint16_t*) coordinate_XY, 32);
		//i==1时，需要在初始位置稳定2s以上
		if (i == 1) {
			if (isTim == 0) {
				if (distance <= 30) {
					HAL_TIM_Base_Start(&htim2);
					isTim = 1;
				}
			} else {
				if (distance > 30) {
					isTim = 1;
					HAL_TIM_Base_Stop(&htim2);
					__HAL_TIM_SET_COUNTER(&htim2, 0);
				} else if (__HAL_TIM_GET_COUNTER(&htim2) >= 30000) {
					i++;
					isTim = 1;
					HAL_TIM_Base_Stop(&htim2);
					__HAL_TIM_SET_COUNTER(&htim2, 0);
				}
			}
		} else if (i > 1 || i < count - 1) { //中间路径只需稍微停留即可，这里停留0.5s
			if (isTim == 0) {
				if (distance <= 30) {
					HAL_TIM_Base_Start(&htim2);
					isTim = 1;
				}
			} else {
				if (distance > 30) {
					isTim = 1;
					HAL_TIM_Base_Stop(&htim2);
					__HAL_TIM_SET_COUNTER(&htim2, 0);
				} else if (__HAL_TIM_GET_COUNTER(&htim2) >= 5000) {
					i++;
					isTim = 1;
					HAL_TIM_Base_Stop(&htim2);
					__HAL_TIM_SET_COUNTER(&htim2, 0);
				}
			}
		}

		//分别使用pid算法调整X,Y的坐标
		//其中0通道控制X轴舵机,1通道控制Y轴舵机
		PID_Calc(&pid_X, coordinate_XY[i][0], speedX);
		PID_Calc(&pid_Y, coordinate_XY[i][1], speedY);
		PCA9685_SetServoAngle(0, pid_X.angle);
		PCA9685_SetServoAngle(1, pid_Y.angle);
	}
}

//模式3：绕圈模式
void ModeRound(void) {
	//确定中心坐标
	GetSetPosi(SetPosi, Mode[1]);
	//将稳定坐标放入PID结构体中
	ChaSetPosi(&pid_X, SetPosi[0]);
	ChaSetPosi(&pid_Y, SetPosi[1]);
}

//选择模式
void SelecMode(uint8_t isInit) {
	uint8_t key;
	uint8_t ModeBuffer[6];  //模式缓存区
	for (uint8_t i = 0; i < 6; i++) {
		ModeBuffer[i] = Mode[i];
		Mode[i] = 0;
	}

	printf("请选择模式:(模式+格点)\r\n如：从1经过2，3至6 ---------- 移动+1+2+3+6\r\n");
	for (uint8_t i = 0; i <= 4; i++) {
		while ((key = keyboard_scan()) == NOPRES)
			//等待按键输入
			;

		/*
		 * 若输入格式不符合要求，则重新输入
		 * 若如何输入，则显示模式缓存区数据
		 * 先输入模式（即稳定、移动和绕圈），后输入数字
		 */
		if (i == 0 && key != STABLE && key != MOVE && key != ROUND) {
			printf("你输入的格式不符合要求，请重新输入!\r\n");
			i = -1;
			continue;
		} else if (i == 0 && (key == STABLE || key == MOVE || key == ROUND)) {
			Mode[i] = key;
			printf("%d  %d  %d  %d  %d\r\n", Mode[0], Mode[1], Mode[2], Mode[3],
					Mode[4]);
			continue;
		} else if (key == DETER) {
			break;
		} else if (key == RESET) {
			for (i = 0; i <= 4; i++) {
				Mode[i] = 0;
			}
			i = -1;
			printf("复位\r\n");
			continue;
		}

		//判断格式输入是否正确
		if ((key >= ONE && key <= THREE) || (key >= FOUR && key <= SIX)
				|| (key >= SEVEN && key <= NINE)) {
			Mode[i] = key;
			printf("%d  %d  %d  %d  %d\r\n", Mode[0], Mode[1], Mode[2], Mode[3],
					Mode[4]);
			continue;
		} else if (key == DETER) {
			break;
		} else if (key == RESET) {
			for (i = 0; i <= 4; i++) {
				Mode[i] = 0;
			}
			i = -1;
			printf("复位\r\n");
			continue;
		}

		//若按下CANCEL键，则取消以上输入，并将模式缓存区的数据恢复
		if (key == CANCEL) {
			if (isInit == 0) {
				for (uint8_t i = 0; i < 6; i++) {
					Mode[i] = ModeBuffer[i];
				}
				return;
			} else {
				printf("你输入的格式不符合要求，请重新输入!\r\n");
				i -= 1;
			}
		} else {
			printf("你输入的格式不符合要求，请重新输入!\r\n");
			i -= 1;
		}
	}
}

//初始化函数
void app_main_init(void) {
	//LCD初始化
	TFTLCD_Init();
	LCD_Clear(WHITE);
	POINT_COLOR = BLACK;

//	//MPU6050初始化,判断MPU6050是否正常连接
//	while (MPU6050_Init(&hi2c1) == 1)
//		;

	//PCA9685初始化,将通道一和通道二(本次需要使用这两个通道)的角度初始化为0
	PCA9685_Init(&hi2c1);
	PCA9685_SetServoAngle(0, 90);
	PCA9685_SetServoAngle(1, 90);

	SelecMode(1);

	//PID初始化, 并设定预设球位置
	PID_Init(&pid_X);
	PID_Init(&pid_Y);

	HAL_Delay(500);   //延时1s用于舵机调整角度
}

//主程序函数
void app_main(void) {
	if (Mode[0] == STABLE) {
		ModeStable();
	} else if (Mode[0] == MOVE) {
		ModeMove();
	} else if (Mode[0] == ROUND) {
		ModeRound();
	}

//	MPU6050_Read_All(&hi2c1, &MPU6050);
	//	mpu6050_send_data((float)MPU6050.KalmanAngleX, (float)MPU6050.KalmanAngleY, 0, 0, 0, 0);
//	usart1_report_imu(MPU6050.Accel_X_RAW, MPU6050.Accel_Y_RAW,
//			MPU6050.Accel_Z_RAW, MPU6050.Gyro_X_RAW, MPU6050.Gyro_Y_RAW,
//			MPU6050.Gyro_Z_RAW, (float) MPU6050.KalmanAngleX * 100,
//			(float) MPU6050.KalmanAngleY * 100, 0);
	//	print("\r\nKalmanAngleX:%.2f\r\nKalmanAngleY:%.2f\r\n", MPU6050.KalmanAngleX, MPU6050.KalmanAngleY);
}

// 须在头文件中添加 #include <stdio.h>

//////////////////////////////////////////////////////////////////
// 加入以下代码,支持printf函数,而不需要选择use MicroLIB
// MDK中同样定义了 __GNUC__，使用__ARMCC_VERSION 或  __CC_ARM 区分MDK和STM32CubeIDE
// MDK预定义宏，详见 ：https://www.keil.com/support/man/docs/armcc/armcc_chr1359125007083.htm

#ifdef __CC_ARM // 或 #ifdef __ARMCC_VERSION
	  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#else
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#endif
#if 1

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x) {
	x = x;
}
//重定义fputc函数
PUTCHAR_PROTOTYPE {
	// 具体哪个串口可以更改huart2为其它串口
	// HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1 , 0xffff);
	while ((USART1->SR & 0X40) == 0) {
	}; //循环发送,直到发送完毕
	USART1->DR = (uint8_t) ch;

	//  while ((USART2->SR & 0X40) == 0) {
	//  }; //循环发送,直到发送完毕
	//  USART2->DR = (uint8_t) ch;

	return ch;
}
#endif
