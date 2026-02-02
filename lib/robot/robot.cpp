/* 
Travail : Projet INF1900
Section # : Section 6
Equipe # : EQUIPE_139-148
Correcteur : .........

Nom des auteurs : Yassine Morri, Areski Oussad, Leith Abderrahim et Adam Rafai

Description : Ce fichier implémente les méthodes de la classe `Robot`, définissant les comportements nécessaires pour 
              naviguer un parcours autonome. Il gère les déplacements, le suivi de ligne, la détection et l’évitement 
              d’obstacles, ainsi que les interactions avec les différentes composantes matérielles du robot.

Rôles principaux :
    - Gérer la logique des déplacements (avancer, tourner, suivre une ligne, etc.).
    - Interagir avec les capteurs pour détecter les obstacles et ajuster les actions en conséquence.
    - Exécuter les étapes du parcours en fonction des états définis dans une machine à états.

Autres informations :
    - Ce fichier est central dans l’orchestration du fonctionnement global du robot.
    - Il utilise les modules matériels (moteurs, capteurs, DEL) et logiciels (énumérations, constantes) pour offrir une solution intégrée.

Table d'etats:
╔═════════════════════════════════════════════════════════════════════════════╗
║                       TABLE D'ÉTAT DU ROBOT – POSITIONS                    ║
╠═════════════════════════════════════════════════════════════════════════════╣
║ ÉTAT (pos)       ║ ACTION ASSOCIÉE               ║ CONDITION DE TRANSITION ║ ÉTAT SUIVANT ║
╠═════════════════════════════════════════════════════════════════════════════╣
║ INIT             ║ suivreLigneInitial()           ║ Tous capteurs actifs    ║ GRILLE        ║
║                  ║                                ║ Tous capteurs éteints   ║ B             ║
╠═════════════════════════════════════════════════════════════════════════════╣
║ A                ║ suivreLigneA()                 ║ Ligne retrouvée         ║ B             ║
╠═════════════════════════════════════════════════════════════════════════════╣
║ B                ║ parcoursB()                    ║ Tous capteurs éteints   ║ C             ║
╠═════════════════════════════════════════════════════════════════════════════╣
║ C                ║ parcoursC()                    ║ Ligne retrouvée         ║ D             ║
╠═════════════════════════════════════════════════════════════════════════════╣
║ D                ║ parcoursD()                    ║ Motif détecté           ║ MAISON        ║
╠═════════════════════════════════════════════════════════════════════════════╣
║ MAISON           ║ parcoursMaison()               ║ 8 virages complétés     ║ J ou FINAL    ║
╠═════════════════════════════════════════════════════════════════════════════╣
║ J                ║ suivreLigneJ()                 ║ Tous capteurs actifs    ║ GRILLE        ║
╠═════════════════════════════════════════════════════════════════════════════╣
║ GRILLE           ║ premierObstacle()              ║ Après balayage          ║ —             ║
║                  ║ deuxiemeObstacle()             ║ 2 intersections trouvées║ A ou FINAL    ║
╠═════════════════════════════════════════════════════════════════════════════╣
║ FINAL            ║ Clignotement LED vert/rouge    ║ Fin de parcours         ║ —             ║
╚═════════════════════════════════════════════════════════════════════════════╝
Note : la variable `pos` est modifiée dynamiquement à l'intérieur des méthodes associées.
*/

#include "robot.h"





bool Robot::estPoteauProcheGrille(){
    if(capteurDistance_.estPoteauProcheGrille()){
        led_.allumerRouge();
        return true;
    }
    else{
        led_.eteindreLed();
        return false;
    }
}

bool Robot::estPoteauProche(){  
    return capteurDistance_.estPoteauProche();
}

void Robot::poteauDetecte(bool poteau){
    for(uint8_t i = 0; i < 8; i++){
        poteau ? led_.allumerRouge() : led_.allumerVert();
        _delay_ms(125);
        led_.eteindreLed();
        _delay_ms(125);
    }
}

//DE INIT À B OU LABYTINTHE
void Robot::suivreLigneInitial(){
    if(suiveurDeLigne.tousLesCapteursActifs()){
        moteur_.arreter();
        moteur_.avancer(DELAI_ARRET);
        while (suiveurDeLigne.tousLesCapteursActifs()){} 
        moteur_.arreter();
        _delay_ms(1000);
        startedA = false;
        approcherPoteau();
        pos = PositionsParcour::GRILLE;
    }
    else if (suiveurDeLigne.tousEteintes()){
        moteur_.arreter();
        sonnette_.creerSon(45);
        _delay_ms(1000);
        sonnette_.stopSon();
        startedA = true;
        pos = PositionsParcour::B;
        virageB_ ? moteur_.virage(VITESSE_DEBUG, VITESSE_DEBUG) : moteur_.virage(VITESSE_DEBUG, VITESSE_DEBUG);
        _delay_ms(DELAI_BOOST);
        while(!suiveurDeLigne.ligneTrouver()){
            virageB_ ? moteur_.virage(VITESSE_MOYENNE, VITESSE_VIRAGE) : moteur_.virage(VITESSE_VIRAGE, VITESSE_MOYENNE);
        }
        moteur_.arreter();
        _delay_ms(50);
    }
    else suivreLigneBase();
}

void Robot::parcoursB(){
    if(suiveurDeLigne.tousLesCapteursActifs()){
        moteur_.avancer(VITESSE_MAX);
        _delay_ms(DELAI_ARRET);
        virageB_ ?
        moteur_.virage(VITESSE_ZERO, VITESSE_MAX) : 
        moteur_.virage(VITESSE_MAX, VITESSE_ZERO);
        while(!suiveurDeLigne.milieuEtNonExtreme()){}
        moteur_.arreter();
    }
    else if(suiveurDeLigne.tousEteintes()){
        moteur_.arreter();
        sonnette_.creerSon(45);
        _delay_ms(1000);
        sonnette_.stopSon();
        moteur_.avancer(VITESSE_MAX);
        _delay_ms(DELAI_ARRET);
        pos = PositionsParcour::C;
        virageC_ ? moteur_.virage(VITESSE_DEBUG, VITESSE_DEBUG) : moteur_.virage(VITESSE_DEBUG, VITESSE_DEBUG);
        _delay_ms(DELAI_BOOST);
        while(!suiveurDeLigne.ligneTrouver()){
            virageC_ ? moteur_.virage(VITESSE_MOYENNE, VITESSE_VIRAGE) : moteur_.virage(VITESSE_VIRAGE, VITESSE_MOYENNE);
        }
        moteur_.arreter();
        _delay_ms(500);
    }
    else{
        suivreLigneBase();
    } 
}

void Robot::parcoursC(){
    if(virageC_){
        while(!(suiveurDeLigne.tousEteintes() || suiveurDeLigne.quatreDroite() ) ){
            suivreLigneBase();
        }   
    }
    else{
        while(!(suiveurDeLigne.tousEteintes() || suiveurDeLigne.quatreGauche() )){
            suivreLigneBase();
        }
    }
    while (!suiveurDeLigne.tousEteintes()){moteur_.avancer(VITESSE_MAX);}
    if(virageC_){
        moteur_.virage(VITESSE_VIRAGE, VITESSE_MOYENNE);
    }
    else{
        moteur_.virage(VITESSE_MOYENNE, VITESSE_VIRAGE);
    }
    while(!suiveurDeLigne.milieuEtNonExtreme()){}
    uart_.envoyerString("ligne trouver apres C");
    pos = PositionsParcour::D;

}

void Robot::parcoursD(){
    if(suiveurDeLigne.tousEteintes() || (suiveurDeLigne.gaucheActif() && suiveurDeLigne.milieuActif() && suiveurDeLigne.droiteActif() && suiveurDeLigne.extremeDroiteActif())){
        sauverVirage(DROITE);
        uart_.envoyerString("je vais dans maison ");
        pos = PositionsParcour::MAISON;
    }
    else suivreLigneBase();
}
//considere que nVirages == 0 apres avoir tourner dans le coin
void Robot::parcoursMaison(){
    while(compteurVirages_ < 8){
        if(suiveurDeLigne.milieuActif() && suiveurDeLigne.droiteActif() && suiveurDeLigne.extremeDroiteActif()){ //if(suiveurDeLigne.tournerADroite()){
            virageMaison(++compteurVirages_);
        }
        else{
            suivreLigneBase();
        }
    }
}

void Robot::virageMaison(uint8_t nVirages){
    switch (nVirages){
        case 1 : //esquiver le point E
            moteur_.avancer(VITESSE_MAX);
            while(suiveurDeLigne.extremeDroiteActif()) {}
            break;
        case 2 : //Rentrer au point F 
            moteur_.virage(VITESSE_MAX, VITESSE_VIRAGE); 
            _delay_ms(DELAI_AVANCER_MS);
            moteur_.arreter(); 
            _delay_ms(DELAI_ARRET);
            moteur_.virageNet(DROITE, VITESSE_DEBUG, VITESSE_DEBUG);
            _delay_ms(DELAI_BOOST);
            moteur_.virageNet(DROITE, VITESSE_VIRAGE, VITESSE_MAX);
            while(!suiveurDeLigne.tousEteintes()) {};
            while(!suiveurDeLigne.milieuEtNonExtreme()) {};
            moteur_.arreter();
            _delay_ms(DELAI_ARRET);
            break;
        case 3 : //Tourner tant que tu trouver un poteau ou t'as seulement les 2 à droite
            moteur_.avancer(VITESSE_MAX);
            _delay_ms(DELAI_AVANCER_MS);
            moteur_.virageNet(DROITE, VITESSE_DEBUG, VITESSE_DEBUG);
            _delay_ms(DELAI_BOOST);
            moteur_.virageNet(DROITE, VITESSE_SURPLACE, VITESSE_SURPLACE);
            while(!(suiveurDeLigne.gaucheActif() && suiveurDeLigne.extremeGaucheActif())){
                if(estPoteauProche()) {
                    poteauH_ = true;
                }
            }
            moteur_.arreter();
            poteauDetecte(poteauH_);
            if(poteauH_) {
                moteur_.virageNet(DROITE, VITESSE_DEBUG, VITESSE_DEBUG);
                _delay_ms(DELAI_BOOST);
                moteur_.virageNet(DROITE, VITESSE_SURPLACE, VITESSE_SURPLACE);
                while(!suiveurDeLigne.milieuEtNonExtreme()){}
                moteur_.arreter();
                compteurVirages_++;
            }
            else{
                moteur_.virageNet(GAUCHE, VITESSE_SURPLACE, VITESSE_SURPLACE);
                while(!suiveurDeLigne.milieuEtNonExtreme()){}
            }
            break;
        case 4 : // Seulement si y'a pas poteau
            moteur_.virageNet(DROITE, VITESSE_DEBUG, VITESSE_DEBUG);
            _delay_ms(DELAI_BOOST);
            sauverVirage(DROITE);
            break;
        case 5 : //tourner si ya un poteau, sinon ignorer     
            moteur_.avancer(VITESSE_MAX);
            _delay_ms(800);
            moteur_.arreter();
            _delay_ms(DELAI_ARRET);
            moteur_.virageNet(DROITE,VITESSE_SURPLACE,VITESSE_SURPLACE);
            while (!suiveurDeLigne.milieuEtNonExtreme()){}
            break;
        case 6 : //virer a droite
            moteur_.virageNet(DROITE, VITESSE_DEBUG, VITESSE_DEBUG);
            _delay_ms(DELAI_BOOST);
            sauverVirage(DROITE);
            break;
        case 7 : // ignorer point F
            moteur_.avancer(VITESSE_MAX);
            while(suiveurDeLigne.extremeDroiteActif()) {}
            break;
        case 8 : //Dans le coin avant d'aller dans le labyrinthe
            moteur_.virageNet(DROITE, VITESSE_DEBUG, VITESSE_DEBUG);
            _delay_ms(DELAI_BOOST);
            sauverVirage(DROITE);
            (!startedA) ? pos = PositionsParcour::FINAL : pos = PositionsParcour::J;
            break;
    }
}


void Robot::suivreLigneJ(){
    if(suiveurDeLigne.tousLesCapteursActifs()){
        moteur_.arreter();
        moteur_.avancer(DELAI_ARRET);
        while (suiveurDeLigne.tousLesCapteursActifs()){} 
        moteur_.arreter();
        _delay_ms(1000);
        approcherPoteau();
        pos = PositionsParcour::GRILLE;
    }
    else{
        suivreLigneBase();
    }
}
void Robot::suivreLigneBase(){
    if(suiveurDeLigne.extremeDroiteActif()){
        moteur_.virage(VITESSE_MAX, VITESSE_ZERO);
    }
    else if(suiveurDeLigne.extremeGaucheActif()){
        moteur_.virage(VITESSE_ZERO, VITESSE_MAX);
    }
    else if(suiveurDeLigne.gaucheActif()) {
        moteur_.virage(VITESSE_VIRAGE, VITESSE_MAX);
    }
    else if(suiveurDeLigne.droiteActif()) {
        moteur_.virage(VITESSE_MAX, VITESSE_VIRAGE);
    }
    else if(suiveurDeLigne.milieuActif()){
        moteur_.avancer(VITESSE_MAX);
    }
}

void Robot::suivreLigneChat(){
    if(suiveurDeLigne.milieuActif()){
        // Ligne parfaitement centrée
        moteur_.avancer(VITESSE_MAX_CHAT);
    }
    else if(suiveurDeLigne.gaucheActif()){
        // Petit ajustement vers la gauche
        moteur_.virage(VITESSE_MOYENNE_CHAT, VITESSE_MAX_CHAT);
    }
    else if(suiveurDeLigne.droiteActif()){
        // Petit ajustement vers la droite
        moteur_.virage(VITESSE_MAX_CHAT, VITESSE_MOYENNE_CHAT);
    }
    else if(suiveurDeLigne.extremeGaucheActif()){
        // Correction forte vers la gauche
        moteur_.virage(VITESSE_MIN_CHAT, VITESSE_MAX_CHAT);
        prioriteGauche = true;
    }
    else if(suiveurDeLigne.extremeDroiteActif()){
        // Correction forte vers la droite
        moteur_.virage(VITESSE_MAX_CHAT, VITESSE_MIN_CHAT);
        prioriteGauche = false;
    }
    else{
        // Si aucun capteur actif, continuer lentement vers l'avant pour retrouver la ligne
        moteur_.avancer(VITESSE_MIN_CHAT);
    }
}

void Robot::sauverVirage(bool aGauche){
    moteur_.avancer(VITESSE_MAX); 
    _delay_ms(DELAI_AVANCER_MS);
    moteur_.arreter(); 
    _delay_ms(DELAI_ARRET);
    if(aGauche){
        moteur_.virageNet(GAUCHE, VITESSE_DEBUG, VITESSE_DEBUG);
        _delay_ms(DELAI_BOOST);
        moteur_.virageNet(GAUCHE, VITESSE_SURPLACE, VITESSE_SURPLACE);
    }
    else {
        moteur_.virageNet(DROITE, VITESSE_DEBUG, VITESSE_DEBUG);
        _delay_ms(DELAI_BOOST);
        moteur_.virageNet(DROITE, VITESSE_SURPLACE, VITESSE_SURPLACE);
    }
    while(!suiveurDeLigne.tousEteintes()) {}
    while(!suiveurDeLigne.milieuEtNonExtreme()) {}
    moteur_.arreter();
    _delay_ms(DELAI_ARRET);
    //Correction
    while(suiveurDeLigne.tousEteintes()){
        if(aGauche){
            moteur_.virageNet(DROITE, VITESSE_SURPLACE, VITESSE_SURPLACE);
        }
        else {
            moteur_.virageNet(GAUCHE, VITESSE_SURPLACE, VITESSE_SURPLACE);
        }
    }
    moteur_.arreter();
    _delay_ms(DELAI_ARRET);
}

void Robot::initialisationParcours(){
    pos = PositionsParcour::INIT;
    while(nAppuis != 2){
        if(boutonInterrupt_.estAppuyé()){
            while(boutonInterrupt_.estAppuyé()){
                led_.allumerVert();
            }
            nAppuis++;
            nAppuis == 1 ? virageB_ = false : virageC_ = false;
        }
        else if(!boutonBlanc_.estAppuyé()){
            while(!boutonBlanc_.estAppuyé()){
                led_.allumerRouge();
            }
            nAppuis++;
            nAppuis == 1 ? virageB_ = true : virageC_ = true;
        }
        led_.eteindreLed();
    }
    led_.eteindreLed();
    _delay_ms(DELAI_DEBUT_DU_PARCOURS_MS);
}


bool Robot::balayageVisuel(){

    while(!(suiveurDeLigne.extremeDroiteActif() && !suiveurDeLigne.milieuActif())){
        moteur_.virageNet(GAUCHE, VITESSE_SURPLACE, VITESSE_SURPLACE);
        if(estPoteauProcheGrille()) return true;
    }
    while(!(suiveurDeLigne.extremeGaucheActif() && !suiveurDeLigne.milieuActif())){
        moteur_.virageNet(DROITE, VITESSE_SURPLACE, VITESSE_SURPLACE);
        if(estPoteauProcheGrille()) return true;
    }
    return false;
}

void Robot::balayageApartirDuCentre(){
    if(balayageVisuel()){
        moteur_.virageNet(DROITE, VITESSE_VIRAGE, VITESSE_VIRAGE);
        while(!suiveurDeLigne.tousEteintes()){}
        moteur_.virageNet(DROITE, VITESSE_VIRAGE, VITESSE_VIRAGE);
        while(true){
            if(estPoteauProcheGrille()){
                moteur_.arreter();
                allerAgaucheApartirDuCentre();
                break;
            }
            else if(suiveurDeLigne.ligneTrouver()){
                uart_.envoyerString("le poteau est a gauche, je continue a droite  ");
                moteur_.arreter();
                _delay_ms(DELAI_ARRET);
                allerAdroiteApartirDuCentre();
                break;
            }
        }
    }
    else{
        while (!suiveurDeLigne.milieuEtNonExtreme())
        {
            moteur_.virageNet(GAUCHE,VITESSE_SURPLACE,VITESSE_SURPLACE);
        }
        
        moteur_.arreter();
    }
    led_.clignoterVert4Hz();
}

void Robot::allerAdroiteApartirDuCentre(){
    moteur_.arreter();
    _delay_ms(1000);
    while(!(suiveurDeLigne.extremeGaucheActif() && suiveurDeLigne.milieuActif() && suiveurDeLigne.gaucheActif())){
        suivreLigneBase();
    }
    moteur_.arreter();
    sauverVirage(GAUCHE);
    // while (!suiveurDeLigne.milieuEtNonExtreme())
    // {
    //     suivreLigneBase();
    // }
    moteur_.arreter();
    _delay_ms(1000);
    voieActuelle = VoieGrille::DROITE;
}

void Robot::allerAgaucheApartirDuCentre(){
   // nbPassagesDeLigne = 0;
    moteur_.arreter();
    _delay_ms(1000);
    moteur_.virageNet(GAUCHE, 128, 128);
    while(suiveurDeLigne.tousEteintes()) {}
    while(!suiveurDeLigne.tousEteintes()) {}
    while(suiveurDeLigne.tousEteintes()) {}
    // while(nbPassagesDeLigne != 2){
    //     if(suiveurDeLigne.ligneTrouver()){
    //         nbPassagesDeLigne++;
    //         if(nbPassagesDeLigne==1){
    //             while(!suiveurDeLigne.tousEteintes()){}
    //             moteur_.arreter();
    //             _delay_ms(1000);
    //             moteur_.virageNet(GAUCHE, 128, 128);
    //         }
    //     }
    // }
    // uart_.envoyerVariable("nbPassageLigne : ",nbPassagesDeLigne);
    moteur_.arreter();
    while(!(suiveurDeLigne.extremeDroiteActif() && suiveurDeLigne.milieuActif() && suiveurDeLigne.droiteActif())){
        suivreLigneBase();
    }
    sauverVirage(DROITE);
    moteur_.arreter();
    _delay_ms(1000);
    voieActuelle = VoieGrille::GAUCHE;
}

void Robot::premierObstacle(){
    nbIntersections_ = 0;
    balayageApartirDuCentre();
    if(voieActuelle == VoieGrille::CENTRE){
        while(nbIntersections_ != 2){
            if(suiveurDeLigne.tousLesCapteursActifs()){
                nbIntersections_++;
                if(nbIntersections_==1){
                    moteur_.avancer(128);
                    while(suiveurDeLigne.tousLesCapteursActifs()){}
                    moteur_.arreter();
                    _delay_ms(1000);////////////////////debug
                }else{break;}
                
            }
            // if(suiveurDeLigne.tousLesCapteursActifs()) {
            //     moteur_.avancer(128);
            //     while(suiveurDeLigne.tousLesCapteursActifs());
            // }
        suivreLigneBase();
        }
        approcherPoteau();

    }
    else if(voieActuelle == VoieGrille::DROITE){
        while(nbIntersections_ != 2){
            if(suiveurDeLigne.troisGauche()){
                nbIntersections_++;
                if(nbIntersections_==1){
                    moteur_.avancer(128);
                    while(suiveurDeLigne.troisGauche()){}
                    moteur_.arreter();
                    _delay_ms(1000);///////////////////////////debug

                }else{break;}
                
            }
            suivreLigneBase(); 
        }
        approcherPoteau();

    }
    else if(voieActuelle == VoieGrille::GAUCHE){
        while(nbIntersections_ != 2){
            if(suiveurDeLigne.troisDroite()){
                nbIntersections_++;
                if(nbIntersections_==1){
                    moteur_.avancer(128);
                    while(suiveurDeLigne.troisDroite()){} 
                    moteur_.arreter();
                    _delay_ms(1000);///////////////////////////debug
                }
                else{break;}
            }
            suivreLigneBase();      
        }
        
        approcherPoteau();
    }
}

void Robot::approcherPoteau() {
    
    for (uint8_t i = 0; i < 165; i++) {
        suivreLigneBase();
        _delay_ms(10);
    }
    moteur_.arreter();
}

void Robot::deuxiemeObstacle(){
    nbIntersections_ = 0;
    nbIntersectionsFinDeGrille_ = 0;
    deuxiemeBalayage();


    ///////////////// CENTRE ////////////// 
    if(voieActuelle == VoieGrille::CENTRE){
        while(nbIntersections_ != 2){
            if(suiveurDeLigne.tousLesCapteursActifs()){
                nbIntersections_++;
                if(nbIntersections_ == 1){
                    moteur_.avancer(144);
                    while(suiveurDeLigne.tousLesCapteursActifs()){}
                }
                else{
                    break;
                }
            }
            suivreLigneBase();
        }
        sauverVirage(DROITE);

        /// DERNIERE LIGNE


        while(nbIntersectionsFinDeGrille_ != 2){
            if(suiveurDeLigne.extremeDroiteActif() && suiveurDeLigne.droiteActif() && suiveurDeLigne.milieuActif()){
                nbIntersectionsFinDeGrille_++;
                if(nbIntersectionsFinDeGrille_ == 1){
                    moteur_.avancer(144);
                    while(suiveurDeLigne.extremeDroiteActif() && suiveurDeLigne.droiteActif() && suiveurDeLigne.milieuActif()){}
                }
                else{
                    break;
                }
            }
            suivreLigneBase();
        }
        //FIN


        sauverVirage(DROITE);
    }

    /////// DROITE /////////////

    else if(voieActuelle == VoieGrille::DROITE){
        while(nbIntersections_ != 2){
            if(suiveurDeLigne.extremeGaucheActif() && suiveurDeLigne.gaucheActif() && suiveurDeLigne.milieuActif()){
                nbIntersections_++;
                if(nbIntersections_ == 1){
                    moteur_.avancer(144);
                    while(suiveurDeLigne.extremeGaucheActif() && suiveurDeLigne.gaucheActif() && suiveurDeLigne.milieuActif()){}
                }
                else{
                    break;
                }
            }
            suivreLigneBase();
        }
        //DERNIERE LIGNE


        sauverVirage(DROITE);
        while(nbIntersectionsFinDeGrille_ != 1){
            if(suiveurDeLigne.extremeDroiteActif() && suiveurDeLigne.droiteActif() && suiveurDeLigne.milieuActif()){
                nbIntersectionsFinDeGrille_++;
                break;
            }
            suivreLigneBase();
        }
        ///////////FIN
        sauverVirage(DROITE);
    }

    //////////// VOIE GAUCHE

    else if(voieActuelle == VoieGrille::GAUCHE){
        while(nbIntersections_ != 2){
            if(suiveurDeLigne.extremeDroiteActif() && suiveurDeLigne.droiteActif() && suiveurDeLigne.milieuActif()){
                nbIntersections_++;
                if(nbIntersections_==1){
                    moteur_.avancer(144);
                    while(suiveurDeLigne.extremeDroiteActif() && suiveurDeLigne.droiteActif() && suiveurDeLigne.milieuActif()){}
                }
                else{
                    break;
                }
            }
            suivreLigneBase();
        }


        ////////DERNIERE LIGNE
        sauverVirage(DROITE);
        while(nbIntersectionsFinDeGrille_ != 3){
            if(suiveurDeLigne.extremeDroiteActif() && suiveurDeLigne.droiteActif() && suiveurDeLigne.milieuActif()){
                nbIntersectionsFinDeGrille_++;
                if(nbIntersectionsFinDeGrille_ == 1 || nbIntersectionsFinDeGrille_ == 2 ){
                    moteur_.avancer(144);
                    while(suiveurDeLigne.extremeDroiteActif() && suiveurDeLigne.droiteActif() && suiveurDeLigne.milieuActif()){}
                }
                else{
                    break;
                }
            }
            suivreLigneBase();
        }
        ///////////////////////////////////////////////FIN
        sauverVirage(DROITE);
    }
}

void Robot::deuxiemeBalayage(){
    nbIntersections_ = 0;
    if(voieActuelle == VoieGrille::CENTRE){
        balayageApartirDuCentre();
    }
    else if(voieActuelle == VoieGrille::GAUCHE){
        balayageApartirDe(GAUCHE);
    }
    else if(voieActuelle == VoieGrille::DROITE){
        balayageApartirDe(DROITE); 
    }
}

void Robot::balayageApartirDe(bool direction){
    if(balayageVisuel()){
        moteur_.virageNet(!direction,VITESSE_VIRAGE,VITESSE_VIRAGE);
        while (!suiveurDeLigne.tousEteintes()){}
        while(true){
            if(estPoteauProcheGrille()){
                uart_.envoyerString("le poteau est au centre , je continue a droite  ");
                moteur_.arreter();
                led_.clignoterVert4Hz();
                allerA(!direction);
                break;
            }
            else if(suiveurDeLigne.ligneTrouver()){
                moteur_.arreter();
                led_.clignoterVert4Hz();
                allerAuCentreApartirDe(direction);
                break;
            }
        }
    }
    else {
        led_.allumerVert();
    }
}   

void Robot::allerAuCentreApartirDe(bool direction){
    while (!suiveurDeLigne.tousLesCapteursActifs())
    {
        suivreLigneBase();
    }
    sauverVirage(direction);
    voieActuelle = VoieGrille::CENTRE;
    moteur_.arreter();
}

void Robot::allerA(bool direction){
    nbIntersectionsDeuxiemeBaleyage_ = 0;
    moteur_.virageNet(direction,VITESSE_VIRAGE,VITESSE_VIRAGE);
    while(!suiveurDeLigne.ligneTrouver()){}
    while(nbIntersectionsDeuxiemeBaleyage_ != 2){
        if(suiveurDeLigne.tousLesCapteursActifs()){
            nbIntersectionsDeuxiemeBaleyage_++;
            if(nbIntersectionsDeuxiemeBaleyage_ == 1){
                moteur_.avancer(128);
                while(suiveurDeLigne.tousLesCapteursActifs()){}
            }
            else{
                break;
            }
        }
        suivreLigneBase();
    }
    sauverVirage(!direction);
    if(direction){
        voieActuelle = VoieGrille::GAUCHE;
    }
    else{
        voieActuelle = VoieGrille::DROITE;
    }
    led_.allumerVert();
}

void Robot::suivreLigneA(){
    if(suiveurDeLigne.tousEteintes()){
        moteur_.arreter();
        sonnette_.creerSon(45);
        _delay_ms(1000);
        sonnette_.stopSon();
        pos = PositionsParcour::B;
        virageB_ ? moteur_.virage(VITESSE_DEBUG, VITESSE_DEBUG) : moteur_.virage(VITESSE_DEBUG, VITESSE_DEBUG);
        _delay_ms(DELAI_BOOST);
        while(!suiveurDeLigne.ligneTrouver()){
            virageB_ ? moteur_.virage(VITESSE_MOYENNE, VITESSE_VIRAGE) : moteur_.virage(VITESSE_VIRAGE, VITESSE_MOYENNE);
        }
        moteur_.arreter();
        _delay_ms(50);
    }
    else{
        suivreLigneBase();
    }
}

void Robot::reussirParcours(){
    uart_.envoyerString("DEBUT ");
    initialisationParcours();
    while(true){
        switch(pos){
            case PositionsParcour::INIT : 
                uart_.envoyerString("init");
                suivreLigneInitial();
                break;
            case PositionsParcour::A :
                suivreLigneA();
                break;
            case PositionsParcour::B:
                uart_.envoyerString("b");
                parcoursB();
                break;
            case PositionsParcour::C:
                uart_.envoyerString("c");
                parcoursC();
                break;
            case PositionsParcour::D: 
                uart_.envoyerString("D");
                parcoursD();
                break;
            case PositionsParcour::MAISON :
                uart_.envoyerString("maison");
                parcoursMaison();
                break;
            case PositionsParcour::J:
                suivreLigneJ();
                break;
            case PositionsParcour::GRILLE:
                premierObstacle();
                deuxiemeObstacle();
                startedA ? pos = PositionsParcour::FINAL : pos = PositionsParcour::A;
                break;
            case PositionsParcour::FINAL:
                moteur_.arreter();
                led_.clignoterVertRouge2Hz();
                //sonnette_.jouerMegalovania();
                break;
        }
    }
}