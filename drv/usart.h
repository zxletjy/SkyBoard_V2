#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"

#define USE_DMA
#define USART1_DMA_TX_SIZE 32

void USART1_Init(u32 bound);
void USART3_Init(u32 bound);
void USART1_SendU8(uint8_t *p, uint8_t length);
extern int AQ_PRINTF(const char * fmt, ... );
#endif


