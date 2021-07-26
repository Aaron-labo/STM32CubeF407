/*
 * usart_dma.c
 *
 *  Created on: 2021年7月19日
 *      Author: Francis
 */
#include "main.h"
#include "usart.h"

// 声明外部变量
extern uint8_t receive_buff[32];
extern uint16_t coordinate_XY[32][2];
extern uint8_t i;

uint16_t asc2int(uint8_t huns, uint8_t tens, uint8_t ones) {
	uint16_t number = (huns - 48) * 100 + (tens - 48) * 10 + (ones - 48);
	return number;
}

/* USER CODE BEGIN 1 */
void USAR_UART_IDLECallback(UART_HandleTypeDef *huart) {
	//数据传输的格式为abcd(x轴,y轴)ef   [abcd即0x61、0x62、0x63、0x64为字头，x轴和y轴信息本别占用三个字节，ef即0x65、0x66为字尾]
	uint8_t start = 0, end = 0;
	uint8_t isStart = 0;
	// 停止本次DMA传输
	HAL_UART_DMAStop(&huart1);



	// 计算接收到的数据长度
	uint8_t data_length = BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);

	for (uint8_t j = 0; j < 32; j++) {
		if (isStart == 0 && receive_buff[j] == 0x61) {
			if (receive_buff[j] == 0x61 && receive_buff[j + 1] == 0x62
					&& receive_buff[j + 2] == 0x63
					&& receive_buff[j + 3] == 0x64) {
				j += 4;
				start = j;
				isStart = 1;
			}
		}
		if (isStart == 1 && receive_buff[j] == 0x65) {
			if (receive_buff[j] == 0x65 && receive_buff[j + 1] == 0x66) {
				end = j - 1;
				isStart = 2;
			}
		}
	}
	if (isStart == 2) {
		for (uint8_t j = start; j <= end; j++) {
			if (j == end) {
				printf("%x\r\n", receive_buff[j]);
			} else {
				printf("%x ", receive_buff[j]);
			}
		}

		i++;
		if (i >= 31) {
			i = 0;
		}
		coordinate_XY[i][0] = asc2int(receive_buff[start],
				receive_buff[start + 1], receive_buff[start + 2]);
		coordinate_XY[i][1] = asc2int(receive_buff[end - 2],
				receive_buff[end - 1], receive_buff[end]);

//		printf("%d %d\r\n", coordinate_XY[i][0], coordinate_XY[i][1]);
	}

// 清零接收缓冲区
	memset(receive_buff, 0, data_length);
	data_length = 0;

// 重启开始DMA传输 每次255字节数据
	HAL_UART_Receive_DMA(&huart1, (uint8_t*) receive_buff, 32);
}

void USER_UART_IRQHandler(UART_HandleTypeDef *huart) {	// 判断是否是串口1
//	printf("\r\n进入中断函数.....\r\n");
	if (USART1 == huart->Instance) {	// 判断是否是空闲中断
		if (RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE)) {// 清除空闲中断标志（否则会一直不断进入中断）
			__HAL_UART_CLEAR_IDLEFLAG(&huart1);
//			printf("\r\nUART1 Idle IQR Detected\r\n");
			// 调用中断处理函数
			USAR_UART_IDLECallback(huart);
		}
	}
}

