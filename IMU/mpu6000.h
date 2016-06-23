#ifndef _SKYBOARD_MPU6000_H_
#define _SKYBOARD_MPU6000_H_
#include "stm32f4xx.h"
#include "IMU.h"
typedef struct
{
	uint8_t buffer[14];//直接从寄存器里面读出来的值
	
}MPU6000_Struct;
extern MPU6000_Struct MPU6000;
uint8_t MPU6000_Check(void);
uint8_t MPU6000_Init(void);
void MPU_Read_ACC_and_GYRO(void);
#endif

