//#pragma once

#include "stm32f4xx_hal.h"
#include "vl53l0x_platform.h"
#define IR_ERROR_NONE      0           //код отсутствия ошибки
#define IR_OUT_OF_RANGE     8190        //расстояние, которое соответствует отсуствию препятствия


uint16_t    IR_GetRange(uint8_t N);                     //расстояние в миллиметрах
uint8_t     IR_Init(I2C_HandleTypeDef* i2c_handle);     //инициализация
uint8_t     IR_Process(void);                           //конечный автомат опроса датчиков

VL53L0X_Error initSensor(VL53L0X_Dev_t *device);
