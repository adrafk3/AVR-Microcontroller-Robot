#include "capteurAnalogique.h"

CapteurAnalogique::CapteurAnalogique() {
    DDRA &= ~(1 << PA5);
}
bool CapteurAnalogique::estPoteauProche() {
    uint16_t tensionLue = can_.lecture(5);
    //uart_.envoyerVariable("Tension lue: ", tensionLue);
    return ((400 <= tensionLue) && (tensionLue <= 800));
}

bool CapteurAnalogique::estPoteauProcheGrille() {
    uint16_t tensionLue = can_.lecture(5);
    uart_.envoyerVariable("Tension lue: ", tensionLue);
    return ((225 <= tensionLue) && (tensionLue <= 800));
}