#include "deplacement.h"

Deplacement::Deplacement() : roueGauche_(PD4,PD6), roueDroite_(PD5,PD7) {
    TCCR2A = 0;
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20); 
    TCCR2B |= (1 << CS21);   // Prescaler de 8
}

void Deplacement::avancer(uint8_t vitesse) {
    roueGauche_.fixerDirection(true);
    roueDroite_.fixerDirection(true);
    roueGauche_.fixerVitesse(vitesse);
    roueDroite_.fixerVitesse(vitesse);
}

void Deplacement::reculer(uint8_t vitesse) {
    roueGauche_.fixerDirection(false);
    roueDroite_.fixerDirection(false);
    roueGauche_.fixerVitesse(vitesse);
    roueDroite_.fixerVitesse(vitesse);
}

void Deplacement::arreter() {
    roueGauche_.arreter();
    roueDroite_.arreter();
}





void Deplacement::virage(uint8_t vitesseGauche, uint8_t vitesseDroite){
    roueGauche_.fixerDirection(AVANT);
    roueDroite_.fixerDirection(AVANT);
    roueGauche_.fixerVitesse(vitesseGauche);
    roueDroite_.fixerVitesse(vitesseDroite);
}

void Deplacement::virageNet(bool aGauche, uint8_t vitesseGauche, uint8_t vitesseDroite){
    roueGauche_.fixerDirection(!aGauche);
    roueDroite_.fixerDirection(aGauche);
    roueGauche_.fixerVitesse(vitesseGauche);
    roueDroite_.fixerVitesse(vitesseDroite);
}

void Deplacement::boost(){
    roueGauche_.fixerDirection(AVANT);
    roueDroite_.fixerDirection(AVANT);
    roueGauche_.fixerVitesse(100);
    roueDroite_.fixerVitesse(100);
}