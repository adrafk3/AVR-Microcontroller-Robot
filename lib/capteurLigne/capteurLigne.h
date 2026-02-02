#ifndef CAPTEUR_LIGNE_H
#define CAPTEUR_LIGNE_H
#include <avr/io.h> 


class Capteur{
public:
    Capteur();
    // Détection individuelle
    bool extremeGaucheActif();
    bool gaucheActif();
    bool milieuActif();
    bool droiteActif();
    bool extremeDroiteActif();

    bool quatreDroite();
    // Combinaisons spécifiques
    bool tousLesCapteursActifs();
    bool quatreGauche();
    bool tousEteintes();
    bool ligneTrouver();
    bool milieuEtNonExtreme();
    bool troisDroite();
    bool troisGauche();

};

#endif