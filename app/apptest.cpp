//Auteurs : Rafai Adam 2260653
//          Arezki 2391996
//          Yassine Morri
//          Leith Ethan Abderrahim 2259562
/* 
Travail : Projet INF1900
Section # : Section 6
Equipe # : EQUIPE_139-148
Correcteur : .........

Nom des auteurs : Yassine Morri, Areski Oussad, Leith Abderrahim et Adam Rafai

Description : Ce programme contient le point d’entrée principal du projet, où un objet de la classe Robot est utilisé pour 
              exécuter l’ensemble des fonctionnalités du robot autonome. La méthode reussirParcours() est appelée pour 
              contrôler le robot tout au long de son parcours prédéfini. Ce programme illustre l’intégration des différentes 
              composantes matérielles et logicielles, comme les capteurs, moteurs, et la logique de déplacement.

Identifications matérielles (Broches I/O) :
    
Matériel contrôlé via la classe Robot :
Suiveur de ligne (Makerline) : Entrée (pins PA0 à PA4)
Capteur de distance : Entrée analogique (pin PA5)
DEL bicolore : Sortie (PC2)
Bouton d’interruption : Entrée (PD2)
Bouton blanc : Entrée (PD3)
Moteurs (roue gauche et roue droite via un pont en H) :
PWM gauche : PD6
Direction gauche : PD4
PWM droite : PD7
Direction droite : PD5
Sonnette (buzzer) : Sortie (PB2)

Autres informations :
    
Le programme utilise des délais (_delay_ms) et des constantes de vitesse pour synchroniser les mouvements.
Une machine à états implémentée dans la classe Robot coordonne les actions pour chaque étape du parcours.
*/

#include "robot.h"


int main(){
   Robot opps;
   
   opps.reussirParcours();
}
