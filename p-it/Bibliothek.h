#pragma once
#include "GatterTyp.h"
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Bibliothek
{
public:
	Bibliothek(void);
	~Bibliothek(void);
private:
	vector<GatterTyp*> bibElemente;
	string datei;
public:
	string getPfad(void);
private:
	void readError(void);
	void openError(void);
public:
	GatterTyp* getBibElement(string typ);
	void dateiAusgabe(void);
	void dateiAuswerten(void);
	bool pfadEinlesen(string pfad);
};

