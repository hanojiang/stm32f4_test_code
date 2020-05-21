#include "iom_public.h"
#include "iom_private.h"


static uint8_t pinDebFailCnt[IOM_IN_ALL_NUMBER] = {0};
static uint8_t pinDebRiseCnt[IOM_IN_ALL_NUMBER] = {0};
static IOM_PIN_IN_STATUS_EM pinCurStatus[IOM_IN_ALL_NUMBER] = {0};
static IOM_PIN_IN_STATUS_EM pinDebStatus[IOM_IN_ALL_NUMBER] = {0};
static IOM_PIN_INDEX_ST pinIndexMatrix[IOM_IN_ALL_NUMBER] = {
    { IOM_IN_KEY_UP, GPIOA, GPIO_Pin_0, GPIO_PuPd_DOWN},
    { IOM_IN_KEY_LEFT, GPIOE, GPIO_Pin_2, GPIO_PuPd_UP},
    { IOM_IN_KEY_RIGHT, GPIOE, GPIO_Pin_4, GPIO_PuPd_UP},
    {IOM_IN_KEY_DOWN, GPIOE, GPIO_Pin_3, GPIO_PuPd_UP}
};

void IOM_Init(){

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOA, ENABLE); //使锟斤拷GPIOF时锟斤拷
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      //output mode
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //鎺ㄦ尳杈撳嚭
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz

    for (uint8_t i = 0; i < IOM_IN_ALL_NUMBER; i++)
    {
        pinCurStatus[i] = IOM_PIN_IN_INVALID;
        pinDebStatus[i] = IOM_PIN_IN_INVALID;
        pinDebFailCnt[i] = 0;
        pinDebRiseCnt[i] = 0;
        
        GPIO_InitStructure.GPIO_Pin = pinIndexMatrix[i].GPIO_Pin;
        GPIO_InitStructure.GPIO_PuPd = pinIndexMatrix[i].GPIO_PuPd; 
        GPIO_Init(pinIndexMatrix[i].GPIOx, &GPIO_InitStructure);
    }
 
}

void IOM_Process5ms(){

    for (uint8_t i = 0; i < IOM_IN_ALL_NUMBER; i++)
    {
        IOM_PIN_IN_STATUS_EM pinStautsTemp = (IOM_PIN_IN_STATUS_EM)GPIO_ReadInputDataBit(pinIndexMatrix[i].GPIOx, pinIndexMatrix[i].GPIO_Pin);
        pinCurStatus[i] = pinStautsTemp;
        
        if (pinCurStatus[i]!= pinDebStatus[i])
        {
            switch(pinStautsTemp){
                case IOM_PIN_IN_LOW:
                    pinDebFailCnt[i]++;
                    if(pinDebFailCnt[i]>=IOM_PIN_DEB_TIME){
                        pinDebFailCnt[i]=0;
                        pinDebStatus[i] = IOM_PIN_IN_LOW;
                    }
                    break;
                
                case IOM_PIN_IN_HIGH:
                    pinDebRiseCnt[i]++;
                    if(pinDebRiseCnt[i]>=IOM_PIN_DEB_TIME){
                        pinDebRiseCnt[i]=0;
                        pinDebStatus[i] = IOM_PIN_IN_HIGH;
                    }
                    break;
                case IOM_PIN_IN_INVALID:
                    break;
            }
        }
        
    }
}

IOM_PIN_IN_STATUS_EM IOM_GetPinDebStatus(IOM_PIN_IN_EM pin_index){

    return pinDebStatus[pin_index];
}