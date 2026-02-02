#ifndef BOUTON_H
#define BOUTON_H

#include <avr/io.h>




class Bouton {
public:
    Bouton(volatile uint8_t *port, uint8_t mask);
    ~Bouton() = default;
    bool estAppuyé();

private:
    static constexpr uint8_t DELAI_ANTI_REBOND_MS = 10;

    volatile uint8_t *pin_;
    uint8_t mask_;

    
    bool estSignalActif();
};

#endif