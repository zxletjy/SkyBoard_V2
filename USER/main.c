#include "coocox.h"
#include "stm32f4xx.h"

#include "nrf24l01.h"
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
void Task_LED( void *pdata )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	while(1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		CoTickDelay( 100 );
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		CoTickDelay( 100 );
	}
}
void Task_NRF(void *p)
{
	NRF_Init(MODEL_RX2, 80);
	while(1)
	{
		NRF_Check_Event();
		CoTickDelay(1);
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




