#ifndef _SKYBOARD_MPU6000_H_
#define _SKYBOARD_MPU6000_H_
#include "stm32f4xx.h"
#include "IMU.h"

void MPU6000_Init(void);
uint8_t MPU6000_Check(void);
#endif

