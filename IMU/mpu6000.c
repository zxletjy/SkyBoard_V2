#include "mpu6000.h"
MPU6000_Struct MPU6000;
void MPU_WriteReg(uint8_t reg, uint8_t val)
{
	MPU_CE_L();
	IMU_SPI_RW(reg);
	IMU_SPI_RW(val);
	MPU_CE_H();
}
uint8_t MPU_ReadReg(uint8_t reg)
{
	uint8_t val;
	MPU_CE_L();
	IMU_SPI_RW(reg|0x80);
	val = IMU_SPI_RW(0xFF);
	MPU_CE_H();
	return val;
}
void MPU_Read_ACC_and_GYRO(void)
{
	uint8_t i=0;
	MPU_CE_L();
	IMU_SPI_RW(0x3B|0x80);
	do
	{
		MPU6000.buffer[i++] = IMU_SPI_RW(0xFF);
	}
	while(i < 14);
	MPU_CE_H();
}
void MPU_IRQ_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(MPU_INT_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = MPU_INT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(MPU_INT_PORT, &GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(MPU_INT_EXTI_PortSource, MPU_INT_EXTI_PinSource);
	
	NVIC_InitStructure.NVIC_IRQChannel = MPU_INTChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MPU_INT_PP;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = MPU_INT_SP;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = MPU_INT_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}
uint8_t MPU6000_Init(void)
{
	uint8_t err=0;
	IMU_SPI_SETBAUD(MPU6000_SPI_BAUD);
	if (MPU6000_Check())
	{
		MPU_WriteReg(107, 0x80);//复位芯片
		Delayms(100);
		MPU_WriteReg(107, 0x03);//用Z轴作为时钟源
		MPU_WriteReg(106, 0x10);//关闭IIC接口
		
		    // GYO scale
#if MPU6000_GYO_SCALE == 250
    MPU_WriteReg(27, 0);
#endif
#if MPU6000_GYO_SCALE == 500
    MPU_WriteReg(27, 0x08);
#endif
#if MPU6000_GYO_SCALE == 1000
    MPU_WriteReg(27, 0x10);
#endif
#if MPU6000_GYO_SCALE == 2000
    MPU_WriteReg(27, 0x18);
#endif

    // ACC scale
#if MPU6000_ACC_SCALE == 2
    MPU_WriteReg(28, 0);
#endif
#if MPU6000_ACC_SCALE == 4
    MPU_WriteReg(28, 0x08);
#endif
#if MPU6000_ACC_SCALE == 8
    MPU_WriteReg(28, 0x10);
#endif
#if MPU6000_ACC_SCALE == 16
    MPU_WriteReg(28, 0x18);
#endif
		// Sample rate
    MPU_WriteReg(25, 0x00);
    // LPF
    MPU_WriteReg(26, 0x00);
		// Interrupt setup
    MPU_WriteReg(55, 0x01<<4);//配置中断模式，高电平触发，读寄存器就清除中断
    MPU_WriteReg(56, 0x01);//开数据中断，即传感器数据准备好了以后就触发中断
		
		MPU_IRQ_Init();
		err = 1;
	}
	else
	{
		err = 0;
	}
	return err;
}
uint8_t MPU6000_Check(void)
{
	uint8_t flag;
	MPU_CE_L();
	IMU_SPI_RW(0x75|0x80);
	flag = IMU_SPI_RW(0xFF);
	MPU_CE_H();
	if (flag == 0x68)
	{
		flag = 1;
	}
	else
	{
		flag = 0;
	}
	return flag;
}

