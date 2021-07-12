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

#include "lcd.h"
#include "fsmc.h"

#include "host_computer.h"
#include "mpu6050.h"

MPU6050_t MPU6050;

void ShowString(){
	uint8_t Buffer[32];
	LCD_ShowString(30, 30, 400, 48, 48, (uint8_t*)"STM32F407");
	print("\r\nKalmanAngleX:%.2f\r\nKalmanAngleY:%.2f\r\n", MPU6050.KalmanAngleX, MPU6050.KalmanAngleY);
	sprintf((char*)Buffer, "KalmanAngleX:%7.2f", MPU6050.KalmanAngleX);
	LCD_ShowString(30, 100, 400, 32, 32, Buffer);
	sprintf((char*)Buffer, "KalmanAngleY:%7.2f", MPU6050.KalmanAngleY);
	LCD_ShowString(30, 150, 400, 32, 32, Buffer);
}

void app_main_init(void) {
	TFTLCD_Init();
	LCD_Clear(WHITE);
	POINT_COLOR = BLACK;

	while (MPU6050_Init(&hi2c1) == 1);
}

void app_main(void) {
	MPU6050_Read_All(&hi2c1, &MPU6050);
//	mpu6050_send_data((float)MPU6050.KalmanAngleX, (float)MPU6050.KalmanAngleY, 0, 0, 0, 0);
	usart1_report_imu(MPU6050.Accel_X_RAW, MPU6050.Accel_Y_RAW, MPU6050.Accel_Z_RAW,
			MPU6050.Gyro_X_RAW, MPU6050.Gyro_Y_RAW, MPU6050.Gyro_Z_RAW,
			(float)MPU6050.KalmanAngleX*100, (float)MPU6050.KalmanAngleY*100, 0);
//	print("\r\nKalmanAngleX:%.2f\r\nKalmanAngleY:%.2f\r\n", MPU6050.KalmanAngleX, MPU6050.KalmanAngleY);
	ShowString();
	HAL_Delay(1000);
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
