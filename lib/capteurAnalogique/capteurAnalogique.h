#include "constantes.h"
#include "can.h"
#include "debug.h"
#include "../UART/UART.h"
#include "led.h"
class CapteurAnalogique{
public:
    CapteurAnalogique();
    bool estPoteauProche();
    bool estPoteauProcheGrille();
private:
    can can_;
    InterfaceUART uart_ = InterfaceUART(2400);
};