#include "key.h"
void KEY1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(KEY1_IRQ_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY1_IRQ_PIN;//��ʼ��MPU�ж�IO
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(KEY1_IRQ_PORT, &GPIO_InitStructure);//��ʼ��GPIO
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	SYSCFG_EXTILineConfig(KEY1_IRQ_EXTI_PortSource, KEY1_IRQ_EXTI_PinSource);
	
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_IRQChannel;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = KEY1_IRQ_PP;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = KEY1_IRQ_SP;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	/* ����EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line = KEY1_EXTI_Line;//LINE
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
	EXTI_Init(&EXTI_InitStructure);//����
}
void KEY1_EXTI_IRQHandler(void)
{
		EXTI->PR = KEY1_EXTI_Line;
}
void KEY2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(KEY2_IRQ_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY2_IRQ_PIN;//��ʼ��MPU�ж�IO
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(KEY2_IRQ_PORT, &GPIO_InitStructure);//��ʼ��GPIO
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	SYSCFG_EXTILineConfig(KEY2_IRQ_EXTI_PortSource, KEY2_IRQ_EXTI_PinSource);
	
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_IRQChannel;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = KEY2_IRQ_PP;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = KEY2_IRQ_SP;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	/* ����EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line = KEY2_EXTI_Line;//LINE
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
	EXTI_Init(&EXTI_InitStructure);//����
}
void KEY2_EXTI_IRQHandler(void)
{
		EXTI->PR = KEY2_EXTI_Line;
}
