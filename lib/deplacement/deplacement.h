#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H


#include "roue.h"

#include <util/delay.h>


class Deplacement {
public:
    static constexpr bool AVANT =  true;
    static constexpr bool ARRIERE =  false;
    static constexpr uint8_t VITESSE_ROTAION_90 = 168;
    static constexpr uint8_t VITESSE_MAX = 255;
    static constexpr uint16_t DELAI_ROTATION_90_MS = 1200; // depend de la tension fournie aux moteurs
    
    Deplacement();
    
    void avancer(uint8_t vitesse);
    void reculer(uint8_t vitesse);
    void virage(uint8_t vitesseGauche, uint8_t vitesseDroite);
    void virageNet(bool aGauche, uint8_t vitesseGauche, uint8_t vitesseDroite);
    void arreter();
    void boost();

private:
    Roue roueGauche_; 
    Roue roueDroite_;
};

#endif /* DEPLACEMENT_H */