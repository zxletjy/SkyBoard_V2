#include "key.h"
void KEY1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(KEY1_IRQ_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY1_IRQ_PIN;//初始化MPU中断IO
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(KEY1_IRQ_PORT, &GPIO_InitStructure);//初始化GPIO
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	SYSCFG_EXTILineConfig(KEY1_IRQ_EXTI_PortSource, KEY1_IRQ_EXTI_PinSource);
	
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_IRQChannel;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = KEY1_IRQ_PP;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = KEY1_IRQ_SP;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	/* 配置EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line = KEY1_EXTI_Line;//LINE
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //上升沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
	EXTI_Init(&EXTI_InitStructure);//配置
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
	
	GPIO_InitStructure.GPIO_Pin = KEY2_IRQ_PIN;//初始化MPU中断IO
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(KEY2_IRQ_PORT, &GPIO_InitStructure);//初始化GPIO
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	SYSCFG_EXTILineConfig(KEY2_IRQ_EXTI_PortSource, KEY2_IRQ_EXTI_PinSource);
	
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_IRQChannel;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = KEY2_IRQ_PP;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = KEY2_IRQ_SP;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	/* 配置EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line = KEY2_EXTI_Line;//LINE
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //上升沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
	EXTI_Init(&EXTI_InitStructure);//配置
}
void KEY2_EXTI_IRQHandler(void)
{
		EXTI->PR = KEY2_EXTI_Line;
}
