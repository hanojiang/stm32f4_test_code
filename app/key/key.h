#ifndef __KEY__H__
#define __KEY__H__
#include "iom_public.h"
#include "stm32f4xx_conf.h"

#define KEY_TIME_CIRCLE 10
#define KEY_LONG_TIME_LIMIT (5000/KEY_TIME_CIRCLE)
#define KEY_INVALID_TIME_LIMIT (10000/KEY_TIME_CIRCLE)

typedef enum{
    KEY_UP_INDEX=0u,
    KEY_LEFT_INDEX,
    KEY_RIGHT_INDEX,
    KEY_DOWN_INDEX,
    KEY_INDEX_NUMBER_ALL,
}KEY_INDEX_EM;

typedef enum{
    KEY_RELEASED=0u,
    KEY_PRESSED,
    KEY_LONGPRESS,
    KEY_INVALID
} KEY_STATUS_EM;

typedef enum{
    LOW_LEVEL_IS_PRESS=0u,
    HIGH_LEVEL_IS_PRESS,
}KEY_LEVEL_TYPE_EM;

typedef struct 
{
    KEY_INDEX_EM keyIndex;
    IOM_PIN_IN_EM iomIndex;
    KEY_LEVEL_TYPE_EM keyLevelType;
}KEY_INDEX_MATRIX_ST;


void Key_Init();
KEY_STATUS_EM Key_GetStatus(KEY_INDEX_EM index);
void Key_Process10ms();


#endif