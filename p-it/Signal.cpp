#include "Signal.h"

string Signal::getZiel(int pos) {

	pos = (pos-1)*4;
	string ergebnis = ziele.substr(pos, 4);
	return ergebnis;

	/*int stringstart = -1;
	int stringend = 0;

	for(int i = 0; i < (pos-1); i++) {
		stringstart = ziele.find(";",stringstart+1);
	}
	stringstart++;
	stringend = ziele.find(";",stringstart);

	string ergebnis = ziele.substr(stringstart, stringend-stringstart);

	return ergebnis;*/

};

void Signal::zielHinzufuegen(string gatterName, int pos) {
	if(ziele=="NULL") {
	ziele="********************";
	}

	//debug
	//cout<<"gattername:"<<gatterName<<endl<<"pos"<<pos<<endl;

	pos = (pos-1)*4;
	ziele.replace(pos, 4, gatterName);
	anzahlZiele++;

	//debug
	//cout<<ziele<<endl;


	/*if(ziele=="NULL") {
	ziele=";;;;;";
	}

	int stringpos = 0;
	
	for(int i = 0; i < (pos-1); i++) {
		stringpos = ziele.find(";",stringpos+1);
	}
	if(pos != 1) {
	stringpos++;
	}
	ziele.insert( stringpos, gatterName );

	anzahlZiele++;*/



};


Signal::Signal() {
	signalTyp = unbekannt;
	quelle = "NULL";
	quellenTyp = "NULL";
	ziele = "NULL";
	anzahlZiele = 0;
	

};

Signal::~Signal() {
	
};