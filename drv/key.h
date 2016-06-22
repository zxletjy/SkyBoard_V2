#ifndef _KEY_H_
#define _KEY_H_
#include "stm32f4xx.h"

#define KEY1_IRQ_PORT								GPIOE
#define KEY1_IRQ_RCC								RCC_AHB1Periph_GPIOE
#define KEY1_IRQ_PIN								GPIO_Pin_4
#define KEY1_EXTI_Line							EXTI_Line4
#define KEY1_EXTI_IRQHandler				EXTI4_IRQHandler
#define KEY1_IRQ_EXTI_PortSource		EXTI_PortSourceGPIOE
#define KEY1_IRQ_EXTI_PinSource			EXTI_PinSource4
#define KEY1_IRQChannel							EXTI4_IRQn
#define KEY1_IRQ_PP									3			//中断优先级
#define KEY1_IRQ_SP									1

#define KEY2_IRQ_PORT								GPIOE
#define KEY2_IRQ_RCC								RCC_AHB1Periph_GPIOE
#define KEY2_IRQ_PIN								GPIO_Pin_3
#define KEY2_EXTI_Line							EXTI_Line3
#define KEY2_EXTI_IRQHandler				EXTI3_IRQHandler
#define KEY2_IRQ_EXTI_PortSource		EXTI_PortSourceGPIOE
#define KEY2_IRQ_EXTI_PinSource			EXTI_PinSource3
#define KEY2_IRQChannel							EXTI3_IRQn
#define KEY2_IRQ_PP									3			//中断优先级
#define KEY2_IRQ_SP									2

void KEY1_Init(void);
void KEY2_Init(void);
#endif

