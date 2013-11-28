#include "Signal.h"

string Signal::getZiel(int pos)
{
	pos = (pos - 1) * 4;
	string ergebnis = ziele.substr(pos, 4);
	return ergebnis;

};

void Signal::zielHinzufuegen(string gatterName, int pos) 
{
	if (ziele=="NULL") {
	ziele = "********************";
	}


	pos = (pos - 1) * 4;
	ziele.replace(pos, 4, gatterName);
	anzahlZiele++;

};

//Konstruktor
Signal::Signal() 
{
	signalTyp = unbekannt;
	quelle = "NULL";
	quellenTyp = "NULL";
	ziele = "NULL";
	anzahlZiele = 0;
};

//Destruktor
Signal::~Signal() 
{
};