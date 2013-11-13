#ifndef SIGNAL_H
#define SIGNAL_H

#include <iostream>
#include <string>

using namespace std;

enum signalTypen { eingang, intern, ausgang, unbekannt };

class Signal {

private:
	signalTypen signalTyp;
	string quelle;
	string quellenTyp;
	string ziele;
	int anzahlZiele;

	

public:
	
	int getAnzahlZiele() { return anzahlZiele; };
	signalTypen getSignalTyp() { return signalTyp; };
	string getQuelle() { return quelle; };
	string getQuellenTyp() { return quellenTyp; };
	string getZiel(int pos);
	void setAnzahlZiele(int nZiele) { anzahlZiele = nZiele; };
	void setSignalTyp(signalTypen sigTyp) { signalTyp = sigTyp; };
	void setQuelle(string gatterName) { quelle = gatterName; };
	void setQuellenTyp(string gatterTyp) { quellenTyp = gatterTyp; };
	void zielHinzufuegen(string gatterName, int pos);

	//Konstruktor
	Signal();
	//Destruktor
	~Signal();



};

#endif