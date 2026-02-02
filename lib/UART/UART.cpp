

#include "UART.h"


void InterfaceUART::initialisationUART(uint16_t baudrate) {
  // N bauds (UBRR = (F_CPU / (16 * N)) - 1 pour F_CPU = 8MHz)
  uint16_t ubrr = (F_CPU / (16 * baudrate)) - 1;
  UBRR0H = 0;
  UBRR0L = ubrr;
  // Activer la transmission et la réception
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  // Format : 8 bits de données, 1 bit de stop, sans parité
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

InterfaceUART::InterfaceUART(uint16_t baudrate) : baudrate_(baudrate) {
  initialisationUART(baudrate_);
}

InterfaceUART::~InterfaceUART() {
  UCSR0B &= ~((1 << TXEN0) | (1 << RXEN0));  // Désactiver TX et RX une fois que l'UART n'est plus utilise
}

void InterfaceUART::transmissionUART(uint8_t donnee) {
  // Attente que le buffer de transmission soit vide
  while (!(UCSR0A & (1 << UDRE0)));
  // Envoi de la donnée
  UDR0 = donnee;
}

uint8_t InterfaceUART::receptionUART() {
  while (!(UCSR0A & (1<<RXC0)));

  return UDR0;
}

 void InterfaceUART::envoyerString(const char* message) {
  while (*message) {
    transmissionUART((uint8_t)*message);
    message++;
  }
}

void InterfaceUART::envoyerVariable(const char* nomVar, uint16_t valeur) {
  envoyerString("[UART DEBUG VAR] ");
  envoyerString(nomVar);
  envoyerString(" = ");
  envoyerString(convertirNombreEnString(valeur));
  envoyerString("\n");
}

const char* InterfaceUART::convertirNombreEnString(uint16_t nombre) {
  static char stringNombre[6];  // 5 chiffres max + '\0'
  uint8_t index = 5;
  stringNombre[index] = '\0';

  do {
    stringNombre[--index] = (nombre % 10) + '0';
    nombre /= 10;
  } while (nombre > 0);

  return &stringNombre[index];
}
