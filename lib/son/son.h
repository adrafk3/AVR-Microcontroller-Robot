#ifndef SON_H
#define SON_H
#define F_CPU 8000000UL
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>
constexpr uint8_t PRESCALER= 128;
constexpr uint8_t DUREE_DOUBLE_CROCHE =124, DUREE_CROCHE=248, DUREE_TRIPLE_CROCHE = 62;

// //Timer Counter 2
class Son{
public:
    Son();
    void creerSonMegalovania(uint16_t frequence);

    void creerSon(uint8_t midiNote);

    void stopSon();
    
    void jouerMegalovania();

private:
    uint16_t ocrConstForce_;
};

#endif /* SON_H */
