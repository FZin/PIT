#include "stdafx.h"
#include "Bibliothek.h"

Bibliothek::Bibliothek(void)
{
}


Bibliothek::~Bibliothek(void)
{
}

string Bibliothek::getPfad(void)
{
	return datei;
}


void Bibliothek::readError(void)
{
	cout<< "Fehler beim Lesen! " << endl;
}


void Bibliothek::openError(void)
{
	cout<< "Fehler beim Oeffnen! " << endl;
}


GatterTyp*  Bibliothek::getBibElement(string typ)
{
	return GatterTyp*;
}


void Bibliothek::dateiAusgabe(void)
{
	int nummer = 1;
	string zeile;
	ifstream bib(datei);
	if ( !bib ) {
		openError();
	}
	while( getline(bib, zeile)) {
		cout<< nummer++ << " " << zeile <<endl;
	}
	if( !bib.eof()){
		readError();
	}

}


void Bibliothek::dateiAuswerten(void)
{
	ifstream bib(datei);
	string zeile;
	while( getline(bib,zeile)) {
		if( zeile[0] == '[' && zeile[1] != '[' && zeile[1] != 'd'){
			GatterTyp* tmp = new GatterTyp;
			string nameFilter = zeile.substr( zeile[1],zeile.size()-2);
			tmp->setName(nameFilter);
		}
		if(zeile.substr(0,2) == "ei"){
			short eingaengeFilter = atoi(zeile.c_str());
			tmp->setEingaenge(eingaengeFilter);
		}
		if(zeile.substr(0,4) == "tpd0"){
			string zahl2 = zeile.substr(5);
			double grundlaufzeitFilter = atof(zahl2.c_str());
			tmp->setGrundlaufzeit(grundlaufzeitFilter);
		}
		if(zeile.substr(0,2) == "kl"){
			short lastFaktorFilter = atoi(zeile.c_str());
			tmp->setLastFaktor(lastFaktorFilter);
		}

		if(zeile.substr(0,2) == "cl"){
			short lastKapazitaetFilter = atoi(zeile.c_str());
			tmp->setLastKapazitaet(lastKapazitaetFilter);
		}
			
	}

}


bool Bibliothek::pfadEinlesen(string pfad)
{
	ifstream bib(pfad);
	if(!bib) {
		openError();
		return false;
	}
	else{
		datei = pfad;
		return true;
	}

}
