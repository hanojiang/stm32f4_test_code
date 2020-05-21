#include "test_public.h"
#include "key.h"
#include "led.h"
#include "oled.h"
#include "adm_public.h"

void TEST_Process5ms()
{
}

void TEST_Process10ms()
{
    
    if (KEY_PRESSED == Key_GetStatus(KEY_UP_INDEX))
    {
        LED_ON(LED0);
        LED_OFF(LED1);
        
        OLED_ShowString(70, 0, "short  ", 12);
    }
    else if (KEY_LONGPRESS == Key_GetStatus(KEY_UP_INDEX))
    {
        LED_ON(LED1);
        LED_OFF(LED0);
        OLED_ShowString(70, 0, "long   ", 12);
    }
    else
    {
        LED_OFF(LED1);
        LED_OFF(LED0);
        OLED_ShowString(70, 0, "invalid", 12);
    }

    OLED_Refresh_Gram();
}

void TEST_Process500ms()
{
    u16 v = 0;
    // v = ADM_GetConvertValueCH5();
    // OLED_ShowNum(0, 20, v, 4, 12);
    u16* pvalue = ADM_GetConvertValue();

    v = pvalue[0];
    OLED_ShowNum(0, 20, v, 4, 12);
    v = pvalue[1];
    OLED_ShowNum(30, 20, v, 4, 12);
    v = pvalue[2];
    OLED_ShowNum(60, 20, v, 4, 12);

    OLED_Refresh_Gram();
    
}
void delay_ms(u16 nms);
void Test_Init()
{
    OLED_Fill(0, 0, 127, 63, 1);
    OLED_Refresh_Gram();
    delay_ms(500);
    OLED_Clear();
    OLED_ShowString(0, 0, "key status:", 12);
    OLED_Refresh_Gram();
}