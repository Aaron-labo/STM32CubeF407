/*
 * app_main.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Francis
 */

#include "app_main.h"
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

uint16_t adc_buffer[10] = { 0 }; //ADC采集数据缓冲区

//每当数据缓冲区被填满，即采集20个数据后，自动调用一次该回调函数
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
	uint32_t sumVoltage = 0;
	float voltage = 0;
	if(hadc->Instance == ADC1){
		for(uint8_t i = 0; i < 10; i++)
		{
			sumVoltage += adc_buffer[i];
		}
		voltage = (sumVoltage * 1.0 / 10) * 3.3 / 4096;
		printf("%.2f\r\n", voltage);
	}
}

void app_main_init() {
	HAL_TIM_Base_Start_IT(&htim3); // 开启计时器
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) &adc_buffer, 10); //DMA方式开启ADC
}

void app_main() {

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

