#ifdef DEBUG
    #include "debug.h"
    #include "UART.h"  // Utilisation de la communication série RS232 pour le debogage
    #include <avr/io.h>


    // UART unique, réutilisable
    static InterfaceUART uartDebug(2400);  

    void envoyerString(const char* message) {
        while (*message) {
            uartDebug.transmissionUART((uint8_t)*message);
            message++;
        }
    }

    void envoyerMessage(const char* message) {
        envoyerString("[UART DEBUG] ");
        envoyerString(message);
        envoyerString("\n");
    }

    const char* convertirNombreEnString(uint16_t nombre) {
        static char stringNombre[6];  // 5 chiffres max + '\0'
        uint8_t index = 5;
        stringNombre[index] = '\0';

        do {
            stringNombre[--index] = (nombre % 10) + '0';
            nombre /= 10;
        } while (nombre > 0);

        return &stringNombre[index];
    }

    void envoyerVariable(const char* nomVar, uint16_t valeur) {
        envoyerString("[UART DEBUG VAR] ");
        envoyerString(nomVar);
        envoyerString(" = ");
        envoyerString(convertirNombreEnString(valeur));
        envoyerString("\n");
    }

#endif