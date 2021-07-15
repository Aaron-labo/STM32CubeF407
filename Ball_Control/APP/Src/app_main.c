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
uint16_t SetPosi_X = 0, SetPosi_Y = 0;   //用于保存预设坐标,初始值为原点位置

float speed, speedX, speedY; //用于存放当前速度
float distance; //存放当前位置和目标位置距离差

uint8_t i = 0;
PID pid_X, pid_Y;  //PID结构体,分别表示X,Y坐标

uint8_t Mode[6] = {0};

//计算小球速度
float ballSpeed(uint16_t *coordinate_XY, uint8_t len, uint8_t i) {
	float distanceX, distanceY;
	uint8_t j = 0;
	j = (i - 10) ? (i >= 10) : (i - 10 + len);
	distanceX = *(coordinate_XY + 2 * i + 0) - *(coordinate_XY + 2 * j + 0);
	distanceY = *(coordinate_XY + 2 * i + 1) - *(coordinate_XY + 2 * j + 1);
	distance = sqrtf(distanceX * distanceX + distanceY * distanceY);

	speedX = distanceX * FRAME / 10;
	speedY = distanceY * FRAME / 10;
	speed = distance * FRAME / 10;
	return speed;
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
	sprintf((char*) Buffer, "Actual_XY:(%4d, %4d)", SetPosi_X, SetPosi_Y);
	LCD_ShowString(30, 100, 400, 32, 32, Buffer);
	//LCD输出当前球坐标，若球的位置达到要求，则输出黑色文字，否则输出红色文字
	if ((coordinate_XY[i][0] - SetPosi_X <= 50
			&& SetPosi_X - coordinate_XY[i][0] >= -50)
			&& (coordinate_XY[i][1] - SetPosi_Y <= 50
					&& coordinate_XY[i][1] - SetPosi_Y >= -50)) {
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

	LCD_ShowString(30, 300, 400, 32, 32, (uint8_t *)"请选择模式");
}

void SelectMode(void)
{

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


	//PID初始化, 并设定预设球位置
	PID_Init(&pid_X);
	PID_Init(&pid_Y);
	ChaSetPosi(&pid_X, SetPosi_X);
	ChaSetPosi(&pid_Y, SetPosi_Y);

	HAL_Delay(1000);   //延时1s用于舵机调整角度
}

//主程序函数
void app_main(void) {
	//分别使用pid算法调整X,Y的坐标
	//其中0通道控制X轴舵机,1通道控制Y轴舵机
	PID_Calc(&pid_X, coordinate_XY[i][0], speedX);
	PID_Calc(&pid_Y, coordinate_XY[i][1], speedY);
	PCA9685_SetServoAngle(0, pid_X.angle);
	PCA9685_SetServoAngle(1, pid_Y.angle);
	keyOperat();

//	MPU6050_Read_All(&hi2c1, &MPU6050);
	//	mpu6050_send_data((float)MPU6050.KalmanAngleX, (float)MPU6050.KalmanAngleY, 0, 0, 0, 0);
//	usart1_report_imu(MPU6050.Accel_X_RAW, MPU6050.Accel_Y_RAW,
//			MPU6050.Accel_Z_RAW, MPU6050.Gyro_X_RAW, MPU6050.Gyro_Y_RAW,
//			MPU6050.Gyro_Z_RAW, (float) MPU6050.KalmanAngleX * 100,
//			(float) MPU6050.KalmanAngleY * 100, 0);
	//	print("\r\nKalmanAngleX:%.2f\r\nKalmanAngleY:%.2f\r\n", MPU6050.KalmanAngleX, MPU6050.KalmanAngleY);

	//同一使用LCD输出相关信息
	ShowString();

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
