#include "adm_public.h"
#include "delay.h"
static u16 adm_convertValue_ch5 = 0;
static u16 adm_convertValue[3] = {0};

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

u16* ADM_GetConvertValue()
{
    return adm_convertValue;
}

u16 ADM_GetConvertValueCH5()
{
    return adm_convertValue_ch5;
}