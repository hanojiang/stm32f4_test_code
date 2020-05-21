#include "task_private.h"
#include "task_public.h"
#include "delay.h"
#include "led.h"
#include "sys.h"
#include "usart.h"
#include "pit.h"
#include "iom_public.h"
#include "test_public.h"
#include "key.h"
#include "oled.h"
#include "adm_public.h"

static u16 task_cnt = 0;

void TASK_SchTable(){

    /* 5 ms */
   
        IOM_Process5ms();
        TEST_Process5ms();
        ADM_Processing5ms();
    
    /* 10 ms */
    if(task_cnt%2 ==0){
        Key_Process10ms();
        TEST_Process10ms();
        
    }
    /* 500ms */
    if(task_cnt%100 ==0){
        TEST_Process500ms();
        
    }

    while (task_cnt==PIT_GetTimeCnt());
    task_cnt++;
}

void TASK_Init(){
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	uart_init(115200);
	LED_Init();
    PIT_Init();
    IOM_Init();
    Key_Init();
    OLED_Init();
    Test_Init();
    ADM_Init();
}