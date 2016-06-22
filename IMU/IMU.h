#ifndef _SKYBOARD_IMU_H_
#define _SKYBOARD_IMU_H_
#include "coocox.h"
#include "stm32f4xx.h"
#include "mpu6000.h"
#include "spi2.h"

#define IMU_SPI_INIT	SPI2_Init
#define IMU_SPI_RW		SPI2_RW

#define MPU_CE_RCC	RCC_AHB1Periph_GPIOE
#define MPU_CE_PORT GPIOE
#define MPU_CE_PIN	GPIO_Pin_3
#define MPU_CE_H()		GPIO_SetBits(MPU_CE_PORT, MPU_CE_PIN)
#define MPU_CE_L()		GPIO_ResetBits(MPU_CE_PORT, MPU_CE_PIN)

#define HMC_CE_RCC	RCC_AHB1Periph_GPIOD
#define HMC_CE_PORT GPIOD
#define HMC_CE_PIN	GPIO_Pin_10
#define HMC_CE_H()		GPIO_SetBits(MPU_CE_PORT, MPU_CE_PIN)
#define HMC_CE_L()		GPIO_ResetBits(MPU_CE_PORT, MPU_CE_PIN)

#define MS5611_CE_RCC	RCC_AHB1Periph_GPIOE
#define MS5611_CE_PORT GPIOE
#define MS5611_CE_PIN	GPIO_Pin_7
#define MS5611_CE_H()		GPIO_SetBits(MPU_CE_PORT, MPU_CE_PIN)
#define MS5611_CE_L()		GPIO_ResetBits(MPU_CE_PORT, MPU_CE_PIN)

extern void IMU_Init(void);
#endif

