#ifndef iom_public_h 
#define iom_public_h 

typedef enum{
    IOM_IN_KEY_UP=0u,
    IOM_IN_KEY_LEFT,
    IOM_IN_KEY_RIGHT,
    IOM_IN_KEY_DOWN,
    IOM_IN_ALL_NUMBER
}IOM_PIN_IN_EM;

typedef enum{
    IOM_PIN_IN_LOW=0u,
    IOM_PIN_IN_HIGH,
    IOM_PIN_IN_INVALID,
}IOM_PIN_IN_STATUS_EM;

void IOM_Init();
void IOM_Process5ms();
IOM_PIN_IN_STATUS_EM IOM_GetPinDebStatus(IOM_PIN_IN_EM pin_index);

#endif	// iom_public_h