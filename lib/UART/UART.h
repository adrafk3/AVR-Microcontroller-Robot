#ifndef UART_H
#define UART_H
#define F_CPU 8000000UL
#include <avr/io.h> 

// Contributeur : Yassine Morri, Arezki Oussad

class InterfaceUART {
public:
    InterfaceUART(uint16_t baudrate);

    ~InterfaceUART();

    void transmissionUART(uint8_t donnee);

    uint8_t receptionUART();

    void envoyerVariable(const char* nomVar, uint16_t valeur);

    const char* convertirNombreEnString(uint16_t nombre);

    void envoyerString(const char* message);

private:
    void initialisationUART(uint16_t baudrate);
    uint16_t baudrate_;
};

#endif /* UART_H */