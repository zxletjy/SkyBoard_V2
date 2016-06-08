#include "coocox.h"
#include "stm32f4xx.h"

#include "nrf24l01.h"
#include "usart.h"
//#include "key.h"
enum
{
	TASK_INIT_PRI=0,
	TASK_NRF_PRI,
	TASK_LED_PRI
};

#define TASK_INIT_STK_SIZE				128
OS_STK   STK_INIT_TASK            [TASK_INIT_STK_SIZE];

#define TASK_NRF_STK_SIZE				128
OS_STK   STK_NRF_TASK            [TASK_NRF_STK_SIZE];

#define  TASK_LED_STK_SIZE              128
OS_STK   STK_LED_TASK               [TASK_LED_STK_SIZE ];

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))
void USART1_SendXYZ(int x, int y, int z)
{
	uint8_t data_to_send[14];
	int data=0;
	data_to_send[0]=0xAA;
	data_to_send[1]=0xFF;
	data = x;
	data_to_send[2]=BYTE3(data);
	data_to_send[3]=BYTE2(data);
	data_to_send[4]=BYTE1(data);
	data_to_send[5]=BYTE0(data);
	
	data = y;
	data_to_send[6]=BYTE3(data);
	data_to_send[7]=BYTE2(data);
	data_to_send[8]=BYTE1(data);
	data_to_send[9]=BYTE0(data);
	
	data = z;
	data_to_send[10]=BYTE3(data);
	data_to_send[11]=BYTE2(data);
	data_to_send[12]=BYTE1(data);
	data_to_send[13]=BYTE0(data);
	
	USART1_SendU8(data_to_send, 14);
}
void Task_LED( void *pdata )
{
	int x=-1,y=10,z=100;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART1_Init(115200);
	while(1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
		CoTickDelay( 100 );
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);
		CoTickDelay( 100 );
		USART1_SendXYZ(x, y, z);
		x--;
		y++;
		z++;
	}
}
void Task_NRF(void *p)
{
//	NRF_Init(MODEL_RX2, 80);
	while(1)
	{
	//	NRF_Check_Event();
		CoTickDelay(100);
	}
}
void Task_INIT(void *p)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//KEY1_Init();
	//KEY2_Init();
	CoCreateTask(Task_NRF, Co_NULL, TASK_NRF_PRI, &STK_NRF_TASK[TASK_NRF_STK_SIZE -1], TASK_NRF_STK_SIZE);
	CoCreateTask(Task_LED, Co_NULL, TASK_LED_PRI, &STK_LED_TASK[TASK_LED_STK_SIZE -1], TASK_LED_STK_SIZE  );
	CoExitTask();
}

int main(void)
{ 	
	CoInitOS();
  
	CoCreateTask(Task_INIT, Co_NULL, TASK_INIT_PRI, &STK_INIT_TASK[TASK_INIT_STK_SIZE -1], TASK_INIT_STK_SIZE  );
	
	CoStartOS();
	while(1)
	{
		
	}
}




