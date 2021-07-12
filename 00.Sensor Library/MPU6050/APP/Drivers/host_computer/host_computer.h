/*
 * host_computer.h
 *
 *  Created on: 2021年6月15日
 *      Author: Francis
 */

#ifndef INC_HOST_COMPUTER_H_
#define INC_HOST_COMPUTER_H_

void usart1_send_char(uint8_t c);
void usart1_niming_report(uint8_t fun,uint8_t*data,uint8_t len);
void mpu6050_send_data(int16_t aacx,int16_t aacy,int16_t aacz,int16_t gyrox,int16_t gyroy,int16_t gyroz);
void usart1_report_imu(int16_t aacx,int16_t aacy,int16_t aacz,int16_t gyrox,int16_t gyroy,int16_t gyroz,int16_t roll,int16_t pitch,int16_t yaw);

#endif /* INC_HOST_COMPUTER_H_ */
