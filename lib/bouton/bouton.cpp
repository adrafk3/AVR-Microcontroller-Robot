#include "bouton.h"
#include <util/delay.h>



Bouton::Bouton(volatile uint8_t *pin, uint8_t mask) : pin_(pin), mask_(mask) {
    DDRD &= ~(1 << PD2);
    DDRD &= ~(1 << PD3);
}

bool Bouton::estAppuyé() { 
    if (estSignalActif()) {
        _delay_ms(DELAI_ANTI_REBOND_MS);
        if(estSignalActif()){
            return true;
        }
    }
    return false;
}


bool Bouton::estSignalActif() {  
    return (PIND & (1 << mask_));
}

