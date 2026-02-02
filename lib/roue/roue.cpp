
#include "roue.h"



Roue::Roue(uint8_t pinDirection, uint8_t pinVitesse) 
    : pinDirection_(pinDirection), pinVitesse_(pinVitesse) {
    DDRD |= (1 << pinDirection_) | (1 << pinVitesse_);
}

void Roue::fixerDirection(bool avant) {
    if (avant) {
        PORTD &= ~(1 << pinDirection_);
    } else {
        PORTD |= (1 << pinDirection_);
    }
}

void Roue::fixerVitesse(uint8_t vitesse) {
    if (pinVitesse_ == PD7) {
        OCR2A = vitesse;
    } else if (pinVitesse_ == PD6) {
        OCR2B = vitesse;
    }
}

void Roue::arreter() {
    fixerVitesse(0);
}