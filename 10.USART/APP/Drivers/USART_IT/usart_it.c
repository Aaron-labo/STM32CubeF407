/*
 * myusart.h
 *
 *  Created on: Apr 5, 2021
 *      Author: Francis
 */

#include "usart_it.h"

/************************************初始化之后使用前定义****************************************************
 // 初始化完成之后，如果希望能够以中断方式接收，必须首先开中断
 //该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
 HAL_UART_Receive_IT(&huart1, (uint8_t*) aRxBuffer, RXBUFFERSIZE);
 usart_register_data_callback(1, ATEK_frmCheck);
 **************************************************************************************************/

/************************************源文件前置定义****************************************************/
//串口中断服务程序
uint8_t aRxBuffer[RXBUFFERSIZE];       //HAL库使用的串口接收缓冲
cb_DataParse data_parse_callback;      // 数据帧处理回调函数指针

/// 注意，以下几个定义不应当在usart.c文件中，作为协议部分，
/// 该函数应当置于独立的协议处理文件中，并暴露访问接口

//注意,读取USARTx->SR能避免莫名其妙的错误
uint8_t USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，    接收完成标志
//bit14，    接收到0x0d
//bit13~0，  接收到的有效字节数目
uint16_t USART_RX_STA = 0;       //接收状态标记

/**************************************************************************************************/

// 接收中断服务函数
/**
 * @brief 每次接收完成之后，需要重新开中断
 * @param huart : 串口句柄
 * @param buf   : 串口接收缓冲区地址
 * @param bufSize:  串口接收缓冲区大小
 * @retval None
 */
void enable_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *buf,
		uint16_t bufSize) {
	uint32_t timeout = 0;

	while (HAL_UART_GetState(huart) != HAL_UART_STATE_READY) {    //等待就绪
		timeout++;                                                  //超时处理
		if (timeout > HAL_MAX_DELAY)
			break;
	}
	timeout = 0;

	while (HAL_UART_Receive_IT(huart, buf, bufSize) != HAL_OK) { //一次处理完成之后，重新开启中断并设置RxXferCount为1
		timeout++; //超时处理
		if (timeout > HAL_MAX_DELAY)
			break;
	}
}

/**********************************************************************
 * @brief 正点原子例程中的帧检测函数
 * @param dat: 串口终端中接收到的数据
 * @retval None
 * @desc: 正点原子的串口接收例程里，需要检测'\r\n'来判断是否接收完成，
 *                   如果直接使用HAL_UART_Transmit进行发送，必须在发送完成后
 *                  再发送一个'\r\n'，否则会出现没有接收完成的问题。
 **********************************************************************/
void ATEK_frmCheck(uint8_t dat) {
	UNUSED(dat);

	if ((USART_RX_STA & 0x8000) == 0) {     //接收未完成
		if (USART_RX_STA & 0x4000) {          //接收到了0x0d
			if (aRxBuffer[0] != 0x0a) {         //接收错误,重新开始
				USART_RX_BUF[USART_RX_STA & 0X3FFF] = 0x0d;
				USART_RX_STA &= 0x3FFF;
				USART_RX_STA += 2;
				USART_RX_BUF[USART_RX_STA & 0X3FFF] = aRxBuffer[0];
			} else {                            //接收完成了
				USART_RX_STA |= 0x8000;
			}
		} else {                              //还没收到0X0D
			if (aRxBuffer[0] == 0x0d)
				USART_RX_STA |= 0x4000;
			else {
				USART_RX_BUF[USART_RX_STA & 0X3FFF] = aRxBuffer[0];
				USART_RX_STA++;
				if (USART_RX_STA > (USART_REC_LEN - 1))
					USART_RX_STA = 0; //接收数据错误,重新开始接收
			}
		}
	}
}
/**********************************************************************
 * @brief 注册数据处理回调函数
 * @param usart_id: 串口号, 1: USART1, 2: USART2 ...
 * @param callback: 需要注册的回调函数
 * @desc: cb_DataParse 为回调函数指针类型，定义为 void callback(uint8_t d)
 **********************************************************************/
void usart_register_data_callback(uint8_t usart_id, cb_DataParse callback) {
	switch (usart_id) {
	case 1:                               // usart1
		data_parse_callback = callback;
		break;
	default:
		data_parse_callback = NULL;
		break;
	}

}

/**
 * @brief Rx Transfer completed callbacks
 * @param huart: uart handle
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART1) {          //串口1

		// data_parse_callback是数据处理函数指针
		if (data_parse_callback != NULL) {
			ATEK_frmCheck(aRxBuffer[0]);
			data_parse_callback(aRxBuffer[0]);
		} else {
			print("未注册数据处理回调函数");
		}
		// 开启接收中断
		enable_UART_Receive_IT(huart, (uint8_t*) aRxBuffer, RXBUFFERSIZE);
	}
}

void MyCallBack(uint8_t date)
{
	UNUSED(date);
	if(USART_RX_STA & 0x8000){
		for(uint8_t i = 0; i < (USART_RX_STA & 0X3FFF); i++){
			printf("%x\r\n", USART_RX_BUF[i]);
		}
		memset(USART_RX_BUF, 0, (USART_RX_STA & 0X3FFF));
		USART_RX_STA = 0;
	}
}
