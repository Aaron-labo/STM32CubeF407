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

#include "vl53l0x.h"

VL53L0X_Dev_t device;
VL53L0X_DeviceInfo_t device_info;
VL53L0X_RangingMeasurementData_t ranging_data;
vl53l0x_calibration_data_t calibration;
uint16_t distance;
uint16_t Mx_Distance = 200;

//初始化函数
void app_main_init(void) {
	while(vl53l0x_init(&device, device_info, calibration));
	vl53l0x_turn_off(&device);
	vl53l0x_wait_boot(&device);
	VL53L0X_SetDeviceAddress(&device, 0x52);
}

//主程序函数
void app_main(void) {
	vl53l0x_update_range(&device, &ranging_data, &distance, Mx_Distance);
	printf("距离为:%d\r\n", distance);
	HAL_Delay(500);
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
