#ifndef DEBUG_H
#define DEBUG_H

// Contributeurs: Yassine Morri, Arezki Oussad

// Vérifie si DEBUG est défini
#include <avr/io.h> 

#ifdef DEBUG
    #define DEBUG_PRINT_MESSAGE(msg) envoyerMessage(msg)
    #define DEBUG_PRINT_VAR(nomVar, valeur) envoyerVariable(nomVar, valeur)

    // Prototypes uniquement accessibles en mode DEBUG
    void envoyerMessage(const char* message);
    void envoyerVariable(const char* nomVar, uint16_t valeur);
    const char* convertirNombreEnString(uint16_t nombre);  // utile pour convertir un nombre en tableau de char
    void envoyerString(const char* message);
#else
    #define DEBUG_PRINT_MESSAGE(msg) do {} while (0) // code mort
    #define DEBUG_PRINT_VAR(nomVar, valeur) do {} while (0) // code mort

#endif // DEBUG

#endif /* DEBUG_H */