/* 
Travail : Projet INF1900
Section # : Section 6
Equipe # : EQUIPE_139-148
Correcteur : .........

Nom des auteurs : Yassine Morri, Areski Oussad, Leith Abderrahim et Adam Rafai

Description : Cette en-tête définit la classe `Robot`, qui regroupe l’ensemble des fonctionnalités nécessaires pour 
              contrôler un robot autonome participant à un parcours prédéfini. Elle inclut des méthodes pour la gestion
              des déplacements, la détection d’obstacles, le suivi de ligne, et des comportements spécifiques pour les 
              différentes étapes du parcours. Elle intègre également des constantes liées à la vitesse, des indicateurs 
              d’état, et des objets représentant des composants matériels du robot.

Identifications matérielles (Broches I/O) :
    - Composantes utilisées :
        - Suiveur de ligne (Makerline) :  Contrôlé via le module CapteurLigne
        - Capteur de distance : Contrôlé via le module CapteurAnalogique
        - Boutons : 
            - Bouton d’interruption
            - Bouton blanc
        - DEL bicolore
        - Moteur : Contrôlé via le module Deplacement
        - UART : Communication sérielle (vitesse configurée à 2400 bauds)
    - Type de composantes :
        - Boutons : 
            - Bouton d’interruption : Entrée (connecté à PD2)
            - Bouton blanc : Entrée (connecté à PD3)
        - Capteur de distance : Entrée analogique connectée au port A
        - Suiveur de ligne (Makerline) :  Entrée (les 5 sensors sont connectés au port A)
        - Moteur : Sortie (roues gauche et droite du pont en H connectée au port D)
        - Sonnette (buzzer) : Sortie (contrôlée via le module Son)
        - LED : Sortie (Connectée au port C)
    - Connexions principales :
        - DEL connectée à PC2
        - Bouton d’interruption sur PD2
        - Bouton blanc sur PD3
        - Moteur : roue gauche (PWM connecté à PD6 et direction connecté à PD4) et roue droite (PWM connecté à PD7 et direction connecté à PD5)
        - Suiveur de ligne (Makerline) : les 5 sensors sont connectés aux pins PA0, PA1, PA2, PA3, PA4 en partant du sensor tout à gauche jusqu'au sensor tout à droite
        - Capteur de distance : Connecté a PA5
        - Sonnette (buzzer) : Connecté a PB2

Autres informations :
    - Ce programme repose sur une machine à états pour coordonner les différentes étapes du parcours.
    - Les vitesses du robot sont définies en constantes (VITESSE_MAX, VITESSE_MOYENNE, etc.).
    - Les états et positions du robot sur une grille sont gérés à l’aide d’énumérations (VoieGrille, PositionsParcour).
*/


#ifndef ROBOT_H
#define ROBOT_H

#include "UART/UART.h"
#include "deplacement.h"
#include "../led/led.h"
#include "son.h"
#include "minuterie.h"
#include "bouton.h"
#include "capteurAnalogique.h"
#include "capteurLigne.h"
#include "constantes.h"

class Robot {
public:

    void reussirParcours();


    bool estPoteauProche();
    void poteauDetecte(bool poteau);

//////////////////////////////////////////////
    void sauverVirage(bool aGauche);
    void approcherPoteau();

    void suivreLigneA();

    bool estPoteauProcheGrille();

    void suivreLigneBase();
    void suivreLigneChat();
    void suivreLigneInitial();

    void parcoursMaison();
    void virageMaison(uint8_t nVirages);

    void initialisationParcours();

    void parcoursB();
    void parcoursC();
    void parcoursD();

    void premierObstacle(); 
    void deuxiemeObstacle();

    bool balayageVisuel();
    void balayageApartirDuCentre();
    void deuxiemeBalayage();
    void balayageApartirDe(bool direction);


    void allerAdroiteApartirDuCentre();
    void allerAgaucheApartirDuCentre();
    void allerAuCentreApartirDe(bool direction);
    void allerA(bool direction);

    void suivreLigneJ();





 


    static constexpr bool GAUCHE = true;
    static constexpr bool DROITE = false;
    static constexpr uint8_t VITESSE_DEBUG = 255;
    static constexpr uint8_t VITESSE_MAX = 132; // 144
    static constexpr uint8_t VITESSE_ZERO = 0;
    static constexpr uint8_t VITESSE_VIRAGE = 120; // 128
    static constexpr uint8_t VITESSE_SURPLACE = 88; // 96
    static constexpr uint8_t VITESSE_MOYENNE = 64; //72
    static constexpr uint16_t DELAI_AVANCER_MS = 1400;
    static constexpr uint16_t DELAI_DEBUT_DU_PARCOURS_MS = 2000;
    static constexpr uint16_t DELAI_ARRET = 200;
    static constexpr uint16_t DELAI_BOOST = 100;

    static constexpr uint8_t VITESSE_MAX_CHAT = 144;
    static constexpr uint8_t VITESSE_MOYENNE_CHAT = 110;
    static constexpr uint8_t VITESSE_MIN_CHAT = 80;
// variables et attributs
    uint8_t nbPassagesDeLigne = 0;
    uint8_t nbIntersections_ = 0;
    uint8_t nbIntersectionsFinDeGrille_=0;
    uint8_t compteurVirages_ = 0;
    uint8_t nAppuis = 0;
    uint8_t nbIntersectionsDeuxiemeBaleyage_ = 0;

    bool startedA;
    bool prioriteGauche;

    bool virageB_;
    bool virageC_;
    bool poteauH_ = false;
    
    VoieGrille voieActuelle = VoieGrille::CENTRE;


    bool verifPointC = true;
    Capteur suiveurDeLigne;
    LED led_ = LED(&PORTC, PC2);
    Deplacement moteur_;
    InterfaceUART uart_ = InterfaceUART(2400);
    Bouton boutonInterrupt_ = Bouton(&PIND,PD2);
    Bouton boutonBlanc_ = Bouton(&PIND,PD3);
    Son sonnette_;
    CapteurAnalogique capteurDistance_;
    PositionsParcour pos = PositionsParcour::INIT;
    
};

#endif /* ROBOT_H */