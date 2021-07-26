#include "PID.h"
#include "app_main.h"

/*
 * 使用串级PID算法，外环PID为位置环，其输出为速度期望；内环PID为速度环，其输出为角度期望，直接控制舵机角度
 */

//坐标PID初始化
void PID_Init(PID *pid) {
	printf("PID Init begin\r\n");
	pid->SetPosi = 40;
	pid->ActualPosi = 0;
	pid->errorPosi[0] = 0;
	pid->errorPosi[1] = 0;
	pid->errorSpeed[0] = 0;
	pid->errorSpeed[1] = 0;
	pid->errorSpeed[2] = 0;
	pid->Speed = 0;
	pid->angle = 90;
	pid->integral = 0;

	pid->PKp = 0.5;
	pid->PKi = 0;
	pid->PKd = 0;
	pid->SKp = 35;
	pid->SKi = 0;
	pid->SKd = 0;
}

//坐标PID调节函数(X轴)
uint16_t PID_Calc(PID *pid, uint16_t Posi, float Speed) {
	/******************************外环位置式PID(位置环)d************************************/

	pid->ActualPosi = Posi;
	pid->errorPosi[0] = pid->SetPosi - pid->ActualPosi;

	/* 设定闭环死区 */
	if ((pid->errorPosi[0] >= -LOC_DEAD_ZONE)
			&& (pid->errorPosi[0] <= LOC_DEAD_ZONE)) {
		pid->errorPosi[0] = 0;
		pid->integral = 0;
		pid->errorPosi[1] = 0;
	}

	if (pid->errorPosi[0] >= LOCAL_MAX) {
		pid->errorPosi[0] = LOCAL_MAX;
	} else if (pid->errorPosi[0] <= -LOCAL_MAX) {
		pid->errorPosi[0] = -LOCAL_MAX;
	}

	//积分分离，即当差值太大时，不叠加积分
	if (pid->errorPosi[0] <= 200) {
		pid->integral += pid->errorPosi[0];
	}

	//位置式PID算法核心函数
	pid->Speed = pid->PKp * pid->errorPosi[0] + pid->PKi * pid->integral
			+ pid->PKd * (pid->errorPosi[0] - pid->errorPosi[1]);
//	printf("比例%hu\r\n积分%hu\r\n微分%hu\r\n输出为%hu\r\n", (unsigned short int)pid->err, (unsigned short int)pid->integral,
//			(unsigned short int)(pid->err - pid->err_last), (unsigned short int)pid->ActualPosi);
	pid->errorPosi[1] = pid->errorPosi[0];

	/*********************************************************************************/

	/******************************内环增量式PID(速度环)d************************************/

	pid->errorSpeed[0] = pid->Speed - Speed;
	//增量式PID核心算法
	pid->angle += pid->SKp * (pid->errorSpeed[0] - pid->errorSpeed[1])
			+ pid->SKi * pid->errorSpeed[0]
			+ pid->SKd
					* (pid->errorSpeed[0] - 2 * pid->errorSpeed[1]
							+ pid->errorSpeed[2]);

	if (pid->angle >= ANGLE_MAX) {
		pid->angle = ANGLE_MAX;
	} else if (pid->angle <= ANGLE_MIN) {
		pid->angle = ANGLE_MIN;
	}

	return pid->angle;

	/****************************************************************************************/
}

//改变设定值
void ChaSetPosi(PID *pid, uint16_t setPosi) {
	pid->SetPosi = setPosi;
}

void PID_Reset(PID *pid) {
	pid->integral = 0;
	pid->Speed = 0;
	pid->angle = 90;
	pid->errorPosi[0] = 0;
	pid->errorPosi[1] = 0;
	pid->errorSpeed[0] = 0;
	pid->errorSpeed[1] = 0;
	pid->errorSpeed[2] = 0;
}
