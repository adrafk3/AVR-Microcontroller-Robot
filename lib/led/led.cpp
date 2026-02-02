
#include "led.h"

LED::LED(volatile uint8_t *port, uint8_t mask) : port_(port), mask_(mask) {
    DDRC |= (1<< mask_) | (1<< (mask_ + 1));  
};

LED::~LED()
{
    eteindreLed(); // eteindre la led une fois qu'elle n'est plus utilisee
}

void LED::allumerVert(){
    *port_ |= (1 << mask_);
    *port_ &= ~(1 << (mask_ + 1));
}

void LED::allumerRouge(){
    *port_ &= ~(1 << mask_);
    *port_ |= (1 << (mask_ + 1));
}
void LED::clignoterVert4Hz(){
    for (int i = 0; i < NB_CLIGNOTEMENTS_2Hz; ++i) {
        allumerVert();
        _delay_ms(125);      // demi-période allumée
        eteindreLed();
        _delay_ms(125);      // demi-période éteinte
    }    
}

void LED::clignoterVertRouge2Hz() {
    for (int i = 0; i < NB_CLIGNOTEMENTS_4Hz; ++i) {
        allumerVert();
        _delay_ms(250);
        allumerRouge();
        _delay_ms(250);
    }

    eteindreLed();
}


void LED::eteindreLed(){
    *port_ &= (1 << mask_);
    *port_ &= (1 << (mask_ + 1));
}


