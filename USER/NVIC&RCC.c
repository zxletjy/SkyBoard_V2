#include "NVIC&RCC.h"
#include "mpu6000.h"
void NVIC_Config(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
}
void EXTI4_IRQHandler(void)
{
	EXTI->PR = EXTI_Line4;
	MPU_Read_ACC_and_GYRO();
}



