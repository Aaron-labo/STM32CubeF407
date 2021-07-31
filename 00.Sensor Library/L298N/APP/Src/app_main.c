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

#include "remote.h"

//修改PWM波的占空比
uint16_t pwmVal[4] = {0};
uint8_t key[2];
uint8_t pwmNum;
uint8_t isSet = 0;;

void app_main_init() {
	HAL_TIM_Base_Start_IT(&htim3); // 开启计时器
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); //开启通道1的PWM输出
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); //开启通道2的PWM输出
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3); //开启通道3的PWM输出
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4); //开启通道4的PWM输出

	HAL_TIM_Base_Start_IT(&htim1);     //定时器更新时、产生中断
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);    //启动输入捕获中断
}

void app_main() {
	if (isSet == 0) {
		while((key[0] = Remote_Scan()) == NOPRES);
		switch (key[0]) {
		case ONE:
			printf("模式一\r\n");
			pwmVal[0] = 500;
			pwmVal[1] = 0;
			pwmNum = 0;
			break;
		case TWO:
			printf("模式二\r\n");
			pwmVal[0] = 0;
			pwmVal[1] = 500;
			pwmNum = 1;
			break;
		case THREE:
			printf("模式三\r\n");
			pwmVal[2] = 500;
			pwmVal[3] = 0;
			pwmNum = 2;
			break;
		case FOUR:
			printf("模式四\r\n");
			pwmVal[2] = 0;
			pwmVal[3] = 500;
			pwmNum = 3;
			break;
		}
		isSet = 1;
	}

	if(isSet == 1)
	{
		while((key[1] = Remote_Scan()) == NOPRES);
		switch (key[1]) {
			case UP:
				pwmVal[pwmNum] += 10;
				printf("PWM增加:%d\r\n", pwmVal[pwmNum]);
				break;
			case DOWN:
				pwmVal[pwmNum] -= 10;
				printf("PWM减小:%d\r\n", pwmVal[pwmNum]);
				break;
			case CETER:
				printf("复位\r\n");
				isSet = 0;
				break;
		}
	}

	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, pwmVal[0]);    //修改通道1的占空比
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, pwmVal[1]);    //修改通带2的占空比
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, pwmVal[2]);    //修改通道1的占空比
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, pwmVal[3]);    //修改通带2的占空比

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

