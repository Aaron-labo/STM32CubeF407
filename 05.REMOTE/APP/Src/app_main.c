/*
 * app_main.c
 *
 *  Created on: Jul 19, 2021
 *      Author: Francis
 */



#include "app_main.h"
#include "usart.h"
#include "remote.h"
#include "tim.h"

void app_main_init()
{
	  HAL_TIM_Base_Start_IT(&htim1);     //定时器更新时、产生中断
	  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);    //启动输入捕获中断
}

void app_main()
{
	Remote_Scan();
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
