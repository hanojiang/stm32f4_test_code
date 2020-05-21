#include "key.h"



static KEY_STATUS_EM key_Status[KEY_INDEX_NUMBER_ALL] = {0};
static uint16_t key_press_count[KEY_INDEX_NUMBER_ALL] = {0};
static KEY_INDEX_MATRIX_ST keyIndexMatrix[KEY_INDEX_NUMBER_ALL] = {
    {KEY_UP_INDEX, IOM_IN_KEY_UP, HIGH_LEVEL_IS_PRESS},
    {KEY_LEFT_INDEX, IOM_IN_KEY_LEFT,LOW_LEVEL_IS_PRESS},
    {KEY_RIGHT_INDEX, IOM_IN_KEY_RIGHT, LOW_LEVEL_IS_PRESS},
    {KEY_DOWN_INDEX, IOM_IN_KEY_DOWN,LOW_LEVEL_IS_PRESS}
};

void Key_Init()
{
    for (uint8_t i = 0; i < KEY_INDEX_NUMBER_ALL; i++)
    {
        key_Status[i] = KEY_RELEASED;
        key_press_count[i] = 0;
    }

}

void Key_Process10ms()
{

    for (uint8_t i = 0; i < KEY_INDEX_NUMBER_ALL; i++)
    {
        if(keyIndexMatrix[i].keyLevelType == LOW_LEVEL_IS_PRESS){
            switch(key_Status[i]){
            case KEY_RELEASED:
                if(IOM_PIN_IN_LOW == IOM_GetPinDebStatus(keyIndexMatrix[i].iomIndex)){
                    key_Status[i] = KEY_PRESSED;
                    key_press_count[i] =0;
                }
                break;
            case KEY_PRESSED:
                if(IOM_PIN_IN_LOW == IOM_GetPinDebStatus(keyIndexMatrix[i].iomIndex)){
                    key_press_count[i]++;
                }
                else{
                    key_Status[i] = KEY_RELEASED;
                }
                if(key_press_count[i]>KEY_LONG_TIME_LIMIT){
                    key_Status[i] = KEY_LONGPRESS;
                }
                break;
            case KEY_LONGPRESS:
                if(IOM_PIN_IN_LOW == IOM_GetPinDebStatus(keyIndexMatrix[i].iomIndex)){
                    key_press_count[i]++;
                }
                else{
                    key_Status[i] = KEY_RELEASED;
                }
                if(key_press_count[i]>KEY_INVALID_TIME_LIMIT){
                    key_Status[i] = KEY_INVALID;
                    key_press_count[i]=0;
                }
                break;
            case KEY_INVALID:
                if(IOM_PIN_IN_HIGH == IOM_GetPinDebStatus(keyIndexMatrix[i].iomIndex)){
                     key_Status[i] = KEY_RELEASED;
                }
            }

        
        }
        else{
            switch(key_Status[i]){
            case KEY_RELEASED:
                if(IOM_PIN_IN_HIGH == IOM_GetPinDebStatus(keyIndexMatrix[i].iomIndex)){
                    key_Status[i] = KEY_PRESSED;
                    key_press_count[i] =0;
                }
                break;
            case KEY_PRESSED:
                if(IOM_PIN_IN_HIGH == IOM_GetPinDebStatus(keyIndexMatrix[i].iomIndex)){
                    key_press_count[i]++;
                }
                else{
                    key_Status[i] = KEY_RELEASED;
                }
                if(key_press_count[i]>KEY_LONG_TIME_LIMIT){
                    key_Status[i] = KEY_LONGPRESS;
                }
                break;
            case KEY_LONGPRESS:
                if(IOM_PIN_IN_HIGH == IOM_GetPinDebStatus(keyIndexMatrix[i].iomIndex)){
                    key_press_count[i]++;
                }
                else{
                    key_Status[i] = KEY_RELEASED;
                }
                if(key_press_count[i]>KEY_INVALID_TIME_LIMIT){
                    key_Status[i] = KEY_INVALID;
                    key_press_count[i]=0;
                }
                break;
            case KEY_INVALID:
                if(IOM_PIN_IN_LOW == IOM_GetPinDebStatus(keyIndexMatrix[i].iomIndex)){
                     key_Status[i] = KEY_RELEASED;
                }
            }
        }
        
    }



    // GPIO_PinState key_cur_status = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
    // switch (key_Status)
    // {
    // case KEY_RELEASED:
    //     if (GPIO_PIN_RESET == key_cur_status)
    //     {
    //         key_Status = KEY_PRESS_CONFIRM;
    //     }
    //     break;
    // case KEY_PRESS_CONFIRM:
    //     if (GPIO_PIN_RESET == key_cur_status)
    //     {
    //         key_Status = KEY_PRESSED;
    //         key_press_count = 0;
    //     }
    //     break;
    // case KEY_PRESSED:
    //     if (GPIO_PIN_RESET == key_cur_status)
    //     {
    //         key_press_count++;
    //     }
    //     else
    //     {
    //         key_Status = KEY_RELEASE_CONFIRM;
    //     }
    //     if (key_press_count > KEY_LONG_TIME_LIMIT)
    //     {
    //         key_Status = KEY_LONGPRESS;
    //     }
    //     break;
    // case KEY_LONGPRESS:
    //     if (key_press_count > KEY_INVALID_TIME_LIMIT)
    //     {
    //         key_Status = KEY_INVALID;
    //         key_press_count=0;
    //     }
    //     if (GPIO_PIN_RESET == key_cur_status)
    //     {
    //         key_press_count++;
    //     }
    //     else
    //     {
    //         key_Status = KEY_RELEASE_CONFIRM;
    //     }
    //     break;
    // case KEY_RELEASE_CONFIRM:
    //     if (GPIO_PIN_RESET == key_cur_status)
    //     {
    //         key_press_count++;
    //     }
    //     else{
    //         key_Status = KEY_RELEASED;
    //         key_press_count=0;
    //     }
    //     break;
    // case KEY_INVALID:
    //     if(GPIO_PIN_SET == key_cur_status){
    //         key_Status = KEY_RELEASED;
    //     }
    // }
}

KEY_STATUS_EM Key_GetStatus(KEY_INDEX_EM index)
{
    return key_Status[index];
}


/* KEY TEST
        
        if(KEY_PRESSED == Key_GetStatus(KEY_UP_INDEX)){
            my_printf("up press");
        }
        if(KEY_LONGPRESS == Key_GetStatus(KEY_UP_INDEX)){
            my_printf("up long press");
        }

        if(KEY_INVALID == Key_GetStatus(KEY_UP_INDEX)){
            my_printf("up invalid ");
        }

        if(KEY_PRESSED == Key_GetStatus(KEY_LEFT_INDEX)){
            my_printf("left press");
        }
        if(KEY_LONGPRESS == Key_GetStatus(KEY_LEFT_INDEX)){
            my_printf("left long press");
        }

        if(KEY_INVALID == Key_GetStatus(KEY_LEFT_INDEX)){
            my_printf("left invalid ");
        }

        if(KEY_PRESSED == Key_GetStatus(KEY_RIGHT_INDEX)){
            my_printf("right press");
        }
        if(KEY_LONGPRESS == Key_GetStatus(KEY_RIGHT_INDEX)){
            my_printf("right long press");
        }

        if(KEY_INVALID == Key_GetStatus(KEY_RIGHT_INDEX)){
            my_printf("right invalid ");
        }

        if(KEY_PRESSED == Key_GetStatus(KEY_DOWN_INDEX)){
            my_printf("down press");
        }
        if(KEY_LONGPRESS == Key_GetStatus(KEY_DOWN_INDEX)){
            my_printf("down long press");
        }

        if(KEY_INVALID == Key_GetStatus(KEY_DOWN_INDEX)){
            my_printf("down invalid ");
        }
        */