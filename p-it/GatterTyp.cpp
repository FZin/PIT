#include "GatterTyp.h"

GatterTyp::GatterTyp(void) {
    grundlaufzeit = 0.0;
    lastFaktor = 0;
    lastKapazitaet = 0;
    eingaenge = 0;
}

GatterTyp::~GatterTyp(void) {
}

bool GatterTyp::getIsFlipflop(void) {
    return false;
}
