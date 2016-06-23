#ifndef _NRF24L01_H_
#define _NRF24L01_H_
#include "stm32f4xx.h"
#include "coocox.h"
#include "spi1.h"
#include "NVIC&RCC.h"//�����ж����ж����ȼ������˶���

#define MODEL_RX				1			//��ͨ����
#define MODEL_TX				2			//��ͨ����
#define MODEL_RX2				3			//����ģʽ2,����˫����
#define MODEL_TX2				4			//����ģʽ2,����˫����

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
#define NRF_CSN_RCC		RCC_AHB1Periph_GPIOC
#define NRF_CSN_PIN		GPIO_Pin_4
#define NRF_CSN_L()		GPIO_ResetBits(NRF_CSN_PORT, NRF_CSN_PIN)
#define NRF_CSN_H()		GPIO_SetBits(NRF_CSN_PORT, NRF_CSN_PIN)

#define NRF_IRQ_PORT							GPIOC
#define NRF_IRQ_RCC								RCC_AHB1Periph_GPIOC
#define NRF_IRQ_PIN								GPIO_Pin_5
#define NRF_EXTI_Line							EXTI_Line5
#define NRF_EXTI_IRQHandler				EXTI9_5_IRQHandler
#define NRF_IRQ_EXTI_PortSource		EXTI_PortSourceGPIOC
#define NRF_IRQ_EXTI_PinSource		EXTI_PinSource5
#define NRF_IRQChannel						EXTI9_5_IRQn
//#define NRF_IRQ_PP								3			//�ж����ȼ�
//#define NRF_IRQ_SP								0

typedef struct
{
	uint8_t RXDATA[RX_PLOAD_WIDTH];//nrf24l01���յ�������
	uint8_t TXDATA[RX_PLOAD_WIDTH];//nrf24l01��Ҫ���͵�����
	uint8_t Rx_Length;//���յ����ݳ���
	uint32_t Rx_IRQ_Count;//��������жϵĴ��������������ж��Ƿ�ʧ��
	OS_FlagID NRF_Rx_Done_Flag;//��������ж�
}NRF_Struct;

extern NRF_Struct NRF;

//��ʼ��,model=1/2/3/4,chΪʵ�õ�ͨ����
void NRF_Init(u8 model, u8 ch);	
//�������ݰ�,����model 2/4
void NRF_TxPacket(uint8_t * tx_buf, uint8_t len);	
//�������ݰ�,����model 3
void NRF_TxPacket_AP(uint8_t * tx_buf, uint8_t len);	
//���NRFģ���Ƿ���������
uint8_t NRF_Check(void);
//����Ƿ���ͨ���¼�
void NRF_Check_Event(void);

#endif


