#include "capteurLigne.h"


Capteur::Capteur(){
    DDRA &= ~((1 << PA0) | (1 << PA1) | (1 << PA2) | (1 << PA3) | (1 << PA4));
}

bool Capteur::extremeGaucheActif(){return PINA & (1 << PA0);}
bool Capteur::gaucheActif(){return PINA & (1 << PA1);}
bool Capteur::milieuActif(){return PINA & (1 << PA2);}
bool Capteur::droiteActif(){return PINA & (1 << PA3);}
bool Capteur::extremeDroiteActif(){return PINA & (1 << PA4);}

bool Capteur::quatreDroite()
{
    return (gaucheActif() && milieuActif() && droiteActif() && extremeDroiteActif());
}

// Bits A, B et C activés : 0b00111
bool Capteur::quatreGauche()
{
    return (extremeGaucheActif() && gaucheActif() && milieuActif() && droiteActif());
}



bool Capteur::ligneTrouver(){ 
    return (extremeGaucheActif() || gaucheActif() || milieuActif() || droiteActif() || extremeDroiteActif()); 
}

bool Capteur::tousEteintes(){    
    return (!extremeGaucheActif() && !gaucheActif() && !milieuActif() && !droiteActif() && !extremeDroiteActif()); 
}
bool Capteur::tousLesCapteursActifs(){
    return (extremeGaucheActif() && gaucheActif() && milieuActif() && droiteActif() && extremeDroiteActif()); 
}




bool Capteur::milieuEtNonExtreme(){
    return ((!extremeGaucheActif() && !extremeDroiteActif()) && (milieuActif() || gaucheActif() || droiteActif()));
}




// Bits C, D et E activés : 0b11100
bool Capteur::troisDroite()
{
    return ( milieuActif() && droiteActif() && extremeDroiteActif());
}

// Bits A, B et C activés : 0b00111
bool Capteur::troisGauche()
{
    return (extremeGaucheActif() && gaucheActif() && milieuActif());
}