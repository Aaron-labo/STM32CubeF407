/*
 * app_main.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Francis
 */

#include "app_main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "lcd.h"
#include "beep.h"
#include "irmp.h"

uint8_t key;
char *str = 0;

void app_main_init() {
	TFTLCD_Init();
	POINT_COLOR = BLUE;
	LCD_ShowString(30, 50, 200, 16, 16, (uint8_t*)"Explorer STM32F4");
	LCD_ShowString(30, 70, 200, 16, 16, (uint8_t*)"REMOTE TEST");
	LCD_ShowString(30, 90, 200, 16, 16, (uint8_t*)"ATOM@ALIENTEK");
	LCD_ShowString(30, 110, 200, 16, 16, (uint8_t*)"2017/4/15");
	LCD_ShowString(30, 130, 200, 16, 16, (uint8_t*)"KEYVAL:");
	LCD_ShowString(30, 150, 200, 16, 16, (uint8_t*)"KEYCNT:");
	LCD_ShowString(30, 170, 200, 16, 16, (uint8_t*)"SYMBOL:");
	printf("starting......");
}

void app_main() {
	key = Remote_Scan();
	if (key) {
		LCD_ShowNum(86, 130, key, 3, 16);		//显示键值
		LCD_ShowNum(86, 150, RmtCnt, 3, 16);	//显示按键次数
		printf("键值：%d", key);
		printf("按键次数：%d", RmtCnt);
		switch (key) {
		case 0:
			str = "ERROR";
			break;
		case 162:
			str = "POWER";
			break;
		case 98:
			str = "UP";
			break;
		case 2:
			str = "PLAY";
			break;
		case 226:
			str = "ALIENTEK";
			break;
		case 194:
			str = "RIGHT";
			break;
		case 34:
			str = "LEFT";
			break;
		case 224:
			str = "VOL-";
			break;
		case 168:
			str = "DOWN";
			break;
		case 144:
			str = "VOL+";
			break;
		case 104:
			str = "1";
			break;
		case 152:
			str = "2";
			break;
		case 176:
			str = "3";
			break;
		case 48:
			str = "4";
			break;
		case 24:
			str = "5";
			break;
		case 122:
			str = "6";
			break;
		case 16:
			str = "7";
			break;
		case 56:
			str = "8";
			break;
		case 90:
			str = "9";
			break;
		case 66:
			str = "0";
			break;
		case 82:
			str = "DELETE";
			break;
		}
		LCD_Fill(86, 170, 116 + 8 * 8, 170 + 16, WHITE);	//清楚之前的显示
		LCD_ShowString(86, 170, 200, 16, 16, (uint8_t*) str);	//显示SYMBOL
		printf("SYMBOL:%s", str);
	} else
		HAL_Delay(10);
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
