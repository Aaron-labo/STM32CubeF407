#ifndef __REMOTE_H
#define __REMOTE_H
#include "main.h"

#define RDATA   HAL_GPIO_ReadPin(IRMP_GPIO_Port, IRMP_Pin)//红外数据输入脚

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0

extern uint8_t RmtCnt;	        //按键按下的次数

void Remote_Init(void);     //红外传感器接收头引脚初始化
uint8_t Remote_Scan(void);
#endif
