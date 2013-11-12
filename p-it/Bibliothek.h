#ifndef BIBLIOTHEK_H
#define BIBLIOTHEK_H

#include "GatterTyp.h"
#include "Flipflop.h"
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Bibliothek
{
private:
	vector<GatterTyp*> bibElemente;
	string datei;
	void readError(void);
	void openError(void);
public:
	Bibliothek(void);
	~Bibliothek(void);
	string getPfad(void);
	GatterTyp* getBibElement(string typ);
	void dateiAusgabe(void);
	void dateiAuswerten(void);
	bool pfadEinlesen(string pfad);
};
#endif

