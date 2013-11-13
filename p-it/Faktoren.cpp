#include "stdafx.h"
#include "Faktoren.h"
#include <iostream>
//#include <iomanip>
using namespace std;


Faktoren::Faktoren()
{
	spannung = 0.0;
	temperatur = 0.0;
	prozess = 0.0;
	spannungFaktor = 0.0;
	temperaturFaktor = 0.0;
	prozessFaktor = 0.0;
}


Faktoren::~Faktoren()
{
}


bool Faktoren::berechneSpannungFaktor(double spg)
{
	double spFaktoren[7][2] = { { 1.08, 1.121557 }, { 1.12, 1075332 }, { 1.16, 1.035161 }, { 1.20, 1.0 }, { 1.24, 0.968480 }, { 1.28, 0.940065 }, { 1.32, 0.914482 } };
	int asize = sizeof (spFaktoren) / sizeof(spFaktoren[0]);
	if ( !(( spg < spFaktoren[0][0] ) || ( spg > spFaktoren[asize - 1][0] ))) {
		spannungFaktor = berechneFaktor(spg, spFaktoren, asize);
		return true;
	}
	cout << "ERR: Die angegebene Spannung liegt nicht innerhalb der vorgegebenen Grenzen!" << endl;
	return false;
}


bool Faktoren::berechneTemperaturFaktor(double temp)
{
	double teFaktoren[15][2] = { { -25, 0.897498 }, { -15, 0.917532 }, { 0, 0.948338 }, { 15, 0.979213 }, { 25, 1.0 }, { 35, 1.020305 }, { 45, 1.040540 }, { 55, 1.061831 }, { 65, 1.082983 }, { 75, 1.103817 }, { 85, 1.124124 }, { 95, 1.144245 }, { 105, 1.164563 }, { 115, 1.184370 }, { 125, 1.204966 } };
	int asize = sizeof (teFaktoren) / sizeof(teFaktoren[0]);
	if (!((temp < teFaktoren[0][0]) || (temp > teFaktoren[asize - 1][0]))) {
		temperaturFaktor = berechneFaktor(temp, teFaktoren, asize);
		return true;
	}
	cout << "ERR: Die angegebene Temperatur liegt nicht innerhalb der vorgegebenen Grenzen!" << endl;
	return false;
}


bool Faktoren::berechneProzessFaktor(short prz)
{
	double prFaktoren[3][2] = { { 1, 1.174235 }, { 2, 1.0 }, { 3, 0.876148 } };
	int asize = sizeof(prFaktoren) / sizeof(prFaktoren[0]);
	for (int i = 0; i < asize; i++){
		int help = prz;
		if (help == prFaktoren[i][0]){
			prozessFaktor = prFaktoren[i][1];
			return true;
		}
	}
	cout << "ERR: Der angegebene Prozess liegt nicht innerhalb der vorgegebenen Grenzen!" << endl;
	return false;
}


double Faktoren::berechneFaktor(double value, double arr[][2], int laenge)
{
	double r;
	for (int i = 0; i < laenge; i++){
		if ((arr[i][0] <= value) && (value < arr[i + 1][0])){
			r = interpolation(value, arr[i][0], arr[i + 1][0], arr[i][1], arr[i + 1][1]);
		}
	}
	return r;
}


double Faktoren::interpolation(double value, double x1, double x2, double y1, double y2)
{
	double ip;
	ip = ((y2 - y1) / (x2 - x1) * (value - x1)) + y1;
	return ip;
}


void Faktoren::ausgabeFaktoren()
{
	if (berechneSpannungFaktor(spannung) && berechneTemperaturFaktor(temperatur) && berechneProzessFaktor(prozess)){
		cout << "Faktoren: KV: " << spannungFaktor << "\|KT: " << temperaturFaktor << "\|KP: " << prozessFaktor << endl;
	}
}


double Faktoren::getSpannung()
{
	return spannung;
}


double Faktoren::getProzess()
{
	return prozess;
}


double Faktoren::getTemperatur()
{
	return temperatur;
}


void Faktoren::getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor)
{
	if (berechneSpannungFaktor(spannung) && berechneTemperaturFaktor(temperatur) && berechneProzessFaktor(prozess)){
		spgFaktor = spannungFaktor;
		tmpFaktor = temperaturFaktor;
		przFaktor = prozessFaktor;
	}
}

bool Faktoren::setSpannung(double spannung)
{
	this->spannung = spannung;
	return true;
}


bool Faktoren::setTemperatur(double temperatur)
{
	this->temperatur = temperatur;
	return true;
}


bool Faktoren::setProzess(short prozess)
{
	this->prozess = prozess;
	return true;
}

bool Faktoren::InfoFromItivDevice()
{
	DevPtr = ItivDev_GetConfigByName("Global\\ITIV_WindowsDevice");
	double neuerWert;
	int neuerInt;
	bool err;
	for (int i = 1; i < 4; i++){
		while (!err){
			err = false;
			*((int*)DevPtr->BaseAddress + CTRL_REG) = 0x0;
			while (!(*(int*)DevPtr->BaseAddress + STAT_REG == 0x01000000));
			*((int*)DevPtr->BaseAddress + CTRL_REG) = i;
			*((int*)DevPtr->BaseAddress + CTRL_REG) = 0x100 + i;
			while (*(int*)DevPtr->BaseAddress + STAT_REG == 0x100);
			if (*(int*)DevPtr->BaseAddress + STAT_REG == 0x10000){
				switch (i)
				{
				case 1:
					neuerWert = *((double*)DevPtr->BaseAddress + DATA_REG);
					err = (setSpannung(neuerWert));
					break;
				case 2:
					neuerInt = *((int*)DevPtr->BaseAddress + DATA_REG);
					err = (setTemperatur(neuerInt));
					break;
				case 3:
					neuerInt = *((int*)DevPtr->BaseAddress + DATA_REG);
					err = (setProzess(neuerInt));
				default:
					break;
				}
			}
		}
	}
	
	
	
	return false;
}
