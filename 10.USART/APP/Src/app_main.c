/*
 * app_main.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Francis
 */

#include "app_main.h"
#include "main.h"
#include "gpio.h"
#include "usart.h"

#include "usart_it.h"

void app_main_init() {
	/************************************初始化之后使用前定义*******************************************/
	 // 初始化完成之后，如果希望能够以中断方式接收，必须首先开中断
	 //该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
	 HAL_UART_Receive_IT(&huart1, (uint8_t*) aRxBuffer, RXBUFFERSIZE);
	 usart_register_data_callback(1, MyCallBack);
	 /**************************************************************************************************/
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
