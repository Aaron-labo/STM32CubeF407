/*
 * app_main.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Francis
 */

#include "app_main.h"

#include "main.h"
#include "tim.h"
#include "gpio.h"

#include "led.h"

uint32_t capture_Buf[2] = {0};  //用于存放时间
uint8_t capture_Cnt = 0;        //标志位
uint32_t high_time = 0;         //用于存放高电平时间

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2){
		switch (capture_Cnt) {
			case 1:
				capture_Cnt++;
				//上升沿捕获并记录下当前计数值
				capture_Buf[0] = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
				//设置为下降沿捕获
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_ICPOLARITY_FALLING);
				break;
			case 2:
				//下降沿捕获并记录当前计数值
				capture_Buf[1] = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
				//停止输入捕获中断
				HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_1);
				capture_Cnt++;
				break;
		}
	}
}

void app_main_init() {

}

void app_main() {
	switch (capture_Cnt) {
		case 0:
			capture_Cnt++;
			//设定为上升沿捕获
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			//开启输入捕获中断
			HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
			break;
		case 3:
			//计算时间差，并打印出来
			high_time = capture_Buf[1] - capture_Buf[0];
			printf("%ld\r\n", high_time);
			capture_Cnt = 0;
			HAL_Delay(1000);
			break;
	}
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

