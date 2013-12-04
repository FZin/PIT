#ifndef MENUE_H
#define MENUE_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "SignalListeErzeuger.h"
#include "LaufzeitAnalysator.h"
#include "Bibliothek.h"
#include "GraphErzeuger.h"
#include "Faktoren.h"

using namespace std;

class Menue {
private:
	Faktoren meineFaktoren;
	Bibliothek meineBibliothek;
	SignalListeErzeuger meinSignalListeErzeuger;
	GraphErzeuger meinGraphErzeuger;
	LaufzeitAnalysator meinLaufzeitanalysator;



	//Signal* signale;
	
	void faktorenMenue();
	void bibliothekMenue();
	void schaltwerkMenue();
	void analyse();
	

public:
	void menueKopf();
	void start();
	//Menue() {};
	//~Menue();

};
#endif