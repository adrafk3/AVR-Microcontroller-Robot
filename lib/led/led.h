#ifndef LED_H
#define LED_H
#include <avr/io.h> 
#include <util/delay.h>
//Contributeur : Arezki Oussad

class LED {
public:
    static constexpr uint16_t COLOR_DELAY_US = 500;
    LED(volatile uint8_t *port, uint8_t mask);

    ~LED();

    void allumerVert();

    void allumerRouge();

    void eteindreLed();

    void clignoterVert4Hz();
    void clignoterVertRouge2Hz();


private:
    static constexpr int DUREE_CLIGNOTEMENTS = 2000;
    static constexpr int PERIODE_2Hz = 250;
    static constexpr int PERIODE_4Hz = 500;
    static constexpr int NB_CLIGNOTEMENTS_2Hz = DUREE_CLIGNOTEMENTS / PERIODE_2Hz;
    static constexpr int NB_CLIGNOTEMENTS_4Hz = DUREE_CLIGNOTEMENTS / PERIODE_4Hz;

    volatile uint8_t *port_;
    uint8_t mask_;
};

#endif /* LED_H */