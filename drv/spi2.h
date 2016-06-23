#ifndef _SPI2_H_
#define _SPI2_H_
#include "stm32f4xx.h"
#define SPI2_GPIO_PORT		GPIOB
#define SPI2_GPIO_RCC			RCC_AHB1Periph_GPIOB
#define SPI2_SCK_PIN			GPIO_Pin_13
#define SPI2_MISO_PIN			GPIO_Pin_14
#define SPI2_MOSI_PIN			GPIO_Pin_15

#define SPI2_SCK_GPIO_PinSource		GPIO_PinSource13
#define SPI2_MISO_GPIO_PinSource	GPIO_PinSource14
#define SPI2_MOSI_GPIO_PinSource	GPIO_PinSource15

void SPI2_Init(void);
uint8_t SPI2_RW(uint8_t data);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
#endif

