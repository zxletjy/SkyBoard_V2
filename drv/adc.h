#ifndef _ADC_H_
#define _ADC_H_
#include "coocox.h"
#include "stm32f4xx.h"
#define ANALOG_DMA_STREAM 		DMA2_Stream0
#define ANALOG_DMA_CHANNEL		DMA_Channel_0
#define ANALOG_CHANNEL_VIN		ADC_Channel_2
#define ANALOG_CHANNEL_ANP		ADC_Channel_3
#define ANALOG_CHANNELS         2
#define ANALOG_SAMPLES          32
#define ANALOG_SAMPLE_TIME      ADC_SampleTime_480Cycles
typedef struct
{
	uint16_t rawSamples[ANALOG_SAMPLES*ANALOG_CHANNELS];
	uint32_t rawChannels[ANALOG_CHANNELS];
	float vIn;
  int8_t batCellCount;
} adcStruct_t;

extern adcStruct_t adcData;
extern void adcInit(void);
extern void analogDecode(void);
#endif
