#ifndef SCHALTWERKELEMENT_H
#define SCHALTWERKELEMENT_H

#include <iostream>
#include <string>


#include "GatterTyp.h"

class SchaltwerkElement
{
private:
	string name;
	GatterTyp* typ;
	double laufzeitEinzelGatter;
	SchaltwerkElement* nachfolgerElement;
	int anzahlNachfolger;
	bool isEingangsElement;
	bool isAusgangsElement;
	short anzahlEingangssignale;


public:
	SchaltwerkElement();
	~SchaltwerkElement();
	string getName() { return name;};
	GatterTyp* getTyp() {return typ;};
	double getLaufzeitEinzelgatter() {return laufzeitEinzelGatter; };
	SchaltwerkElement* getNachfolgerElement(int pos);
	int getAnzahlNachfolger() {return anzahlNachfolger;};
	short getAnzahlEingangssignale() {return anzahlEingangssignale;};
	bool getIsEingangsElement() {return isEingangsElement; };
	bool getIsAusgangsElement() { return isAusgangsElement; };
	void setName(string n) { name = n; };
	void nachfolgerHinzufuegen( SchaltwerkElement* schaltwerkElement, int pos );
	void setAnzahlNachfolger(int anzahlN) { anzahlNachfolger= anzahlN; };
	void setAnzahlEingangssignale(short anzahlE) {anzahlEingangssignale = anzahlE;};
	void setIsEingangsElement( bool isEingangsEl) { isEingangsElement = isEingangsEl; };
	void setIsAusgangsElement( bool isAusgangsEl) { isAusgangsElement = isAusgangsEl; };
	void setLaufzeitEinzelgatter( double lfz) {laufzeitEinzelGatter = lfz; };

	

};

#endif