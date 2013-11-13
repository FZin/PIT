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
	cout << "Fehler beim Lesen! " << endl;
}


void Bibliothek::openError(void)
{
	cout << "Fehler beim Oeffnen! " << endl;
}


GatterTyp*  Bibliothek::getBibElement(string typ)
{
	for (int i = 0; i != bibElemente.size(); i++) {
		if (bibElemente.at(i)->getName() == typ) {
			return bibElemente.at(i);
		}
		else{
			return bibElemente.at(0); //falls kein typ gefunden wird zeiger auf erstes element zurückgeben
		}
	}
}


void Bibliothek::dateiAusgabe(void)
{
	int nummer = 1;
	string zeile;
	ifstream bib(datei);
	if (!bib) {
		openError();
	}
	while (getline(bib, zeile)) {
		cout << nummer++ << " " << zeile << endl;
	}
	if (!bib.eof()){
		readError();
	}
	bib.close();

}


void Bibliothek::dateiAuswerten(void)
{
	ifstream bib(datei);
	string zeile;
	while (getline(bib,zeile)) {
		if (zeile[0] == '[' && zeile[1] != '[' && zeile[1] != 'd') {
			GatterTyp* tmp = new GatterTyp;
			string nameFilter = zeile.substr(1, zeile.size()-2);
			tmp->setName(nameFilter);
		    while (getline(bib, zeile) && zeile.size() != 0) {
				if (zeile.substr(0,2) == "ei") {
					string zahl = zeile.substr(3);
					short eingaengeFilter = atoi(zahl.c_str());
					tmp->setEingaenge(eingaengeFilter);
				}
				if (zeile.substr(0,4) == "tpd0") {
					string zahl = zeile.substr(5);
					double grundLaufzeitFilter = atof(zahl.c_str());
					tmp->setGrundLaufzeit(grundLaufzeitFilter);
				}
				if (zeile.substr(0,2) == "kl") {
					string zahl = zeile.substr(3);
					short lastFaktorFilter = atoi(zahl.c_str());
					tmp->setLastFaktor(lastFaktorFilter);
				}
				if (zeile.substr(0,2) == "cl") {
					string zahl = zeile.substr(3);
					short lastKapazitaetFilter = atoi(zahl.c_str());
					tmp->setLastKapazitaet(lastKapazitaetFilter);
				}
			}
			bibElemente.push_back(tmp);
		}
		if (zeile.substr(0,5)=="[dff]") {
			Flipflop* tmp = new Flipflop;
			string nameFilter = zeile.substr(1, zeile.size()-2);
			tmp->setName(nameFilter);
			while (getline(bib, zeile) && zeile.size() != 0) {
				if (zeile.substr(0,2) == "ed") {
					string zahl = zeile.substr(3);
					short eingaengeFilter = atoi(zahl.c_str());
					tmp->setEingaenge(eingaengeFilter);
				}
				if (zeile.substr(0,6) == "tsetup") {
					string zahl = zeile.substr(7);
					short setupTimeFilter = atoi(zahl.c_str());
					tmp->setSetupTime(setupTimeFilter);
				}
				if (zeile.substr(0,5) == "thold") {
					string zahl = zeile.substr(6);
					short holdTimeFilter = atoi(zahl.c_str());
					tmp->setHoldTime(holdTimeFilter);
				}
				if (zeile.substr(0,2) == "cd") {
					string zahl = zeile.substr(3);
					short lastKapazitaetClockFilter = atoi(zahl.c_str());
					tmp->setLastKapazitaetClock(lastKapazitaetClockFilter);
				}
				if (zeile.substr(0,2) == "et") {                    //überschreibt D-Eingang! was tun?
					string zahl = zeile.substr(3);
					short eingaengeFilter = atoi(zahl.c_str());
					tmp->setEingaenge(eingaengeFilter);
				}
				if (zeile.substr(0,4) == "tpdt") {
					string zahl = zeile.substr(5);
					double grundLaufzeitFilter = atof(zahl.c_str());
					tmp->setGrundLaufzeit(grundLaufzeitFilter);
				}
				if (zeile.substr(0,2) == "kl") {
					string zahl = zeile.substr(3);
					short lastFaktorFilter = atoi(zahl.c_str());
					tmp->setLastFaktor(lastFaktorFilter);
				}
				if (zeile.substr(0,2) == "ct") {
					string zahl = zeile.substr(3);
					short lastKapazitaetFilter = atoi(zahl.c_str());
					tmp->setLastKapazitaet(lastKapazitaetFilter);
				}
			}
			bibElemente.push_back(tmp);
		}
		else{
			readError();
		}
	}
	bib.close();
}


bool Bibliothek::pfadEinlesen(string pfad)
{
	ifstream bib(pfad);
	if(!bib) {
		openError();
		bib.close();
		return false;
	}
	else{
		datei = pfad;
		bib.close();
		return true;
	}
}
