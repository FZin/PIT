#ifndef FLIPFLOP_H
#define FLIPFLOP_H

#include "gattertyp.h"

//Initialisierung der Klasse Flipflop als Kindklasse von Klasse GatterTyp

class Flipflop :
public GatterTyp {
private:
    short setupTime;
    short holdTime;
    short lastKapazitaetClock;
public:
    Flipflop(void);
    ~Flipflop(void);
    bool getIsFlipflop();

    //Inline get- und set-Methoden

    short getSetupTime(void) {
        return setupTime;
    }

    short getHoldTime(void) {
        return holdTime;
    }

    short getLastKapazitaetClock(void) {
        return lastKapazitaetClock;
    }

    void setSetupTime(short st) {
        setupTime = st;
    }

    void setHoldTime(short ht) {
        holdTime = ht;
    }

    void setLastKapazitaetClock(short lkc) {
        lastKapazitaetClock = lkc;
    }
};
#endif

