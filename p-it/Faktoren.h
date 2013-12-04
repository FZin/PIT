#ifndef FAKTOREN_H
#define FAKTOREN_H

#include "itiv_win_drv.h"
#include <iostream>

class Faktoren {
private:
    double spannung;
    double temperatur;
    double prozess;
    double spannungFaktor;
    double temperaturFaktor;
    double prozessFaktor;
    bool berechneSpannungFaktor(double spg);
    bool berechneTemperaturFaktor(double temp);
    bool berechneProzessFaktor(short prz);
    double berechneFaktor(double value, double arr[][2], unsigned int laenge);
    double interpolation(double value, double x1, double x2, double y1, double y2);


public:
    Faktoren();
    virtual ~Faktoren();
    void ausgabeFaktoren();
    double getSpannung();
    double getTemperatur();
    double getProzess();
    void getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor);
    bool setSpannung(double spannung);
    bool setTemperatur(double temperatur);
    bool setProzess(short prozess);
    bool InfoFromItivDevice();
    double debugVar;
};
#endif