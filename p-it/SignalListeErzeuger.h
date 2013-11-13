#ifndef SIGNALLISTEERZEUGER_H
#define SIGNALLISTEERZEUGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Signal.h"


using namespace std;

class SignalListeErzeuger {

private:
	Signal* signale;
	short anzahlSignale;
	string datei;
	long frequenz;

public:
	void setPfad(string pfad);
	void ausgabeSchaltnetzdatei();
	void ausgabeSignale();
	string getdatei() {return datei; };
	SignalListeErzeuger();
	~SignalListeErzeuger();

};

#endif