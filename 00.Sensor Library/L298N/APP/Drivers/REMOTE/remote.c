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
	uint8_t key = 0;
	if(recFlag)
	{
		BEEP_On();
		recFlag = 0;    //防止if语句重复成立
		if(IRCodes[2])
		{
			key = IRCodes[2];
		}else{
			key = NOPRES;
		}
		HAL_Delay(100);
		BEEP_Off();
    }else{
    	key = NOPRES;
    }

	return key;
}
