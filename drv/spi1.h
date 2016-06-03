#ifndef _SPI1_H_
#define _SPI1_H_
#include "stm32f4xx.h"

#define SPI1_GPIO_PORT		GPIOA
#define SPI1_GPIO_RCC			RCC_AHB1Periph_GPIOA
#define SPI1_SCK_PIN			GPIO_Pin_5
#define SPI1_MISO_PIN			GPIO_Pin_6
#define SPI1_MOSI_PIN			GPIO_Pin_7

#define SPI1_SCK_GPIO_PinSource		GPIO_PinSource5
#define SPI1_MISO_GPIO_PinSource	GPIO_PinSource6
#define SPI1_MOSI_GPIO_PinSource	GPIO_PinSource7

void SPI1_Init(void);
uint8_t SPI1_RW(uint8_t data);
#endif

