
#pragma once
#include "itiv_win_drv.h"

class Faktoren
{
public:
	Faktoren();
	virtual ~Faktoren();
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
	double berechneFaktor(double value, double arr[][2], int laenge);
	double interpolation(double value, double x1, double x2, double y1, double y2);
	ItivDev_Config* DevPtr;
	
public:
	void ausgabeFaktoren();
	double getSpannung();
	double getTemperatur();
	double getProzess();
	void getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor);
	bool setSpannung(double spannung);
	bool setTemperatur(double temperatur);
	bool setProzess(short prozess);

	bool InfoFromItivDevice();
};

