#ifndef _NRF24L01_H_
#define _NRF24L01_H_
#include "stm32f4xx.h"
#include "spi1.h"


#define MODEL_RX				1			//普通接收
#define MODEL_TX				2			//普通发送
#define MODEL_RX2				3			//接收模式2,用于双向传输
#define MODEL_TX2				4			//发送模式2,用于双向传输

#define RX_PLOAD_WIDTH  255  	
#define TX_PLOAD_WIDTH  255  	
#define TX_ADR_WIDTH    5 	 	
#define RX_ADR_WIDTH    5   

#define NRF_CE_PORT GPIOA
#define NRF_CE_RCC	RCC_AHB1Periph_GPIOA
#define NRF_CE_PIN	GPIO_Pin_4
#define NRF_CE_L()		GPIO_ResetBits(NRF_CE_PORT, NRF_CE_PIN)
#define NRF_CE_H()		GPIO_SetBits(NRF_CE_PORT, NRF_CE_PIN)

#define NRF_CSN_PORT	GPIOC
#define NRF_CSN_RCC		RCC_AHB1Periph_GPIOA
#define NRF_CSN_PIN		GPIO_Pin_4
#define NRF_CSN_L()		GPIO_ResetBits(NRF_CSN_PORT, NRF_CSN_PIN)
#define NRF_CSN_H()		GPIO_SetBits(NRF_CSN_PORT, NRF_CSN_PIN)

extern uint8_t NRF24L01_2_RXDATA[RX_PLOAD_WIDTH];//nrf24l01接收到的数据
extern uint8_t NRF24L01_2_TXDATA[RX_PLOAD_WIDTH];//nrf24l01需要发送的数据
extern uint8_t NRF_LinkFlag;	


//初始化,model=1/2/3/4,ch为实用的通道号
void NRF_Init(u8 model, u8 ch);	
//发送数据包,用于model 2/4
void NRF_TxPacket(uint8_t * tx_buf, uint8_t len);	
//发送数据包,用于model 3
void NRF_TxPacket_AP(uint8_t * tx_buf, uint8_t len);	
//检查NRF模块是否正常工作
uint8_t NRF_Check(void);
//检查是否有通信事件
void NRF_Check_Event(void);

#endif


