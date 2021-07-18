/**
 ******************************************************************************
 * @file    usart.c
 * @brief   This file provides code for the configuration
 *          of the USART instances.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
// 声明外部变量
extern uint8_t receive_buff[32];
extern uint8_t coordinate_XY[32][2];
extern uint8_t i;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

/* USART1 init function */

void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);  // 使能串口空闲中断
	HAL_UART_Receive_DMA(&huart1, (uint8_t*) receive_buff, 8); //设置DMA传输，将串口1的数据搬运到recvive_buff中，每次255个字节
	/* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (uartHandle->Instance == USART1) {
		/* USER CODE BEGIN USART1_MspInit 0 */

		/* USER CODE END USART1_MspInit 0 */
		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART1 GPIO Configuration
		 PA9     ------> USART1_TX
		 PA10     ------> USART1_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART1 DMA Init */
		/* USART1_RX Init */
		hdma_usart1_rx.Instance = DMA2_Stream2;
		hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
		hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
		hdma_usart1_rx.Init.Priority = DMA_PRIORITY_HIGH;
		hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK) {
			Error_Handler();
		}

		__HAL_LINKDMA(uartHandle, hdmarx, hdma_usart1_rx);

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspInit 1 */

		/* USER CODE END USART1_MspInit 1 */
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle) {

	if (uartHandle->Instance == USART1) {
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
		 PA9     ------> USART1_TX
		 PA10     ------> USART1_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

		/* USART1 DMA DeInit */
		HAL_DMA_DeInit(uartHandle->hdmarx);

		/* USART1 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
void USAR_UART_IDLECallback(UART_HandleTypeDef *huart) {
	// 停止本次DMA传输
	HAL_UART_DMAStop(&huart1);

	// 计算接收到的数据长度
	uint8_t data_length = BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);

	// 测试函数：将接收到的数据打印出去
	printf("Receive Data(length = %d): \r\n", data_length);
	printf("receive_buff[0] = %x\r\n", receive_buff[0]);
	printf("receive_buff[1] = %x\r\n", receive_buff[1]);
	printf("receive_buff[2] = %x\r\n", receive_buff[2]);
	printf("receive_buff[3] = %x\r\n", receive_buff[3]);

	coordinate_XY[i][0] = receive_buff[0] + (receive_buff[1] << 8);
	coordinate_XY[i][1] = receive_buff[2] + (receive_buff[3] << 8);
	i++;
	if (i >= 31) {
		i = 0;
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
			printf("UART1 Idle IQR Detected\r\n");
			// 调用中断处理函数
			USAR_UART_IDLECallback(huart);
		}
	}
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
