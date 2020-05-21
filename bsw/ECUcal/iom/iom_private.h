#ifndef iom_private_h 
#define iom_private_h
#include "iom_public.h"
#include "stm32f4xx_conf.h"

#define IOM_PIN_DEB_TIME 4
typedef struct 
{
    IOM_PIN_IN_EM PIN_IN;
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
    GPIOPuPd_TypeDef GPIO_PuPd;

}IOM_PIN_INDEX_ST;




#endif	// iom_private_h