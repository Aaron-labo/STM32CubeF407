/*
 * app_main.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Francis
 */

#include "app_main.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "math.h"
#include "tim.h"

#include "pca9685.h"
#include "PID.h"
#include "ssd1306.h"
#include "remote.h"

#define FRAME 10  //设置摄像头帧率为50
#define RESOLUTION 10 //即10个像素点表示1cm
#define LEN 32

//MPU6050_t MPU6050; //MPU6050结构体，用于存放欧拉角的原始值和结果
uint8_t receive_buff[LEN] = { 0 }; //DMA接收缓存区

uint16_t coordinate_XY[LEN][2] = { 0 };  //用于保存当前球坐标
uint16_t SetPosi[2];	//用于保存预设坐标,初始值为原点位置

float speed, speedX, speedY; //用于存放当前速度
float distance; //存放当前位置和目标位置距离差

PID pid_X, pid_Y;  //PID结构体,分别表示X,Y坐标

uint8_t Mode[6] = { 0 }; //模式选择缓存区
uint8_t i = 0; //用于存放模式选择缓存区的向量

float tim;

//计算小球速度
void ballSpeed() {
	float distanceX, distanceY, distanceIns; //用于存放X，Y方向上的间距
	uint8_t j = 0;
	j = (i - 1) ? (i >= 1) : (i - 1 + LEN);  //使用当前帧的坐标和10帧前的坐标计算瞬时速度
	//计算瞬时的X方向、Y方向和总间距
	distanceX = (coordinate_XY[i][0] - coordinate_XY[j][0]) / RESOLUTION;
	distanceY = (coordinate_XY[i][1] - coordinate_XY[j][1]) / RESOLUTION;
	distanceIns = sqrtf(distanceX * distanceX + distanceY * distanceY);

	//顺便计算出当前位置与目标位置的间距
	distance = sqrt(
			(coordinate_XY[i][0] - SetPosi[0])
					* (coordinate_XY[i][0] - SetPosi[0])
					+ (coordinate_XY[i][1] - SetPosi[1])
							* (coordinate_XY[i][1] - SetPosi[1]));

	/*
	 * 计算各方向上的速度
	 * dt = 1 / FRAME * 10 (FRAME为帧率)
	 * speed = distance / dt = distance * FRAME / 10
	 */
	speedX = distanceX / tim;
	speedY = distanceY / tim;
	speed = distanceIns / tim;
	printf("%.2f\r\n", speed);
}

//确定9个位置坐标
//长宽均为400
void GetSetPosi(uint16_t *SetPosi, uint8_t number) {
	switch (number) {
	case ONE:
		SetPosi[0] = 80;
		SetPosi[1] = 80;
		break;
	case TWO:
		SetPosi[0] = 200;
		SetPosi[1] = 80;
		break;
	case THREE:
		SetPosi[0] = 320;
		SetPosi[1] = 80;
		break;
	case FOUR:
		SetPosi[0] = 80;
		SetPosi[1] = 200;
		break;
	case FIVE:
		SetPosi[0] = 200;
		SetPosi[1] = 200;
		break;
	case SIX:
		SetPosi[0] = 320;
		SetPosi[1] = 200;
		break;
	case SEVEN:
		SetPosi[0] = 80;
		SetPosi[1] = 320;
		break;
	case EIGHT:
		SetPosi[0] = 200;
		SetPosi[1] = 320;
		break;
	case NINE:
		SetPosi[0] = 320;
		SetPosi[1] = 320;
		break;
	}
}

//LCD显示函数，isInit=1表示在初始化中调用
void ShowString() {
	char Buffer[32]; //输出文本暂存区

	ssd1306_DrawRectangle(85, 21, 125, 31, White);
	ssd1306_DrawRectangle(85, 32, 125, 52, White);
	//OLED输出设定球坐标(包括位置期望和当前位置)
	sprintf(Buffer, "Set_XY:(%3d,%3d)", SetPosi[0], SetPosi[1]);
	ssd1306_SetCursor(5, 5);
	ssd1306_WriteString(Buffer, Font_6x8, White);
	//OLED输出当前球坐标
	sprintf(Buffer, "Act_XY:(%3d,%3d)", coordinate_XY[i][0],
			coordinate_XY[i][1]);
	ssd1306_SetCursor(5, 13);
	ssd1306_WriteString(Buffer, Font_6x8, White);

	sprintf(Buffer, "Dis:%6.2f", distance);
	ssd1306_SetCursor(5, 21);
	ssd1306_WriteString(Buffer, Font_6x8, White);

	//OLED输出设定球速度(包括速度期望和当前速度)
	sprintf(Buffer, "Exp_Sp:%5.2f",
			sqrtf(pid_X.Speed * pid_X.Speed + pid_Y.Speed * pid_Y.Speed));
	ssd1306_SetCursor(5, 29);
	ssd1306_WriteString(Buffer, Font_6x8, White);
	//OLED输出当前球速度
	sprintf(Buffer, "Act_Sp:%5.2f", speed);
	ssd1306_SetCursor(5, 37);
	ssd1306_WriteString(Buffer, Font_6x8, White);

	printf("Exp_Sp:%5.2f\r\n", sqrtf(pid_X.Speed * pid_X.Speed + pid_Y.Speed * pid_Y.Speed));
	printf("Act_Sp:%5.2f\r\n", speed);

	//OLED输出耗费时间
	sprintf(Buffer, "Tot_Ti:%5.2f",
	__HAL_TIM_GET_COUNTER(&htim5) * 1.0 / 10000);
	ssd1306_SetCursor(5, 45);
	ssd1306_WriteString(Buffer, Font_6x8, White);
	sprintf(Buffer, "Sta_Ti:%5.2f",
	__HAL_TIM_GET_COUNTER(&htim2) * 1.0 / 10000);
	ssd1306_SetCursor(5, 53);
	ssd1306_WriteString(Buffer, Font_6x8, White);

	ssd1306_UpdateScreen();
}

//LCD输出模式选择相关内容
void ShowMode(uint8_t key, uint8_t i) {

	//没按下一个键，在LCD上显示按键信息
	//i == 0xff则表示输出每个按键信息
	if (i == 0xff) {

		ssd1306_SetCursor(88, 23);
		switch (key) {
		case STABLE:
			ssd1306_WriteString("STABLE", Font_6x8, White);
			break;
		case MOVE:
			ssd1306_WriteString("MOVE  ", Font_6x8, White);
			break;
		case ROUND:
			ssd1306_WriteString("ROUND ", Font_6x8, White);
			break;
		case ONE:
			ssd1306_WriteString("ONE   ", Font_6x8, White);
			break;
		case TWO:
			ssd1306_WriteString("TWO   ", Font_6x8, White);
			break;
		case THREE:
			ssd1306_WriteString("THREE ", Font_6x8, White);
			break;
		case FOUR:
			ssd1306_WriteString("FOUR  ", Font_6x8, White);
			break;
		case FIVE:
			ssd1306_WriteString("FIVE  ", Font_6x8, White);
			break;
		case SIX:
			ssd1306_WriteString("SIX   ", Font_6x8, White);
			break;
		case SEVEN:
			ssd1306_WriteString("SEVEN ", Font_6x8, White);
			break;
		case EIGHT:
			ssd1306_WriteString("EIGHT ", Font_6x8, White);
			break;
		case NINE:
			ssd1306_WriteString("NINE  ", Font_6x8, White);
			break;
		case ZERO:
			ssd1306_WriteString("ZERO  ", Font_6x8, White);
			break;
		case DETER:
			ssd1306_WriteString("DETER ", Font_6x8, White);
			break;
		case REPLACE:
			ssd1306_WriteString("REPLACE ", Font_6x8, White);
			break;
		case CANCEL:
			ssd1306_WriteString("CANCEL", Font_6x8, White);
			break;
		case INIT:
			ssd1306_WriteString("INIT  ", Font_6x8, White);
		}
	} else {
		//若i不为0xff则表示显示Mode模式缓存区中的信息
		switch (key) {
		case STABLE:

			ssd1306_SetCursor(88, 35);
			ssd1306_WriteString("STABLE", Font_6x8, White);
			break;
		case MOVE:
			ssd1306_SetCursor(88, 35);
			ssd1306_WriteString("MOVE  ", Font_6x8, White);
			break;
		case ROUND:
			ssd1306_SetCursor(88, 35);
			ssd1306_WriteString("ROUND ", Font_6x8, White);
			break;
		case ONE:
			ssd1306_SetCursor(83 + 8 * i, 44);
			ssd1306_WriteString("1", Font_6x8, White);
			break;
		case TWO:
			ssd1306_SetCursor(83 + 8 * i, 44);
			ssd1306_WriteString("2", Font_6x8, White);
			break;
		case THREE:
			ssd1306_SetCursor(83 + 8 * i, 44);
			ssd1306_WriteString("3", Font_6x8, White);
			break;
		case FOUR:
			ssd1306_SetCursor(83 + 8 * i, 44);
			ssd1306_WriteString("4", Font_6x8, White);
			break;
		case FIVE:
			ssd1306_SetCursor(83 + 8 * i, 44);
			ssd1306_WriteString("5", Font_6x8, White);
			break;
		case SIX:
			ssd1306_SetCursor(83 + 8 * i, 44);
			ssd1306_WriteString("6", Font_6x8, White);
			break;
		case SEVEN:
			ssd1306_SetCursor(83 + 8 * i, 44);
			ssd1306_WriteString("7", Font_6x8, White);
			break;
		case EIGHT:
			ssd1306_SetCursor(83 + 8 * i, 44);
			ssd1306_WriteString("8", Font_6x8, White);
			break;
		case NINE:
			ssd1306_SetCursor(83 + 8 * i, 44);
			ssd1306_WriteString("9", Font_6x8, White);
			break;
		}
	}
	ssd1306_UpdateScreen();
}

//模式1：稳定模式
void ModeStable(void) {
	//确定稳定坐标
	GetSetPosi(SetPosi, Mode[1]);
	//将稳定坐标放入PID结构体中
	ChaSetPosi(&pid_X, SetPosi[0]);
	ChaSetPosi(&pid_Y, SetPosi[1]);

	//计算小球速度,同时查看间距
	ballSpeed();
	//分别使用pid算法调整X,Y的坐标
	//其中0通道控制X轴舵机,1通道控制Y轴舵机
	PID_Calc(&pid_X, coordinate_XY[i][0], speedX);
	PID_Calc(&pid_Y, coordinate_XY[i][1], speedY);
	PCA9685_SetServoAngle(0, pid_X.angle);
	PCA9685_SetServoAngle(1, pid_Y.angle);

	//同一使用LCD输出相关信息
	ShowString();
}

//模式2：移动模式
void ModeMove(void) {
	uint8_t count = 0;
	static uint8_t isTim = 0;  //判断是否稳定，是否开始计时，isTim为1即为开始计时
	while (Mode[count] != 0) {
		count++;
	}

	for (uint8_t i = 1; i < count;) {

		//确定目的坐标
		GetSetPosi(SetPosi, Mode[i]);
		ChaSetPosi(&pid_X, SetPosi[0]);
		ChaSetPosi(&pid_Y, SetPosi[1]);

		//计算小球速度,同时查看间距
		ballSpeed();
		//i==1时，需要在初始位置稳定2s以上
		if (i == 1) {
			if (isTim == 0) { //isTim为1表示未开始计时，需判断是否开始计时
				if (distance <= 30) {  //若间距小于30，则开始计时
					HAL_TIM_Base_Start(&htim2);
					isTim = 1; //isTim置1表示已开始计时
				}
			} else {
				if (distance > 30) {  //若间距大于30，则停止计时
					isTim = 0;
					HAL_TIM_Base_Stop(&htim2);
					__HAL_TIM_SET_COUNTER(&htim2, 0);  //重新将计时器置零，方便下次计时
				} else if (__HAL_TIM_GET_COUNTER(&htim2) >= 30000) { //若间距小于30的情况下持续了3s，则完成稳定任务
					i++;	//i加一，则进入下一环节，即小球移动
					isTim = 0;
					HAL_TIM_Base_Stop(&htim2);
					__HAL_TIM_SET_COUNTER(&htim2, 0);
				}
			}
		} else if (i > 1 || i < count - 1) { //中间路径只需稍微停留即可，这里停留0.5s
			if (isTim == 0) {  //计时步骤同上
				if (distance <= 30) {
					HAL_TIM_Base_Start(&htim2);
					isTim = 1;
				}
			} else {
				if (distance > 30) {
					isTim = 1;
					HAL_TIM_Base_Stop(&htim2);
					__HAL_TIM_SET_COUNTER(&htim2, 0);
				} else if (__HAL_TIM_GET_COUNTER(&htim2) >= 5000) {
					i++;
					isTim = 1;
					HAL_TIM_Base_Stop(&htim2);
					__HAL_TIM_SET_COUNTER(&htim2, 0);
				}
			}
		}

		//分别使用pid算法调整X,Y的坐标
		//其中0通道控制X轴舵机,1通道控制Y轴舵机
		PID_Calc(&pid_X, coordinate_XY[i][0], speedX);
		PID_Calc(&pid_Y, coordinate_XY[i][1], speedY);
		PCA9685_SetServoAngle(0, pid_X.angle);
		PCA9685_SetServoAngle(1, pid_Y.angle);

		ShowString();
	}
}

//模式3：绕圈模式
void ModeRound(void) {
	//绕圈模式使用极坐标转为直角坐标
	uint16_t radius = 100;   //半径设置为100
	uint8_t zita = 0;      //角度初始位为0

	while (1) {
		//确定中心坐标
		GetSetPosi(SetPosi, Mode[1]);
		//根据中心坐标和相对极坐标，确定其直角坐标
		SetPosi[0] += (uint16_t) (radius * cos(zita));
		SetPosi[1] += (uint16_t) (radius * sin(zita));

		//将稳定坐标放入PID结构体中
		ChaSetPosi(&pid_X, SetPosi[0]);
		ChaSetPosi(&pid_Y, SetPosi[1]);

		//计算小球速度,同时查看间距
		ballSpeed();

		//当当前位置与目标位置间距小于20，目标坐标角度增加10度
		if (distance <= 20) {
			zita += 10;
		}

		//分别使用pid算法调整X,Y的坐标
		//其中0通道控制X轴舵机,1通道控制Y轴舵机
		PID_Calc(&pid_X, coordinate_XY[i][0], speedX);
		PID_Calc(&pid_Y, coordinate_XY[i][1], speedY);
		PCA9685_SetServoAngle(0, pid_X.angle);
		PCA9685_SetServoAngle(1, pid_Y.angle);

		//若角度达到了360度，重置为0，起到循环的目的
		if (zita == 360) {
			zita = 0;
		}
		ShowString();
	}
}

void SelfInspection(void) {
	PCA9685_SetServoAngle(0, 90);
	PCA9685_SetServoAngle(1, 90);
	HAL_Delay(1000);

	PCA9685_SetServoAngle(0, 40);
	PCA9685_SetServoAngle(1, 40);
	HAL_Delay(400);

	PCA9685_SetServoAngle(0, 140);
	PCA9685_SetServoAngle(1, 140);
	HAL_Delay(400);

	PCA9685_SetServoAngle(0, 40);
	PCA9685_SetServoAngle(1, 140);
	HAL_Delay(400);

	PCA9685_SetServoAngle(0, 140);
	PCA9685_SetServoAngle(1, 40);
	HAL_Delay(1000);

	PCA9685_SetServoAngle(0, 70);
	PCA9685_SetServoAngle(1, 70);
	HAL_Delay(400);

	PCA9685_SetServoAngle(0, 110);
	PCA9685_SetServoAngle(1, 110);
	HAL_Delay(400);

	PCA9685_SetServoAngle(0, 70);
	PCA9685_SetServoAngle(1, 110);
	HAL_Delay(400);

	PCA9685_SetServoAngle(0, 110);
	PCA9685_SetServoAngle(1, 70);
	HAL_Delay(1000);

	HAL_Delay(1000);
	PCA9685_SetServoAngle(0, 90);
	PCA9685_SetServoAngle(1, 90);
	HAL_Delay(1000);
}

//选择模式,isInit=1表示在初始化中调用
void SelecMode(uint8_t isInit) {
	uint8_t key;
	uint8_t ModeBuffer[6];  //模式缓存区
	for (uint8_t i = 0; i < 6; i++) { //将原本模式缓存区中的信息保存起来
		ModeBuffer[i] = Mode[i];
		Mode[i] = 0;
	}

	HAL_TIM_Base_Start_IT(&htim1);     //定时器更新时、产生中断
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);    //启动输入捕获中断

	printf("请选择模式:(模式+格点)\r\n如：从1经过2，3至6 ---------- 移动+1+2+3+6\r\n");
	for (int i = 0; i < 6; i++) {
		while ((key = Remote_Scan()) == NOPRES)
			//等待按键输入
			;

		if (key == ZERO) {
			SelfInspection();
			i -= 1;
			continue;
		} else if (key == INIT) {
			PCA9685_SetServoAngle(0, 95);
			PCA9685_SetServoAngle(1, 95);
			i -= 1;
			continue;
		}

		/*
		 * 若输入格式不符合要求，则重新输入
		 * 若如何输入，则显示模式缓存区数据
		 * 先输入模式（即稳定、移动和绕圈），后输入数字，最后一位一定为确定键，并开始计时
		 */
		if (i == 5) { //该判断语句的多用是确保最后一定按下确定键
			if (key == DETER) {
				HAL_TIM_Base_Start(&htim5); //按下确定键后开始计时
				PID_Reset(&pid_X); 		   //并重置PID信息
				PID_Reset(&pid_Y);
				return; 		   //跳出函数，开始控制
			} else {
				printf("你输入的格式不符合要求，请按下确定键!\r\n");
				i -= 1; //若输入格式不符合要求则重新输入
				continue;
			}
		} else if (i == 0 && key != STABLE && key != MOVE && key != ROUND) {
			printf("你输入的格式不符合要求，请输入模式!\r\n");
			i = -1; //若输入格式不符合要求则重新输入
			continue;
		} else if (i == 0 && (key == STABLE || key == MOVE || key == ROUND)) {
			Mode[i] = key; //若输入符合要求，则将键值存入模式缓存区中
			printf("%d  %d  %d  %d  %d\r\n", Mode[0], Mode[1], Mode[2], Mode[3],
					Mode[4]);

			//在LCD中显示按键信息
			ShowMode(key, i);

			continue;
		} else if (key == DETER) {
			HAL_TIM_Base_Start(&htim5); //按下确定键后开始计时
			PID_Reset(&pid_X);		   //并重置PID信息
			PID_Reset(&pid_Y);
			break;
		} else if (key == REPLACE) {
			for (i = 0; i <= 4; i++) { //按下复位键后，将模式缓存区中的信息清零
				Mode[i] = 0;
			}
			ssd1306_SetCursor(88, 35);
			ssd1306_WriteString("      ", Font_6x8, White);
			ssd1306_SetCursor(88, 44);
			ssd1306_WriteString("      ", Font_6x8, White);
			ssd1306_UpdateScreen();
			i = -1; //i=-1,进入下一个循环后，会自动加一，即从0重新开始
			printf("复位\r\n");
			continue;
		}

		//判断格式输入是否正确
		if (key == ONE || key == TWO || key == THREE || key == FOUR
				|| key == FIVE || key == SIX || key == SEVEN || key == EIGHT
				|| key == NINE) {
			Mode[i] = key; //若输入符合要求，则将键值存入模式缓存区中
			printf("%d  %d  %d  %d  %d\r\n", Mode[0], Mode[1], Mode[2], Mode[3],
					Mode[4]);

			//在LCD中显示按键信息
			ShowMode(key, i);

			continue;
		} else if (key == DETER) {
			HAL_TIM_Base_Start(&htim5); //按下确定键后开始计时
			PID_Reset(&pid_X);		   //并重置PID信息
			PID_Reset(&pid_Y);
			break;
		} else if (key == REPLACE) {
			for (i = 0; i <= 4; i++) {		   //按下复位键后，将模式缓存区中的信息清零
				Mode[i] = 0;
			}
			ssd1306_SetCursor(88, 35);
			ssd1306_WriteString("      ", Font_6x8, White);
			ssd1306_SetCursor(88, 44);
			ssd1306_WriteString("      ", Font_6x8, White);
			ssd1306_UpdateScreen();
			i = -1;		   //i=-1,进入下一个循环后，会自动加一，即从0重新开始
			printf("复位\r\n");
			continue;
		}

		//若按下CANCEL键，则取消以上输入，并将模式缓存区的数据恢复
		if (key == CANCEL) {
			if (isInit == 0) {
				for (uint8_t i = 0; i < 6; i++) { //恢复模式缓存区原本的信息
					Mode[i] = ModeBuffer[i];
				}
				HAL_TIM_Base_Start(&htim5); //重新开始计时
				return;
			} else {
				printf("你输入的格式不符合要求，初次设置模式，不能使用取消键!\r\n");
				i -= 1; //在初始化选择模式时，不能使用取消键
			}
		} else {
			printf("你输入的格式不符合要求，请输入数字按键!\r\n");
			i -= 1;
		}
	}
	HAL_TIM_Base_Stop_IT(&htim1);     //停止定时器更新时、产生中断
	HAL_TIM_IC_Stop_IT(&htim1, TIM_CHANNEL_1);    //关闭输入捕获中断
}

//初始化函数
void app_main_init(void) {
	//OLED初始化
	ssd1306_Init();
	ssd1306_Fill(Black);

	//PCA9685初始化,将通道一和通道二(本次需要使用这两个通道)的角度初始化
	PCA9685_Init(&hi2c1);

	//显示信息
	ShowString();
	//选择模式
	SelecMode(1);

	//PID初始化, 并设定预设球位置
	PID_Init(&pid_X);
	PID_Init(&pid_Y);

	HAL_Delay(500);   //延时0.5s用于舵机调整角度
}

//主程序函数
void app_main(void) {
	if (Mode[0] == STABLE) {
		ModeStable();
	} else if (Mode[0] == MOVE) {
		ModeMove();
	} else if (Mode[0] == ROUND) {
		ModeRound();
	}
}

// 须在头文件中添加 #include <stdio.h>

//////////////////////////////////////////////////////////////////
// 加入以下代码,支持printf函数,而不需要选择use MicroLIB
// MDK中同样定义了 __GNUC__，使用__ARMCC_VERSION 或  __CC_ARM 区分MDK和STM32CubeIDE
// MDK预定义宏，详见 ：https://www.keil.com/support/man/docs/armcc/armcc_chr1359125007083.htm

#ifdef __CC_ARM // 或 #ifdef __ARMCC_VERSION
	  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#else
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#endif
#if 1

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x) {
	x = x;
}
//重定义fputc函数
PUTCHAR_PROTOTYPE {
	// 具体哪个串口可以更改huart2为其它串口
	// HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1 , 0xffff);
	while ((USART1->SR & 0X40) == 0) {
	}; //循环发送,直到发送完毕
	USART1->DR = (uint8_t) ch;

	//  while ((USART2->SR & 0X40) == 0) {
	//  }; //循环发送,直到发送完毕
	//  USART2->DR = (uint8_t) ch;

	return ch;
}
#endif
