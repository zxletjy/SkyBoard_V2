#include "adc.h"
#include <string.h>
adcStruct_t adcData __attribute__((section(".ccm")));
void analogDecode(void)
{
    int i, j;

    for (i = 0; i < ANALOG_CHANNELS; i++)
        adcData.rawChannels[i] = 0;

    for (i = 0; i < ANALOG_SAMPLES; i++)
        for (j = 0; j < ANALOG_CHANNELS; j++)
            adcData.rawChannels[j] += adcData.rawSamples[i * ANALOG_CHANNELS + j];

    adcData.vIn = adcData.rawChannels[0] / ANALOG_SAMPLES*0.00161+0.08;
	ADC_SoftwareStartConv(ADC1);
}
void adcInit(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
  memset((void *)&adcData, 0, sizeof(adcData));
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	DMA_DeInit(ANALOG_DMA_STREAM);
	DMA_InitStructure.DMA_Channel = ANALOG_DMA_CHANNEL;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)adcData.rawSamples;
	DMA_InitStructure.DMA_PeripheralBaseAddr = ((uint32_t)ADC1+0x4c);
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = ANALOG_SAMPLES*ANALOG_CHANNELS;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(ANALOG_DMA_STREAM, &DMA_InitStructure);

	DMA_Cmd(ANALOG_DMA_STREAM, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	// ADC Common Init
	ADC_CommonStructInit(&ADC_CommonInitStructure);
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
	ADC_CommonInit(&ADC_CommonInitStructure);

	// ADC1 configuration
	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = ANALOG_CHANNELS;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ANALOG_CHANNEL_VIN, 1, ANALOG_SAMPLE_TIME);
	ADC_RegularChannelConfig(ADC1, ANALOG_CHANNEL_ANP, 2, ANALOG_SAMPLE_TIME);

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
}

