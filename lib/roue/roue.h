#ifndef ROUE_H
#define ROUE_H
#include <avr/io.h> 


class Roue {
public:
    Roue(uint8_t pinDirection, uint8_t pinVitesse);
    void fixerDirection(bool avant);
    void fixerVitesse(uint8_t vitesse);
    void arreter();

private:
    uint8_t pinDirection_;
    uint8_t pinVitesse_;
};

#endif /* ROUE_H */