#ifndef _NVIC_RCC_H_
#define _NVIC_RCC_H_
#include "stm32f4xx.h"

#define MPU_INT_PP								0
#define MPU_INT_SP								0
#define HMS_INT_PP								0
#define HMS_INT_SP								1

#define USART1_IRQ_PP							2
#define USART1_IRQ_SP							0

#define NRF_IRQ_PP								3			//中断优先级
#define NRF_IRQ_SP								0


void NVIC_Config(void);
#endif

