/*
 * hc_sr04.h
 *
 *  Created on: May 24, 2021
 *      Author: Francis
 */

#ifndef INC_HC_SR04_H_
#define INC_HC_SR04_H_

#include "main.h"
#include "tim.h"

typedef struct hc_sr04_device_st {
    GPIO_TypeDef      *trig_port;
    uint16_t          trig_pin;
    GPIO_TypeDef      *echo_port;
    uint16_t          echo_pin;
    TIM_HandleTypeDef *tim;         //us级硬件定时器

    double            distance;     //测算距离
} hc_sr04_device_t;

void HC_SR04_Init(hc_sr04_device_t *hc_sr04_device);
int HC_SR04_Measure(hc_sr04_device_t *hc_sr04_device);

#endif /* INC_HC_SR04_H_ */
