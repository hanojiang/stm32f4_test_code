#include "pit.h"
static u16 timeTickCnt = 0;


void PIT_Init()
{
    TIM_TimeBaseInitTypeDef tim2_TimeBaseInitStruct;
    NVIC_InitTypeDef nvic_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    tim2_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    tim2_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    tim2_TimeBaseInitStruct.TIM_Prescaler = 8399;
    tim2_TimeBaseInitStruct.TIM_Period = 49;
    
    nvic_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
    nvic_InitStruct.NVIC_IRQChannelSubPriority = 0x03;
    TIM_TimeBaseInit(TIM2, &tim2_TimeBaseInitStruct);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    NVIC_Init(&nvic_InitStruct);
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
    if(SET == TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
        timeTickCnt++;
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

u16 PIT_GetTimeCnt()
{
    return timeTickCnt;
}