#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "main.h"

#define LOCAL_MAX 45
#define LOC_DEAD_ZONE 4.5 //死区范围
#define ANGLE_MAX1 100
#define ANGLE_MIN1 80
#define ANGLE_MAX2 110
#define ANGLE_MIN2 70
#define ANGLE_MAX3 120
#define ANGLE_MIN3 60
#define ANGLE_MAX4 130
#define ANGLE_MIN4 50
#define DANGLE_MAX 0.7

typedef struct {
	uint16_t SetPosi;  //定义设定值
	uint16_t ActualPosi;  //定义实际值
	int16_t errorPosi[2]; //用于存放位置误差
	int16_t errorSpeed[3]; //用于存放速度误差
	float PKp, PKi, PKd;  //定义位置比例、积分、微分系数
	float SKp, SKi, SKd;  //定义速度比例、积分、微分系数
	float Speed;  //定义速度期望
	float angle;  //定义舵机角度期望
	float PosiIntegral;  //定义位置积分值
	float SpeedIntergral;
} PID;

void PID_Init(PID* pid);
uint16_t PID_Calc(PID *pid, uint16_t Posi, float Speed);
void ChaSetPosi(PID *pid, uint16_t setPosi);
void PID_Reset(PID* pid);

#endif
