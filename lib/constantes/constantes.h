/* 
Travail : Projet INF1900
Section # : Section 6
Equipe # : EQUIPE_139-148
Correcteur : .........

Nom des auteurs : Yassine Morri, Areski Oussad, Leith Abderrahim et Adam Rafai

Description : Ce fichier d’en-tête définit plusieurs énumérations utilisées dans le projet pour simplifier et structurer 
              la gestion des constantes liées au robot. Ces énumérations représentent les modes de fonctionnement des 
              minuteries, les étapes du parcours, et les positions ou voies de navigation du robot dans une grille.

Identifications matérielles (Broches I/O) :
    - Ce fichier ne contient pas de connexion matérielle directe. Il définit uniquement des constantes logiques utilisées 
      par les autres modules (par exemple, `Timer1`, gestion du parcours, navigation dans une grille).

Description des énumérations :
    - Prescaler : Définit les valeurs de prescaler pour configurer la vitesse d’exécution des minuteries du robot.
        - PRESCALER_256 : Division par 256 (utilisé pour régler une fréquence plus basse du Timer1).
        - PRESCALER_1024 : Division par 1024 (fréquence encore plus basse pour des délais plus longs).

    - Timer1Mode: Définit les modes de fonctionnement du Timer1.
        - NORMAL : Mode normal, où le timer compte jusqu’à sa valeur maximale avant de revenir à 0.
        - CTC : Mode Clear Timer on Compare Match, où le timer s’arrête et recommence dès qu’il atteint une valeur cible.

    - PositionsParcour : Définit les étapes principales du parcours du robot.
        - INIT : État initial avant le début du parcours.
        - B, C, D : Étapes intermédiaires du parcours.
        - J : Zone désignée pour une étape spécifique.
        - GRILLE : État où le robot navigue dans une grille.
        - MAISON : Zone ou état de retour vers la "maison".
        - FINAL : État final une fois le parcours terminé.

    - VoieGrille : Définit les positions possibles du robot dans une grille.
        - CENTRE : Position au centre de la grille.
        - GAUCHE : Position sur la voie gauche.
        - DROITE : Position sur la voie droite.

Autres informations :
    - Ces énumérations facilitent la lisibilité du code en remplaçant des valeurs numériques magiques par des noms explicites.
    - Elles permettent également une gestion plus flexible et modulaire des constantes dans l’ensemble du projet.
*/

#ifndef CONSTANTES_H
#define CONSTANTES_H


enum class Prescaler {
    PRESCALER_256 = 256, //= (1 << CS12),       // Division par 256
    PRESCALER_1024 = 1024 //= (1 << CS12) | (1 << CS10) // Division par 1024
};

enum class Timer1Mode {
    NORMAL,      // Mode Normal
    CTC         // Mode CTC
};

enum class PositionsParcour {
    INIT,
    A,
    B,
    C,
    D,
    J,
    GRILLE,
    MAISON,
    FINAL
};


enum class VoieGrille {
    CENTRE,
    GAUCHE,
    DROITE
};


#endif /* CONSTANTES_H */
