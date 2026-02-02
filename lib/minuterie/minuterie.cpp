#include "minuterie.h"

// Minuterie* minuterie_active = nullptr;

Minuterie::Minuterie()
    : gExpire_(false), gCompteurCycles_(0) {}

void Minuterie::partirMinuterie(uint16_t dureeMs) {
    gExpire_ = false;
    // minuterie_active = this;

    TCNT1 = 0;
    OCR1A = (dureeMs * 7812UL) / 1000UL; // Avec prescaler 1024, F_CPU = 8 MHz
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC + /1024
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A); // Active l’interruption sur Compare A
}