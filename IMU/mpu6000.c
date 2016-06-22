#include "mpu6000.h"
void MPU6000_Init(void)
{
	MPU6000_Check();
}
uint8_t MPU6000_Check(void)
{
	uint8_t flag;
	MPU_CE_L();
	IMU_SPI_RW(0x75);
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

