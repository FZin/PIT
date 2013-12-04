#include "Flipflop.h"

Flipflop::Flipflop(void) {
    setupTime = 0;
    holdTime = 0;
    lastKapazitaetClock = 0;
}

Flipflop::~Flipflop(void) {
}

bool Flipflop::getIsFlipflop() {
    return true;
}
