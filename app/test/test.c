#include "test_public.h"
#include "key.h"
#include "led.h"
#include "oled.h"
#include "adm_public.h"
#include "lcd.h"
#include "stdlib.h"
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
    u8 lcd_id[12];
    static u8 x = 0;
    // v = ADM_GetConvertValueCH5();
    // OLED_ShowNum(0, 20, v, 4, 12);
    u16 *pvalue = ADM_GetConvertValue();

    v = pvalue[0];
    OLED_ShowNum(0, 20, v, 4, 12);
    v = pvalue[1];
    OLED_ShowNum(30, 20, v, 4, 12);
    v = pvalue[2];
    OLED_ShowNum(60, 20, v, 4, 12);

    OLED_Refresh_Gram();

    //POINT_COLOR = RED;
    setFrontColor(RED);                                 //画笔颜色：红色
    sprintf((char *)lcd_id, "LCD ID:%04X", lcddev.id); //将LCD ID打印到lcd_id数组。

    switch (x)
    {
        case 0:
            LCD_Clear(WHITE);
            break;
        case 1:
            LCD_Clear(BLACK);
            break;
        case 2:
            LCD_Clear(BLUE);
            break;
        case 3:
            LCD_Clear(RED);
            break;
        case 4:
            LCD_Clear(MAGENTA);
            break;
        case 5:
            LCD_Clear(GREEN);
            break;
        case 6:
            LCD_Clear(CYAN);
            break;
        case 7:
            LCD_Clear(YELLOW);
            break;
        case 8:
            LCD_Clear(BRRED);
            break;
        case 9:
            LCD_Clear(GRAY);
            break;
        case 10:
            LCD_Clear(LGRAY);
            break;
        case 11:
            LCD_Clear(BROWN);
            break;
    }
    LCD_ShowString(30, 40, 210, 24, 24, "Explorer STM32F4");
    LCD_ShowString(30, 70, 200, 16, 16, "TFTLCD TEST");
    LCD_ShowString(30, 90, 200, 16, 16, "ATOM@ALIENTEK");
    LCD_ShowString(30, 110, 200, 16, 16, lcd_id); //显示LCD ID
    LCD_ShowString(30, 130, 200, 12, 12, "2014/5/4");
    x++;
    if (x == 12)
        x = 0;
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