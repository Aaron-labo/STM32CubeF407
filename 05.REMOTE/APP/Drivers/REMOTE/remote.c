/*
 * remote.c
 *
 *  Created on: Jul 19, 2021
 *      Author: 李健
 */
#include "app_main.h"
#include "remote.h"
#include "usart.h"
#include "beep.h"

uint32_t upCount = 0;   //向上计数
uint16_t valueUp = 0;   //高电平计数
uint16_t valueDown = 0;   //低电平计数
uint8_t isUpCompare = 1;      //是否为上升沿捕获标记
uint16_t width;           //脉宽
uint16_t buffer[128] = {0};    //接收缓冲区
uint16_t bufferId = 0;        //接收缓冲区数组下标
uint8_t recFlag = 0;    //接收完成标志位
char IRCodes[4] = {0};


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	upCount++;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(isUpCompare)   //如果是上升沿捕获
	{
		valueUp = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		isUpCompare = 0;
		__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);   //设置为下降沿捕获
		upCount = 0;
	}
	else
	{
		valueDown = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		isUpCompare = 1;
		__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);   //设置为上升沿捕获
		width = valueDown + upCount*65536 - valueUp;
		if(width > 4400 && width < 4600)    //判断同步码
		{
			bufferId = 0;
			buffer[bufferId++] = width;
		}
		else if(bufferId > 0)
		{
			buffer[bufferId++] = width;
			if(bufferId > 32)   //所有码一共32位已经全部收到
			{
				recFlag = 1;
				bufferId = 0;
			}

		}
	}
	for(int i=0;i<4;i++)
		{
			IRCodes[i] = 0;
		}

		for(int i =0;i < 32; i++)
		{
			if(buffer[i+1]<1000)
			{
				IRCodes[i/8] = IRCodes[i/8]<<1;
			}
			else
			{
				IRCodes[i/8] = IRCodes[i/8]<<1;
				IRCodes[i/8] |= 0x01;
			}
		}
}

uint8_t Remote_Scan(void)
{
	if(recFlag)
	{
		BEEP_On();
		recFlag = 0;    //防止if语句重复成立
//		for(int i =0;i<4 ;i++)
//		{
//			printf("%d  ",IRCodes[i]);
//		}
//			printf("\r\n");

		switch (IRCodes[2]) {
			case ONE:
				printf("1\r\n");
				break;
			case TWO:
				printf("2\r\n");
				break;
			case THREE:
				printf("3\r\n");
				break;
			case FOUR:
				printf("4\r\n");
				break;
			case FIVE:
				printf("5\r\n");
				break;
			case SIX:
				printf("6\r\n");
				break;
			case SEVEN:
				printf("7\r\n");
				break;
			case EIGHT:
				printf("8\r\n");
				break;
			case NINE:
				printf("9\r\n");
				break;
			case ZERO:
				printf("0\r\n");
				break;
			case STAR:
				printf("*\r\n");
				break;
			case WELL:
				printf("#\r\n");
				break;
			case UP:
				printf("UP\r\n");
				break;
			case DOWN:
				printf("DOWN\r\n");
				break;
			case RIGHT:
				printf("RIGHT\r\n");
				break;
			case LEFT:
				printf("LEFT\r\n");
				break;
			case CETER:
				printf("CETER\r\n");
				break;
		}
		HAL_Delay(100);
    }
	BEEP_Off();
	return IRCodes[2];
}

