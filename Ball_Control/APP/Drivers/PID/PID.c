#include "PID.h"
#include "app_main.h"

/*
 * 使用串级PID算法，外环PID为位置环，其输出为速度期望；内环PID为速度环，其输出为角度期望，直接控制舵机角度
 */

//坐标PID初始化
void PID_Init(PID *pid) {
	pid->SetPosi = 0;
	pid->ActualPosi = 0;
	pid->errorPosi[0] = 0;
	pid->errorPosi[1] = 0;
	pid->errorSpeed[0] = 0;
	pid->errorSpeed[1] = 0;
	pid->errorSpeed[2] = 0;
	pid->Speed = 0;
	pid->angle = 95;
	pid->integral = 0;
	pid->a = 0.08;

	pid->PKp = 1;
	pid->PKi = 0;
	pid->PKd = 0;
	pid->SKp = 0.001;
	pid->SKi = 2.8e-06;
	pid->SKd = 0.05;
}

//坐标PID调节函数(X轴)
uint16_t PID_Calc(PID *pid, uint16_t Posi, float Speed) {
//	float max_angle, min_angle;
//	if(Speed <= 10 && Speed >= -10){
//		max_angle = ANGLE_MAX1;
//		min_angle = ANGLE_MIN1;
//	}else if(Speed <= 20 && Speed >= -20){
//		max_angle = ANGLE_MAX2;
//		min_angle = ANGLE_MIN2;
//	}else if(Speed <= 30 && Speed >= -30){
//		max_angle = ANGLE_MAX3;
//		min_angle = ANGLE_MIN3;
//	}else{
//		max_angle = ANGLE_MAX4;
//		min_angle = ANGLE_MIN4;
//	}

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

	float error = (pid->errorSpeed[0] - pid->errorSpeed[1])*pid->a + (pid->errorSpeed[1] - pid->errorSpeed[2])*(1-pid->a);

	//增量式PID核心算法
	pid->angle = pid->SKp * pid->errorPosi[0] + pid->SKi * pid->integral + pid->SKd * error;

	if(pid->angle >= 30){
		pid->angle = 30;
	}else if(pid->angle <= -30){
		pid->angle = -30;
	}

	float angle = 95 + pid->angle;

	return angle;

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
