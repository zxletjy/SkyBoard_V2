#include "usart.h"	
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

//初始化IO 串口1 
//bound:波特率
void USART1_Init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
#ifdef USE_DMA
	DMA_InitTypeDef  DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2时钟使能 
#endif
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断
#ifdef USE_DMA
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)USART1 + 0x04;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = (USART1_DMA_TX_SIZE != 0) ? USART1_DMA_TX_SIZE : 16;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_INC4;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream7, &DMA_InitStructure);

	DMA_SetCurrDataCounter(DMA2_Stream7, 0);
	DMA_ITConfig(DMA2_Stream7, DMA_IT_TC, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
		
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
#endif
}
__asm void FastMemCpy(u8* dest, u8* src, u16 size)
{
	MOVS r3, r2, asr #5 
	BEQ copywords 
	and r2, r2, #0x1f        ;subtract chunks from size
	stmfd   sp!, {r4-r11}    ;save working registers

octcopy
	ldmia r1!, {r4-r11};        ;load 8 words from src
	stmia r0!, {r4-r11};        ;write 8 words to dest
	subs r3, r3, #1;        ;more 8-word chunks to move?
	bne octcopy;        ;loop if more chunks
	ldmfd   sp!, {r4-r11}    ;restore working registers

copywords
	movs r3, r2, asr #2        ;any more whole words to move?
	beq     copybytes        ;jump if no more whole words
	
	stmdb sp!, {lr}    	;push return address
wordcopy
	ldr lr, [r1], #4  	;read next word from src
	str lr, [r0], #4  	;write next word to dest
	subs r3, r3, #1    	;decrement word count
	bne wordcopy   	;loop while more words to move
	ldmia sp!, {lr}    	;pop return address
	
copybytes
	ands r2, r2, #3    	;any last bytes to transfer?
	beq done    	;return if already done
	
bytecopy
	ldrb r3, [r1], #1  	;read byte from src
	strb r3, [r0], #1  	;write byte to dest
	subs r2, r2, #1    	;--size (decrement loop count)
	bne bytecopy  	;loop if more bytes to move
done
	bx lr;    	;return to caller
}
void USART1_SendU8(uint8_t *p, uint8_t length)
{
#ifdef USE_DMA
	static u8 buf[64];
	FastMemCpy(buf, p, length);
	//memcpy(buf, p, length);
	DMA2_Stream7->M0AR = (uint32_t)buf;
	DMA2_Stream7->NDTR = length;
	DMA_Cmd(DMA2_Stream7, ENABLE);
#else
	uint8_t i = 0;
	for (i=0; i<length; i++)
	{
		while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
		USART1->DR = *(p+i);  
	}
#endif
}
void DMA2_Stream7_IRQHandler(void)
{
	DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF5|DMA_FLAG_HTIF5|DMA_FLAG_TEIF5|DMA_FLAG_DMEIF5|DMA_FLAG_FEIF5|DMA_FLAG_TCIF7|
															DMA_FLAG_HTIF7|DMA_FLAG_TEIF7|DMA_FLAG_DMEIF7|DMA_FLAG_FEIF7);
}
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		
  } 
}

int AQ_PRINTF(const char * fmt, ... )
{
	va_list argptr;//声明一个转换参数的变量
	int cnt;
	char buffer[64];						//这个必须是静态的
//	int i;
	memset(buffer, 0, sizeof(buffer));//清空buffer
//	for (i=0; i<64; i++)
//	{
//		buffer[i] = 0;
//	}
//	do
//	{
//		buffer[i++] = 0;
//	}
//	while(i<64);
	va_start(argptr, fmt);						//初始化变量
	//将带参数的字符串按照参数列表格式化到buffer中
	cnt = vsnprintf(buffer, sizeof(buffer), fmt, argptr);
	va_end(argptr);										//结束变量列表

	USART1_SendU8((uint8_t *)buffer, cnt);
	
	return cnt;
}
void USART3_Init(u32 bound)
{
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART1); //GPIOD8复用为USART3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART1); //GPIOD9复用为USART3
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //GPIOD8与GPIOD9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure); //初始化PD8，PD9

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART3, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART3, ENABLE);  //使能串口3
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
}

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		USART1->DR = USART3->DR;
  } 
}





