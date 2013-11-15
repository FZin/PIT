#include "SchaltwerkElement.h"

SchaltwerkElement::SchaltwerkElement() { 

	name = "";
	typ = NULL;
	laufzeitEinzelGatter = 0;
	nachfolgerElement = NULL;
	anzahlNachfolger = 0;
	isEingangsElement = false;
	isAusgangsElement = false;
	anzahlEingangssignale = 0;

};

SchaltwerkElement::~SchaltwerkElement() {


};

SchaltwerkElement* SchaltwerkElement::getNachfolgerElement(int pos) {

	SchaltwerkElement* temp = &nachfolgerElement[pos-1];


	return temp;
};

void SchaltwerkElement::nachfolgerHinzufuegen( SchaltwerkElement* schaltwerkElement, int pos ) {
	



	

	
};