/*
 * myusart.h
 *
 *  Created on: Apr 5, 2021
 *      Author: Francis
 */

#ifndef INC_MYUSART_H_
#define INC_MYUSART_H_

#include "app_main.h"
#include <stdio.h>
#include <memory.h>

/************************************头文件定义****************************************************/

 #define RXBUFFERSIZE   1                        //接收缓存大小
 extern uint8_t aRxBuffer[RXBUFFERSIZE];         //USART接收Buffer

 typedef void(*cb_DataParse)(uint8_t dat);
 void usart_register_data_callback(uint8_t usart_id, cb_DataParse callback);           // 注册数据解析回调函数
 void MyCallBack(uint8_t date);

 // 注意，以下几个定义不应当在usart.c文件中，作为协议部分，
 // 该函数应当置于独立的协议处理文件中，并暴露访问接口
 // 此处将该函数暴露出来，为的是测试函数里可以统一注册该处理函数
 void ATEK_frmCheck(uint8_t dat);                // 正点原子解析函数，
 #define USART_REC_LEN           200             //定义最大接收字节数
 extern uint8_t  USART_RX_BUF[USART_REC_LEN];    //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
 extern uint16_t USART_RX_STA;                   //接收状态标记

 /**************************************************************************************************/


 #ifdef DEBUG
//#define print(format, ...) printf( format "\r\n",##__VA_ARGS__)
#define print(format, ...) printf("[%04d: %s ][ %10s ]:" format "\r\n",__LINE__,__FILE__,__func__, ##__VA_ARGS__)
#define debug(format, ...) printf("[%04d: %s ][ %10s ]:" format "\r\n",__LINE__,__FILE__,__func__, ##__VA_ARGS__)
#else
//#define print(format, ...)
#define print(format, ...) printf( format "\r\n",##__VA_ARGS__)
#define debug(format, ...)
#endif

#endif /* INC_MYUSART_H_ */
