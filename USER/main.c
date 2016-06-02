#include "coocox.h"
#include "stm32f4xx.h"

#define  TASK_STK_SIZE              128
OS_STK   STK_LED_TASK               [128];
void Task_LED( void *pdata )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	while(1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
		CoTickDelay( 100 );
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);
		CoTickDelay( 100 );
	}
}
int main(void)
{ 	
	CoInitOS();
  
	CoCreateTask(Task_LED, Co_NULL, 10, &STK_LED_TASK[TASK_STK_SIZE-1], TASK_STK_SIZE );
	
	CoStartOS();
	while(1)
	{
		
	}
}




