#ifndef __PIT_H_ 
#define __PIT_H_ 

#include "stm32f4xx_conf.h"

void PIT_Init();
u16 PIT_GetTimeCnt();
#endif	// __PIT_H_