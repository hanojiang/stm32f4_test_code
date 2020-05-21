#ifndef __LED_H
#define __LED_H
#include "sys.h"



#define LED0_PORT GPIOF
#define LED1_PORT GPIOF

#define LED0_PIN GPIO_Pin_9
#define LED1_PIN GPIO_Pin_10

#define PORT(led) led##_PORT
#define PIN(led) led##_PIN

#define LED_ON(led) GPIO_ResetBits(PORT(led), PIN(led))
#define LED_OFF(led) GPIO_SetBits(PORT(led), PIN(led))
#define LED_TOGGLE(led) GPIO_ToggleBits(PORT(led), PIN(led))
// #define LED0 PFout(9)	// DS0
// #define LED1 PFout(10)	// DS1	 

void LED_Init(void); 				    
#endif
