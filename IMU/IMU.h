#ifndef _SKYBOARD_IMU_H_
#define _SKYBOARD_IMU_H_
#include "coocox.h"
#include "stm32f4xx.h"
#include "NVIC&RCC.h"
#include "mpu6000.h"
#include "spi2.h"

#define IMU_SPI_INIT			SPI2_Init
#define IMU_SPI_RW				SPI2_RW
#define IMU_SPI_SETBAUD		SPI2_SetSpeed
#define Delayms						CoTickDelay
//MPU6000
#define MPU_CE_RCC			RCC_AHB1Periph_GPIOE
#define MPU_CE_PORT 		GPIOE
#define MPU_CE_PIN			GPIO_Pin_3
#define MPU_CE_H()			GPIO_SetBits(MPU_CE_PORT, MPU_CE_PIN)
#define MPU_CE_L()			GPIO_ResetBits(MPU_CE_PORT, MPU_CE_PIN)
#define MPU6000_SPI_BAUD SPI_BaudRatePrescaler_4
#define MPU6000_GYO_SCALE				2000
#define MPU6000_ACC_SCALE				16

#define MPU_INT_RCC			RCC_AHB1Periph_GPIOE
#define MPU_INT_PORT		GPIOE
#define MPU_INT_PIN			GPIO_Pin_4
#define MPU_INT_EXTI_Line								EXTI_Line4
#define MPU_INT_EXTI_PortSource			EXTI_PortSourceGPIOE
#define MPU_INT_EXTI_PinSource			EXTI_PinSource4
#define MPU_INTChannel							EXTI4_IRQn

//HMC5983L
#define HMC_CE_RCC			RCC_AHB1Periph_GPIOD
#define HMC_CE_PORT 		GPIOD
#define HMC_CE_PIN			GPIO_Pin_10
#define HMC_CE_H()			GPIO_SetBits(HMC_CE_PORT, HMC_CE_PIN)
#define HMC_CE_L()			GPIO_ResetBits(HMC_CE_PORT, HMC_CE_PIN)
//MS5611
#define MS5611_CE_RCC			RCC_AHB1Periph_GPIOE
#define MS5611_CE_PORT 		GPIOE
#define MS5611_CE_PIN			GPIO_Pin_7
#define MS5611_CE_H()			GPIO_SetBits(MS5611_CE_PORT, MS5611_CE_PIN)
#define MS5611_CE_L()			GPIO_ResetBits(MS5611_CE_PORT, MS5611_CE_PIN)
//EEPROM
#define EEPROM_CE_RCC			RCC_AHB1Periph_GPIOD
#define EEPROM_CE_PORT 		GPIOD
#define EEPROM_CE_PIN			GPIO_Pin_3
#define EEPROM_CE_H()			GPIO_SetBits(EEPROM_CE_PORT, EEPROM_CE_PIN)
#define EEPROM_CE_L()			GPIO_ResetBits(EEPROM_CE_PORT, EEPROM_CE_PIN)

extern void IMU_Init(void);
#endif

