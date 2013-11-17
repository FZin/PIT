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

//Fehlerausgabe, wenn Fehler beim Lesen der Datei
void Bibliothek::readError(void)
{
	cout << "Fehler beim Lesen! " << endl;
}

//Fehlerausgabe, wenn Fehler beim Oeffnen der Datei
void Bibliothek::openError(void)
{
	cout << "Fehler beim Oeffnen! " << endl;
}

//Rückgabe eines Zeigers auf gesuchtes Element
GatterTyp*  Bibliothek::getBibElement(string typ)
{
	for (int i = 0; i != bibElemente.size(); i++) {
		if (bibElemente.at(i)->getName() == typ) {
			return bibElemente.at(i);
		}
		else{
			return bibElemente.at(0);  //Falls kein typ mit eingegebenem Namen gefunden wurde, Zeiger auf erstes element zurückgeben
		}
	}
	return NULL; //Falls keine Elemente vorhanden, Rückgabe "NULL-Zeiger"
}

//Ausgabe der einzulesenden Datei auf dem Bildschirm
void Bibliothek::dateiAusgabe(void)
{
	int nummer = 1;
	string zeile;
	ifstream bib(datei);
	if (!bib) {
		openError();
	}
	while (getline(bib, zeile)) {  // getline: Zeilenweises Einlesen der Datei
		cout << nummer++ << " " << zeile << endl; // Nummerierung der eingelesenen Zeilen
	}
	if (!bib.eof()){
		readError();
	}
	bib.close();

}

//Auswertung der Datei, d.h. einlesen und abspeichern benötigter Werte in entsprechende Attribute
void Bibliothek::dateiAuswerten(void)
{
	ifstream bib(datei);
	string zeile;
	while (getline(bib,zeile)) {
		if (zeile[0] == '[' && zeile[1] != '[' && zeile[1] != 'd') { //Suche nach Zeilen mit Namen der Gatter
			GatterTyp* tmp = new GatterTyp;   //Anlegen eines dynamischen Objektes
			string nameFilter = zeile.substr(1, zeile.size()-2);
			tmp->setName(nameFilter); //Namen des dynamischen Objektes festlegen/speichern
		    while (getline(bib, zeile) && zeile.size() != 0) { //Block weiter auslesen
				if (zeile.substr(0,2) == "ei") { //Allgemeines Prinzip: Suche nach Zeilen mit benötigten Werten, auslesen und speichern der Werte   
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
			bibElemente.push_back(tmp); //dynamisches Objekt mit entsprechenden Eigenschaften wird in Vektor bibElemente am Ende hinzugefuegt
		}
		if (zeile.substr(0,5)=="[dff]") { //Suche nach Zeilen mit Namen von Flipflops
			Flipflop* tmp = new Flipflop;  //s.o.
			string nameFilter = zeile.substr(1, zeile.size()-2);
			tmp->setName(nameFilter);
			while (getline(bib, zeile) && zeile.size() != 0) { //s.o.
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
			bibElemente.push_back(tmp); //s.o.
		}
		else{
			readError();
		}
	}
	bib.close();
}

// Einlesen des Pfades
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
