#ifndef __ADM_PUBLIC_H_ 
#define __ADM_PUBLIC_H_ 
#include "stm32f4xx_conf.h"

void ADM_Init();
void ADM_Processing5ms();
u16* ADM_GetConvertValue();
u16 ADM_GetConvertValueCH5();
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx, u16 ndtr);


#endif	// __ADM_PUBLIC_H_