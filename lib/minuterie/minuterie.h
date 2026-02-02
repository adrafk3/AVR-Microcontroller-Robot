#ifndef MINUTERIE_H
#define MINUTERIE_H

#include <avr/io.h>

class Minuterie {
public:
    Minuterie(); // Constructeur
    void partirMinuterie(uint16_t dureeMs); // Lance la minuterie
private:
    volatile bool gExpire_;               // Flag d'expiration
    volatile uint8_t gCompteurCycles_;       // Pour usage avancé
};

// Pointeur vers l'instance active utilisée dans l'ISR
// extern Minuterie* minuterie_active;

#endif