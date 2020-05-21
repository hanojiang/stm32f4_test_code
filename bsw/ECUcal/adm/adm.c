#include "adm_public.h"
#include "delay.h"
static u16 adm_convertValue_ch5 = 0;
static  __IO u16 adm_convertValue[3] = {0};

#if 0
void ADM_Init()
{
    ADC_InitTypeDef adc_InitStruct;
    ADC_CommonInitTypeDef adc_CommonInitStruct;
    GPIO_InitTypeDef gpio_InitStruct;

    gpio_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    gpio_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    gpio_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    GPIO_Init(GPIOA, &gpio_InitStruct);

    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);

    adc_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
    adc_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    adc_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
    adc_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

    ADC_CommonInit(&adc_CommonInitStruct);

    adc_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    adc_InitStruct.ADC_ContinuousConvMode = DISABLE;
    adc_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
    adc_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    // adc_InitStruct.ADC_NbrOfConversion = 1;//3
    adc_InitStruct.ADC_NbrOfConversion = 3;
    adc_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    // adc_InitStruct.ADC_ScanConvMode = DISABLE;
    adc_InitStruct.ADC_ScanConvMode = ENABLE;
    ADC_DiscModeChannelCountConfig(ADC1, 1); //对 ADC 规则组通道配置间断模式
    ADC_DiscModeCmd(ADC1, ENABLE); //使能指定的 ADC 规则组通道的间断模式

    ADC_Init(ADC1, &adc_InitStruct);
    ADC_Cmd(ADC1, ENABLE);

  

    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_56Cycles);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_56Cycles);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 3, ADC_SampleTime_56Cycles);

}

void ADM_Processing5ms()
{

    u16 tmp = 0;
    
    //  ADC_SoftwareStartConv(ADC1);
    //  while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    //  adm_convertValue_ch5 = ADC_GetConversionValue(ADC1);
    for (uint8_t i = 0; i < 3; i++)
    {
        ADC_SoftwareStartConv(ADC1);
        ADC_EOCOnEachRegularChannelCmd(ADC1, ENABLE);
        while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
        {
            tmp++;
        }
        // delay_us(100);
        adm_convertValue[i] = ADC_GetConversionValue(ADC1);
    }
}


#else
void ADM_Init()
{
    ADC_InitTypeDef adc_InitStruct;
    ADC_CommonInitTypeDef adc_CommonInitStruct;
    GPIO_InitTypeDef gpio_InitStruct;
    DMA_InitTypeDef dma_InitStruct;

    gpio_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    gpio_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    gpio_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    GPIO_Init(GPIOA, &gpio_InitStruct);

    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);

    adc_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
    adc_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
    adc_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
    adc_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

    ADC_CommonInit(&adc_CommonInitStruct);

    adc_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    adc_InitStruct.ADC_ContinuousConvMode = DISABLE;
    adc_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
    adc_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    // adc_InitStruct.ADC_NbrOfConversion = 1;//3
    adc_InitStruct.ADC_NbrOfConversion = 3;
    adc_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    // adc_InitStruct.ADC_ScanConvMode = DISABLE;
    adc_InitStruct.ADC_ScanConvMode = ENABLE;

    ADC_Init(ADC1, &adc_InitStruct);
    // ADC_Cmd(ADC1, ENABLE);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_56Cycles);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_56Cycles);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 3, ADC_SampleTime_56Cycles);

    DMA_DeInit(DMA2_Stream0);
    while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE){}//等待 DMA 可配置
    dma_InitStruct.DMA_Channel = DMA_Channel_0;
    dma_InitStruct.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;
    dma_InitStruct.DMA_Memory0BaseAddr = (u32)adm_convertValue;
    dma_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
    dma_InitStruct.DMA_BufferSize = 3;
    dma_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    dma_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    dma_InitStruct.DMA_Mode = DMA_Mode_Circular;
    dma_InitStruct.DMA_Priority = DMA_Priority_High;
    dma_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    dma_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

    DMA_Init(DMA2_Stream0, &dma_InitStruct);
    DMA_Cmd(DMA2_Stream0, ENABLE);

    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
    
}

void ADM_Processing5ms()
{
    
    ADC_SoftwareStartConv(ADC1);
    

}

void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx, u16 ndtr)
{
    DMA_Cmd(DMA_Streamx, DISABLE); //关闭 DMA 传输
    while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE)
    {
    }                                          //确保 DMA 可以被设置
    DMA_SetCurrDataCounter(DMA_Streamx, ndtr); //数据传输量
    DMA_Cmd(DMA_Streamx, ENABLE);              //开启 DMA 传输
}
#endif

u16* ADM_GetConvertValue()
{
    return adm_convertValue;
}

u16 ADM_GetConvertValueCH5()
{
    return adm_convertValue_ch5;
}